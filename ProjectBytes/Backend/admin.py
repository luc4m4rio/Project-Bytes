"""
Root cockpit API (/admin/v1/*), mounted only on the admin listener (server.make_admin_server).

Rules every endpoint follows:
  * staff session required (password + TOTP), checked per request with idle timeout
  * explicit permission per action (roles in staff.py / config staffRoles), plus per-role limits
  * every state change needs a written reason and is appended to the hash-chained audit log
  * mass actions (gift all players) need a typed confirmation phrase
"""
from __future__ import annotations

import json
import re
import secrets
import time

import economy as economy_rules
import staff as staff_rules
from server import ApiError, Backend, Request, now

GIFT_ALL_CONFIRMATION = "GIFT ALL PLAYERS"
COMMAND_TYPES = {
    "broadcast": "server.command",       # message to everyone on the target server(s)
    "message": "server.command",         # message to one player
    "shutdown": "server.command",        # countdown, kick everyone, exit
    "refresh_character": "server.command",
    "kick": "player.kick",
    "exec": "server.exec",               # raw server console command
}


# ---- helpers -------------------------------------------------------------------------------------

def _staff(b: Backend, r: Request, permission: str | None = "view") -> dict:
    staff = b.staff.authenticate(r.headers)
    if permission and permission not in staff["permissions"]:
        raise ApiError(403, f"Your role ({staff['role']}) lacks the '{permission}' permission")
    return staff


def _reason(body: dict) -> str:
    reason = str(body.get("reason") or "").strip()
    if len(reason) < 3:
        raise ApiError(400, "A reason is required for every action (it is written to the audit log)")
    return reason[:500]


def _audit(b: Backend, staff: dict, r: Request, action: str, target_type: str = "", target_id: str = "",
           reason: str = "", details: dict | None = None) -> None:
    b.staff.audit(staff, action, target_type, target_id, reason, details, r.client_ip)


def _int(body: dict, key: str, default: int = 0) -> int:
    value = body.get(key, default)
    if value is None or value == "":
        return default
    try:
        return int(value)
    except (TypeError, ValueError):
        raise ApiError(400, f"{key} must be a number")


def _query_limit(r: Request, default: int, maximum: int) -> int:
    try:
        return max(1, min(maximum, int((r.query.get("limit") or [str(default)])[0])))
    except ValueError:
        raise ApiError(400, "limit must be a number")


def _account(b: Backend, account_id: str):
    row = b.db.execute("SELECT * FROM accounts WHERE id = ?", (account_id,)).fetchone()
    if not row:
        raise ApiError(404, "Unknown account")
    return row


def _character_owner(b: Backend, character_id: str):
    row = b.db.execute("SELECT c.*, a.username AS username FROM characters c JOIN accounts a ON a.id = c.account_id "
                       "WHERE c.id = ?", (character_id,)).fetchone()
    if not row:
        raise ApiError(404, "Unknown character")
    return row


def _server_for_character(b: Backend, character_id: str) -> dict | None:
    for server in b.servers.values():
        if character_id in server["characterIds"]:
            return server
    return None


def _ban_json(row) -> dict:
    active = row["revoked_at"] is None and (row["expires_at"] is None or row["expires_at"] > now())
    return {"banId": row["id"], "accountId": row["account_id"], "reason": row["reason"], "createdAt": row["created_at"],
            "createdBy": row["created_by"], "expiresAt": row["expires_at"] or 0, "revokedAt": row["revoked_at"] or 0,
            "revokedBy": row["revoked_by"], "revokeReason": row["revoke_reason"], "active": active,
            "username": row["username"] if "username" in row.keys() else ""}


def _check_attachment_limits(staff: dict, attachments: list[dict]) -> None:
    """Limits apply to the TOTAL per currency / item, so repeating an attachment doesn't multiply the cap."""
    limits = staff["limits"]
    currency_totals: dict[str, int] = {}
    item_totals: dict[str, int] = {}
    for a in attachments:
        if a["type"] == "currency":
            currency_totals[a["currency"]] = currency_totals.get(a["currency"], 0) + a["amount"]
        else:
            item_totals[a["itemId"]] = item_totals.get(a["itemId"], 0) + a["quantity"]
    if "maxCurrencyAmount" in limits and any(v > limits["maxCurrencyAmount"] for v in currency_totals.values()):
        raise ApiError(403, f"Your role may give at most {limits['maxCurrencyAmount']:,} per currency")
    if "maxItemQuantity" in limits and any(v > limits["maxItemQuantity"] for v in item_totals.values()):
        raise ApiError(403, f"Your role may give at most {limits['maxItemQuantity']} of an item")


def _kick_online(b: Backend, account_id: str, message: str, staff_name: str) -> list[str]:
    """Caller holds lock. Queues a kick for every online character of the account."""
    queued = []
    for row in b.db.execute("SELECT id FROM characters WHERE account_id = ?", (account_id,)):
        server = _server_for_character(b, row["id"])
        if server:
            queued.append(b.queue_command(server["serverId"], "kick", {"characterId": row["id"], "message": message},
                                          staff_name))
    return queued


