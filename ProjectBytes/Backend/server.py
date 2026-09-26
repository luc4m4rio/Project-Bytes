#!/usr/bin/env python3
"""
Project Bytes backend - the "world server" that sits between players and district servers.

Loosely modelled on APB Reloaded's split of responsibilities:

    Login server     -> /v1/auth/*        accounts + sessions
    Character store  -> /v1/characters/*  several characters per account, each with its own identity
    World server     -> /v1/districts/*   district list, requirement checks, join tickets
    Control plane    -> /v1/servers/*     dedicated district servers register, heartbeat, redeem tickets

A client never connects to a district server directly without a ticket: it asks the backend to join a
district, the backend checks the district requirements (rank, threat, faction, account flags), picks an
instance and returns `address + ticket`. The ticket is HMAC-signed, so the district server can verify it
offline during PreLogin, then redeem it once (anti-replay) and pull the fresh character record.

Stdlib only (Python 3.9+):

    python Backend/server.py                     # serve
    python Backend/server.py --reset             # wipe the dev database first
    python Backend/server.py admin list          # inspect accounts/characters
    python Backend/server.py admin set-stats Tester1 --rank 80 --threat Silver
"""
from __future__ import annotations

import argparse
import base64
import copy
import hashlib
import hmac
import json
import os
import re
import secrets
import sqlite3
import sys
import threading
import time
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import parse_qs, urlparse

import appearance as appearance_rules
import economy as economy_rules
import orchestrator as orchestration
import staff as staff_rules

HERE = os.path.dirname(os.path.abspath(__file__))
DEFAULT_CONFIG_PATH = os.path.join(HERE, "config.json")

# Order matters: requirements such as minThreat/maxThreat are ranges over this list.
THREATS = ["Green", "Bronze", "Silver", "Gold"]
FACTIONS = ["Enforcer", "Criminal"]

USERNAME_RE = re.compile(r"^[A-Za-z0-9_.-]{3,32}$")
CHARACTER_NAME_RE = re.compile(r"^[A-Za-z][A-Za-z0-9_-]{2,15}$")

DEFAULT_CONFIG = {
    "host": "127.0.0.1",
    "port": 8080,
    "database": "Saved/bytes.db",
    "appearanceCatalog": "../Content/Data/AppearanceCatalog.json",
    "itemCatalog": "../Content/Data/ItemCatalog.json",
    # Root cockpit (staff control panel). Separate listener; keep it on localhost / behind a VPN.
    "adminHost": "127.0.0.1",
    "adminPort": 8090,
    "adminAllowedIps": [],
    "staffRequire2FA": True,
    "deploy": {},
    "devMode": False,
    "serverKey": "dev-server-key-change-me",
    "sessionTtlSeconds": 7 * 24 * 3600,
    "ticketTtlSeconds": 60,
    "heartbeatSeconds": 5,
    "heartbeatTimeoutSeconds": 20,
    "maxCharactersPerAccount": 4,
    "maxRank": 255,
    "standingPerRank": 1000,
    "startingMoney": 5000,
    "passwordIterations": 120_000,
    "districts": [],
}


class ApiError(Exception):
    def __init__(self, status: int, message: str, reasons: list[str] | None = None):
        super().__init__(message)
        self.status = status
        self.message = message
        self.reasons = reasons or []


def now() -> int:
    return int(time.time())


def canon(value, options: list[str], what: str) -> str | None:
    """Case-insensitive match against a list of canonical names (e.g. 'silver' -> 'Silver')."""
    if value is None or value == "":
        return None
    for option in options:
        if str(value).lower() == option.lower():
            return option
    raise ApiError(400, f"Unknown {what} '{value}'. Expected one of: {', '.join(options)}")


# --------------------------------------------------------------------------------------------------
# District requirements
# --------------------------------------------------------------------------------------------------

def normalize_requirements(raw: dict | None) -> dict:
    """
    Turn the friendly config format into the explicit format sent to clients and servers.
    Every field is optional; an empty/absent field means "no requirement".

      minRank / maxRank          -> ints, 0 = unrestricted
      threats                    -> explicit list, e.g. ["Silver"]
      minThreat / maxThreat      -> range shorthand, e.g. maxThreat "Bronze" = Green + Bronze
      factions                   -> e.g. ["Criminal"]
      requiredAccountFlags       -> e.g. ["tester"]
    """
    raw = raw or {}
    threats = raw.get("threats")
    if threats:
        threats = [canon(t, THREATS, "threat") for t in threats]
    elif raw.get("minThreat") or raw.get("maxThreat"):
        lo = THREATS.index(canon(raw["minThreat"], THREATS, "threat")) if raw.get("minThreat") else 0
        hi = THREATS.index(canon(raw["maxThreat"], THREATS, "threat")) if raw.get("maxThreat") else len(THREATS) - 1
        threats = THREATS[lo:hi + 1]
    else:
        threats = []
    factions = [canon(f, FACTIONS, "faction") for f in (raw.get("factions") or [])]
    return {
        "minRank": int(raw.get("minRank") or 0),
        "maxRank": int(raw.get("maxRank") or 0),
        "allowedThreats": sorted(set(threats), key=THREATS.index),
        "allowedFactions": sorted(set(factions), key=FACTIONS.index),
        "requiredAccountFlags": [str(f) for f in (raw.get("requiredAccountFlags") or [])],
    }


def evaluate_requirements(req: dict, rank: int, threat: str, faction: str, account_flags: list[str]) -> list[str]:
    """Returns human-readable reasons why the character may NOT join. Empty list = eligible.
    Mirrored in C++ by FBytesDistrictRequirements::Evaluate - keep the two in sync."""
    reasons = []
    if req["minRank"] > 0 and rank < req["minRank"]:
        reasons.append(f"Requires rank {req['minRank']} or higher (you are rank {rank})")
    if req["maxRank"] > 0 and rank > req["maxRank"]:
        reasons.append(f"Restricted to rank {req['maxRank']} or lower (you are rank {rank})")
    if req["allowedThreats"] and threat not in req["allowedThreats"]:
        reasons.append(f"Restricted to {'/'.join(req['allowedThreats'])} threat (you are {threat})")
    if req["allowedFactions"] and faction not in req["allowedFactions"]:
        reasons.append(f"Restricted to {'/'.join(req['allowedFactions'])} (you are {faction})")
    flags = {f.lower() for f in account_flags}
    for flag in req["requiredAccountFlags"]:
        if flag.lower() not in flags:
            reasons.append(f"Requires account flag '{flag}'")
    return reasons


# --------------------------------------------------------------------------------------------------
# Join tickets:  base64url(json claims) + "." + base64url(HMAC-SHA1(key, first part))
# Verified in C++ by BytesTicket::Verify.
# --------------------------------------------------------------------------------------------------

def b64url(data: bytes) -> str:
    return base64.urlsafe_b64encode(data).rstrip(b"=").decode("ascii")


def b64url_decode(text: str) -> bytes:
    return base64.urlsafe_b64decode(text + "=" * (-len(text) % 4))


def sign_ticket(key: bytes, claims: dict) -> str:
    payload = b64url(json.dumps(claims, separators=(",", ":")).encode("utf-8"))
    signature = b64url(hmac.new(key, payload.encode("ascii"), hashlib.sha1).digest())
    return f"{payload}.{signature}"


def verify_ticket(key: bytes, token: str, at: int | None = None) -> dict:
    payload, _, signature = token.partition(".")
    expected = hmac.new(key, payload.encode("ascii"), hashlib.sha1).digest()
    if not hmac.compare_digest(expected, b64url_decode(signature)):
        raise ValueError("bad signature")
    claims = json.loads(b64url_decode(payload))
    if claims["expiresAt"] < (at if at is not None else now()):
        raise ValueError("expired")
    return claims


