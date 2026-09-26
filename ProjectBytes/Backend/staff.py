"""
Staff identity for the root cockpit: accounts separate from player accounts, role-based permissions,
TOTP two-factor, login lockout, short sessions, and a hash-chained (tamper-evident) audit log.

Nothing here is reachable from the public game API: the cockpit routes are only mounted on the admin
listener (see admin.py), which binds to 127.0.0.1 by default.
"""
from __future__ import annotations

import base64
import hashlib
import hmac
import json
import secrets
import struct
import threading
import time
import urllib.parse

STAFF_SCHEMA = """
CREATE TABLE IF NOT EXISTS staff (
    id TEXT PRIMARY KEY,
    username TEXT NOT NULL UNIQUE COLLATE NOCASE,
    pw_salt TEXT NOT NULL,
    pw_hash TEXT NOT NULL,
    role TEXT NOT NULL,
    totp_secret TEXT NOT NULL DEFAULT '',
    disabled INTEGER NOT NULL DEFAULT 0,
    created_at INTEGER NOT NULL,
    created_by TEXT NOT NULL DEFAULT '',
    last_login_at INTEGER
);
CREATE TABLE IF NOT EXISTS staff_sessions (
    token_hash TEXT PRIMARY KEY,
    staff_id TEXT NOT NULL REFERENCES staff(id) ON DELETE CASCADE,
    created_at INTEGER NOT NULL,
    expires_at INTEGER NOT NULL,
    last_seen_at INTEGER NOT NULL,
    ip TEXT NOT NULL DEFAULT ''
);
CREATE TABLE IF NOT EXISTS audit_log (
    seq INTEGER PRIMARY KEY AUTOINCREMENT,
    at INTEGER NOT NULL,
    staff_id TEXT NOT NULL,
    staff_name TEXT NOT NULL,
    action TEXT NOT NULL,
    target_type TEXT NOT NULL DEFAULT '',
    target_id TEXT NOT NULL DEFAULT '',
    reason TEXT NOT NULL DEFAULT '',
    details TEXT NOT NULL DEFAULT '{}',
    ip TEXT NOT NULL DEFAULT '',
    prev_hash TEXT NOT NULL,
    hash TEXT NOT NULL
);
"""

ALL_PERMISSIONS = [
    "view",               # read dashboards, servers, players
    "deploy",             # spin up / stop instances
    "server.command",     # broadcast, message, shutdown, refresh
    "server.exec",        # raw console commands on district servers
    "player.kick",
    "player.ban",
    "player.sessions",    # force-logout a player
    "player.flags",       # account flags (tester, premium...)
    "economy.grant",      # give currency/items to a player directly
    "economy.gift",       # mail a gift to one player
    "economy.gift_all",   # gift every player
    "audit.read",
    "staff.manage",       # create/disable staff, change roles
]

DEFAULT_ROLES = {
    "owner": ["*"],
    "admin": ["view", "deploy", "server.command", "player.kick", "player.ban", "player.sessions", "player.flags",
              "economy.grant", "economy.gift", "economy.gift_all", "audit.read"],
    "gamemaster": ["view", "server.command", "player.kick", "player.ban", "player.sessions", "economy.grant",
                   "economy.gift", "audit.read"],
    "moderator": ["view", "player.kick", "player.ban", "audit.read"],
    "support": ["view", "economy.gift"],
}

# Per-role caps on top of permissions. Missing = unlimited (still bounded by the global caps in admin.py).
DEFAULT_ROLE_LIMITS = {
    "gamemaster": {"maxBanHours": 720, "maxCurrencyAmount": 100000, "maxItemQuantity": 10},
    "moderator": {"maxBanHours": 72},
    "support": {"maxCurrencyAmount": 10000, "maxItemQuantity": 1},
}

GENESIS_HASH = "0" * 64


class StaffError(Exception):
    def __init__(self, status: int, message: str):
        super().__init__(message)
        self.status = status
        self.message = message


