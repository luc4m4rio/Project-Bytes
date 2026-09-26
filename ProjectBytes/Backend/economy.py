"""
Currencies, items, inventories and the mailbox (gifts).

Currencies (Content/Data/ItemCatalog.json):
  * character-scoped "money" lives on the character row (earned in districts)
  * account-scoped currencies (e.g. "bp") live in account_wallets and are shared by all characters

Staff give things two ways:
  * direct grant  - lands immediately on a character / account (the district server is told to refresh)
  * mail / gift   - lands in the account mailbox; the player claims it onto the character of their choice.
                    Gifts to *everyone* are a single global_gifts row plus a per-account claim marker, so a gift
                    to a million accounts is one insert (and can optionally include accounts created later).
"""
from __future__ import annotations

import json
import os
import secrets
import time

ECONOMY_SCHEMA = """
CREATE TABLE IF NOT EXISTS account_wallets (
    account_id TEXT NOT NULL,
    currency TEXT NOT NULL,
    amount INTEGER NOT NULL DEFAULT 0,
    PRIMARY KEY (account_id, currency)
);
CREATE TABLE IF NOT EXISTS inventory (
    id TEXT PRIMARY KEY,
    character_id TEXT NOT NULL,
    item_id TEXT NOT NULL,
    quantity INTEGER NOT NULL,
    acquired_at INTEGER NOT NULL,
    expires_at INTEGER,
    source TEXT NOT NULL DEFAULT ''
);
CREATE INDEX IF NOT EXISTS inventory_character ON inventory(character_id);
CREATE TABLE IF NOT EXISTS mail (
    id TEXT PRIMARY KEY,
    account_id TEXT NOT NULL,
    subject TEXT NOT NULL,
    body TEXT NOT NULL DEFAULT '',
    attachments TEXT NOT NULL DEFAULT '[]',
    sender TEXT NOT NULL DEFAULT 'Staff',
    created_at INTEGER NOT NULL,
    expires_at INTEGER,
    claimed_at INTEGER,
    claimed_character_id TEXT
);
CREATE INDEX IF NOT EXISTS mail_account ON mail(account_id);
CREATE TABLE IF NOT EXISTS global_gifts (
    id TEXT PRIMARY KEY,
    subject TEXT NOT NULL,
    body TEXT NOT NULL DEFAULT '',
    attachments TEXT NOT NULL DEFAULT '[]',
    sender TEXT NOT NULL DEFAULT 'Staff',
    created_at INTEGER NOT NULL,
    expires_at INTEGER,
    include_new_accounts INTEGER NOT NULL DEFAULT 0,
    max_account_rowid INTEGER NOT NULL DEFAULT 0,
    revoked_at INTEGER
);
CREATE TABLE IF NOT EXISTS global_gift_claims (
    gift_id TEXT NOT NULL,
    account_id TEXT NOT NULL,
    claimed_at INTEGER NOT NULL,
    character_id TEXT NOT NULL,
    PRIMARY KEY (gift_id, account_id)
);
"""

MAX_ATTACHMENTS = 10


class EconomyError(Exception):
    def __init__(self, status: int, message: str):
        super().__init__(message)
        self.status = status
        self.message = message


def now() -> int:
    return int(time.time())


class ItemCatalog:
    def __init__(self, data: dict):
        self.currencies = {c["id"]: c for c in data.get("currencies", [])}
        self.items = {i["id"]: i for i in data.get("items", [])}

    @classmethod
    def load(cls, path: str | None) -> "ItemCatalog":
        if path and os.path.exists(path):
            with open(path, "r", encoding="utf-8") as f:
                return cls(json.load(f))
        return cls({"currencies": [{"id": "money", "displayName": "$", "scope": "character"}], "items": []})

    def to_json(self) -> dict:
        return {"currencies": list(self.currencies.values()), "items": list(self.items.values())}