# --------------------------------------------------------------------------------------------------
# Config
# --------------------------------------------------------------------------------------------------

def load_config(path: str | None) -> dict:
    cfg = copy.deepcopy(DEFAULT_CONFIG)
    base_dir = HERE
    if path:
        with open(path, "r", encoding="utf-8") as f:
            user = json.load(f)
        cfg.update({k: v for k, v in user.items() if not k.startswith("_")})
        base_dir = os.path.dirname(os.path.abspath(path))

    # Environment overrides, handy for scripts/CI.
    for env, key, cast in (
        ("BYTES_BACKEND_HOST", "host", str),
        ("BYTES_BACKEND_PORT", "port", int),
        ("BYTES_SERVER_KEY", "serverKey", str),
        ("BYTES_DATABASE", "database", str),
    ):
        if os.environ.get(env):
            cfg[key] = cast(os.environ[env])

    if cfg["database"] != ":memory:" and not os.path.isabs(cfg["database"]):
        cfg["database"] = os.path.join(base_dir, cfg["database"])
    for key in ("appearanceCatalog", "itemCatalog"):
        if cfg.get(key) and not os.path.isabs(cfg[key]):
            cfg[key] = os.path.normpath(os.path.join(base_dir, cfg[key]))
    cfg["_baseDir"] = base_dir

    districts = {}
    for d in cfg["districts"]:
        did = d["id"]
        display = d.get("displayName", did)
        districts[did] = {
            "districtId": did,
            "displayName": display,
            "shortName": d.get("shortName") or display,
            "type": d.get("type", "Action"),
            "map": d.get("map", "/Engine/Maps/Entry"),
            "maxPlayers": int(d.get("maxPlayers", 80)),
            "requirements": normalize_requirements(d.get("requirements")),
        }
    cfg["_districts"] = districts
    return cfg


# --------------------------------------------------------------------------------------------------
# Backend state
# --------------------------------------------------------------------------------------------------

SCHEMA = """
CREATE TABLE IF NOT EXISTS meta (key TEXT PRIMARY KEY, value TEXT NOT NULL);
CREATE TABLE IF NOT EXISTS accounts (
    id TEXT PRIMARY KEY,
    username TEXT NOT NULL UNIQUE COLLATE NOCASE,
    pw_salt TEXT NOT NULL,
    pw_hash TEXT NOT NULL,
    flags TEXT NOT NULL DEFAULT '[]',
    max_characters INTEGER,
    created_at INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS sessions (
    token_hash TEXT PRIMARY KEY,
    account_id TEXT NOT NULL REFERENCES accounts(id) ON DELETE CASCADE,
    expires_at INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS characters (
    id TEXT PRIMARY KEY,
    account_id TEXT NOT NULL REFERENCES accounts(id) ON DELETE CASCADE,
    name TEXT NOT NULL UNIQUE COLLATE NOCASE,
    faction TEXT NOT NULL,
    rank INTEGER NOT NULL DEFAULT 1,
    standing INTEGER NOT NULL DEFAULT 0,
    threat TEXT NOT NULL DEFAULT 'Green',
    money INTEGER NOT NULL DEFAULT 0,
    clan TEXT NOT NULL DEFAULT '',
    appearance TEXT NOT NULL DEFAULT '',
    last_district TEXT NOT NULL DEFAULT '',
    online_instance TEXT NOT NULL DEFAULT '',
    created_at INTEGER NOT NULL
);
CREATE TABLE IF NOT EXISTS bans (
    id TEXT PRIMARY KEY,
    account_id TEXT NOT NULL,
    reason TEXT NOT NULL,
    created_at INTEGER NOT NULL,
    created_by TEXT NOT NULL,
    expires_at INTEGER,
    revoked_at INTEGER,
    revoked_by TEXT NOT NULL DEFAULT '',
    revoke_reason TEXT NOT NULL DEFAULT ''
);
CREATE INDEX IF NOT EXISTS bans_account ON bans(account_id);
CREATE TABLE IF NOT EXISTS server_commands (
    id TEXT PRIMARY KEY,
    server_id TEXT NOT NULL,
    instance_id TEXT NOT NULL,
    type TEXT NOT NULL,
    payload TEXT NOT NULL,
    created_at INTEGER NOT NULL,
    created_by TEXT NOT NULL,
    status TEXT NOT NULL DEFAULT 'queued',
    delivered_at INTEGER,
    completed_at INTEGER,
    result TEXT NOT NULL DEFAULT ''
);
CREATE INDEX IF NOT EXISTS server_commands_server ON server_commands(server_id, status);
CREATE TABLE IF NOT EXISTS tickets (
    id TEXT PRIMARY KEY,
    account_id TEXT NOT NULL,
    character_id TEXT NOT NULL,
    server_id TEXT NOT NULL,
    district_id TEXT NOT NULL,
    issued_at INTEGER NOT NULL,
    expires_at INTEGER NOT NULL,
    redeemed_at INTEGER
);
"""