def _refresh_if_online(b: Backend, character_id: str | None, account_id: str, staff_name: str, note: str = "") -> None:
    """Caller holds lock. Tell district servers to reload characters after a grant, and optionally tell the player."""
    ids = [character_id] if character_id else [r["id"] for r in
                                                b.db.execute("SELECT id FROM characters WHERE account_id = ?", (account_id,))]
    for cid in ids:
        server = _server_for_character(b, cid)
        if server:
            b.queue_command(server["serverId"], "refresh_character", {"characterId": cid}, staff_name)
            if note:
                b.queue_command(server["serverId"], "message", {"characterId": cid, "message": note, "style": "gift"},
                                staff_name)


# ---- session -------------------------------------------------------------------------------------

def login(b: Backend, r: Request) -> dict:
    username = str(r.body.get("username") or "")
    if len(username) > 64 or len(str(r.body.get("password") or "")) > 256:
        raise ApiError(401, "Invalid credentials")
    try:
        result = b.staff.login(username, str(r.body.get("password") or ""), str(r.body.get("code") or ""), r.client_ip)
    except staff_rules.StaffError as e:
        if e.status == 401:  # lockout responses (429) aren't logged, so a flood can't bloat the audit log
            b.staff.audit({"staffId": "", "username": username.strip()[:32]}, "staff.login_failed", "staff", "", "", {},
                          r.client_ip)
        raise
    b.staff.audit(result["staff"], "staff.login", "staff", result["staff"]["staffId"], "", {}, r.client_ip)
    return result


def logout(b: Backend, r: Request) -> dict:
    b.staff.logout(r.headers)
    return {}


def _public_staff(staff: dict) -> dict:
    return {k: v for k, v in staff.items() if not k.startswith("_")}


def me(b: Backend, r: Request) -> dict:
    return {"staff": _public_staff(_staff(b, r, None))}


def change_password(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, None)
    b.staff.change_password(staff, str(r.body.get("current") or ""), str(r.body.get("new") or ""), r.client_ip)
    _audit(b, staff, r, "staff.password_changed", "staff", staff["staffId"], "", {"otherSessionsRevoked": True})
    return {}


# ---- overview / catalog --------------------------------------------------------------------------

def overview(b: Backend, r: Request) -> dict:
    staff = _staff(b, r)
    with b.lock:
        b._reap_servers()
        b.orchestrator.link_servers(b.servers)
        servers = list(b.servers.values())
        stats = {
            "accounts": b.db.execute("SELECT COUNT(*) FROM accounts").fetchone()[0],
            "characters": b.db.execute("SELECT COUNT(*) FROM characters").fetchone()[0],
            "online": sum(len(s["characterIds"]) for s in servers),
            "servers": len(servers),
            "capacity": sum(s["maxPlayers"] for s in servers),
            "activeBans": b.db.execute("SELECT COUNT(*) FROM bans WHERE revoked_at IS NULL AND "
                                       "(expires_at IS NULL OR expires_at > ?)", (now(),)).fetchone()[0],
            "pendingCommands": b.db.execute("SELECT COUNT(*) FROM server_commands WHERE status IN ('queued','delivered')"
                                            ).fetchone()[0],
            "activeGifts": b.db.execute("SELECT COUNT(*) FROM global_gifts WHERE revoked_at IS NULL AND "
                                        "(expires_at IS NULL OR expires_at > ?)", (now(),)).fetchone()[0],
        }
        per_district = {}
        for s in servers:
            d = per_district.setdefault(s["districtId"], {"districtId": s["districtId"], "instances": 0, "online": 0,
                                                          "capacity": 0})
            d["instances"] += 1
            d["online"] += len(s["characterIds"])
            d["capacity"] += s["maxPlayers"]
        recent = []
        if "audit.read" in staff["permissions"]:
            recent = [b.staff.audit_row_json(x) for x in
                      b.db.execute("SELECT * FROM audit_log ORDER BY seq DESC LIMIT 12").fetchall()]
    deployments = b.orchestrator.list()
    import server as server_module
    return {"securityWarnings": server_module.security_warnings(b.cfg), "stats": stats, "districts": [dict(v, displayName=b.districts.get(k, {}).get("displayName", k))
                                          for k, v in sorted(per_district.items())],
            "deployments": {"running": sum(1 for d in deployments if d["status"] in ("starting", "running")),
                            "configured": b.orchestrator.configured()},
            "recentAudit": recent, "serverTime": now()}