class Economy:
    def __init__(self, db, lock, catalog: ItemCatalog):
        self.db = db
        self.lock = lock
        self.catalog = catalog
        db.executescript(ECONOMY_SCHEMA)

    # -- attachments --------------------------------------------------------------------------------

    def normalize_attachments(self, raw) -> list[dict]:
        """[{"type":"currency","currency":"bp","amount":500}, {"type":"item","itemId":"...","quantity":1}]"""
        if not isinstance(raw, list) or not raw:
            raise EconomyError(400, "Add at least one attachment (currency or item)")
        if len(raw) > MAX_ATTACHMENTS:
            raise EconomyError(400, f"At most {MAX_ATTACHMENTS} attachments")
        out = []
        for entry in raw:
            if not isinstance(entry, dict):
                raise EconomyError(400, "Attachments must be objects")
            kind = entry.get("type")
            if kind == "currency":
                currency = self.catalog.currencies.get(str(entry.get("currency") or ""))
                if not currency:
                    raise EconomyError(400, f"Unknown currency '{entry.get('currency')}'")
                amount = self._positive_int(entry.get("amount"), "amount")
                out.append({"type": "currency", "currency": currency["id"], "amount": amount,
                            "displayName": f"{amount:,} {currency['displayName']}"})
            elif kind == "item":
                item = self.catalog.items.get(str(entry.get("itemId") or ""))
                if not item:
                    raise EconomyError(400, f"Unknown item '{entry.get('itemId')}'")
                quantity = self._positive_int(entry.get("quantity", 1), "quantity")
                if not item.get("stackable") and quantity > 1:
                    raise EconomyError(400, f"{item['displayName']} isn't stackable; quantity must be 1")
                if item.get("stackable") and quantity > int(item.get("maxStack", 1)) * 10:
                    raise EconomyError(400, f"{item['displayName']}: quantity too large")
                out.append({"type": "item", "itemId": item["id"], "quantity": quantity,
                            "displayName": f"{item['displayName']}" + (f" x{quantity}" if quantity > 1 else "")})
            else:
                raise EconomyError(400, "Attachment type must be 'currency' or 'item'")
        return out

    @staticmethod
    def _positive_int(value, what: str) -> int:
        if isinstance(value, bool) or not isinstance(value, (int, float)) or int(value) != value or value <= 0:
            raise EconomyError(400, f"{what} must be a positive whole number")
        if value > 2_000_000_000:
            raise EconomyError(400, f"{what} is too large")
        return int(value)

    # -- applying (caller holds the lock and commits) -----------------------------------------------

    def _character(self, character_id: str):
        row = self.db.execute("SELECT * FROM characters WHERE id = ?", (character_id,)).fetchone()
        if not row:
            raise EconomyError(404, "Unknown character")
        return row

    def apply(self, attachments: list[dict], account_id: str, character_id: str | None, source: str) -> None:
        for a in attachments:
            if a["type"] == "currency":
                currency = self.catalog.currencies[a["currency"]]
                if currency.get("scope") == "character":
                    if not character_id:
                        raise EconomyError(400, f"{currency['displayName']} needs a character")
                    self._character(character_id)
                    self.db.execute("UPDATE characters SET money = MIN(money + ?, 2000000000) WHERE id = ?",
                                    (a["amount"], character_id))
                else:
                    self.db.execute(
                        "INSERT INTO account_wallets (account_id, currency, amount) VALUES (?,?,?) "
                        "ON CONFLICT(account_id, currency) DO UPDATE SET amount = MIN(amount + excluded.amount, 2000000000)",
                        (account_id, a["currency"], a["amount"]))
            else:
                if not character_id:
                    raise EconomyError(400, "Items need a character")
                self._character(character_id)
                self._add_item(character_id, a["itemId"], a["quantity"], source)

    def _add_item(self, character_id: str, item_id: str, quantity: int, source: str) -> None:
        item = self.catalog.items[item_id]
        days = int(item.get("durationDays") or 0)
        expires = now() + days * 86400 if days else None
        if item.get("stackable") and not expires:
            existing = self.db.execute("SELECT id FROM inventory WHERE character_id = ? AND item_id = ? AND expires_at IS NULL",
                                       (character_id, item_id)).fetchone()
            if existing:
                self.db.execute("UPDATE inventory SET quantity = quantity + ? WHERE id = ?", (quantity, existing["id"]))
                return
        count = quantity if not item.get("stackable") else 1
        for _ in range(count):
            self.db.execute("INSERT INTO inventory (id, character_id, item_id, quantity, acquired_at, expires_at, source) "
                            "VALUES (?,?,?,?,?,?,?)",
                            ("inv_" + secrets.token_hex(8), character_id, item_id,
                             quantity if item.get("stackable") else 1, now(), expires, source))

    def adjust_currency(self, account_id: str, character_id: str | None, currency_id: str, delta: int) -> None:
        """Signed adjustment (staff can also remove). Never below zero. Caller holds lock + commits."""
        currency = self.catalog.currencies.get(currency_id)
        if not currency:
            raise EconomyError(400, f"Unknown currency '{currency_id}'")
        if currency.get("scope") == "character":
            if not character_id:
                raise EconomyError(400, f"{currency['displayName']} needs a character")
            self._character(character_id)
            self.db.execute("UPDATE characters SET money = MAX(0, MIN(money + ?, 2000000000)) WHERE id = ?",
                            (delta, character_id))
        else:
            self.db.execute("INSERT INTO account_wallets (account_id, currency, amount) VALUES (?,?,0) "
                            "ON CONFLICT(account_id, currency) DO NOTHING", (account_id, currency_id))
            self.db.execute("UPDATE account_wallets SET amount = MAX(0, MIN(amount + ?, 2000000000)) "
                            "WHERE account_id = ? AND currency = ?", (delta, account_id, currency_id))

    def remove_item(self, entry_id: str) -> dict:
        row = self.db.execute("SELECT * FROM inventory WHERE id = ?", (entry_id,)).fetchone()
        if not row:
            raise EconomyError(404, "Unknown inventory entry")
        self.db.execute("DELETE FROM inventory WHERE id = ?", (entry_id,))
        return dict(row)

    # -- queries ------------------------------------------------------------------------------------

    def wallet(self, account_id: str) -> list[dict]:
        rows = {r["currency"]: r["amount"] for r in
                self.db.execute("SELECT currency, amount FROM account_wallets WHERE account_id = ?", (account_id,))}
        return [{"currency": c["id"], "displayName": c["displayName"], "amount": rows.get(c["id"], 0)}
                for c in self.catalog.currencies.values() if c.get("scope") != "character"]

    def inventory(self, character_id: str) -> list[dict]:
        self.db.execute("DELETE FROM inventory WHERE expires_at IS NOT NULL AND expires_at < ?", (now(),))
        out = []
        for r in self.db.execute("SELECT * FROM inventory WHERE character_id = ? ORDER BY acquired_at", (character_id,)):
            item = self.catalog.items.get(r["item_id"], {})
            out.append({"entryId": r["id"], "itemId": r["item_id"], "displayName": item.get("displayName", r["item_id"]),
                        "category": item.get("category", ""), "quantity": r["quantity"],
                        "expiresAt": r["expires_at"] or 0, "source": r["source"]})
        return out

    def _mail_json(self, row, kind: str) -> dict:
        return {"mailId": row["id"], "kind": kind, "subject": row["subject"], "body": row["body"],
                "sender": row["sender"], "attachments": json.loads(row["attachments"]),
                "createdAt": row["created_at"], "expiresAt": row["expires_at"] or 0}

    def account_rowid(self, account_id: str) -> int:
        row = self.db.execute("SELECT rowid FROM accounts WHERE id = ?", (account_id,)).fetchone()
        return row[0] if row else 0

    def mailbox(self, account_id: str) -> list[dict]:
        # Eligibility for "everyone" gifts uses account insertion order, not timestamps (same-second signups).
        account_rowid = self.account_rowid(account_id)
        moment = now()
        direct = self.db.execute(
            "SELECT * FROM mail WHERE account_id = ? AND claimed_at IS NULL AND (expires_at IS NULL OR expires_at > ?) "
            "ORDER BY created_at DESC", (account_id, moment)).fetchall()
        gifts = self.db.execute(
            "SELECT g.* FROM global_gifts g WHERE g.revoked_at IS NULL AND (g.expires_at IS NULL OR g.expires_at > ?) "
            "AND (g.include_new_accounts = 1 OR g.max_account_rowid >= ?) "
            "AND NOT EXISTS (SELECT 1 FROM global_gift_claims c WHERE c.gift_id = g.id AND c.account_id = ?) "
            "ORDER BY g.created_at DESC", (moment, account_rowid, account_id)).fetchall()
        return [self._mail_json(r, "gift") for r in gifts] + [self._mail_json(r, "mail") for r in direct]

    # -- sending / claiming (caller holds lock + commits) -------------------------------------------

    def send_mail(self, account_id: str, subject: str, body: str, attachments: list[dict], sender: str,
                  expires_in_days: int | None) -> str:
        mail_id = "mail_" + secrets.token_hex(8)
        expires = now() + expires_in_days * 86400 if expires_in_days else None
        self.db.execute("INSERT INTO mail (id, account_id, subject, body, attachments, sender, created_at, expires_at) "
                        "VALUES (?,?,?,?,?,?,?,?)",
                        (mail_id, account_id, subject, body, json.dumps(attachments), sender, now(), expires))
        return mail_id

    def send_global_gift(self, subject: str, body: str, attachments: list[dict], sender: str,
                         expires_in_days: int | None, include_new_accounts: bool) -> str:
        gift_id = "gift_" + secrets.token_hex(8)
        expires = now() + expires_in_days * 86400 if expires_in_days else None
        max_rowid = self.db.execute("SELECT COALESCE(MAX(rowid), 0) FROM accounts").fetchone()[0]
        self.db.execute("INSERT INTO global_gifts (id, subject, body, attachments, sender, created_at, expires_at, "
                        "include_new_accounts, max_account_rowid) VALUES (?,?,?,?,?,?,?,?,?)",
                        (gift_id, subject, body, json.dumps(attachments), sender, now(), expires,
                         1 if include_new_accounts else 0, max_rowid))
        return gift_id

    def claim(self, account_id: str, mail_id: str, character_id: str) -> dict:
        moment = now()
        if mail_id.startswith("gift_"):
            gift = self.db.execute("SELECT * FROM global_gifts WHERE id = ?", (mail_id,)).fetchone()
            eligible = gift and gift["revoked_at"] is None and (gift["expires_at"] is None or gift["expires_at"] > moment) \
                and (gift["include_new_accounts"] or gift["max_account_rowid"] >= self.account_rowid(account_id))
            if not eligible:
                raise EconomyError(404, "That gift isn't available")
            try:
                self.db.execute("INSERT INTO global_gift_claims (gift_id, account_id, claimed_at, character_id) VALUES (?,?,?,?)",
                                (mail_id, account_id, moment, character_id))
            except Exception:
                raise EconomyError(409, "Already claimed")
            attachments = json.loads(gift["attachments"])
        else:
            row = self.db.execute("SELECT * FROM mail WHERE id = ? AND account_id = ?", (mail_id, account_id)).fetchone()
            if not row or (row["expires_at"] and row["expires_at"] <= moment):
                raise EconomyError(404, "Unknown or expired mail")
            if row["claimed_at"]:
                raise EconomyError(409, "Already claimed")
            self.db.execute("UPDATE mail SET claimed_at = ?, claimed_character_id = ? WHERE id = ?",
                            (moment, character_id, mail_id))
            attachments = json.loads(row["attachments"])
        self.apply(attachments, account_id, character_id, source=mail_id)
        return {"claimed": attachments}