# --------------------------------------------------------------------------------------------------
# TOTP (RFC 6238, SHA-1, 30 s, 6 digits) - works with any authenticator app
# --------------------------------------------------------------------------------------------------

def new_totp_secret() -> str:
    return base64.b32encode(secrets.token_bytes(20)).decode("ascii").rstrip("=")


def totp_code(secret: str, at: float | None = None, step: int = 30, digits: int = 6) -> str:
    key = base64.b32decode(secret + "=" * (-len(secret) % 8), casefold=True)
    counter = int((time.time() if at is None else at) // step)
    digest = hmac.new(key, struct.pack(">Q", counter), hashlib.sha1).digest()
    offset = digest[-1] & 0x0F
    value = struct.unpack(">I", digest[offset:offset + 4])[0] & 0x7FFFFFFF
    return str(value % (10 ** digits)).zfill(digits)


def verify_totp(secret: str, code: str, at: float | None = None, window: int = 1) -> bool:
    code = (code or "").strip().replace(" ", "")
    if not secret or not code.isdigit():
        return False
    moment = time.time() if at is None else at
    return any(hmac.compare_digest(totp_code(secret, moment + drift * 30), code) for drift in range(-window, window + 1))


def totp_uri(secret: str, username: str, issuer: str = "Project Bytes Cockpit") -> str:
    label = urllib.parse.quote(f"{issuer}:{username}")
    return f"otpauth://totp/{label}?secret={secret}&issuer={urllib.parse.quote(issuer)}&digits=6&period=30"


# --------------------------------------------------------------------------------------------------
# Staff service
# --------------------------------------------------------------------------------------------------

class StaffService:
    def __init__(self, db, lock: threading.RLock, cfg: dict):
        self.db = db
        self.lock = lock
        self.roles: dict[str, list[str]] = cfg.get("staffRoles") or DEFAULT_ROLES
        self.role_limits: dict[str, dict] = cfg.get("staffRoleLimits") or DEFAULT_ROLE_LIMITS
        self.require_2fa = bool(cfg.get("staffRequire2FA", True))
        self.session_ttl = int(cfg.get("staffSessionTtlSeconds", 8 * 3600))
        self.idle_timeout = int(cfg.get("staffIdleTimeoutSeconds", 30 * 60))
        self.iterations = int(cfg.get("passwordIterations", 120_000))
        self.max_failures = int(cfg.get("staffMaxLoginFailures", 5))
        self.lockout_seconds = int(cfg.get("staffLockoutSeconds", 600))
        self._failures: dict[str, list[float]] = {}
        db.executescript(STAFF_SCHEMA)

    # -- passwords / roles --------------------------------------------------------------------------

    def _hash(self, password: str, salt: str) -> str:
        return hashlib.pbkdf2_hmac("sha256", password.encode("utf-8"), bytes.fromhex(salt), self.iterations).hex()

    @staticmethod
    def _token_hash(token: str) -> str:
        return hashlib.sha256(token.encode("utf-8")).hexdigest()

    def permissions_for(self, role: str) -> list[str]:
        granted = self.roles.get(role, [])
        return list(ALL_PERMISSIONS) if "*" in granted else [p for p in granted if p in ALL_PERMISSIONS]

    def limits_for(self, role: str) -> dict:
        return dict(self.role_limits.get(role, {}))

    def staff_json(self, row) -> dict:
        return {
            "staffId": row["id"],
            "username": row["username"],
            "role": row["role"],
            "permissions": self.permissions_for(row["role"]),
            "limits": self.limits_for(row["role"]),
            "twoFactor": bool(row["totp_secret"]),
            "disabled": bool(row["disabled"]),
            "createdAt": row["created_at"],
            "createdBy": row["created_by"],
            "lastLoginAt": row["last_login_at"],
        }

    @staticmethod
    def validate_password(password: str) -> None:
        if len(password) < 12:
            raise StaffError(400, "Staff passwords must be at least 12 characters")

    def create(self, username: str, password: str, role: str, created_by: str, with_2fa: bool = True) -> tuple[dict, str]:
        """Returns (staff json, totp secret or '')."""
        username = (username or "").strip()
        if not 3 <= len(username) <= 32 or not username.replace("_", "").replace("-", "").replace(".", "").isalnum():
            raise StaffError(400, "Staff usernames must be 3-32 characters: letters, digits, '.', '_' or '-'")
        if role not in self.roles:
            raise StaffError(400, f"Unknown role '{role}'. Roles: {', '.join(self.roles)}")
        self.validate_password(password)
        salt = secrets.token_hex(16)
        secret = new_totp_secret() if with_2fa else ""
        staff_id = "stf_" + secrets.token_hex(8)
        with self.lock:
            try:
                self.db.execute(
                    "INSERT INTO staff (id, username, pw_salt, pw_hash, role, totp_secret, created_at, created_by) "
                    "VALUES (?,?,?,?,?,?,?,?)",
                    (staff_id, username, salt, self._hash(password, salt), role, secret, int(time.time()), created_by))
                self.db.commit()
            except Exception as e:  # sqlite3.IntegrityError
                if "UNIQUE" in str(e):
                    raise StaffError(409, "That staff username already exists")
                raise
            row = self.db.execute("SELECT * FROM staff WHERE id = ?", (staff_id,)).fetchone()
        return self.staff_json(row), secret

    def owner_count(self) -> int:
        owner_roles = [r for r, perms in self.roles.items() if "*" in perms]
        if not owner_roles:
            return 0
        marks = ",".join("?" for _ in owner_roles)
        return self.db.execute(f"SELECT COUNT(*) FROM staff WHERE disabled = 0 AND role IN ({marks})", owner_roles).fetchone()[0]

    # -- login / sessions ---------------------------------------------------------------------------

    def _locked(self, key: str) -> bool:
        cutoff = time.time() - self.lockout_seconds
        recent = [t for t in self._failures.get(key, []) if t > cutoff]
        self._failures[key] = recent
        return len(recent) >= self.max_failures

    def login(self, username: str, password: str, code: str, ip: str) -> dict:
        key = f"{(username or '').lower()}|{ip}"
        with self.lock:
            if self._locked(key):
                raise StaffError(429, f"Too many failed attempts; try again in {self.lockout_seconds // 60} minutes")
            row = self.db.execute("SELECT * FROM staff WHERE username = ?", ((username or "").strip(),)).fetchone()
            ok = bool(row) and hmac.compare_digest(self._hash(password or "", row["pw_salt"]), row["pw_hash"])
            if ok and row["disabled"]:
                ok = False
            if ok and (row["totp_secret"] or self.require_2fa):
                ok = bool(row["totp_secret"]) and verify_totp(row["totp_secret"], code)
            if not ok:
                self._failures.setdefault(key, []).append(time.time())
                # One generic message: don't reveal which factor failed or whether the user exists.
                raise StaffError(401, "Invalid credentials")
            self._failures.pop(key, None)
            token = secrets.token_urlsafe(32)
            moment = int(time.time())
            self.db.execute("DELETE FROM staff_sessions WHERE expires_at < ?", (moment,))
            self.db.execute("INSERT INTO staff_sessions (token_hash, staff_id, created_at, expires_at, last_seen_at, ip) "
                            "VALUES (?,?,?,?,?,?)",
                            (self._token_hash(token), row["id"], moment, moment + self.session_ttl, moment, ip))
            self.db.execute("UPDATE staff SET last_login_at = ? WHERE id = ?", (moment, row["id"]))
            self.db.commit()
        return {"token": token, "staff": self.staff_json(row), "expiresAt": moment + self.session_ttl}

    def authenticate(self, headers) -> dict:
        auth = headers.get("Authorization") or ""
        if not auth.startswith("Bearer "):
            raise StaffError(401, "Not signed in")
        token_hash = self._token_hash(auth[len("Bearer "):].strip())
        moment = int(time.time())
        with self.lock:
            row = self.db.execute(
                "SELECT s.*, ss.last_seen_at AS seen, ss.expires_at AS exp FROM staff_sessions ss "
                "JOIN staff s ON s.id = ss.staff_id WHERE ss.token_hash = ?", (token_hash,)).fetchone()
            if not row or row["disabled"] or row["exp"] < moment or moment - row["seen"] > self.idle_timeout:
                if row:
                    self.db.execute("DELETE FROM staff_sessions WHERE token_hash = ?", (token_hash,))
                    self.db.commit()
                raise StaffError(401, "Session expired; sign in again")
            self.db.execute("UPDATE staff_sessions SET last_seen_at = ? WHERE token_hash = ?", (moment, token_hash))
            self.db.commit()
        return self.staff_json(row)

    def logout(self, headers) -> None:
        auth = headers.get("Authorization") or ""
        if auth.startswith("Bearer "):
            with self.lock:
                self.db.execute("DELETE FROM staff_sessions WHERE token_hash = ?", (self._token_hash(auth[7:].strip()),))
                self.db.commit()

    def revoke_sessions(self, staff_id: str) -> None:
        with self.lock:
            self.db.execute("DELETE FROM staff_sessions WHERE staff_id = ?", (staff_id,))
            self.db.commit()

    # -- audit --------------------------------------------------------------------------------------

    @staticmethod
    def _entry_hash(prev_hash: str, entry: dict) -> str:
        canonical = json.dumps(entry, sort_keys=True, separators=(",", ":"))
        return hashlib.sha256((prev_hash + canonical).encode("utf-8")).hexdigest()

    def audit(self, staff: dict, action: str, target_type: str = "", target_id: str = "", reason: str = "",
              details: dict | None = None, ip: str = "") -> dict:
        """Append-only, hash-chained. There is deliberately no API to edit or delete entries."""
        with self.lock:
            last = self.db.execute("SELECT hash FROM audit_log ORDER BY seq DESC LIMIT 1").fetchone()
            prev_hash = last["hash"] if last else GENESIS_HASH
            entry = {
                "at": int(time.time()),
                "staffId": staff.get("staffId", ""),
                "staffName": staff.get("username", ""),
                "action": action,
                "targetType": target_type,
                "targetId": target_id,
                "reason": reason,
                "details": details or {},
                "ip": ip,
            }
            digest = self._entry_hash(prev_hash, entry)
            cur = self.db.execute(
                "INSERT INTO audit_log (at, staff_id, staff_name, action, target_type, target_id, reason, details, ip, "
                "prev_hash, hash) VALUES (?,?,?,?,?,?,?,?,?,?,?)",
                (entry["at"], entry["staffId"], entry["staffName"], action, target_type, target_id, reason,
                 json.dumps(entry["details"], sort_keys=True), ip, prev_hash, digest))
            self.db.commit()
            return dict(entry, seq=cur.lastrowid, hash=digest)

    @staticmethod
    def audit_row_json(row) -> dict:
        return {
            "seq": row["seq"], "at": row["at"], "staffId": row["staff_id"], "staffName": row["staff_name"],
            "action": row["action"], "targetType": row["target_type"], "targetId": row["target_id"],
            "reason": row["reason"], "details": json.loads(row["details"]), "ip": row["ip"], "hash": row["hash"],
        }

    def verify_audit_chain(self) -> dict:
        with self.lock:
            rows = self.db.execute("SELECT * FROM audit_log ORDER BY seq").fetchall()
        prev = GENESIS_HASH
        for row in rows:
            entry = {
                "at": row["at"], "staffId": row["staff_id"], "staffName": row["staff_name"], "action": row["action"],
                "targetType": row["target_type"], "targetId": row["target_id"], "reason": row["reason"],
                "details": json.loads(row["details"]), "ip": row["ip"],
            }
            if row["prev_hash"] != prev or self._entry_hash(prev, entry) != row["hash"]:
                return {"ok": False, "entries": len(rows), "brokenAt": row["seq"]}
            prev = row["hash"]
        return {"ok": True, "entries": len(rows), "head": prev}