def catalog(b: Backend, r: Request) -> dict:
    _staff(b, r)
    return {
        "items": list(b.economy.catalog.items.values()),
        "currencies": list(b.economy.catalog.currencies.values()),
        "districts": [{"districtId": d["districtId"], "displayName": d["displayName"], "type": d["type"],
                       "maxPlayers": d["maxPlayers"]} for d in b.districts.values()],
        "commandTypes": COMMAND_TYPES,
        "roles": {name: b.staff.permissions_for(name) for name in b.staff.roles},
        "roleLimits": b.staff.role_limits,
        "giftAllConfirmation": GIFT_ALL_CONFIRMATION,
    }


# ---- servers & commands --------------------------------------------------------------------------

def servers(b: Backend, r: Request) -> dict:
    _staff(b, r)
    with b.lock:
        b._reap_servers()
        out = []
        for s in sorted(b.servers.values(), key=lambda s: (s["districtId"], s["index"])):
            players = []
            if s["characterIds"]:
                marks = ",".join("?" for _ in s["characterIds"])
                for row in b.db.execute(f"SELECT c.id, c.name, c.faction, c.rank, c.threat, a.id AS aid, a.username FROM "
                                        f"characters c JOIN accounts a ON a.id = c.account_id WHERE c.id IN ({marks})",
                                        s["characterIds"]):
                    players.append({"characterId": row["id"], "name": row["name"], "faction": row["faction"],
                                    "rank": row["rank"], "threat": row["threat"], "accountId": row["aid"],
                                    "username": row["username"]})
            out.append(dict(b._instance_json(s), serverId=s["serverId"], districtId=s["districtId"],
                            address=f"{s['host']}:{s['port']}", lastSeen=s["lastSeen"], build=s.get("build", ""),
                            players=players))
    return {"servers": out}


def send_command(b: Backend, r: Request) -> dict:
    body = r.body
    command_type = str(body.get("type") or "")
    if command_type not in COMMAND_TYPES:
        raise ApiError(400, f"Unknown command type. Use one of: {', '.join(COMMAND_TYPES)}")
    staff = _staff(b, r, COMMAND_TYPES[command_type])
    reason = _reason(body)
    target = body.get("target") or {}
    target_type = str(target.get("type") or "")
    target_id = str(target.get("id") or "")

    payload = {"message": str(body.get("message") or "")[:500], "characterId": str(body.get("characterId") or ""),
               "reason": reason, "style": str(body.get("style") or "info")[:16],
               "delaySeconds": max(0, min(600, _int(body, "delaySeconds", 30))),
               "consoleCommand": str(body.get("consoleCommand") or "")[:500]}
    if command_type in ("broadcast", "message") and not payload["message"].strip():
        raise ApiError(400, "Write the message to send")
    if command_type in ("message", "kick", "refresh_character"):
        target_type, target_id = "character", payload["characterId"] or target_id
        payload["characterId"] = target_id
        if not target_id:
            raise ApiError(400, "Pick the player (characterId)")
    if command_type == "exec" and not payload["consoleCommand"].strip():
        raise ApiError(400, "Enter the console command")
    if command_type == "kick" and not payload["message"]:
        payload["message"] = f"Removed by staff: {reason}"

    with b.lock:
        b._reap_servers()
        if target_type == "all":
            targets = list(b.servers.values())
        elif target_type == "district":
            targets = [s for s in b.servers.values() if s["districtId"] == target_id]
        elif target_type == "server":
            targets = [s for s in b.servers.values() if target_id in (s["serverId"], s["instanceId"])]
        elif target_type == "character":
            server = _server_for_character(b, target_id)
            if not server:
                raise ApiError(404, "That player isn't online")
            targets = [server]
        else:
            raise ApiError(400, "Target type must be all, district, server or character")
        if not targets:
            raise ApiError(404, "No online servers match that target")
        ids = [b.queue_command(s["serverId"], command_type, payload, staff["username"]) for s in targets]
    _audit(b, staff, r, f"server.{command_type}", target_type, target_id, reason,
           {"commandIds": ids, "instances": [s["instanceId"] for s in targets],
            **{k: v for k, v in payload.items() if k in ("message", "delaySeconds", "consoleCommand") and v}})
    return {"commandIds": ids, "instances": [s["instanceId"] for s in targets]}


def list_commands(b: Backend, r: Request) -> dict:
    staff = _staff(b, r)
    limit = _query_limit(r, 100, 500)
    with b.lock:
        rows = b.db.execute("SELECT * FROM server_commands ORDER BY created_at DESC LIMIT ?", (limit,)).fetchall()
    if "server.exec" not in staff["permissions"]:
        rows = [x for x in rows if x["type"] != "exec"]  # console commands/output are owner-level information
    return {"commands": [{"commandId": x["id"], "serverId": x["server_id"], "instanceId": x["instance_id"],
                          "type": x["type"], "payload": json.loads(x["payload"]), "createdAt": x["created_at"],
                          "createdBy": x["created_by"], "status": x["status"], "deliveredAt": x["delivered_at"] or 0,
                          "completedAt": x["completed_at"] or 0, "result": x["result"]} for x in rows]}


