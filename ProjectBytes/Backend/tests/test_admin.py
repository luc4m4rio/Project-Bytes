"""Root cockpit: staff auth/2FA/permissions, audit chain, bans, commands, economy, gifts, deployments."""
import json
import os
import sys
import tempfile
import textwrap
import threading
import time
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, ".."))
import server as bb  # noqa: E402
import staff as st  # noqa: E402
from test_backend import SERVER_KEY, Client  # noqa: E402

PASSWORD = "correct-horse-battery"


class AdminTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()
        cfg = bb.load_config(os.path.join(os.path.dirname(bb.__file__), "config.json"))
        cfg.update(database=":memory:", serverKey=SERVER_KEY, passwordIterations=1000)
        self.fake_server = os.path.join(self.tmp, "fake_server.py")
        with open(self.fake_server, "w") as f:
            f.write(textwrap.dedent(f"""\
                #!{sys.executable}
                # Stand-in for a UE district server: registers, heartbeats, acks shutdown and exits.
                import json, os, sys, time, urllib.request
                a = {{k.lstrip('-').split('=')[0]: k.split('=', 1)[1] for k in sys.argv[1:] if k.startswith('-') and '=' in k}}
                def post(path, body):
                    req = urllib.request.Request(a['BytesBackend'] + path, data=json.dumps(body).encode(), method='POST',
                        headers={{'Content-Type': 'application/json', 'X-Bytes-Server-Key': os.environ['BYTES_SERVER_KEY']}})
                    return json.loads(urllib.request.urlopen(req).read())
                reg = post('/v1/servers/register', {{'districtId': a['District'], 'host': '127.0.0.1', 'port': int(a['port'])}})
                while True:
                    time.sleep(0.2)
                    hb = post('/v1/servers/heartbeat', {{'serverId': reg['serverId'], 'characterIds': []}})
                    for c in hb.get('commands', []):
                        post('/v1/servers/commands/ack', {{'serverId': reg['serverId'], 'results': [
                            {{'commandId': c['commandId'], 'ok': True, 'message': 'fake ' + c['type']}}]}})
                        if c['type'] == 'shutdown':
                            sys.exit(0)
                """))
        os.chmod(self.fake_server, 0o755)
        cfg["deploy"] = {"serverExe": self.fake_server, "basePort": 17777, "logDir": self.tmp, "forceKillAfterSeconds": 5}
        cfg["_baseDir"] = self.tmp
        self.backend = bb.Backend(cfg)
        self.game = bb.make_server(self.backend, "127.0.0.1", 0, quiet=True)
        self.admin = bb.make_admin_server(self.backend, "127.0.0.1", 0, quiet=True)
        for httpd in (self.game, self.admin):
            threading.Thread(target=httpd.serve_forever, daemon=True).start()
        game_url = f"http://127.0.0.1:{self.game.server_address[1]}"
        self.backend.orchestrator.backend_url = game_url
        self.player = Client(game_url)
        self.srv = Client(game_url)
        self.cockpit = Client(f"http://127.0.0.1:{self.admin.server_address[1]}")
        _, self.owner_secret = self.backend.staff.create("root", PASSWORD, "owner", "test")

    def tearDown(self):
        self.backend.orchestrator.shutdown_all()
        for httpd in (self.game, self.admin):
            httpd.shutdown()
            httpd.server_close()

    # helpers
    def sign_in(self, client, username="root", secret=None):
        status, body = client.call("POST", "/admin/v1/login", {
            "username": username, "password": PASSWORD, "code": st.totp_code(secret or self.owner_secret)})
        self.assertEqual(status, 200, body)
        client.token = body["token"]
        return body

    def make_player(self, name="alice", char="Vex"):
        self.player.token = None
        self.player.call("POST", "/v1/auth/register", {"username": name, "password": "hunter22"})
        _, body = self.player.call("POST", "/v1/auth/login", {"username": name, "password": "hunter22"})
        self.player.token = body["sessionToken"]
        _, c = self.player.call("POST", "/v1/characters", {"name": char, "faction": "Criminal"})
        return body["account"]["accountId"], c["character"]["characterId"]

    def register_server(self, district="financial", port=7777):
        _, reg = self.srv.call("POST", "/v1/servers/register", {"districtId": district, "host": "127.0.0.1", "port": port},
                               {"X-Bytes-Server-Key": SERVER_KEY})
        return reg

    def heartbeat(self, reg, chars=()):
        return self.srv.call("POST", "/v1/servers/heartbeat", {"serverId": reg["serverId"], "characterIds": list(chars)},
                             {"X-Bytes-Server-Key": SERVER_KEY})[1]

    # tests
    def test_totp(self):
        secret = st.new_totp_secret()
        self.assertGreaterEqual(st.verify_totp(secret, st.totp_code(secret)), 0)
        self.assertEqual(st.verify_totp(secret, "\u0660" * 6), -1)  # Arabic-Indic digits: rejected, not a crash
        # RFC 6238 test vector (SHA-1, T=59 -> 94287082, 8 digits)
        rfc = "GEZDGNBVGY3TQOJQGEZDGNBVGY3TQOJQ"
        self.assertEqual(st.totp_code(rfc, at=59, digits=8), "94287082")

    def test_auth_2fa_lockout_and_isolation(self):
        # Admin routes don't exist on the public game listener.
        self.assertEqual(self.player.call("POST", "/admin/v1/login", {})[0], 404)
        self.assertEqual(self.cockpit.call("GET", "/admin/v1/overview")[0], 401)
        # Right password, wrong/missing TOTP -> generic failure.
        self.assertEqual(self.cockpit.call("POST", "/admin/v1/login",
                                           {"username": "root", "password": PASSWORD, "code": ""})[0], 401)
        for _ in range(4):
            self.cockpit.call("POST", "/admin/v1/login", {"username": "root", "password": "nope", "code": "1"})
        status, body = self.cockpit.call("POST", "/admin/v1/login", {"username": "root", "password": PASSWORD,
                                                                      "code": st.totp_code(self.owner_secret)})
        self.assertEqual(status, 429, body)  # locked out after 5 failures
        self.backend.staff._failures.clear()
        self.sign_in(self.cockpit)
        self.assertEqual(self.cockpit.call("GET", "/admin/v1/overview")[0], 200)
        # Cockpit page served with a strict CSP.
        import urllib.request
        with urllib.request.urlopen(self.cockpit.base + "/") as resp:
            self.assertIn("frame-ancestors 'none'", resp.headers["Content-Security-Policy"])
            self.assertIn(b"cockpit", resp.read().lower())

    def test_permissions_and_escalation(self):
        self.sign_in(self.cockpit)
        status, body = self.cockpit.call("POST", "/admin/v1/staff", {"username": "mod1", "password": PASSWORD,
                                                                     "role": "moderator", "reason": "new hire"})
        self.assertEqual(status, 200, body)
        mod = Client(self.cockpit.base)
        self.sign_in(mod, "mod1", body["totpSecret"])
        account_id, _ = self.make_player()
        # Moderators can temp-ban within their limit but not permanently, and can't give items or manage staff.
        self.assertEqual(mod.call("POST", f"/admin/v1/players/{account_id}/ban",
                                  {"reason": "toxic", "durationHours": 0})[0], 403)
        self.assertEqual(mod.call("POST", f"/admin/v1/players/{account_id}/ban",
                                  {"reason": "toxic", "durationHours": 24})[0], 200)
        self.assertEqual(mod.call("POST", "/admin/v1/grants", {"accountId": account_id, "currency": "bp",
                                                               "amount": 5, "reason": "nope"})[0], 403)
        self.assertEqual(mod.call("GET", "/admin/v1/staff")[0], 403)
        # Reason is mandatory.
        self.assertEqual(self.cockpit.call("POST", f"/admin/v1/players/{account_id}/ban", {"durationHours": 1})[0], 400)
        # Admins don't manage staff (so can't mint owners); the last owner can't remove themselves.
        _, adm = self.cockpit.call("POST", "/admin/v1/staff", {"username": "adm1", "password": PASSWORD, "role": "admin",
                                                               "reason": "ops"})
        admin_client = Client(self.cockpit.base)
        self.sign_in(admin_client, "adm1", adm["totpSecret"])
        self.assertEqual(admin_client.call("POST", "/admin/v1/staff", {"username": "evil", "password": PASSWORD,
                                                                       "role": "owner", "reason": "promote"})[0], 403)
        me = self.cockpit.call("GET", "/admin/v1/me")[1]["staff"]
        self.assertEqual(self.cockpit.call("POST", f"/admin/v1/staff/{me['staffId']}",
                                           {"disabled": True, "reason": "oops"})[0], 400)
        self.assertEqual(self.cockpit.call("POST", f"/admin/v1/staff/{me['staffId']}",
                                           {"role": "admin", "reason": "demote myself"})[0], 409)

    def test_bans_enforced_everywhere(self):
        self.sign_in(self.cockpit)
        account_id, char_id = self.make_player()
        reg = self.register_server()
        self.heartbeat(reg, [char_id])
        status, body = self.cockpit.call("POST", f"/admin/v1/players/{account_id}/ban",
                                         {"reason": "cheating", "publicReason": "Aimbot", "durationHours": 48})
        self.assertEqual(status, 200, body)
        self.assertEqual(len(body["kickCommands"]), 1)  # online -> kicked
        commands = self.heartbeat(reg, [char_id])["commands"]
        self.assertEqual((commands[0]["type"], commands[0]["characterId"]), ("kick", char_id))
        self.assertIn("Aimbot", commands[0]["message"])
        # Sessions revoked, login refused with reason.
        self.assertEqual(self.player.call("GET", "/v1/characters")[0], 401)
        status, body = self.player.call("POST", "/v1/auth/login", {"username": "alice", "password": "hunter22"})
        self.assertEqual(status, 403)
        self.assertIn("Reason: Aimbot", body["reasons"])
        # Ban log + revoke.
        bans = self.cockpit.call("GET", "/admin/v1/bans?active=1")[1]["bans"]
        self.assertEqual(len(bans), 1)
        self.assertEqual(self.cockpit.call("POST", f"/admin/v1/bans/{bans[0]['banId']}/revoke",
                                           {"reason": "appeal accepted"})[0], 200)
        self.assertEqual(self.player.call("POST", "/v1/auth/login", {"username": "alice", "password": "hunter22"})[0], 200)

    def test_commands_roundtrip(self):
        self.sign_in(self.cockpit)
        reg1 = self.register_server("financial", 7777)
        reg2 = self.register_server("waterfront", 7778)
        status, body = self.cockpit.call("POST", "/admin/v1/commands", {
            "type": "broadcast", "message": "Restart in 10 minutes", "target": {"type": "all"}, "reason": "patch"})
        self.assertEqual((status, len(body["commandIds"])), (200, 2))
        self.cockpit.call("POST", "/admin/v1/commands", {"type": "shutdown", "delaySeconds": 60,
                                                         "target": {"type": "district", "id": "waterfront"},
                                                         "reason": "maintenance", "message": "bye"})
        c1 = self.heartbeat(reg1)["commands"]
        c2 = self.heartbeat(reg2)["commands"]
        self.assertEqual([c["type"] for c in c1], ["broadcast"])
        self.assertEqual([c["type"] for c in c2], ["broadcast", "shutdown"])
        self.assertEqual(c2[1]["delaySeconds"], 60)
        self.assertEqual(self.heartbeat(reg1)["commands"], [])  # delivered once
        self.srv.call("POST", "/v1/servers/commands/ack", {"serverId": reg1["serverId"], "results": [
            {"commandId": c1[0]["commandId"], "ok": True, "message": "shown to 3 players"}]},
            {"X-Bytes-Server-Key": SERVER_KEY})
        done = {c["commandId"]: c for c in self.cockpit.call("GET", "/admin/v1/commands")[1]["commands"]}
        self.assertEqual((done[c1[0]["commandId"]]["status"], done[c1[0]["commandId"]]["result"]),
                         ("done", "shown to 3 players"))
        # exec is owner-only by default.
        self.assertEqual(self.cockpit.call("POST", "/admin/v1/commands", {
            "type": "exec", "consoleCommand": "stat unit", "target": {"type": "server", "id": "financial-1"},
            "reason": "perf check"})[0], 200)

    def test_grants_gifts_and_mail(self):
        self.sign_in(self.cockpit)
        account_id, char_id = self.make_player()
        status, body = self.cockpit.call("POST", "/admin/v1/grants", {
            "characterId": char_id, "itemId": "wpn_ntec5_gold", "reason": "tournament winner"})
        self.assertEqual(status, 200, body)
        self.cockpit.call("POST", "/admin/v1/grants", {"accountId": account_id, "currency": "bp", "amount": 1500,
                                                       "reason": "compensation"})
        self.cockpit.call("POST", "/admin/v1/grants", {"characterId": char_id, "currency": "money", "amount": -1000,
                                                       "reason": "exploit rollback"})
        inv = self.player.call("GET", f"/v1/characters/{char_id}/inventory")[1]["items"]
        self.assertEqual([i["itemId"] for i in inv], ["wpn_ntec5_gold"])
        self.assertEqual(self.player.call("GET", "/v1/wallet")[1]["currencies"][0]["amount"], 1500)
        self.assertEqual(self.player.call("GET", "/v1/characters")[1]["characters"][0]["money"], 4000)

        attachments = [{"type": "currency", "currency": "bp", "amount": 250},
                       {"type": "item", "itemId": "con_frag_grenade", "quantity": 5}]
        # Gift to everyone needs the typed confirmation.
        self.assertEqual(self.cockpit.call("POST", "/admin/v1/gifts", {"target": "all", "subject": "Launch week",
                                                                       "attachments": attachments, "reason": "launch"})[0], 400)
        status, body = self.cockpit.call("POST", "/admin/v1/gifts", {
            "target": "all", "subject": "Launch week", "attachments": attachments, "reason": "launch",
            "confirm": "GIFT ALL PLAYERS", "includeNewAccounts": False})
        self.assertEqual(status, 200, body)
        self.cockpit.call("POST", "/admin/v1/gifts", {"target": "account", "accountId": account_id,
                                                      "subject": "Sorry about the crash",
                                                      "attachments": [{"type": "item", "itemId": "spc_name_change"}],
                                                      "reason": "ticket #42"})
        mail = self.player.call("GET", "/v1/mail")[1]["mail"]
        self.assertEqual(sorted(m["subject"] for m in mail), ["Launch week", "Sorry about the crash"])
        gift = next(m for m in mail if m["kind"] == "gift")
        status, body = self.player.call("POST", f"/v1/mail/{gift['mailId']}/claim", {"characterId": char_id})
        self.assertEqual(status, 200, body)
        self.assertEqual(self.player.call("POST", f"/v1/mail/{gift['mailId']}/claim", {"characterId": char_id})[0], 409)
        self.assertEqual(self.player.call("GET", "/v1/wallet")[1]["currencies"][0]["amount"], 1750)
        # Accounts created after a non-inclusive gift don't get it.
        self.make_player("bob", "Mara")
        self.assertEqual(self.player.call("GET", "/v1/mail")[1]["mail"], [])

    def test_audit_chain_detects_tampering(self):
        self.sign_in(self.cockpit)
        account_id, _ = self.make_player()
        self.cockpit.call("POST", f"/admin/v1/players/{account_id}/flags", {"flag": "tester", "reason": "QA group"})
        verify = self.cockpit.call("GET", "/admin/v1/audit/verify")[1]
        self.assertTrue(verify["ok"])
        entries = self.cockpit.call("GET", "/admin/v1/audit?action=flag")[1]["entries"]
        self.assertEqual(entries[0]["reason"], "QA group")
        self.backend.db.execute("UPDATE audit_log SET reason = 'nothing to see' WHERE action LIKE 'player.flag%'")
        self.backend.db.commit()
        self.assertFalse(self.cockpit.call("GET", "/admin/v1/audit/verify")[1]["ok"])

    def test_deploy_spin_up_and_stop(self):
        self.sign_in(self.cockpit)
        status, body = self.cockpit.call("POST", "/admin/v1/deployments",
                                         {"districtId": "financial", "count": 2, "reason": "evening peak"})
        self.assertEqual(status, 200, body)
        deadline = time.time() + 10
        while time.time() < deadline and len(self.backend.servers) < 2:
            time.sleep(0.1)
        deployments = self.cockpit.call("GET", "/admin/v1/deployments")[1]["deployments"]
        self.assertEqual(sorted(d["status"] for d in deployments), ["running", "running"])
        target = deployments[0]
        status, body = self.cockpit.call("POST", f"/admin/v1/deployments/{target['deploymentId']}/stop",
                                         {"mode": "graceful", "delaySeconds": 5, "reason": "scale down"})
        self.assertEqual(status, 200, body)
        self.assertTrue(body["commandId"])
        deadline = time.time() + 10
        while time.time() < deadline:
            d = next(x for x in self.cockpit.call("GET", "/admin/v1/deployments")[1]["deployments"]
                     if x["deploymentId"] == target["deploymentId"])
            if d["status"] == "stopped":
                break
            time.sleep(0.2)
        self.assertEqual(d["status"], "stopped")


    # ---- security regressions ----------------------------------------------------------------------

    def test_login_hardening(self):
        # Unicode digits used to raise inside compare_digest -> 500 only when the password was right.
        status, body = self.cockpit.call("POST", "/admin/v1/login", {"username": "root", "password": PASSWORD,
                                                                      "code": "\u0660" * 6})
        self.assertEqual((status, body["error"]), (401, "Invalid credentials"))
        # Padding/case can't create a fresh lockout bucket.
        for name in ("root", " root", "ROOT", "root\t", "\troot"):
            self.cockpit.call("POST", "/admin/v1/login", {"username": name, "password": "wrong", "code": "1"})
        self.assertEqual(self.cockpit.call("POST", "/admin/v1/login", {
            "username": "  Root ", "password": PASSWORD, "code": st.totp_code(self.owner_secret)})[0], 429)
        self.backend.staff._failures.clear()
        # A TOTP code works once.
        self.sign_in(self.cockpit)
        self.assertEqual(self.cockpit.call("POST", "/admin/v1/login", {
            "username": "root", "password": PASSWORD, "code": st.totp_code(self.owner_secret)})[0], 401)

    def test_limits_scoping_and_unban(self):
        self.sign_in(self.cockpit)
        secrets_by_role = {}
        for role in ("support", "gamemaster", "moderator"):
            _, body = self.cockpit.call("POST", "/admin/v1/staff", {"username": role + "1", "password": PASSWORD,
                                                                    "role": role, "reason": "test"})
            client = Client(self.cockpit.base)
            self.sign_in(client, role + "1", body["totpSecret"])
            secrets_by_role[role] = client
        alice, alice_char = self.make_player("alice", "Vex")
        _, bob_char = self.make_player("bob", "Mara")
        # Repeating attachments can't multiply a role's cap.
        status, _ = secrets_by_role["support"].call("POST", "/admin/v1/gifts", {
            "target": "account", "accountId": alice, "subject": "x", "reason": "test",
            "attachments": [{"type": "currency", "currency": "bp", "amount": 10000}] * 10})
        self.assertEqual(status, 403)
        # Removing an item must name the character that owns it.
        self.cockpit.call("POST", "/admin/v1/grants", {"characterId": alice_char, "itemId": "wpn_obir", "reason": "test grant"})
        entry = self.player.call("GET", f"/v1/characters/{bob_char}/inventory")[1]["items"]
        self.assertEqual(entry, [])
        alice_inv = self.backend.economy.inventory(alice_char)
        status, _ = secrets_by_role["gamemaster"].call("POST", "/admin/v1/grants", {
            "characterId": bob_char, "removeEntryId": alice_inv[0]["entryId"], "reason": "sneaky"})
        self.assertEqual(status, 404)
        self.assertEqual(len(self.backend.economy.inventory(alice_char)), 1)
        # Moderators can't lift an owner's permanent ban.
        ban = self.cockpit.call("POST", f"/admin/v1/players/{alice}/ban", {"reason": "cheat", "durationHours": 0})[1]
        self.assertEqual(secrets_by_role["moderator"].call("POST", f"/admin/v1/bans/{ban['banId']}/revoke",
                                                           {"reason": "friend"})[0], 403)

    def test_idle_timeout_ignores_background_polls(self):
        self.sign_in(self.cockpit)
        self.backend.staff.idle_timeout = 1
        time.sleep(1.2)
        status, _ = self.cockpit.call("GET", "/admin/v1/overview", headers={"X-Cockpit-Background": "1"})
        self.assertEqual(status, 401)

    def test_audit_detects_deleted_tail_and_host_check(self):
        self.sign_in(self.cockpit)
        account_id, _ = self.make_player()
        self.cockpit.call("POST", f"/admin/v1/players/{account_id}/flags", {"flag": "tester", "reason": "QA group"})
        self.assertTrue(self.backend.staff.verify_audit_chain()["ok"])
        self.backend.db.execute("DELETE FROM audit_log WHERE seq = (SELECT MAX(seq) FROM audit_log)")
        self.backend.db.commit()
        self.assertFalse(self.backend.staff.verify_audit_chain()["ok"])
        # DNS rebinding: a foreign Host header is refused.
        self.assertEqual(self.cockpit.call("GET", "/admin/v1/me", headers={"Host": "evil.example:8090"})[0], 403)


if __name__ == "__main__":
    unittest.main()
