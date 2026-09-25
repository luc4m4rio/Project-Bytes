"""End-to-end tests for the backend over real HTTP:  python -m unittest discover -s Backend/tests"""
import json
import os
import sys
import threading
import unittest
import urllib.error
import urllib.request

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import server as bb  # noqa: E402

SERVER_KEY = "test-server-key"


class Client:
    def __init__(self, base):
        self.base = base
        self.token = None

    def call(self, method, path, body=None, headers=None):
        data = json.dumps(body).encode() if body is not None else None
        req = urllib.request.Request(self.base + path, data=data, method=method)
        req.add_header("Content-Type", "application/json")
        if self.token:
            req.add_header("Authorization", f"Bearer {self.token}")
        for k, v in (headers or {}).items():
            req.add_header(k, v)
        try:
            with urllib.request.urlopen(req) as resp:
                return resp.status, json.loads(resp.read())
        except urllib.error.HTTPError as e:
            return e.code, json.loads(e.read())


class BackendTest(unittest.TestCase):
    def setUp(self):
        cfg = bb.load_config(os.path.join(os.path.dirname(bb.__file__), "config.json"))
        cfg.update(database=":memory:", serverKey=SERVER_KEY, passwordIterations=1000)
        self.backend = bb.Backend(cfg)
        self.httpd = bb.make_server(self.backend, "127.0.0.1", 0, quiet=True)
        threading.Thread(target=self.httpd.serve_forever, daemon=True).start()
        self.base = f"http://127.0.0.1:{self.httpd.server_address[1]}"
        self.client = Client(self.base)
        self.srv = Client(self.base)

    def tearDown(self):
        self.httpd.shutdown()
        self.httpd.server_close()

    # helpers
    def login(self, user="alice", pw="hunter22"):
        self.assertEqual(self.client.call("POST", "/v1/auth/register", {"username": user, "password": pw})[0], 200)
        status, body = self.client.call("POST", "/v1/auth/login", {"username": user, "password": pw})
        self.assertEqual(status, 200)
        self.client.token = body["sessionToken"]
        return body

    def make_char(self, name, faction="Enforcer"):
        status, body = self.client.call("POST", "/v1/characters", {"name": name, "faction": faction})
        self.assertEqual(status, 200, body)
        return body["character"]

    def register_server(self, district, port):
        status, body = self.srv.call("POST", "/v1/servers/register",
                                     {"districtId": district, "host": "127.0.0.1", "port": port},
                                     {"X-Bytes-Server-Key": SERVER_KEY})
        self.assertEqual(status, 200, body)
        return body

    # tests
    def test_accounts(self):
        self.login()
        self.assertEqual(self.client.call("POST", "/v1/auth/register",
                                          {"username": "ALICE", "password": "whatever"})[0], 409)
        self.assertEqual(self.client.call("POST", "/v1/auth/login",
                                          {"username": "alice", "password": "wrong!"})[0], 401)
        status, body = self.client.call("GET", "/v1/auth/me")
        self.assertEqual((status, body["account"]["username"]), (200, "alice"))
        self.client.call("POST", "/v1/auth/logout")
        self.assertEqual(self.client.call("GET", "/v1/characters")[0], 401)

    def test_multiple_characters_with_own_identity(self):
        self.login()
        a = self.make_char("Vex", "Criminal")
        b = self.make_char("Mara", "enforcer")
        self.assertEqual(b["faction"], "Enforcer")
        self.assertNotEqual(a["characterId"], b["characterId"])
        self.assertEqual(self.client.call("POST", "/v1/characters", {"name": "vex", "faction": "Enforcer"})[0], 409)
        self.assertEqual(self.client.call("POST", "/v1/characters", {"name": "x", "faction": "Enforcer"})[0], 400)
        self.assertEqual(self.client.call("POST", "/v1/characters", {"name": "NoFaction"})[0], 400)
        self.make_char("Third")
        self.make_char("Fourth")
        status, body = self.client.call("POST", "/v1/characters", {"name": "Fifth", "faction": "Enforcer"})
        self.assertEqual(status, 409)
        self.assertIn("slots", body["error"])
        self.assertEqual(self.client.call("DELETE", f"/v1/characters/{a['characterId']}")[0], 200)
        self.assertEqual(len(self.client.call("GET", "/v1/characters")[1]["characters"]), 3)

    def test_requirements(self):
        req = bb.normalize_requirements({"minRank": 80, "threats": ["silver"]})
        self.assertEqual(req["allowedThreats"], ["Silver"])
        self.assertEqual(len(bb.evaluate_requirements(req, 1, "Green", "Enforcer", [])), 2)
        self.assertEqual(bb.evaluate_requirements(req, 80, "Silver", "Criminal", []), [])
        self.assertEqual(bb.normalize_requirements({"maxThreat": "Bronze"})["allowedThreats"], ["Green", "Bronze"])
        self.assertEqual(bb.normalize_requirements({"minThreat": "Silver"})["allowedThreats"], ["Silver", "Gold"])
        empty = bb.normalize_requirements(None)
        self.assertEqual(bb.evaluate_requirements(empty, 1, "Gold", "Criminal", []), [])
        flags = bb.normalize_requirements({"requiredAccountFlags": ["tester"]})
        self.assertEqual(bb.evaluate_requirements(flags, 1, "Green", "Criminal", ["Tester"]), [])

    def test_join_flow(self):
        self.login()
        char = self.make_char("Vex", "Criminal")
        cid = char["characterId"]

        status, body = self.client.call("POST", "/v1/districts/join", {"characterId": cid, "districtId": "financial"})
        self.assertEqual(status, 503)  # nothing running yet

        self.assertEqual(self.srv.call("POST", "/v1/servers/register", {"districtId": "financial", "port": 1})[0], 401)
        reg1 = self.register_server("financial", 7777)
        reg2 = self.register_server("financial", 7778)
        self.assertEqual((reg1["instanceId"], reg2["instanceId"]), ("financial-1", "financial-2"))
        key = bytes(__import__("base64").b64decode(reg1["ticketKey"]))

        status, body = self.client.call("GET", f"/v1/districts?characterId={cid}")
        fin = next(d for d in body["districts"] if d["districtId"] == "financial")
        vet = next(d for d in body["districts"] if d["districtId"] == "waterfront-veteran")
        self.assertEqual((len(fin["instances"]), fin["ineligibleReasons"]), (2, []))
        self.assertEqual(len(vet["ineligibleReasons"]), 2)

        status, join = self.client.call("POST", "/v1/districts/join", {"characterId": cid, "districtId": "financial"})
        self.assertEqual(status, 200, join)
        claims = bb.verify_ticket(key, join["ticket"])
        self.assertEqual((claims["characterName"], claims["faction"], claims["serverId"]),
                         ("Vex", "Criminal", reg1["serverId"]))
        self.assertEqual(join["address"], "127.0.0.1:7777")
        with self.assertRaises(ValueError):
            bb.verify_ticket(b"wrong-key", join["ticket"])
        with self.assertRaises(ValueError):
            bb.verify_ticket(key, join["ticket"], at=claims["expiresAt"] + 1)

        hdr = {"X-Bytes-Server-Key": SERVER_KEY}
        # Wrong server can't redeem, right one can exactly once.
        self.assertEqual(self.srv.call("POST", "/v1/servers/redeem",
                                       {"serverId": reg2["serverId"], "ticketId": claims["ticketId"]}, hdr)[0], 403)
        status, red = self.srv.call("POST", "/v1/servers/redeem",
                                    {"serverId": reg1["serverId"], "ticketId": claims["ticketId"],
                                     "characterId": cid}, hdr)
        self.assertEqual((status, red["character"]["onlineInstance"]), (200, "financial-1"))
        self.assertEqual(self.srv.call("POST", "/v1/servers/redeem",
                                       {"serverId": reg1["serverId"], "ticketId": claims["ticketId"]}, hdr)[0], 409)

        # Veteran district: rejected with reasons, then allowed after dev stat change.
        self.register_server("waterfront-veteran", 7790)
        status, body = self.client.call("POST", "/v1/districts/join",
                                        {"characterId": cid, "districtId": "waterfront-veteran"})
        self.assertEqual(status, 403)
        self.assertEqual(len(body["reasons"]), 2)
        status, body = self.client.call("POST", "/v1/dev/characters/set",
                                        {"characterId": cid, "rank": 80, "threat": "silver"})
        self.assertEqual((status, body["character"]["rank"], body["character"]["threat"]), (200, 80, "Silver"))
        status, _ = self.client.call("POST", "/v1/districts/join",
                                     {"characterId": cid, "districtId": "waterfront-veteran"})
        self.assertEqual(status, 200)

        # Progression written back by a server; rank follows standing.
        status, body = self.srv.call("POST", "/v1/servers/characters/update",
                                     {"serverId": reg1["serverId"], "characterId": cid, "standingDelta": 1500,
                                      "moneyDelta": -100}, hdr)
        self.assertEqual((status, body["character"]["rank"]), (200, 81))

        # Heartbeat drives presence; unknown servers are told to re-register.
        self.srv.call("POST", "/v1/servers/heartbeat", {"serverId": reg1["serverId"], "characterIds": []}, hdr)
        chars = self.client.call("GET", "/v1/characters")[1]["characters"]
        self.assertEqual(chars[0]["onlineInstance"], "")
        self.assertEqual(self.srv.call("POST", "/v1/servers/heartbeat", {"serverId": "srv_nope"}, hdr)[0], 404)

    def test_fill_and_capacity(self):
        self.login()
        cid = self.make_char("Filler")["characterId"]
        reg = self.srv.call("POST", "/v1/servers/register",
                            {"districtId": "fightclub", "host": "127.0.0.1", "port": 7800, "maxPlayers": 1},
                            {"X-Bytes-Server-Key": SERVER_KEY})[1]
        self.client.call("POST", "/v1/dev/characters/set", {"characterId": cid, "rank": 10})
        self.assertEqual(self.client.call("POST", "/v1/districts/join",
                                          {"characterId": cid, "districtId": "fightclub"})[0], 200)
        # The unredeemed ticket reserves the only slot.
        status, body = self.client.call("POST", "/v1/districts/join", {"characterId": cid, "districtId": "fightclub"})
        self.assertEqual(status, 503, body)
        self.assertEqual(reg["maxPlayers"], 1)

    def test_stale_servers_are_reaped(self):
        reg = self.register_server("financial", 7777)
        self.backend.servers[reg["serverId"]]["lastSeen"] -= 1000
        self.assertEqual(self.backend.status()["servers"], [])


if __name__ == "__main__":
    unittest.main()