# ---- deployments ---------------------------------------------------------------------------------

def list_deployments(b: Backend, r: Request) -> dict:
    _staff(b, r)
    with b.lock:
        b._reap_servers()
        b.orchestrator.link_servers(b.servers)
    o = b.orchestrator
    return {"deployments": o.list(), "configured": o.configured(),
            "mode": "serverExe" if o.server_exe else ("editor" if o.engine_dir else "unconfigured"),
            "maxInstances": o.max_instances}


def spawn(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, "deploy")
    reason = _reason(r.body)
    district_id = str(r.body.get("districtId") or "")
    region = str(r.body.get("region") or "")
    if not re.fullmatch(r"[A-Za-z0-9_-]{0,16}", region):
        raise ApiError(400, "Region tags are up to 16 letters, digits, '_' or '-'")
    started = b.orchestrator.spawn(district_id, _int(r.body, "count", 1), region,
                                   _int(r.body, "maxPlayers", 0), staff["username"])
    _audit(b, staff, r, "deploy.spawn", "district", district_id, reason,
           {"deployments": [d["deploymentId"] for d in started], "ports": [d["port"] for d in started]})
    return {"started": started}


def stop_deployment(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, "deploy")
    reason = _reason(r.body)
    deploy_id = r.params["did"]
    force = str(r.body.get("mode") or "graceful") == "force"
    deployment = b.orchestrator.get(deploy_id)
    if not deployment:
        raise ApiError(404, "Unknown deployment")
    command_id = ""
    if not force:
        with b.lock:
            b.orchestrator.link_servers(b.servers)
            if deployment["serverId"] and deployment["serverId"] in b.servers:
                command_id = b.queue_command(deployment["serverId"], "shutdown", {
                    "delaySeconds": max(0, min(600, _int(r.body, "delaySeconds", 30))),
                    "message": str(r.body.get("message") or "This district is shutting down for maintenance")[:500],
                    "reason": reason}, staff["username"])
    result = b.orchestrator.mark_stopping(deploy_id, force=force or not command_id)
    _audit(b, staff, r, "deploy.stop", "deployment", deploy_id, reason,
           {"mode": "force" if force or not command_id else "graceful", "commandId": command_id})
    return {"deployment": result, "commandId": command_id}


def deployment_log(b: Backend, r: Request) -> dict:
    _staff(b, r, "deploy")
    log = b.orchestrator.log_tail(r.params["did"])
    return {"log": re.sub(r"(?i)(BytesServerKey=)\S+", r"\1[redacted]", log)}


# ---- players -------------------------------------------------------------------------------------

def search_players(b: Backend, r: Request) -> dict:
    _staff(b, r)
    q = ((r.query.get("q") or [""])[0]).strip()
    with b.lock:
        if q:
            like = f"%{q}%"
            rows = b.db.execute(
                "SELECT DISTINCT a.* FROM accounts a LEFT JOIN characters c ON c.account_id = a.id "
                "WHERE a.username LIKE ? OR a.id = ? OR c.name LIKE ? OR c.id = ? ORDER BY a.created_at DESC LIMIT 50",
                (like, q, like, q)).fetchall()
        else:
            rows = b.db.execute("SELECT * FROM accounts ORDER BY created_at DESC LIMIT 50").fetchall()
        out = []
        for a in rows:
            chars = b.db.execute("SELECT id, name, faction, rank, threat, online_instance FROM characters "
                                 "WHERE account_id = ? ORDER BY created_at", (a["id"],)).fetchall()
            out.append({"accountId": a["id"], "username": a["username"], "createdAt": a["created_at"],
                        "flags": json.loads(a["flags"]), "banned": bool(b.active_ban(a["id"])),
                        "characters": [{"characterId": c["id"], "name": c["name"], "faction": c["faction"],
                                        "rank": c["rank"], "threat": c["threat"], "onlineInstance": c["online_instance"]}
                                       for c in chars]})
    return {"players": out}


def player_detail(b: Backend, r: Request) -> dict:
    staff = _staff(b, r)
    account_id = r.params["aid"]
    with b.lock:
        account = _account(b, account_id)
        chars = b.db.execute("SELECT * FROM characters WHERE account_id = ? ORDER BY created_at", (account_id,)).fetchall()
        characters = [dict(b._character_json(c), inventory=b.economy.inventory(c["id"])) for c in chars]
        bans = [_ban_json(x) for x in b.db.execute("SELECT * FROM bans WHERE account_id = ? ORDER BY created_at DESC",
                                                   (account_id,)).fetchall()]
        sessions = b.db.execute("SELECT COUNT(*) FROM sessions WHERE account_id = ? AND expires_at > ?",
                                (account_id, now())).fetchone()[0]
        audit = []
        if "audit.read" in staff["permissions"]:
            targets = [account_id] + [c["id"] for c in chars]
            marks = ",".join("?" for _ in targets)
            audit = [b.staff.audit_row_json(x) for x in b.db.execute(
                f"SELECT * FROM audit_log WHERE target_id IN ({marks}) ORDER BY seq DESC LIMIT 50", targets).fetchall()]
        mailbox = b.economy.mailbox(account_id)
        b.db.commit()
    return {"account": dict(b._account_json(account), createdAt=account["created_at"], activeSessions=sessions),
            "characters": characters, "wallet": b.economy.wallet(account_id), "bans": bans,
            "mailbox": mailbox, "audit": audit}


