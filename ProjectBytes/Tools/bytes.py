#!/usr/bin/env python3
"""
Project Bytes local playtest launcher.

    python Tools/bytes.py up                                  backend + one server per district in config
    python Tools/bytes.py up -d financial=2 -d waterfront -c 2  backend + 2x Financial + 1x Waterfront + 2 clients
    python Tools/bytes.py backend [--reset]                   just the backend (foreground)
    python Tools/bytes.py server financial [--port 7790]      one extra district server
    python Tools/bytes.py client [--user tester3] [--join financial] [--faction Criminal]
    python Tools/bytes.py status                              running instances + populations
    python Tools/bytes.py admin set-stats Tester1 --rank 80 --threat Silver
    python Tools/bytes.py build                               compile the editor target

Servers and clients run from the *editor* binary (UnrealEditor -server / -game), which works with the
launcher-installed engine; no source build or packaging needed. Pass --server-exe / --client-exe to use
packaged builds instead.

Engine location: --engine, env UE_ENGINE_DIR, Tools/playtest.local.json {"engineDir": "..."}, or the
default Epic Games Launcher install path for UE 5.8.
"""
from __future__ import annotations

import argparse
import json
import os
import platform
import shutil
import signal
import socket
import subprocess
import sys
import time
import urllib.error
import urllib.request

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_DIR = os.path.dirname(TOOLS_DIR)
UPROJECT = os.path.join(PROJECT_DIR, "ProjectBytes.uproject")
BACKEND = os.path.join(PROJECT_DIR, "Backend", "server.py")
BACKEND_CONFIG = os.path.join(PROJECT_DIR, "Backend", "config.json")
LOCAL_SETTINGS = os.path.join(TOOLS_DIR, "playtest.local.json")
LOG_DIR = os.path.join(PROJECT_DIR, "Saved", "Playtest")
ENGINE_VERSION = "5.8"
IS_WINDOWS = platform.system() == "Windows"
IS_MAC = platform.system() == "Darwin"


# --------------------------------------------------------------------------------------------------
# Settings / discovery
# --------------------------------------------------------------------------------------------------

def load_local_settings() -> dict:
    if os.path.exists(LOCAL_SETTINGS):
        with open(LOCAL_SETTINGS, "r", encoding="utf-8") as f:
            return json.load(f)
    return {}


def load_backend_config() -> dict:
    with open(BACKEND_CONFIG, "r", encoding="utf-8") as f:
        return json.load(f)


def find_engine_dir(explicit: str | None) -> str:
    candidates = [explicit, os.environ.get("UE_ENGINE_DIR"), load_local_settings().get("engineDir")]
    if IS_WINDOWS:
        candidates.append(rf"C:\Program Files\Epic Games\UE_{ENGINE_VERSION}")
    elif IS_MAC:
        candidates.append(f"/Users/Shared/Epic Games/UE_{ENGINE_VERSION}")
    else:
        candidates.append(os.path.expanduser(f"~/UnrealEngine/UE_{ENGINE_VERSION}"))
    for c in candidates:
        if c and os.path.isdir(os.path.join(c, "Engine")):
            return c
    sys.exit("Could not find Unreal Engine %s. Pass --engine <dir>, set UE_ENGINE_DIR, or create %s with "
             '{"engineDir": "C:/Program Files/Epic Games/UE_%s"}' % (ENGINE_VERSION, LOCAL_SETTINGS, ENGINE_VERSION))


def editor_binary(engine_dir: str, console: bool) -> str:
    if IS_WINDOWS:
        name = "UnrealEditor-Cmd.exe" if console else "UnrealEditor.exe"
        path = os.path.join(engine_dir, "Engine", "Binaries", "Win64", name)
    elif IS_MAC:
        path = os.path.join(engine_dir, "Engine", "Binaries", "Mac", "UnrealEditor.app", "Contents", "MacOS", "UnrealEditor")
    else:
        path = os.path.join(engine_dir, "Engine", "Binaries", "Linux", "UnrealEditor")
    if not os.path.exists(path):
        sys.exit(f"Editor binary not found: {path}")
    return path


def backend_url(cfg: dict) -> str:
    return f"http://{cfg.get('host', '127.0.0.1')}:{cfg.get('port', 8080)}"


def http_json(url: str, timeout: float = 2.0):
    with urllib.request.urlopen(url, timeout=timeout) as resp:
        return json.loads(resp.read())