class Backend:
    def __init__(self, cfg: dict):
        self.cfg = cfg
        self.districts: dict[str, dict] = cfg["_districts"]
        db_path = cfg["database"]
        if db_path != ":memory:":
            os.makedirs(os.path.dirname(db_path), exist_ok=True)
        self.db = sqlite3.connect(db_path, check_same_thread=False)
        self.db.row_factory = sqlite3.Row
        self.db.execute("PRAGMA foreign_keys = ON")
        self.db.executescript(SCHEMA)
        self.lock = threading.RLock()
        # Live district servers are ephemeral: kept in memory. After a backend restart servers get a 404 on
        # their next heartbeat and simply register again.
        self.servers: dict[str, dict] = {}
        self.ticket_key = self._load_or_create_ticket_key()
        # Same catalog the game ships (Content/Data/AppearanceCatalog.json): the backend is the authority on
        # which parts/tattoos a character has unlocked.
        self.economy = economy_rules.Economy(self.db, self.lock, economy_rules.ItemCatalog.load(cfg.get("itemCatalog")))
        self.staff = staff_rules.StaffService(self.db, self.lock, cfg)
        self.orchestrator = orchestration.Orchestrator(cfg, cfg.get("_baseDir", HERE))
        self.catalog = None
        if cfg.get("appearanceCatalog") and os.path.exists(cfg["appearanceCatalog"]):
            self.catalog = appearance_rules.Catalog.load(cfg["appearanceCatalog"])
        elif cfg.get("appearanceCatalog"):
            print(f"[backend] warning: appearance catalog not found at {cfg['appearanceCatalog']}; "
                  "appearances will only be size-checked", flush=True)

    # -- helpers ------------------------------------------------------------------------------------

    def _load_or_create_ticket_key(self) -> bytes:
        row = self.db.execute("SELECT value FROM meta WHERE key = 'ticket_key'").fetchone()
        if row:
            return base64.b64decode(row["value"])
        key = secrets.token_bytes(32)
        self.db.execute("INSERT INTO meta (key, value) VALUES ('ticket_key', ?)", (base64.b64encode(key).decode(),))
        self.db.commit()
        return key

    def _hash_password(self, password: str, salt: str) -> str:
        return hashlib.pbkdf2_hmac("sha256", password.encode("utf-8"), bytes.fromhex(salt),
                                   self.cfg["passwordIterations"]).hex()

    @staticmethod
    def _token_hash(token: str) -> str:
        return hashlib.sha256(token.encode("utf-8")).hexdigest()

    def _account_json(self, row) -> dict:
        return {
            "accountId": row["id"],
            "username": row["username"],
            "flags": json.loads(row["flags"]),
            "maxCharacters": self._max_characters(row),
        }

    def _max_characters(self, account_row) -> int:
        return account_row["max_characters"] or self.cfg["maxCharactersPerAccount"]

    @staticmethod
    def _character_json(row) -> dict:
        return {
            "characterId": row["id"],
            "name": row["name"],
            "faction": row["faction"],
            "rank": row["rank"],
            "standing": row["standing"],
            "threat": row["threat"],
            "money": row["money"],
            "clan": row["clan"],
            "appearance": row["appearance"],
            "lastDistrict": row["last_district"],
            "onlineInstance": row["online_instance"],
        }

    def _rank_for_standing(self, standing: int) -> int:
        return max(1, min(self.cfg["maxRank"], 1 + standing // self.cfg["standingPerRank"]))

    def _owned_character(self, account, character_id: str):
        row = self.db.execute("SELECT * FROM characters WHERE id = ? AND account_id = ?",
                              (character_id, account["id"])).fetchone()
        if not row:
            raise ApiError(404, "Character not found on this account")
        return row

    def _district(self, district_id: str) -> dict:
        district = self.districts.get(district_id)
        if not district:
            raise ApiError(404, f"Unknown district '{district_id}'")
        return district

    def _require_server_key(self, headers) -> None:
        supplied = headers.get("X-Bytes-Server-Key") or ""
        if not hmac.compare_digest(supplied.encode(), str(self.cfg["serverKey"]).encode()):
            raise ApiError(401, "Invalid server key")

    def _server(self, server_id: str) -> dict:
        server = self.servers.get(server_id or "")
        if not server:
            raise ApiError(404, "Unknown server; register again")
        return server

    def _reap_servers(self) -> None:
        deadline = now() - self.cfg["heartbeatTimeoutSeconds"]
        for sid in [sid for sid, s in self.servers.items() if s["lastSeen"] < deadline]:
            self._drop_server(sid)

    def _drop_server(self, server_id: str) -> None:
        server = self.servers.pop(server_id, None)
        self.db.execute("UPDATE server_commands SET status = 'undeliverable', completed_at = ? "
                        "WHERE server_id = ? AND status IN ('queued', 'delivered')", (now(), server_id))
        if server:
            self.db.execute("UPDATE characters SET online_instance = '' WHERE online_instance = ?",
                            (server["instanceId"],))
            self.db.commit()

    def _pending_tickets(self, server_id: str) -> int:
        return self.db.execute(
            "SELECT COUNT(*) FROM tickets WHERE server_id = ? AND redeemed_at IS NULL AND expires_at >= ?",
            (server_id, now())).fetchone()[0]

    def _instance_json(self, server: dict) -> dict:
        return {
            "instanceId": server["instanceId"],
            "displayName": server["displayName"],
            "region": server["region"],
            "population": len(server["characterIds"]),
            "maxPlayers": server["maxPlayers"],
        }

    def active_ban(self, account_id: str):
        return self.db.execute(
            "SELECT * FROM bans WHERE account_id = ? AND revoked_at IS NULL AND (expires_at IS NULL OR expires_at > ?) "
            "ORDER BY COALESCE(expires_at, 9999999999) DESC LIMIT 1", (account_id, now())).fetchone()

    @staticmethod
    def ban_reasons(ban) -> list[str]:
        until = "permanently" if not ban["expires_at"] else \
            "until " + time.strftime("%Y-%m-%d %H:%M UTC", time.gmtime(ban["expires_at"]))
        return [f"Reason: {ban['reason']}", f"Banned {until}"]

    def _refuse_if_banned(self, account_id: str) -> None:
        ban = self.active_ban(account_id)
        if ban:
            raise ApiError(403, "This account is banned", self.ban_reasons(ban))

    def authenticate(self, headers) -> sqlite3.Row:
        auth = headers.get("Authorization") or ""
        if not auth.startswith("Bearer "):
            raise ApiError(401, "Not logged in")
        with self.lock:
            row = self.db.execute(
                "SELECT a.* FROM sessions s JOIN accounts a ON a.id = s.account_id "
                "WHERE s.token_hash = ? AND s.expires_at >= ?",
                (self._token_hash(auth[len("Bearer "):].strip()), now())).fetchone()
        if not row:
            raise ApiError(401, "Session expired; log in again")
        return row

    # -- accounts -----------------------------------------------------------------------------------

    def register(self, body: dict) -> dict:
        username = str(body.get("username") or "").strip()
        password = str(body.get("password") or "")
        if not USERNAME_RE.match(username):
            raise ApiError(400, "Usernames must be 3-32 characters: letters, digits, '.', '_' or '-'")
        if len(password) < 6:
            raise ApiError(400, "Passwords must be at least 6 characters")
        salt = secrets.token_hex(16)
        account_id = "acc_" + secrets.token_hex(8)
        flags: list[str] = []
        with self.lock:
            try:
                self.db.execute(
                    "INSERT INTO accounts (id, username, pw_salt, pw_hash, flags, created_at) VALUES (?,?,?,?,?,?)",
                    (account_id, username, salt, self._hash_password(password, salt), json.dumps(flags), now()))
                self.db.commit()
            except sqlite3.IntegrityError:
                raise ApiError(409, "That username is already registered")
            row = self.db.execute("SELECT * FROM accounts WHERE id = ?", (account_id,)).fetchone()
        return {"account": self._account_json(row)}

    def login(self, body: dict) -> dict:
        username = str(body.get("username") or "").strip()
        password = str(body.get("password") or "")
        with self.lock:
            row = self.db.execute("SELECT * FROM accounts WHERE username = ?", (username,)).fetchone()
        if not row or not hmac.compare_digest(self._hash_password(password, row["pw_salt"]), row["pw_hash"]):
            raise ApiError(401, "Wrong username or password")
        token = secrets.token_urlsafe(32)
        with self.lock:
            # Ban check and session creation in one critical section: a ban can't slip in between.
            self._refuse_if_banned(row["id"])
            self.db.execute("DELETE FROM sessions WHERE expires_at < ?", (now(),))
            self.db.execute("INSERT INTO sessions (token_hash, account_id, expires_at) VALUES (?,?,?)",
                            (self._token_hash(token), row["id"], now() + self.cfg["sessionTtlSeconds"]))
            self.db.commit()
        return {"sessionToken": token, "account": self._account_json(row)}

    def logout(self, headers) -> dict:
        auth = headers.get("Authorization") or ""
        if auth.startswith("Bearer "):
            with self.lock:
                self.db.execute("DELETE FROM sessions WHERE token_hash = ?",
                                (self._token_hash(auth[len("Bearer "):].strip()),))
                self.db.commit()
        return {}

    def me(self, account) -> dict:
        return {"account": self._account_json(account)}

    # -- characters ---------------------------------------------------------------------------------

    def list_characters(self, account) -> dict:
        with self.lock:
            rows = self.db.execute("SELECT * FROM characters WHERE account_id = ? ORDER BY created_at, name",
                                   (account["id"],)).fetchall()
        return {"characters": [self._character_json(r) for r in rows], "account": self._account_json(account)}

    def create_character(self, account, body: dict) -> dict:
        name = str(body.get("name") or "").strip()
        if not CHARACTER_NAME_RE.match(name):
            raise ApiError(400, "Character names must be 3-16 characters (letters, digits, '_' or '-') "
                                "and start with a letter")
        faction = canon(body.get("faction"), FACTIONS, "faction")
        if not faction:
            raise ApiError(400, f"Pick a faction: {', '.join(FACTIONS)}")
        appearance = self._validate_appearance(body.get("appearance"), rank=1, faction=faction)
        with self.lock:
            count = self.db.execute("SELECT COUNT(*) FROM characters WHERE account_id = ?",
                                    (account["id"],)).fetchone()[0]
            limit = self._max_characters(account)
            if count >= limit:
                raise ApiError(409, f"All {limit} character slots are in use")
            character_id = "chr_" + secrets.token_hex(8)
            try:
                self.db.execute(
                    "INSERT INTO characters (id, account_id, name, faction, money, appearance, created_at) "
                    "VALUES (?,?,?,?,?,?,?)",
                    (character_id, account["id"], name, faction, self.cfg["startingMoney"], appearance, now()))
                self.db.commit()
            except sqlite3.IntegrityError:
                raise ApiError(409, f"The name '{name}' is already taken")
            row = self.db.execute("SELECT * FROM characters WHERE id = ?", (character_id,)).fetchone()
        return {"character": self._character_json(row)}

    def _validate_appearance(self, raw, rank: int, faction: str) -> str:
        raw = raw or ""
        if not isinstance(raw, str) or len(raw.encode("utf-8")) > appearance_rules.MAX_APPEARANCE_BYTES:
            raise ApiError(400, f"appearance must be a string of at most {appearance_rules.MAX_APPEARANCE_BYTES} bytes")
        if not self.catalog:
            return raw
        normalized, errors = appearance_rules.validate(self.catalog, raw, rank, faction)
        if errors:
            raise ApiError(400, "That look isn't allowed", errors)
        return normalized

    def update_appearance(self, account, character_id: str, body: dict) -> dict:
        """Re-edit an existing character (APB's wardrobe). Validated against the character's current rank."""
        with self.lock:
            row = self._owned_character(account, character_id)
            if row["online_instance"]:
                raise ApiError(409, f"{row['name']} is in {row['online_instance']}; leave the district to change looks")
            appearance = self._validate_appearance(body.get("appearance"), row["rank"], row["faction"])
            self.db.execute("UPDATE characters SET appearance = ? WHERE id = ?", (appearance, row["id"]))
            self.db.commit()
            row = self.db.execute("SELECT * FROM characters WHERE id = ?", (row["id"],)).fetchone()
        return {"character": self._character_json(row)}

    def delete_character(self, account, character_id: str) -> dict:
        with self.lock:
            row = self._owned_character(account, character_id)
            if row["online_instance"]:
                raise ApiError(409, f"{row['name']} is currently online in {row['online_instance']}")
            self.db.execute("DELETE FROM characters WHERE id = ?", (character_id,))
            self.db.commit()
        return {}

    # -- districts ----------------------------------------------------------------------------------

    def list_districts(self, account, character_id: str | None) -> dict:
        with self.lock:
            self._reap_servers()
            character = self._owned_character(account, character_id) if character_id else None
            flags = json.loads(account["flags"])
            out = []
            for district in self.districts.values():
                reasons = []
                if character:
                    reasons = evaluate_requirements(district["requirements"], character["rank"],
                                                    character["threat"], character["faction"], flags)
                instances = sorted((s for s in self.servers.values() if s["districtId"] == district["districtId"]),
                                   key=lambda s: s["index"])
                out.append({
                    "districtId": district["districtId"],
                    "displayName": district["displayName"],
                    "type": district["type"],
                    "requirements": district["requirements"],
                    "ineligibleReasons": reasons,
                    "instances": [self._instance_json(s) for s in instances],
                })
        return {"districts": out}

    def join_district(self, account, body: dict) -> dict:
        district_id = str(body.get("districtId") or "")
        instance_id = str(body.get("instanceId") or "")
        with self.lock:
            self._refuse_if_banned(account["id"])
            character = self._owned_character(account, str(body.get("characterId") or ""))
            district = self._district(district_id)
            flags = json.loads(account["flags"])
            reasons = evaluate_requirements(district["requirements"], character["rank"], character["threat"],
                                            character["faction"], flags)
            if reasons:
                raise ApiError(403, f"{character['name']} can't enter {district['displayName']}", reasons)

            self._reap_servers()
            candidates = [s for s in self.servers.values() if s["districtId"] == district_id
                          and (not instance_id or s["instanceId"] == instance_id)]
            if instance_id and not candidates:
                raise ApiError(404, f"Instance '{instance_id}' is not running")
            if not candidates:
                raise ApiError(503, f"No {district['displayName']} servers are running "
                                    f"(start one: python Tools/bytes.py server {district_id})")

            def load(s):
                return len(s["characterIds"]) + self._pending_tickets(s["serverId"])

            open_servers = [s for s in candidates if load(s) < s["maxPlayers"]]
            if not open_servers:
                raise ApiError(503, f"All {district['displayName']} instances are full")
            # APB-style fill: put players where the action is, lowest index breaks ties.
            server = max(open_servers, key=lambda s: (load(s), -s["index"]))

            ticket_id = "tkt_" + secrets.token_hex(8)
            issued = now()
            expires = issued + self.cfg["ticketTtlSeconds"]
            self.db.execute(
                "INSERT INTO tickets (id, account_id, character_id, server_id, district_id, issued_at, expires_at) "
                "VALUES (?,?,?,?,?,?,?)",
                (ticket_id, account["id"], character["id"], server["serverId"], district_id, issued, expires))
            self.db.execute("DELETE FROM tickets WHERE expires_at < ?", (issued - 3600,))
            self.db.commit()

        claims = {
            "ticketId": ticket_id,
            "accountId": account["id"],
            "characterId": character["id"],
            "characterName": character["name"],
            "faction": character["faction"],
            "rank": character["rank"],
            "threat": character["threat"],
            "clan": character["clan"],
            "accountFlags": flags,
            "districtId": district_id,
            "instanceId": server["instanceId"],
            "serverId": server["serverId"],
            "expiresAt": expires,
        }
        return {
            "districtId": district_id,
            "instanceId": server["instanceId"],
            "displayName": server["displayName"],
            "address": f"{server['host']}:{server['port']}",
            "ticket": sign_ticket(self.ticket_key, claims),
        }

    # -- dedicated server control plane -------------------------------------------------------------

    def server_register(self, headers, body: dict, client_ip: str) -> dict:
        self._require_server_key(headers)
        district = self._district(str(body.get("districtId") or ""))
        host = str(body.get("host") or client_ip)
        port = int(body.get("port") or 7777)
        max_players = int(body.get("maxPlayers") or 0) or district["maxPlayers"]
        region = str(body.get("region") or "")
        with self.lock:
            self._reap_servers()
            # A server restarting on the same address replaces its stale entry.
            for sid in [sid for sid, s in self.servers.items() if s["host"] == host and s["port"] == port]:
                self._drop_server(sid)
            used = {s["index"] for s in self.servers.values() if s["districtId"] == district["districtId"]}
            index = next(i for i in range(1, 10_000) if i not in used)
            server_id = "srv_" + secrets.token_hex(6)
            server = {
                "serverId": server_id,
                "districtId": district["districtId"],
                "instanceId": f"{district['districtId']}-{index}",
                "index": index,
                "displayName": f"{district['shortName']}-{index}" + (f" [{region}]" if region else ""),
                "region": region,
                "host": host,
                "port": port,
                "maxPlayers": max_players,
                "characterIds": [],
                "lastSeen": now(),
                "build": str(body.get("build") or ""),
            }
            self.servers[server_id] = server
        print(f"[backend] district server up: {server['displayName']} ({server_id}) at {host}:{port}", flush=True)
        return {
            "serverId": server_id,
            "districtId": district["districtId"],
            "instanceId": server["instanceId"],
            "displayName": server["displayName"],
            "maxPlayers": max_players,
            "requirements": district["requirements"],
            "ticketKey": base64.b64encode(self.ticket_key).decode("ascii"),
            "heartbeatSeconds": self.cfg["heartbeatSeconds"],
        }

    def server_heartbeat(self, headers, body: dict) -> dict:
        self._require_server_key(headers)
        with self.lock:
            server = self._server(body.get("serverId"))
            current = [str(c) for c in (body.get("characterIds") or [])]
            left = set(server["characterIds"]) - set(current)
            for cid in left:
                self.db.execute("UPDATE characters SET online_instance = '' WHERE id = ? AND online_instance = ?",
                                (cid, server["instanceId"]))
            for cid in current:
                self.db.execute("UPDATE characters SET online_instance = ? WHERE id = ?",
                                (server["instanceId"], cid))
            self.db.commit()
            server["characterIds"] = current
            server["lastSeen"] = now()
            commands = self._take_commands(server["serverId"])
        return {"ok": True, "commands": commands}

    def server_unregister(self, headers, body: dict) -> dict:
        self._require_server_key(headers)
        with self.lock:
            server = self.servers.get(str(body.get("serverId") or ""))
            if server:
                print(f"[backend] district server down: {server['displayName']}", flush=True)
                self._drop_server(server["serverId"])
        return {}

    def server_redeem(self, headers, body: dict) -> dict:
        """One-time ticket consumption. The server already verified the signature offline in PreLogin;
        this call prevents replays and hands back the authoritative character record."""
        self._require_server_key(headers)
        with self.lock:
            server = self._server(body.get("serverId"))
            ticket = self.db.execute("SELECT * FROM tickets WHERE id = ?", (str(body.get("ticketId") or ""),)).fetchone()
            if not ticket:
                raise ApiError(404, "Unknown ticket")
            if ticket["server_id"] != server["serverId"]:
                raise ApiError(403, "Ticket was issued for a different server")
            if body.get("characterId") and body["characterId"] != ticket["character_id"]:
                raise ApiError(403, "Ticket belongs to a different character")
            if ticket["redeemed_at"]:
                raise ApiError(409, "Ticket has already been used")
            if ticket["expires_at"] < now():
                raise ApiError(410, "Ticket expired")
            ban = self.active_ban(ticket["account_id"])
            if ban:
                raise ApiError(403, "Account is banned", self.ban_reasons(ban))
            self.db.execute("UPDATE tickets SET redeemed_at = ? WHERE id = ?", (now(), ticket["id"]))
            self.db.execute("UPDATE characters SET online_instance = ?, last_district = ? WHERE id = ?",
                            (server["instanceId"], server["districtId"], ticket["character_id"]))
            self.db.commit()
            if ticket["character_id"] not in server["characterIds"]:
                server["characterIds"].append(ticket["character_id"])
            character = self.db.execute("SELECT * FROM characters WHERE id = ?", (ticket["character_id"],)).fetchone()
            account = self.db.execute("SELECT * FROM accounts WHERE id = ?", (ticket["account_id"],)).fetchone()
            if not character or not account:
                raise ApiError(404, "Character no longer exists")
        return {"character": self._character_json(character), "accountFlags": json.loads(account["flags"])}

    def server_update_character(self, headers, body: dict) -> dict:
        """Progression written back by the authoritative district server."""
        self._require_server_key(headers)
        with self.lock:
            self._server(body.get("serverId"))
            row = self.db.execute("SELECT * FROM characters WHERE id = ?", (str(body.get("characterId") or ""),)).fetchone()
            if not row:
                raise ApiError(404, "Unknown character")
            standing = max(0, row["standing"] + int(body.get("standingDelta") or 0))
            money = max(0, row["money"] + int(body.get("moneyDelta") or 0))
            threat = canon(body.get("threat"), THREATS, "threat") or row["threat"]
            self.db.execute("UPDATE characters SET standing = ?, rank = ?, money = ?, threat = ? WHERE id = ?",
                            (standing, self._rank_for_standing(standing), money, threat, row["id"]))
            self.db.commit()
            row = self.db.execute("SELECT * FROM characters WHERE id = ?", (row["id"],)).fetchone()
        return {"character": self._character_json(row)}

    # -- staff command queue (delivered on heartbeat) -----------------------------------------------

    COMMAND_FIELDS = ("characterId", "message", "reason", "style", "consoleCommand")

    def queue_command(self, server_id: str, command_type: str, payload: dict, created_by: str) -> str:
        """Caller holds the lock. Payload is flattened into fixed fields the C++ side parses."""
        server = self.servers.get(server_id)
        if not server:
            raise ApiError(404, "That server is not online")
        command_id = "cmd_" + secrets.token_hex(8)
        self.db.execute("INSERT INTO server_commands (id, server_id, instance_id, type, payload, created_at, created_by) "
                        "VALUES (?,?,?,?,?,?,?)",
                        (command_id, server_id, server["instanceId"], command_type, json.dumps(payload), now(), created_by))
        self.db.commit()
        return command_id

    def _take_commands(self, server_id: str) -> list[dict]:
        rows = self.db.execute("SELECT * FROM server_commands WHERE server_id = ? AND status = 'queued' ORDER BY created_at",
                               (server_id,)).fetchall()
        out = []
        for row in rows:
            payload = json.loads(row["payload"])
            command = {"commandId": row["id"], "type": row["type"], "delaySeconds": int(payload.get("delaySeconds") or 0)}
            for key in self.COMMAND_FIELDS:
                command[key] = str(payload.get(key) or "")
            out.append(command)
        if rows:
            self.db.execute(f"UPDATE server_commands SET status = 'delivered', delivered_at = ? WHERE id IN "
                            f"({','.join('?' for _ in rows)})", [now()] + [r["id"] for r in rows])
            self.db.commit()
        return out

    def server_ack_commands(self, headers, body: dict) -> dict:
        self._require_server_key(headers)
        with self.lock:
            server_id = str(body.get("serverId") or "")
            for result in body.get("results") or []:
                self.db.execute("UPDATE server_commands SET status = ?, completed_at = ?, result = ? WHERE id = ? AND server_id = ?",
                                ("done" if result.get("ok") else "failed", now(), str(result.get("message") or "")[:4000],
                                 str(result.get("commandId") or ""), server_id))
            self.db.commit()
        return {}

    def server_get_character(self, headers, body: dict) -> dict:
        """Fresh character record for a player already in the district (after staff grants)."""
        self._require_server_key(headers)
        with self.lock:
            self._server(body.get("serverId"))
            row = self.db.execute("SELECT * FROM characters WHERE id = ?", (str(body.get("characterId") or ""),)).fetchone()
            if not row:
                raise ApiError(404, "Unknown character")
        return {"character": self._character_json(row)}

    # -- wallet / inventory / mail (player API) -----------------------------------------------------

    def wallet(self, account) -> dict:
        with self.lock:
            return {"currencies": self.economy.wallet(account["id"])}

    def character_inventory(self, account, character_id: str) -> dict:
        with self.lock:
            self._owned_character(account, character_id)
            items = self.economy.inventory(character_id)
            self.db.commit()
        return {"items": items}

    def mailbox(self, account) -> dict:
        with self.lock:
            return {"mail": self.economy.mailbox(account["id"])}

    def claim_mail(self, account, mail_id: str, body: dict) -> dict:
        with self.lock:
            self._refuse_if_banned(account["id"])
            character = self._owned_character(account, str(body.get("characterId") or ""))
            try:
                result = self.economy.claim(account["id"], mail_id, character["id"])
                self.db.commit()
            except economy_rules.EconomyError as e:
                self.db.rollback()
                raise ApiError(e.status, e.message)
            character = self.db.execute("SELECT * FROM characters WHERE id = ?", (character["id"],)).fetchone()
        return dict(result, character=self._character_json(character), currencies=self.economy.wallet(account["id"]))

    # -- dev / admin --------------------------------------------------------------------------------

    def set_character_stats(self, character_id: str, rank=None, threat=None, money=None, standing=None) -> dict:
        with self.lock:
            row = self.db.execute("SELECT * FROM characters WHERE id = ? OR name = ?",
                                  (character_id, character_id)).fetchone()
            if not row:
                raise ApiError(404, f"Unknown character '{character_id}'")
            new_standing = row["standing"]
            new_rank = row["rank"]
            if standing is not None:
                new_standing = max(0, int(standing))
                new_rank = self._rank_for_standing(new_standing)
            if rank is not None:
                new_rank = max(1, min(self.cfg["maxRank"], int(rank)))
                new_standing = (new_rank - 1) * self.cfg["standingPerRank"]
            new_threat = canon(threat, THREATS, "threat") or row["threat"]
            new_money = row["money"] if money is None else max(0, min(2_000_000_000, int(money)))
            self.db.execute("UPDATE characters SET rank = ?, standing = ?, threat = ?, money = ? WHERE id = ?",
                            (new_rank, new_standing, new_threat, new_money, row["id"]))
            self.db.commit()
            row = self.db.execute("SELECT * FROM characters WHERE id = ?", (row["id"],)).fetchone()
        return {"character": self._character_json(row)}

    def dev_set_character(self, account, body: dict) -> dict:
        if not self.cfg["devMode"]:
            raise ApiError(403, "Dev endpoints are disabled (devMode=false)")
        with self.lock:
            self._owned_character(account, str(body.get("characterId") or ""))
        return self.set_character_stats(body["characterId"], rank=body.get("rank"), threat=body.get("threat"),
                                        money=body.get("money"), standing=body.get("standing"))

    def status(self) -> dict:
        with self.lock:
            self._reap_servers()
            servers = [dict(self._instance_json(s), serverId=s["serverId"], districtId=s["districtId"],
                            address=f"{s['host']}:{s['port']}", lastSeen=s["lastSeen"])
                       for s in sorted(self.servers.values(), key=lambda s: (s["districtId"], s["index"]))]
            accounts = self.db.execute("SELECT COUNT(*) FROM accounts").fetchone()[0]
            characters = self.db.execute("SELECT COUNT(*) FROM characters").fetchone()[0]
        return {"servers": servers, "accounts": accounts, "characters": characters,
                "districts": list(self.districts.keys())}


# --------------------------------------------------------------------------------------------------
# HTTP
# --------------------------------------------------------------------------------------------------

class Request:
    def __init__(self, handler: "Handler", params: dict, body: dict, query: dict):
        self.headers = handler.headers
        self.params = params
        self.body = body
        self.query = query
        self.client_ip = handler.client_address[0]


def _q(req: Request, key: str) -> str | None:
    values = req.query.get(key)
    return values[0] if values else None


ROUTES = [
    ("GET", r"/v1/health", lambda b, r: {"ok": True, "time": now()}),
    ("GET", r"/v1/status", lambda b, r: b.status()),
    ("POST", r"/v1/auth/register", lambda b, r: b.register(r.body)),
    ("POST", r"/v1/auth/login", lambda b, r: b.login(r.body)),
    ("POST", r"/v1/auth/logout", lambda b, r: b.logout(r.headers)),
    ("GET", r"/v1/auth/me", lambda b, r: b.me(b.authenticate(r.headers))),
    ("GET", r"/v1/characters", lambda b, r: b.list_characters(b.authenticate(r.headers))),
    ("POST", r"/v1/characters", lambda b, r: b.create_character(b.authenticate(r.headers), r.body)),
    ("POST", r"/v1/characters/(?P<cid>[A-Za-z0-9_]+)/appearance",
     lambda b, r: b.update_appearance(b.authenticate(r.headers), r.params["cid"], r.body)),
    ("DELETE", r"/v1/characters/(?P<cid>[A-Za-z0-9_]+)",
     lambda b, r: b.delete_character(b.authenticate(r.headers), r.params["cid"])),
    ("GET", r"/v1/districts", lambda b, r: b.list_districts(b.authenticate(r.headers), _q(r, "characterId"))),
    ("POST", r"/v1/districts/join", lambda b, r: b.join_district(b.authenticate(r.headers), r.body)),
    ("POST", r"/v1/servers/register", lambda b, r: b.server_register(r.headers, r.body, r.client_ip)),
    ("POST", r"/v1/servers/heartbeat", lambda b, r: b.server_heartbeat(r.headers, r.body)),
    ("POST", r"/v1/servers/unregister", lambda b, r: b.server_unregister(r.headers, r.body)),
    ("POST", r"/v1/servers/redeem", lambda b, r: b.server_redeem(r.headers, r.body)),
    ("POST", r"/v1/servers/characters/update", lambda b, r: b.server_update_character(r.headers, r.body)),
    ("POST", r"/v1/servers/commands/ack", lambda b, r: b.server_ack_commands(r.headers, r.body)),
    ("POST", r"/v1/servers/characters/get", lambda b, r: b.server_get_character(r.headers, r.body)),
    ("GET", r"/v1/wallet", lambda b, r: b.wallet(b.authenticate(r.headers))),
    ("GET", r"/v1/characters/(?P<cid>[A-Za-z0-9_]+)/inventory",
     lambda b, r: b.character_inventory(b.authenticate(r.headers), r.params["cid"])),
    ("GET", r"/v1/mail", lambda b, r: b.mailbox(b.authenticate(r.headers))),
    ("POST", r"/v1/mail/(?P<mid>[A-Za-z0-9_]+)/claim",
     lambda b, r: b.claim_mail(b.authenticate(r.headers), r.params["mid"], r.body)),
    ("POST", r"/v1/dev/characters/set", lambda b, r: b.dev_set_character(b.authenticate(r.headers), r.body)),
]
COMPILED_ROUTES = [(m, re.compile(p), fn) for m, p, fn in ROUTES]


class Handler(BaseHTTPRequestHandler):
    backend: Backend = None  # set by make_server
    routes = COMPILED_ROUTES
    quiet = False
    static_dir: str | None = None       # admin listener: serves the cockpit UI
    allowed_ips: list[str] = []         # admin listener: optional IP allowlist
    allowed_hosts: list[str] = []       # admin listener: accepted Host headers
    security_headers = False
    server_version = "BytesBackend/1.0"
    protocol_version = "HTTP/1.1"

    STATIC_TYPES = {".html": "text/html; charset=utf-8", ".js": "text/javascript; charset=utf-8",
                    ".css": "text/css; charset=utf-8", ".svg": "image/svg+xml", ".png": "image/png"}

    def log_message(self, fmt, *args):
        if not self.quiet:
            sys.stderr.write("[http] %s %s\n" % (self.address_string(), fmt % args))

    def _headers(self) -> None:
        if self.security_headers:
            self.send_header("Content-Security-Policy",
                             "default-src 'self'; img-src 'self' data:; style-src 'self'; script-src 'self'; "
                             "connect-src 'self'; frame-ancestors 'none'; base-uri 'none'; form-action 'none'")
            self.send_header("X-Content-Type-Options", "nosniff")
            self.send_header("X-Frame-Options", "DENY")
            self.send_header("Referrer-Policy", "no-referrer")
            self.send_header("Cache-Control", "no-store")

    def _send(self, status: int, payload: dict) -> None:
        data = json.dumps(payload).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json")
        self.send_header("Content-Length", str(len(data)))
        self._headers()
        self.end_headers()
        self.wfile.write(data)

    def _serve_static(self, path: str) -> bool:
        if not self.static_dir:
            return False
        name = "index.html" if path in ("/", "") else path.lstrip("/")
        full = os.path.normpath(os.path.join(self.static_dir, name))
        ext = os.path.splitext(full)[1]
        if not full.startswith(os.path.normpath(self.static_dir) + os.sep) or ext not in self.STATIC_TYPES \
                or not os.path.isfile(full):
            return False
        with open(full, "rb") as f:
            data = f.read()
        self.send_response(200)
        self.send_header("Content-Type", self.STATIC_TYPES[ext])
        self.send_header("Content-Length", str(len(data)))
        self._headers()
        self.end_headers()
        self.wfile.write(data)
        return True

    def _dispatch(self, method: str) -> None:
        parsed = urlparse(self.path)
        if self.allowed_ips and self.client_address[0] not in self.allowed_ips:
            self._send(403, {"error": "Forbidden", "reasons": []})
            return
        if self.allowed_hosts and (self.headers.get("Host") or "").lower() not in self.allowed_hosts:
            # Blocks DNS-rebinding pages in a staff member's browser from talking to the localhost cockpit.
            self._send(403, {"error": "Unexpected Host header", "reasons": []})
            return
        length = int(self.headers.get("Content-Length") or 0)
        if length > 1_000_000:
            self._send(413, {"error": "Request too large", "reasons": []})
            return
        raw = self.rfile.read(length) if length > 0 else b""
        try:
            if method == "GET" and not parsed.path.startswith(("/v1/", "/admin/")) and self._serve_static(parsed.path):
                return
            try:
                body = json.loads(raw.decode("utf-8")) if raw.strip() else {}
            except (ValueError, UnicodeDecodeError):
                raise ApiError(400, "Request body is not valid JSON")
            if not isinstance(body, dict):
                raise ApiError(400, "Request body must be a JSON object")
            path_matched = False
            for route_method, pattern, fn in self.routes:
                match = pattern.fullmatch(parsed.path)
                if not match:
                    continue
                path_matched = True
                if route_method != method:
                    continue
                result = fn(self.backend, Request(self, match.groupdict(), body, parse_qs(parsed.query)))
                self._send(200, result)
                return
            raise ApiError(405 if path_matched else 404, f"No route for {method} {parsed.path}")
        except ApiError as e:
            self._send(e.status, {"error": e.message, "reasons": e.reasons})
        except (staff_rules.StaffError, economy_rules.EconomyError, orchestration.DeployError) as e:
            self._send(e.status, {"error": e.message, "reasons": []})
        except Exception as e:  # keep the server alive, but make the failure loud
            import traceback
            traceback.print_exc()
            self._send(500, {"error": "Internal error (see backend log)", "reasons": []})

    def do_GET(self):
        self._dispatch("GET")

    def do_POST(self):
        self._dispatch("POST")

    def do_DELETE(self):
        self._dispatch("DELETE")


def make_server(backend: Backend, host: str, port: int, quiet: bool = False) -> ThreadingHTTPServer:
    handler = type("BoundHandler", (Handler,), {"backend": backend, "quiet": quiet})
    server = ThreadingHTTPServer((host, port), handler)
    server.daemon_threads = True
    return server


def make_admin_server(backend: Backend, host: str, port: int, quiet: bool = False) -> ThreadingHTTPServer:
    """Root cockpit listener: admin API + UI only (no game routes), security headers, optional IP allowlist."""
    import admin
    bound_port = port
    server = ThreadingHTTPServer((host, port), Handler)  # bind first so port 0 (tests) resolves
    bound_port = server.server_address[1]
    hosts = {f"{h}:{bound_port}" for h in ("127.0.0.1", "localhost", "[::1]", host)}
    hosts |= {str(x).lower() for x in (backend.cfg.get("adminAllowedHosts") or [])}
    server.RequestHandlerClass = type("AdminHandler", (Handler,), {
        "allowed_hosts": sorted(hosts),
        "backend": backend, "quiet": quiet, "routes": admin.COMPILED_ADMIN_ROUTES,
        "static_dir": os.path.join(HERE, "cockpit"), "allowed_ips": list(backend.cfg.get("adminAllowedIps") or []),
        "security_headers": True,
    })
    server.daemon_threads = True
    return server


# --------------------------------------------------------------------------------------------------
# CLI
# --------------------------------------------------------------------------------------------------

def _admin(backend: Backend, args) -> int:
    db = backend.db
    if args.admin_cmd == "list":
        for acc in db.execute("SELECT * FROM accounts ORDER BY created_at").fetchall():
            print(f"{acc['username']}  ({acc['id']})  flags={json.loads(acc['flags'])}  "
                  f"slots={backend._max_characters(acc)}")
            for c in db.execute("SELECT * FROM characters WHERE account_id = ? ORDER BY created_at", (acc["id"],)):
                online = f"  online in {c['online_instance']}" if c["online_instance"] else ""
                print(f"    {c['name']:<16} {c['faction']:<9} rank {c['rank']:<3} {c['threat']:<6} "
                      f"${c['money']}{online}")
    elif args.admin_cmd == "set-stats":
        c = backend.set_character_stats(args.character, rank=args.rank, threat=args.threat, money=args.money,
                                        standing=args.standing)["character"]
        _cli_audit(backend, "cli.set_stats", "character", c["characterId"],
                   {"rank": args.rank, "threat": args.threat, "money": args.money, "standing": args.standing})
        print(f"{c['name']}: rank {c['rank']} ({c['standing']} standing), threat {c['threat']}, ${c['money']}")
    elif args.admin_cmd in ("flag", "unflag"):
        row = db.execute("SELECT * FROM accounts WHERE username = ?", (args.username,)).fetchone()
        if not row:
            print(f"Unknown account '{args.username}'")
            return 1
        flags = [f for f in json.loads(row["flags"]) if f.lower() != args.flag.lower()]
        if args.admin_cmd == "flag":
            flags.append(args.flag)
        db.execute("UPDATE accounts SET flags = ? WHERE id = ?", (json.dumps(flags), row["id"]))
        db.commit()
        _cli_audit(backend, f"cli.{args.admin_cmd}", "account", row["id"], {"flag": args.flag})
        print(f"{row['username']} flags: {flags}")
    elif args.admin_cmd == "slots":
        db.execute("UPDATE accounts SET max_characters = ? WHERE username = ?", (args.count, args.username))
        db.commit()
        _cli_audit(backend, "cli.slots", "account", args.username, {"count": args.count})
        print(f"{args.username} may now have {args.count} characters")
    return 0


DEFAULT_SERVER_KEY = "dev-server-key-change-me"
LOOPBACK = ("127.0.0.1", "localhost", "::1")


def security_warnings(cfg: dict) -> list[str]:
    warnings = []
    if cfg.get("devMode"):
        warnings.append("devMode is on: players can set their own rank/threat/money through /v1/dev (bypasses staff control)")
    if cfg.get("serverKey") in ("", DEFAULT_SERVER_KEY):
        warnings.append("serverKey is the public default: anyone who knows it can register fake servers and change characters")
    if not cfg.get("staffRequire2FA", True):
        warnings.append("staffRequire2FA is off")
    return warnings


def _cli_audit(backend: Backend, action: str, target_type: str, target_id: str, details: dict | None = None) -> None:
    import getpass
    try:
        who = getpass.getuser()
    except Exception:
        who = "unknown"
    backend.staff.audit({"staffId": "", "username": f"cli:{who}"[:32]}, action, target_type, target_id,
                        "command line on the server machine", details or {})


def _staff_cli(backend: Backend, args) -> int:
    import getpass
    service = backend.staff
    if args.staff_cmd == "create":
        password = args.password or getpass.getpass(f"Password for {args.username} (12+ chars): ")
        try:
            created, secret = service.create(args.username, password, args.role, "cli", with_2fa=not args.no_2fa)
        except staff_rules.StaffError as e:
            print(e.message)
            return 1
        _cli_audit(backend, "staff.created", "staff", created["staffId"], {"username": created["username"], "role": args.role})
        print(f"Created {args.role} '{created['username']}'.")
        if secret:
            print("Add this to an authenticator app (Google Authenticator, 1Password, Authy...):")
            print(f"  secret: {secret}")
            print(f"  uri:    {staff_rules.totp_uri(secret, created['username'])}")
            print(f"  current code (to check your app): {staff_rules.totp_code(secret)}")
        elif service.require_2fa:
            print("WARNING: staffRequire2FA is on, so this account can't sign in until 2FA is reset.")
    elif args.staff_cmd == "list":
        for row in backend.db.execute("SELECT * FROM staff ORDER BY created_at"):
            print(f"{row['username']:<20} {row['role']:<11} 2FA={'yes' if row['totp_secret'] else 'no ':<3} "
                  f"{'DISABLED' if row['disabled'] else ''}")
    elif args.staff_cmd == "reset-2fa":
        secret = staff_rules.new_totp_secret()
        row = backend.db.execute("SELECT id FROM staff WHERE username = ?", (args.username,)).fetchone()
        if not row:
            print(f"Unknown staff '{args.username}'")
            return 1
        backend.db.execute("UPDATE staff SET totp_secret = ?, totp_last_counter = -1 WHERE id = ?", (secret, row["id"]))
        backend.db.commit()
        service.revoke_sessions(row["id"])
        _cli_audit(backend, "staff.2fa_reset", "staff", row["id"], {"username": args.username})
        print(f"New secret for {args.username}: {secret}\n  uri: {staff_rules.totp_uri(secret, args.username)}")
    elif args.staff_cmd in ("disable", "enable"):
        row = backend.db.execute("SELECT id FROM staff WHERE username = ?", (args.username,)).fetchone()
        if not row:
            print(f"Unknown staff '{args.username}'")
            return 1
        backend.db.execute("UPDATE staff SET disabled = ? WHERE id = ?", (1 if args.staff_cmd == "disable" else 0, row["id"]))
        backend.db.commit()
        if args.staff_cmd == "disable":
            service.revoke_sessions(row["id"])
        _cli_audit(backend, f"staff.{args.staff_cmd}d", "staff", row["id"], {"username": args.username})
        print(f"{args.username}: {args.staff_cmd}d")
    elif args.staff_cmd == "verify-audit":
        print(json.dumps(service.verify_audit_chain(), indent=2))
    return 0


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description="Project Bytes backend (accounts, characters, districts)")
    parser.add_argument("--config", default=DEFAULT_CONFIG_PATH)
    parser.add_argument("--host")
    parser.add_argument("--port", type=int)
    parser.add_argument("--reset", action="store_true", help="delete the database before starting")
    parser.add_argument("--quiet", action="store_true", help="don't log every HTTP request")
    parser.add_argument("--allow-insecure", action="store_true",
                        help="start on a non-loopback address even with devMode / the default server key")
    sub = parser.add_subparsers(dest="cmd")

    admin = sub.add_parser("admin", help="offline admin commands against the database")
    admin_sub = admin.add_subparsers(dest="admin_cmd", required=True)
    admin_sub.add_parser("list", help="list accounts and characters")
    s = admin_sub.add_parser("set-stats", help="set a character's rank/threat/money (name or id)")
    s.add_argument("character")
    s.add_argument("--rank", type=int)
    s.add_argument("--standing", type=int)
    s.add_argument("--threat", choices=[t.lower() for t in THREATS] + THREATS)
    s.add_argument("--money", type=int)
    for name in ("flag", "unflag"):
        f = admin_sub.add_parser(name, help=f"{'add' if name == 'flag' else 'remove'} an account flag")
        f.add_argument("username")
        f.add_argument("flag")
    sl = admin_sub.add_parser("slots", help="override an account's character slot count")
    sl.add_argument("username")
    sl.add_argument("count", type=int)

    st = sub.add_parser("staff", help="root cockpit staff accounts (run on the server machine)")
    st_sub = st.add_subparsers(dest="staff_cmd", required=True)
    sc = st_sub.add_parser("create", help="create a staff account (the first one should be an owner)")
    sc.add_argument("username")
    sc.add_argument("--role", default="owner")
    sc.add_argument("--password", help="omit to be prompted")
    sc.add_argument("--no-2fa", action="store_true", help="only if staffRequire2FA is false (local dev)")
    st_sub.add_parser("list")
    for name in ("reset-2fa", "disable", "enable"):
        st_sub.add_parser(name).add_argument("username")
    st_sub.add_parser("verify-audit", help="check the audit log hash chain")

    args = parser.parse_args(argv)
    cfg = load_config(args.config)
    if args.host:
        cfg["host"] = args.host
    if args.port:
        cfg["port"] = args.port

    if args.reset and cfg["database"] != ":memory:" and os.path.exists(cfg["database"]):
        os.remove(cfg["database"])
        print(f"[backend] deleted {cfg['database']}")

    try:
        backend = Backend(cfg)
    except ApiError as e:
        print(f"[backend] config error: {e.message}")
        return 1

    if args.cmd == "admin":
        try:
            return _admin(backend, args)
        except ApiError as e:
            print(e.message)
            return 1
    if args.cmd == "staff":
        return _staff_cli(backend, args)

    warnings = security_warnings(cfg)
    for warning in warnings:
        print(f"[backend] SECURITY WARNING: {warning}", flush=True)
    exposed = cfg["host"] not in LOOPBACK or (cfg.get("adminPort") and cfg.get("adminHost") not in LOOPBACK)
    if warnings and exposed and not args.allow_insecure:
        print("[backend] Refusing to listen on a non-loopback address with the settings above. Fix them "
              "(devMode false, a secret serverKey, staffRequire2FA true) or pass --allow-insecure.", flush=True)
        return 2

    httpd = make_server(backend, cfg["host"], cfg["port"], quiet=args.quiet)
    print(f"[backend] Project Bytes backend listening on http://{cfg['host']}:{cfg['port']}  "
          f"(db: {cfg['database']}, devMode={cfg['devMode']})", flush=True)
    print(f"[backend] districts: {', '.join(backend.districts)}", flush=True)
    admin_httpd = None
    if cfg.get("adminPort"):
        admin_httpd = make_admin_server(backend, cfg["adminHost"], cfg["adminPort"], quiet=args.quiet)
        threading.Thread(target=admin_httpd.serve_forever, daemon=True).start()
        staff_count = backend.db.execute("SELECT COUNT(*) FROM staff").fetchone()[0]
        print(f"[backend] root cockpit on http://{cfg['adminHost']}:{cfg['adminPort']}/ "
              f"({staff_count} staff account(s){'' if staff_count else ' - create one: python Backend/server.py staff create <name>'})",
              flush=True)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()
        if admin_httpd:
            admin_httpd.shutdown()
        backend.orchestrator.shutdown_all()
    return 0


if __name__ == "__main__":
    # Run through the importable module so admin.py (which imports `server`) shares the same classes.
    sys.path.insert(0, HERE)
    import server as _server_module
    sys.exit(_server_module.main())