def ban_player(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, "player.ban")
    reason = _reason(r.body)
    account_id = r.params["aid"]
    hours = _int(r.body, "durationHours", 0)  # 0 = permanent
    limit = staff["limits"].get("maxBanHours")
    if limit is not None and (hours <= 0 or hours > limit):
        raise ApiError(403, f"Your role may ban for at most {limit} hours (no permanent bans)")
    if hours < 0:
        raise ApiError(400, "durationHours must be 0 (permanent) or positive")
    public_reason = str(r.body.get("publicReason") or reason)[:300]
    with b.lock:
        account = _account(b, account_id)
        ban_id = "ban_" + secrets.token_hex(8)
        b.db.execute("INSERT INTO bans (id, account_id, reason, created_at, created_by, expires_at) VALUES (?,?,?,?,?,?)",
                     (ban_id, account_id, public_reason, now(), staff["username"], now() + hours * 3600 if hours else None))
        b.db.execute("DELETE FROM sessions WHERE account_id = ?", (account_id,))
        b.db.commit()
        kicked = _kick_online(b, account_id, f"You have been banned: {public_reason}", staff["username"])
    _audit(b, staff, r, "player.ban", "account", account_id, reason,
           {"banId": ban_id, "username": account["username"], "durationHours": hours or "permanent",
            "publicReason": public_reason, "kickCommands": kicked})
    return {"banId": ban_id, "kickCommands": kicked}


def list_bans(b: Backend, r: Request) -> dict:
    _staff(b, r)
    active_only = (r.query.get("active") or ["0"])[0] == "1"
    with b.lock:
        rows = b.db.execute("SELECT bans.*, a.username FROM bans JOIN accounts a ON a.id = bans.account_id "
                            "ORDER BY bans.created_at DESC LIMIT 500").fetchall()
    bans = [_ban_json(x) for x in rows]
    return {"bans": [x for x in bans if x["active"]] if active_only else bans}


def revoke_ban(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, "player.unban")
    reason = _reason(r.body)
    with b.lock:
        row = b.db.execute("SELECT * FROM bans WHERE id = ?", (r.params["bid"],)).fetchone()
        if not row:
            raise ApiError(404, "Unknown ban")
        if row["revoked_at"]:
            raise ApiError(409, "Already revoked")
        limit = staff["limits"].get("maxBanHours")
        if limit is not None and (row["expires_at"] is None or row["expires_at"] - row["created_at"] > limit * 3600):
            raise ApiError(403, f"Your role may only lift bans it could have issued (up to {limit} hours)")
        b.db.execute("UPDATE bans SET revoked_at = ?, revoked_by = ?, revoke_reason = ? WHERE id = ?",
                     (now(), staff["username"], reason, row["id"]))
        b.db.commit()
    _audit(b, staff, r, "player.unban", "account", row["account_id"], reason, {"banId": row["id"]})
    return {}


def revoke_sessions(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, "player.sessions")
    reason = _reason(r.body)
    account_id = r.params["aid"]
    with b.lock:
        _account(b, account_id)
        count = b.db.execute("DELETE FROM sessions WHERE account_id = ?", (account_id,)).rowcount
        b.db.commit()
        kicked = _kick_online(b, account_id, "Your session was ended by staff", staff["username"]) \
            if r.body.get("kick") else []
    _audit(b, staff, r, "player.sessions_revoked", "account", account_id, reason, {"sessions": count, "kicks": kicked})
    return {"revoked": count, "kickCommands": kicked}


def set_flag(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, "player.flags")
    reason = _reason(r.body)
    flag = str(r.body.get("flag") or "").strip()
    if not re.fullmatch(r"[A-Za-z0-9_.-]{1,32}", flag):
        raise ApiError(400, "Flags are 1-32 characters: letters, digits, '.', '_' or '-'")
    enabled = bool(r.body.get("enabled", True))
    with b.lock:
        account = _account(b, r.params["aid"])
        flags = [f for f in json.loads(account["flags"]) if f.lower() != flag.lower()]
        if enabled:
            flags.append(flag)
        b.db.execute("UPDATE accounts SET flags = ? WHERE id = ?", (json.dumps(flags), account["id"]))
        b.db.commit()
    _audit(b, staff, r, "player.flag_" + ("added" if enabled else "removed"), "account", account["id"], reason,
           {"flag": flag})
    return {"flags": flags}


# ---- economy -------------------------------------------------------------------------------------