def backend_alive(url: str) -> bool:
    try:
        return bool(http_json(url + "/v1/health").get("ok"))
    except (urllib.error.URLError, OSError, ValueError):
        return False


def port_free(port: int) -> bool:
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        try:
            s.bind(("0.0.0.0", port))
            return True
        except OSError:
            return False


def next_free_port(start: int, taken: set[int]) -> int:
    port = start
    while port in taken or not port_free(port):
        port += 1
    taken.add(port)
    return port


# --------------------------------------------------------------------------------------------------
# Process management
# --------------------------------------------------------------------------------------------------

class Processes:
    def __init__(self, show_consoles: bool):
        self.show_consoles = show_consoles
        self.procs: list[tuple[str, subprocess.Popen]] = []
        os.makedirs(LOG_DIR, exist_ok=True)

    def start(self, name: str, cmd: list[str], log: bool = True) -> subprocess.Popen:
        kwargs = {"cwd": PROJECT_DIR}
        log_path = None
        if self.show_consoles and IS_WINDOWS:
            kwargs["creationflags"] = subprocess.CREATE_NEW_CONSOLE
        elif log:
            log_path = os.path.join(LOG_DIR, f"{name}.log")
            kwargs["stdout"] = open(log_path, "w", encoding="utf-8", errors="replace")
            kwargs["stderr"] = subprocess.STDOUT
        proc = subprocess.Popen(cmd, **kwargs)
        self.procs.append((name, proc))
        print(f"  started {name:<28} pid {proc.pid:<7}" + (f" log: {os.path.relpath(log_path, PROJECT_DIR)}" if log_path else ""))
        return proc

    def wait(self) -> None:
        print("\nRunning. Ctrl+C stops everything.")
        # Treat a plain kill/terminal close like Ctrl+C so child servers don't get orphaned.
        for sig in ("SIGTERM", "SIGHUP", "SIGBREAK"):
            if hasattr(signal, sig):
                signal.signal(getattr(signal, sig), lambda *_: (_ for _ in ()).throw(KeyboardInterrupt()))
        try:
            while True:
                time.sleep(1)
                for name, proc in list(self.procs):
                    code = proc.poll()
                    if code is not None:
                        print(f"  {name} exited with code {code}")
                        self.procs.remove((name, proc))
                if not self.procs:
                    return
        except KeyboardInterrupt:
            pass
        finally:
            self.stop_all()

    def stop_all(self) -> None:
        if not self.procs:
            return
        print("\nStopping...")
        for _, proc in reversed(self.procs):
            if proc.poll() is None:
                if IS_WINDOWS:
                    proc.terminate()
                else:
                    proc.send_signal(signal.SIGINT)
        deadline = time.time() + 10
        for _, proc in self.procs:
            try:
                proc.wait(timeout=max(0.1, deadline - time.time()))
            except subprocess.TimeoutExpired:
                proc.kill()
        self.procs.clear()


# --------------------------------------------------------------------------------------------------
# Command builders
# --------------------------------------------------------------------------------------------------

def backend_cmd(args, reset: bool = False) -> list[str]:
    cmd = [sys.executable, BACKEND, "--config", BACKEND_CONFIG]
    if reset:
        cmd.append("--reset")
    if getattr(args, "quiet", False):
        cmd.append("--quiet")
    return cmd


def server_cmd(args, cfg: dict, district_id: str, port: int) -> list[str]:
    districts = {d["id"]: d for d in cfg.get("districts", [])}
    if district_id not in districts:
        sys.exit(f"Unknown district '{district_id}'. Known: {', '.join(districts)}")
    district = districts[district_id]
    map_url = f"{args.map or district.get('map', '/Engine/Maps/Entry')}?game=District"
    engine_args = [
        "-server", "-log", "-unattended", "-NoCrashDialog", "-nosteam",
        f"-port={port}",
        f"-District={district_id}",
        f"-BytesBackend={backend_url(cfg)}",
        f"-BytesServerKey={cfg.get('serverKey', '')}",
        f"-BytesPublicHost={args.public_host}",
    ]
    if args.region:
        engine_args.append(f"-BytesRegion={args.region}")
    if not (args.show_consoles and IS_WINDOWS):
        engine_args += ["-stdout", "-FullStdOutLogOutput"]
    if args.server_exe:
        return [args.server_exe, map_url] + engine_args
    return [editor_binary(find_engine_dir(args.engine), console=True), UPROJECT, map_url] + engine_args


