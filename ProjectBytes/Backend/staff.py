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
import os
import re
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
    last_login_at INTEGER,
    totp_last_counter INTEGER NOT NULL DEFAULT -1
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
    "player.unban",       # lift bans (separate so moderators can't undo owners' bans)
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
    "admin": ["view", "deploy", "server.command", "player.kick", "player.ban", "player.unban", "player.sessions", "player.flags",
              "economy.grant", "economy.gift", "economy.gift_all", "audit.read"],
    "gamemaster": ["view", "server.command", "player.kick", "player.ban", "player.unban", "player.sessions", "economy.grant",
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


def verify_totp(secret: str, code: str, at: float | None = None, window: int = 1, min_counter: int = -1) -> int:
    """Returns the matched time-step counter, or -1. Counters <= min_counter are rejected (no replay)."""
    code = (code or "").strip().replace(" ", "")
    # ASCII digits only: str.isdigit() also accepts other scripts' digits, which made compare_digest raise.
    if not secret or not re.fullmatch(r"[0-9]{6}", code):
        return -1
    moment = time.time() if at is None else at
    base = int(moment // 30)
    for drift in range(-window, window + 1):
        counter = base + drift
        if counter > min_counter and hmac.compare_digest(totp_code(secret, counter * 30).encode(), code.encode()):
            return counter
    return -1


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
        columns = {row[1] for row in db.execute("PRAGMA table_info(staff)")}
        if "totp_last_counter" not in columns:
            db.execute("ALTER TABLE staff ADD COLUMN totp_last_counter INTEGER NOT NULL DEFAULT -1")
            db.commit()
        # Audit entries are HMAC'd with a key that lives OUTSIDE the database, so someone who can write the DB
        # can't quietly rewrite history and recompute the chain.
        self.audit_key = self._load_audit_key(cfg)
        # Burn the same PBKDF2 time for unknown usernames (no timing oracle for which staff accounts exist).
        self._dummy_salt = secrets.token_hex(16)

    @staticmethod
    def _load_audit_key(cfg: dict) -> bytes:
        if os.environ.get("BYTES_AUDIT_KEY"):
            return os.environ["BYTES_AUDIT_KEY"].encode("utf-8")
        if cfg.get("auditKey"):
            return str(cfg["auditKey"]).encode("utf-8")
        database = cfg.get("database", ":memory:")
        if database == ":memory:":
            return secrets.token_bytes(32)
        path = os.path.join(os.path.dirname(database), "audit.key")
        if not os.path.exists(path):
            fd = os.open(path, os.O_WRONLY | os.O_CREAT | os.O_EXCL, 0o600)
            with os.fdopen(fd, "w") as f:
                f.write(secrets.token_hex(32))
        with open(path, "r", encoding="utf-8") as f:
            return f.read().strip().encode("utf-8")

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

    @staticmethod
    def normalize_username(username) -> str:
        return str(username or "").strip().lower()[:64]

    def _prune_failures(self) -> None:
        cutoff = time.time() - self.lockout_seconds
        for key in list(self._failures):
            recent = [t for t in self._failures[key] if t > cutoff]
            if recent:
                self._failures[key] = recent
            else:
                del self._failures[key]

    def _locked(self, *keys: str) -> bool:
        self._prune_failures()
        return any(len(self._failures.get(k, [])) >= self.max_failures for k in keys)

    def _record_failure(self, *keys: str) -> None:
        for key in keys:
            self._failures.setdefault(key, []).append(time.time())

    def login(self, username: str, password: str, code: str, ip: str) -> dict:
        name = self.normalize_username(username)
        # Two counters: per account (any IP) and per IP (any account). Padding/case can't make a fresh key.
        keys = (f"user|{name}", f"ip|{ip}")
        with self.lock:
            if self._locked(*keys):
                raise StaffError(429, f"Too many failed attempts; try again in {self.lockout_seconds // 60} minutes")
            ok = False
            row = None
            try:
                row = self.db.execute("SELECT * FROM staff WHERE username = ?", (name,)).fetchone() if name else None
                if row is None:
                    self._hash(password or "", self._dummy_salt)  # same cost as a real check
                else:
                    ok = hmac.compare_digest(self._hash(password or "", row["pw_salt"]).encode(), row["pw_hash"].encode())
                if ok and row["disabled"]:
                    ok = False
                counter = -1
                if ok and (row["totp_secret"] or self.require_2fa):
                    counter = verify_totp(row["totp_secret"], code, min_counter=row["totp_last_counter"]) \
                        if row["totp_secret"] else -1
                    ok = counter >= 0
            except Exception:
                ok = False  # any malformed input is just a failed attempt (never a distinguishable error)
            if not ok:
                self._record_failure(*keys)
                # One generic message: don't reveal which factor failed or whether the user exists.
                raise StaffError(401, "Invalid credentials")
            for key in keys:
                self._failures.pop(key, None)
            if counter >= 0:
                self.db.execute("UPDATE staff SET totp_last_counter = ? WHERE id = ?", (counter, row["id"]))
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
        """Background polls (X-Cockpit-Background: 1) don't count as activity for the idle timeout."""
        auth = headers.get("Authorization") or ""
        background = (headers.get("X-Cockpit-Background") or "") == "1"
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
            if not background:
                self.db.execute("UPDATE staff_sessions SET last_seen_at = ? WHERE token_hash = ?", (moment, token_hash))
                self.db.commit()
        staff = self.staff_json(row)
        staff["_tokenHash"] = token_hash
        return staff

    def logout(self, headers) -> None:
        auth = headers.get("Authorization") or ""
        if auth.startswith("Bearer "):
            with self.lock:
                self.db.execute("DELETE FROM staff_sessions WHERE token_hash = ?", (self._token_hash(auth[7:].strip()),))
                self.db.commit()

    def revoke_sessions(self, staff_id: str, keep_token_hash: str = "") -> None:
        with self.lock:
            self.db.execute("DELETE FROM staff_sessions WHERE staff_id = ? AND token_hash != ?", (staff_id, keep_token_hash))
            self.db.commit()

    def change_password(self, staff: dict, current: str, new: str, ip: str) -> None:
        keys = (f"user|{self.normalize_username(staff['username'])}", f"ip|{ip}")
        with self.lock:
            if self._locked(*keys):
                raise StaffError(429, "Too many failed attempts; try again later")
            row = self.db.execute("SELECT * FROM staff WHERE id = ?", (staff["staffId"],)).fetchone()
            if not hmac.compare_digest(self._hash(current or "", row["pw_salt"]).encode(), row["pw_hash"].encode()):
                self._record_failure(*keys)
                raise StaffError(403, "Current password is wrong")
            self.validate_password(new)
            salt = secrets.token_hex(16)
            self.db.execute("UPDATE staff SET pw_salt = ?, pw_hash = ? WHERE id = ?", (salt, self._hash(new, salt), row["id"]))
            self.db.commit()
        self.revoke_sessions(row["id"], keep_token_hash=staff.get("_tokenHash", ""))

    # -- audit --------------------------------------------------------------------------------------

    def _entry_hash(self, prev_hash: str, entry: dict) -> str:
        canonical = json.dumps(entry, sort_keys=True, separators=(",", ":"))
        return hmac.new(self.audit_key, (prev_hash + canonical).encode("utf-8"), hashlib.sha256).hexdigest()

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
        expected_seq = rows[0]["seq"] if rows else 1
        if rows and expected_seq != 1:
            return {"ok": False, "entries": len(rows), "brokenAt": 1, "problem": "entries missing from the start"}
        top = self.db.execute("SELECT seq FROM sqlite_sequence WHERE name = 'audit_log'").fetchone()
        last_seq = rows[-1]["seq"] if rows else 0
        if top and top["seq"] != last_seq:
            return {"ok": False, "entries": len(rows), "brokenAt": last_seq + 1, "problem": "latest entries deleted"}
        for row in rows:
            if row["seq"] != expected_seq:
                return {"ok": False, "entries": len(rows), "brokenAt": expected_seq, "problem": "entry deleted"}
            expected_seq += 1
            entry = {
                "at": row["at"], "staffId": row["staff_id"], "staffName": row["staff_name"], "action": row["action"],
                "targetType": row["target_type"], "targetId": row["target_id"], "reason": row["reason"],
                "details": json.loads(row["details"]), "ip": row["ip"],
            }
            if row["prev_hash"] != prev or not hmac.compare_digest(self._entry_hash(prev, entry), row["hash"]):
                return {"ok": False, "entries": len(rows), "brokenAt": row["seq"], "problem": "entry modified"}
            prev = row["hash"]
        return {"ok": True, "entries": len(rows), "head": prev}