def grant(b: Backend, r: Request) -> dict:
    """Direct grant (or removal with a negative amount) onto a character/account, applied immediately."""
    staff = _staff(b, r, "economy.grant")
    reason = _reason(r.body)
    body = r.body
    note = str(body.get("notifyMessage") or "")[:300]
    if note and "server.command" not in staff["permissions"]:
        raise ApiError(403, "Sending a custom message to the player needs the server.command permission")
    with b.lock:
        character = _character_owner(b, str(body["characterId"])) if body.get("characterId") else None
        account_id = character["account_id"] if character else str(body.get("accountId") or "")
        account = _account(b, account_id)
        details = {"username": account["username"], "character": character["name"] if character else ""}
        limits = staff["limits"]
        try:
            if body.get("currency"):
                amount = _int(body, "amount")
                if amount == 0:
                    raise ApiError(400, "amount can't be 0 (negative removes)")
                if "maxCurrencyAmount" in limits and abs(amount) > limits["maxCurrencyAmount"]:
                    raise ApiError(403, f"Your role may give at most {limits['maxCurrencyAmount']:,} per currency")
                b.economy.adjust_currency(account_id, character["id"] if character else None, str(body["currency"]), amount)
                details.update(currency=body["currency"], amount=amount)
            elif body.get("itemId"):
                if not character:
                    raise ApiError(400, "Items are given to a character")
                attachments = b.economy.normalize_attachments(
                    [{"type": "item", "itemId": body["itemId"], "quantity": _int(body, "quantity", 1)}])
                _check_attachment_limits(staff, attachments)
                b.economy.apply(attachments, account_id, character["id"], source=f"staff:{staff['username']}")
                details.update(itemId=body["itemId"], quantity=attachments[0]["quantity"])
            elif body.get("removeEntryId"):
                if not character:
                    raise ApiError(400, "Say which character the item is removed from")
                removed = b.economy.remove_item(str(body["removeEntryId"]), character["id"])
                if "maxItemQuantity" in limits and removed["quantity"] > limits["maxItemQuantity"]:
                    raise ApiError(403, f"Your role may remove at most {limits['maxItemQuantity']} of an item")
                details.update(removed=removed["item_id"], quantity=removed["quantity"], entryId=removed["id"])
            else:
                raise ApiError(400, "Give a currency+amount, an itemId, or removeEntryId")
            b.db.commit()
        except economy_rules.EconomyError as e:
            b.db.rollback()
            raise ApiError(e.status, e.message)
        except Exception:
            b.db.rollback()  # never leave a half-applied change for the next commit to pick up
            raise
        _refresh_if_online(b, character["id"] if character else None, account_id, staff["username"], note)
    _audit(b, staff, r, "economy.grant", "character" if character else "account",
           character["id"] if character else account_id, reason, details)
    return {"ok": True, "wallet": b.economy.wallet(account_id)}


def send_gift(b: Backend, r: Request) -> dict:
    body = r.body
    to_all = str(body.get("target") or "") == "all"
    staff = _staff(b, r, "economy.gift_all" if to_all else "economy.gift")
    reason = _reason(body)
    subject = str(body.get("subject") or "").strip()[:120]
    if not subject:
        raise ApiError(400, "Give the gift a subject (players see it in their mailbox)")
    message = str(body.get("body") or "")[:2000]
    expires = _int(body, "expiresInDays", 30) or None
    try:
        attachments = b.economy.normalize_attachments(body.get("attachments"))
    except economy_rules.EconomyError as e:
        raise ApiError(e.status, e.message)
    _check_attachment_limits(staff, attachments)
    sender = "Project Bytes Staff"  # fixed: staff can't impersonate other senders
    if to_all and body.get("announce", True) and "server.command" not in staff["permissions"]:
        raise ApiError(403, "Announcing in districts needs the server.command permission (untick 'announce')")

    with b.lock:
        if to_all:
            if str(body.get("confirm") or "") != GIFT_ALL_CONFIRMATION:
                raise ApiError(400, f"Type '{GIFT_ALL_CONFIRMATION}' to confirm a gift to every player")
            gift_id = b.economy.send_global_gift(subject, message, attachments, sender, expires,
                                                 bool(body.get("includeNewAccounts", False)))
            b.db.commit()
            recipients = b.db.execute("SELECT COUNT(*) FROM accounts").fetchone()[0]
            if body.get("announce", True):
                for server in b.servers.values():
                    b.queue_command(server["serverId"], "broadcast",
                                    {"message": f"Gift for everyone: {subject}! Check your mail.", "style": "gift"},
                                    staff["username"])
            target_type, target_id = "all", gift_id
        else:
            account = _account(b, str(body.get("accountId") or ""))
            gift_id = b.economy.send_mail(account["id"], subject, message, attachments, sender, expires)
            b.db.commit()
            recipients = 1
            _refresh_if_online(b, None, account["id"], staff["username"], f"You received mail: {subject}")
            target_type, target_id = "account", account["id"]
    _audit(b, staff, r, "economy.gift_all" if to_all else "economy.gift", target_type, target_id, reason,
           {"giftId": gift_id, "subject": subject, "attachments": attachments, "recipients": recipients,
            "includeNewAccounts": bool(body.get("includeNewAccounts", False)) if to_all else False})
    return {"giftId": gift_id, "recipients": recipients}