def client_cmd(args, cfg: dict, index: int, user: str, character: str, faction: str, district: str | None) -> list[str]:
    col, row = index % 3, index // 3
    engine_args = [
        "-game", "-windowed", "-ResX=960", "-ResY=540", f"-WinX={40 + col * 980}", f"-WinY={60 + row * 580}",
        "-log", "-nosteam",
        f"-BytesBackend={backend_url(cfg)}",
        f"-BytesUser={user}", f"-BytesPass={args.password}", "-BytesAutoRegister",
        f"-BytesCharacter={character}", f"-BytesFaction={faction}",
    ]
    if district:
        engine_args.append(f"-BytesDistrict={district}")
    if args.client_exe:
        return [args.client_exe] + engine_args
    return [editor_binary(find_engine_dir(args.engine), console=False), UPROJECT] + engine_args


def parse_district_specs(specs: list[str] | None, cfg: dict) -> list[tuple[str, int]]:
    if not specs:
        return [(d["id"], 1) for d in cfg.get("districts", [])]
    out = []
    for spec in specs:
        for part in spec.split(","):
            name, _, count = part.partition("=")
            out.append((name.strip(), int(count) if count else 1))
    return out


def ensure_backend(args, procs: Processes, cfg: dict) -> None:
    url = backend_url(cfg)
    if backend_alive(url):
        print(f"  backend already running at {url}")
        return
    procs.start("backend", backend_cmd(args, reset=getattr(args, "reset", False)))
    for _ in range(50):
        if backend_alive(url):
            return
        time.sleep(0.1)
    procs.stop_all()
    sys.exit(f"Backend did not come up at {url}; see {os.path.join(LOG_DIR, 'backend.log')}")


# --------------------------------------------------------------------------------------------------
# Commands
# --------------------------------------------------------------------------------------------------

def cmd_up(args) -> int:
    cfg = load_backend_config()
    procs = Processes(args.show_consoles)
    print("Starting local playtest cluster")
    ensure_backend(args, procs, cfg)

    taken: set[int] = set()
    districts = parse_district_specs(args.district, cfg)
    for district_id, count in districts:
        for _ in range(count):
            port = next_free_port(args.base_port, taken)
            procs.start(f"server-{district_id}-{port}", server_cmd(args, cfg, district_id, port))

    join = args.join or (districts[0][0] if districts else None)
    for i in range(args.clients):
        user = f"tester{i + 1}"
        faction = "Enforcer" if i % 2 == 0 else "Criminal"
        procs.start(f"client-{user}", client_cmd(args, cfg, i, user, f"Tester{i + 1}", faction, join), log=False)

    print(f"\nBackend: {backend_url(cfg)}   status: python Tools/bytes.py status")
    if args.clients:
        print(f"Clients auto-login as tester1..tester{args.clients} (password '{args.password}') and join '{join}'.")
    procs.wait()
    return 0


def cmd_backend(args) -> int:
    return subprocess.call(backend_cmd(args, reset=args.reset), cwd=PROJECT_DIR)


def cmd_server(args) -> int:
    cfg = load_backend_config()
    procs = Processes(args.show_consoles)
    if not backend_alive(backend_url(cfg)):
        print(f"Warning: backend not reachable at {backend_url(cfg)}; the server will keep retrying registration.")
    port = next_free_port(args.port, set())
    procs.start(f"server-{args.district_id}-{port}", server_cmd(args, cfg, args.district_id, port))
    procs.wait()
    return 0


def cmd_client(args) -> int:
    cfg = load_backend_config()
    procs = Processes(False)
    user = args.user
    character = args.character or (user[:1].upper() + user[1:])
    procs.start(f"client-{user}", client_cmd(args, cfg, args.slot, user, character, args.faction, args.join), log=False)
    procs.wait()
    return 0


def cmd_status(args) -> int:
    cfg = load_backend_config()
    url = backend_url(cfg)
    try:
        status = http_json(url + "/v1/status")
    except (urllib.error.URLError, OSError) as e:
        print(f"Backend not reachable at {url}: {e}")
        return 1
    print(f"Backend {url}: {status['accounts']} accounts, {status['characters']} characters")
    if not status["servers"]:
        print("No district servers registered.")
    for s in status["servers"]:
        print(f"  {s['displayName']:<24} {s['instanceId']:<24} {s['address']:<22} {s['population']}/{s['maxPlayers']}")
    return 0


