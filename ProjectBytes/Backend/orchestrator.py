"""
Deployment orchestrator: the cockpit's "spin up instance" button.

Starts dedicated district servers as child processes of the backend on this machine, using either a packaged
server executable (deploy.serverExe) or the editor binary in -server mode (deploy.engineDir / UE_ENGINE_DIR),
the same way Tools/bytes.py does. Instances find the backend and register themselves; the orchestrator links a
deployment to its live server by port.

Stopping is graceful first (a "shutdown" command with a countdown, delivered on the server's next heartbeat),
then forced after a grace period. Servers started by hand or by Tools/bytes.py show up too and can be shut down
by command, but only processes started here can be force-killed.
"""
from __future__ import annotations

import os
import platform
import secrets
import socket
import subprocess
import threading
import time

IS_WINDOWS = platform.system() == "Windows"
IS_MAC = platform.system() == "Darwin"


class DeployError(Exception):
    def __init__(self, status: int, message: str):
        super().__init__(message)
        self.status = status
        self.message = message


def _port_free(port: int) -> bool:
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        try:
            s.bind(("0.0.0.0", port))
            return True
        except OSError:
            return False


class Orchestrator:
    def __init__(self, cfg: dict, base_dir: str):
        deploy = dict(cfg.get("deploy") or {})
        self.base_dir = base_dir
        self.server_exe = deploy.get("serverExe") or ""
        self.engine_dir = deploy.get("engineDir") or os.environ.get("UE_ENGINE_DIR", "")
        self.uproject = os.path.normpath(os.path.join(base_dir, deploy.get("uproject", "../ProjectBytes.uproject")))
        self.public_host = deploy.get("publicHost", "127.0.0.1")
        self.base_port = int(deploy.get("basePort", 7777))
        self.max_instances = int(deploy.get("maxInstances", 32))
        self.extra_args = list(deploy.get("extraArgs", []))
        self.log_dir = os.path.normpath(os.path.join(base_dir, deploy.get("logDir", "Saved/Deployments")))
        self.grace_seconds = int(deploy.get("forceKillAfterSeconds", 90))
        self.backend_url = f"http://{cfg.get('host', '127.0.0.1')}:{cfg.get('port', 8080)}"
        self.server_key = cfg.get("serverKey", "")
        self.districts = cfg["_districts"]
        self.lock = threading.RLock()
        self.deployments: dict[str, dict] = {}

    # -- command line -------------------------------------------------------------------------------

    def configured(self) -> bool:
        return bool(self.server_exe) or bool(self.engine_dir)

    def _editor_binary(self) -> str:
        if IS_WINDOWS:
            return os.path.join(self.engine_dir, "Engine", "Binaries", "Win64", "UnrealEditor-Cmd.exe")
        if IS_MAC:
            return os.path.join(self.engine_dir, "Engine", "Binaries", "Mac", "UnrealEditor.app", "Contents", "MacOS", "UnrealEditor")
        return os.path.join(self.engine_dir, "Engine", "Binaries", "Linux", "UnrealEditor")

    def build_command(self, district_id: str, port: int, region: str, max_players: int) -> list[str]:
        district = self.districts[district_id]
        map_url = f"{district.get('map', '/Engine/Maps/Entry')}?game=District"
        args = [
            "-server", "-log", "-unattended", "-NoCrashDialog", "-nosteam", "-stdout", "-FullStdOutLogOutput",
            f"-port={port}", f"-District={district_id}", f"-BytesBackend={self.backend_url}",
            f"-BytesServerKey={self.server_key}", f"-BytesPublicHost={self.public_host}",
        ]
        if region:
            args.append(f"-BytesRegion={region}")
        if max_players:
            args.append(f"-BytesMaxPlayers={max_players}")
        args += self.extra_args
        if self.server_exe:
            exe = self.server_exe if os.path.isabs(self.server_exe) else os.path.join(self.base_dir, self.server_exe)
            return [exe, map_url] + args
        return [self._editor_binary(), self.uproject, map_url] + args

    # -- lifecycle ----------------------------------------------------------------------------------

    def _used_ports(self) -> set[int]:
        return {d["port"] for d in self.deployments.values() if d["status"] in ("starting", "running", "stopping")}

    def _next_port(self, taken: set[int]) -> int:
        port = self.base_port
        while port in taken or not _port_free(port):
            port += 1
            if port > self.base_port + 1000:
                raise DeployError(503, "No free ports")
        return port

    def spawn(self, district_id: str, count: int, region: str, max_players: int, staff_name: str) -> list[dict]:
        if district_id not in self.districts:
            raise DeployError(404, f"Unknown district '{district_id}'")
        if not self.configured():
            raise DeployError(400, "Deployment isn't configured: set deploy.serverExe or deploy.engineDir in "
                                   "Backend/config.json (or the UE_ENGINE_DIR environment variable)")
        if not 1 <= count <= 16:
            raise DeployError(400, "Spin up between 1 and 16 instances at a time")
        os.makedirs(self.log_dir, exist_ok=True)
        started = []
        with self.lock:
            self.refresh()
            active = sum(1 for d in self.deployments.values() if d["status"] in ("starting", "running", "stopping"))
            if active + count > self.max_instances:
                raise DeployError(409, f"Instance limit reached ({self.max_instances}); stop some first")
            taken = self._used_ports()
            for _ in range(count):
                port = self._next_port(taken)
                taken.add(port)
                deploy_id = "dep_" + secrets.token_hex(6)
                log_path = os.path.join(self.log_dir, f"{district_id}-{port}-{deploy_id}.log")
                command = self.build_command(district_id, port, region, max_players)
                log = open(log_path, "w", encoding="utf-8", errors="replace")
                try:
                    kwargs = {"stdout": log, "stderr": subprocess.STDOUT, "cwd": self.base_dir}
                    if IS_WINDOWS:
                        kwargs["creationflags"] = subprocess.CREATE_NEW_PROCESS_GROUP
                    proc = subprocess.Popen(command, **kwargs)
                except OSError as e:
                    log.close()
                    raise DeployError(500, f"Could not start {command[0]}: {e}")
                self.deployments[deploy_id] = {
                    "deploymentId": deploy_id, "districtId": district_id, "port": port, "region": region,
                    "pid": proc.pid, "status": "starting", "startedAt": int(time.time()), "startedBy": staff_name,
                    "stoppedAt": 0, "exitCode": None, "logPath": log_path, "serverId": "", "instanceId": "",
                    "_proc": proc, "_log": log, "_killAt": 0,
                }
                started.append(self.public(self.deployments[deploy_id]))
        return started

    def link_servers(self, servers: dict[str, dict]) -> None:
        """Attach live registrations to deployments (same port)."""
        by_port = {s["port"]: s for s in servers.values()}
        with self.lock:
            for d in self.deployments.values():
                server = by_port.get(d["port"])
                if server and d["status"] in ("starting", "running"):
                    d["serverId"] = server["serverId"]
                    d["instanceId"] = server["instanceId"]
                    d["status"] = "running"

    def refresh(self) -> None:
        with self.lock:
            moment = time.time()
            for d in self.deployments.values():
                proc = d.get("_proc")
                if proc is None:
                    continue
                code = proc.poll()
                if code is not None:
                    if d["status"] != "stopped":
                        d["status"] = "stopped" if d["status"] == "stopping" else "exited"
                        d["exitCode"] = code
                        d["stoppedAt"] = int(moment)
                    d["_log"].close()
                    d["_proc"] = None
                elif d["_killAt"] and moment >= d["_killAt"]:
                    proc.kill()
                    d["status"] = "stopped"
                    d["exitCode"] = "killed"
                    d["stoppedAt"] = int(moment)

    def mark_stopping(self, deploy_id: str, force: bool) -> dict:
        with self.lock:
            self.refresh()
            d = self.deployments.get(deploy_id)
            if not d:
                raise DeployError(404, "Unknown deployment")
            if d["_proc"] is None:
                raise DeployError(409, "That instance isn't running")
            if force:
                d["_proc"].kill()
                d["status"] = "stopping"
                d["_killAt"] = 0
            else:
                d["status"] = "stopping"
                d["_killAt"] = time.time() + self.grace_seconds
            return self.public(d)

    def list(self) -> list[dict]:
        with self.lock:
            self.refresh()
            return [self.public(d) for d in sorted(self.deployments.values(), key=lambda d: -d["startedAt"])]

    def get(self, deploy_id: str) -> dict | None:
        with self.lock:
            return self.deployments.get(deploy_id)

    def log_tail(self, deploy_id: str, lines: int = 200) -> str:
        d = self.get(deploy_id)
        if not d:
            raise DeployError(404, "Unknown deployment")
        try:
            with open(d["logPath"], "r", encoding="utf-8", errors="replace") as f:
                return "".join(f.readlines()[-lines:])
        except OSError:
            return ""

    def shutdown_all(self) -> None:
        with self.lock:
            for d in self.deployments.values():
                if d.get("_proc") is not None:
                    d["_proc"].terminate()

    @staticmethod
    def public(d: dict) -> dict:
        return {k: v for k, v in d.items() if not k.startswith("_")}