def list_gifts(b: Backend, r: Request) -> dict:
    _staff(b, r)
    with b.lock:
        gifts = [{"giftId": g["id"], "subject": g["subject"], "attachments": json.loads(g["attachments"]),
                  "sender": g["sender"], "createdAt": g["created_at"], "expiresAt": g["expires_at"] or 0,
                  "includeNewAccounts": bool(g["include_new_accounts"]), "revokedAt": g["revoked_at"] or 0,
                  "claims": b.db.execute("SELECT COUNT(*) FROM global_gift_claims WHERE gift_id = ?", (g["id"],)).fetchone()[0]}
                 for g in b.db.execute("SELECT * FROM global_gifts ORDER BY created_at DESC LIMIT 100").fetchall()]
        mail = [{"mailId": m["id"], "accountId": m["account_id"], "username": m["username"], "subject": m["subject"],
                 "attachments": json.loads(m["attachments"]), "createdAt": m["created_at"],
                 "claimedAt": m["claimed_at"] or 0}
                for m in b.db.execute("SELECT mail.*, a.username FROM mail JOIN accounts a ON a.id = mail.account_id "
                                      "ORDER BY mail.created_at DESC LIMIT 100").fetchall()]
    return {"globalGifts": gifts, "mail": mail}


def revoke_gift(b: Backend, r: Request) -> dict:
    staff = _staff(b, r, "economy.gift_all")
    reason = _reason(r.body)
    with b.lock:
        cur = b.db.execute("UPDATE global_gifts SET revoked_at = ? WHERE id = ? AND revoked_at IS NULL",
                           (now(), r.params["gid"]))
        b.db.commit()
        if not cur.rowcount:
            raise ApiError(404, "Unknown or already revoked gift")
    _audit(b, staff, r, "economy.gift_revoked", "gift", r.params["gid"], reason)
    return {}


# ---- audit ---------------------------------------------------------------------------------------

def audit_log(b: Backend, r: Request) -> dict:
    _staff(b, r, "audit.read")
    q = {k: (v[0] if v else "") for k, v in r.query.items()}
    limit = _query_limit(r, 200, 1000)
    clauses, params = [], []
    for key, column in (("action", "action"), ("staff", "staff_name"), ("target", "target_id")):
        if q.get(key):
            clauses.append(f"{column} LIKE ?")
            params.append(f"%{q[key]}%")
    where = ("WHERE " + " AND ".join(clauses)) if clauses else ""
    with b.lock:
        rows = b.db.execute(f"SELECT * FROM audit_log {where} ORDER BY seq DESC LIMIT ?", params + [limit]).fetchall()
    return {"entries": [b.staff.audit_row_json(x) for x in rows]}


def audit_verify(b: Backend, r: Request) -> dict:
    _staff(b, r, "audit.read")
    return b.staff.verify_audit_chain()


# ---- staff management ----------------------------------------------------------------------------

def list_staff(b: Backend, r: Request) -> dict:
    _staff(b, r, "staff.manage")
    with b.lock:
        rows = b.db.execute("SELECT * FROM staff ORDER BY created_at").fetchall()
    return {"staff": [b.staff.staff_json(x) for x in rows]}


def _guard_role(b: Backend, actor: dict, role: str) -> None:
    if "*" in b.staff.roles.get(role, []) and "*" not in b.staff.roles.get(actor["role"], []):
        raise ApiError(403, "Only an owner can grant the owner role")


def create_staff(b: Backend, r: Request) -> dict:
    actor = _staff(b, r, "staff.manage")
    reason = _reason(r.body)
    role = str(r.body.get("role") or "")
    _guard_role(b, actor, role)
    created, secret = b.staff.create(str(r.body.get("username") or ""), str(r.body.get("password") or ""), role,
                                     actor["username"], with_2fa=True)
    _audit(b, actor, r, "staff.created", "staff", created["staffId"], reason,
           {"username": created["username"], "role": role})
    return {"staff": _public_staff(created), "totpSecret": secret, "totpUri": staff_rules.totp_uri(secret, created["username"])}