def cmd_admin(args) -> int:
    return subprocess.call([sys.executable, BACKEND, "--config", BACKEND_CONFIG, "admin"] + args.rest, cwd=PROJECT_DIR)


def cmd_build(args) -> int:
    engine = find_engine_dir(args.engine)
    if IS_WINDOWS:
        script = os.path.join(engine, "Engine", "Build", "BatchFiles", "Build.bat")
        plat = "Win64"
    elif IS_MAC:
        script = os.path.join(engine, "Engine", "Build", "BatchFiles", "Mac", "Build.sh")
        plat = "Mac"
    else:
        script = os.path.join(engine, "Engine", "Build", "BatchFiles", "Linux", "Build.sh")
        plat = "Linux"
    cmd = [script, args.target, plat, args.configuration, f"-Project={UPROJECT}", "-WaitMutex"]
    print(" ".join(cmd))
    return subprocess.call(cmd, cwd=PROJECT_DIR)


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description="Project Bytes local playtest launcher",
                                     formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__)
    sub = parser.add_subparsers(dest="cmd", required=True)

    def add_ue_args(p):
        p.add_argument("--engine", help="Unreal Engine install dir (contains Engine/)")
        p.add_argument("--map", help="override the district map from Backend/config.json")
        p.add_argument("--public-host", default="127.0.0.1", help="address clients use to reach servers")
        p.add_argument("--region", default="", help="region tag shown on instances, e.g. EU")
        p.add_argument("--server-exe", help="packaged dedicated server executable instead of the editor")
        p.add_argument("--client-exe", help="packaged game executable instead of the editor")
        p.add_argument("--password", default="playtest", help="password for auto-login test accounts")
        p.add_argument("--show-consoles", action="store_true", help="Windows: one console window per server")

    up = sub.add_parser("up", help="backend + district servers (+ clients)")
    add_ue_args(up)
    up.add_argument("-d", "--district", action="append",
                    help="district[=count], repeatable or comma separated; default: one of each district")
    up.add_argument("-c", "--clients", type=int, default=0, help="number of auto-login clients")
    up.add_argument("-j", "--join", help="district the clients join (default: first district)")
    up.add_argument("--base-port", type=int, default=7777)
    up.add_argument("--reset", action="store_true", help="wipe the backend database first")
    up.add_argument("--quiet", action="store_true", help="less backend request logging")
    up.set_defaults(func=cmd_up)

    be = sub.add_parser("backend", help="run only the backend (foreground)")
    be.add_argument("--reset", action="store_true")
    be.add_argument("--quiet", action="store_true")
    be.set_defaults(func=cmd_backend)

    sv = sub.add_parser("server", help="start one district server")
    add_ue_args(sv)
    sv.add_argument("district_id")
    sv.add_argument("--port", type=int, default=7777, help="first port to try")
    sv.set_defaults(func=cmd_server)

    cl = sub.add_parser("client", help="start one game client")
    add_ue_args(cl)
    cl.add_argument("--user", default="tester1")
    cl.add_argument("--character", help="character name (default: capitalized user)")
    cl.add_argument("--faction", default="Enforcer", choices=["Enforcer", "Criminal"])
    cl.add_argument("-j", "--join", help="district to auto-join")
    cl.add_argument("--slot", type=int, default=0, help="window position slot")
    cl.set_defaults(func=cmd_client)

    st = sub.add_parser("status", help="list registered district servers")
    st.set_defaults(func=cmd_status)

    ad = sub.add_parser("admin", help="backend admin commands (list, set-stats, flag, unflag, slots)")
    ad.add_argument("rest", nargs=argparse.REMAINDER)
    ad.set_defaults(func=cmd_admin)

    bd = sub.add_parser("build", help="compile the project with UnrealBuildTool")
    bd.add_argument("--target", default="ProjectBytesEditor",
                    help="ProjectBytesEditor (default), ProjectBytes, ProjectBytesServer*, ProjectBytesClient* "
                         "(*needs a source-built engine)")
    bd.add_argument("--configuration", default="Development")
    bd.add_argument("--engine", help="Unreal Engine install dir (contains Engine/)")
    bd.set_defaults(func=cmd_build)

    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