def update_staff(b: Backend, r: Request) -> dict:
    actor = _staff(b, r, "staff.manage")
    reason = _reason(r.body)
    staff_id = r.params["sid"]
    with b.lock:
        row = b.db.execute("SELECT * FROM staff WHERE id = ?", (staff_id,)).fetchone()
        if not row:
            raise ApiError(404, "Unknown staff member")
        target_is_owner = "*" in b.staff.roles.get(row["role"], [])
        if target_is_owner and "*" not in b.staff.roles.get(actor["role"], []):
            raise ApiError(403, "Only an owner can change an owner")
        changes = {}
        if "role" in r.body:
            role = str(r.body["role"])
            if role not in b.staff.roles:
                raise ApiError(400, "Unknown role")
            _guard_role(b, actor, role)
            changes["role"] = role
        if "disabled" in r.body:
            if staff_id == actor["staffId"]:
                raise ApiError(400, "You can't disable yourself")
            changes["disabled"] = 1 if r.body["disabled"] else 0
        if not changes:
            raise ApiError(400, "Nothing to change")
        b.db.execute(f"UPDATE staff SET {', '.join(k + ' = ?' for k in changes)} WHERE id = ?",
                     list(changes.values()) + [staff_id])
        if b.staff.owner_count() == 0:
            b.db.rollback()
            raise ApiError(409, "There must always be at least one active owner")
        b.db.commit()
    if changes.get("disabled") or "role" in changes:
        b.staff.revoke_sessions(staff_id)
    _audit(b, actor, r, "staff.updated", "staff", staff_id, reason, {"username": row["username"], **changes})
    return {}


def reset_staff_2fa(b: Backend, r: Request) -> dict:
    actor = _staff(b, r, "staff.manage")
    reason = _reason(r.body)
    staff_id = r.params["sid"]
    secret = staff_rules.new_totp_secret()
    with b.lock:
        row = b.db.execute("SELECT * FROM staff WHERE id = ?", (staff_id,)).fetchone()
        if not row:
            raise ApiError(404, "Unknown staff member")
        if "*" in b.staff.roles.get(row["role"], []) and "*" not in b.staff.roles.get(actor["role"], []):
            raise ApiError(403, "Only an owner can reset an owner's 2FA")
        b.db.execute("UPDATE staff SET totp_secret = ? WHERE id = ?", (secret, staff_id))
        b.db.commit()
    b.staff.revoke_sessions(staff_id)
    _audit(b, actor, r, "staff.2fa_reset", "staff", staff_id, reason, {"username": row["username"]})
    return {"totpSecret": secret, "totpUri": staff_rules.totp_uri(secret, row["username"])}


# ---- routes --------------------------------------------------------------------------------------

ADMIN_ROUTES = [
    ("POST", r"/admin/v1/login", login),
    ("POST", r"/admin/v1/logout", logout),
    ("GET", r"/admin/v1/me", me),
    ("POST", r"/admin/v1/me/password", change_password),
    ("GET", r"/admin/v1/overview", overview),
    ("GET", r"/admin/v1/catalog", catalog),
    ("GET", r"/admin/v1/servers", servers),
    ("POST", r"/admin/v1/commands", send_command),
    ("GET", r"/admin/v1/commands", list_commands),
    ("GET", r"/admin/v1/deployments", list_deployments),
    ("POST", r"/admin/v1/deployments", spawn),
    ("POST", r"/admin/v1/deployments/(?P<did>dep_[a-f0-9]+)/stop", stop_deployment),
    ("GET", r"/admin/v1/deployments/(?P<did>dep_[a-f0-9]+)/log", deployment_log),
    ("GET", r"/admin/v1/players", search_players),
    ("GET", r"/admin/v1/players/(?P<aid>acc_[a-f0-9]+)", player_detail),
    ("POST", r"/admin/v1/players/(?P<aid>acc_[a-f0-9]+)/ban", ban_player),
    ("POST", r"/admin/v1/players/(?P<aid>acc_[a-f0-9]+)/sessions/revoke", revoke_sessions),
    ("POST", r"/admin/v1/players/(?P<aid>acc_[a-f0-9]+)/flags", set_flag),
    ("GET", r"/admin/v1/bans", list_bans),
    ("POST", r"/admin/v1/bans/(?P<bid>ban_[a-f0-9]+)/revoke", revoke_ban),
    ("POST", r"/admin/v1/grants", grant),
    ("POST", r"/admin/v1/gifts", send_gift),
    ("GET", r"/admin/v1/gifts", list_gifts),
    ("POST", r"/admin/v1/gifts/(?P<gid>gift_[a-f0-9]+)/revoke", revoke_gift),
    ("GET", r"/admin/v1/audit", audit_log),
    ("GET", r"/admin/v1/audit/verify", audit_verify),
    ("GET", r"/admin/v1/staff", list_staff),
    ("POST", r"/admin/v1/staff", create_staff),
    ("POST", r"/admin/v1/staff/(?P<sid>stf_[a-f0-9]+)", update_staff),
    ("POST", r"/admin/v1/staff/(?P<sid>stf_[a-f0-9]+)/reset-2fa", reset_staff_2fa),
]
COMPILED_ADMIN_ROUTES = [(m, re.compile(p), fn) for m, p, fn in ADMIN_ROUTES]
