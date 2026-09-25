"""Appearance validation rules (Backend/appearance.py). Endpoint tests live in test_backend.py."""
import json
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import appearance as ap  # noqa: E402

CATALOG = ap.Catalog.load(ap.default_catalog_path())


def look(**overrides):
    base = {"version": 1, "body": "male", "morphs": {}, "colors": {}, "parts": {}, "tattoos": []}
    base.update(overrides)
    return json.dumps(base)


def check(raw, rank=1, faction="Enforcer"):
    normalized, errors = ap.validate(CATALOG, raw, rank, faction)
    return (json.loads(normalized) if normalized else None), errors


class AppearanceRules(unittest.TestCase):
    def test_empty_means_default_look(self):
        self.assertEqual(ap.validate(CATALOG, "", 1, "Enforcer"), ("", []))

    def test_morphs_clamped_and_unknown_dropped(self):
        out, errors = check(look(morphs={"height": 5, "muscle": -1, "noseWidth": -0.25, "gone": 1}))
        self.assertEqual(errors, [])
        self.assertEqual(out["morphs"], {"height": 1.0, "muscle": 0.0, "noseWidth": -0.25})

    def test_required_slots_filled_with_defaults(self):
        out, _ = check(look())
        self.assertEqual({s: p["id"] for s, p in out["parts"].items()},
                         {"top": "tshirt", "legs": "jeans", "shoes": "sneakers"})

    def test_palette_and_hex(self):
        self.assertEqual(check(look(colors={"skin": "#8D5524", "eyes": "#123abc"}))[0]["colors"],
                         {"skin": "#8d5524", "eyes": "#123abc"})
        self.assertEqual(len(check(look(colors={"skin": "#123456"}))[1]), 1)
        self.assertEqual(len(check(look(colors={"eyes": "blue"}))[1]), 1)

    def test_rank_and_faction_unlocks(self):
        coat = look(parts={"jacket": {"id": "coat_long", "colors": ["#000000"]}})
        self.assertEqual(check(coat)[1], ["Long Coat unlocks at rank 60"])
        self.assertEqual(check(coat, rank=60)[1], [])
        vest = look(parts={"jacket": {"id": "vest_tactical"}})
        self.assertEqual(check(vest, rank=80, faction="Criminal")[1], ["Tactical Vest is Enforcer only"])

    def test_part_rules(self):
        self.assertIn("doesn't go in", check(look(parts={"top": {"id": "jeans"}}))[1][0])
        self.assertIn("isn't available", check(look(body="female", parts={"facialHair": {"id": "beard_full"}}))[1][0])
        colors = check(look(parts={"glasses": {"id": "glasses_aviator", "colors": ["#111111", "#222222"]}}))[0]
        self.assertEqual(colors["parts"]["glasses"]["colors"], ["#111111"])  # only one channel

    def test_tattoos(self):
        layer = {"decal": "tat_skull", "region": "leftUpperArm", "x": 2, "y": -1, "scale": 9, "rotation": 270,
                 "opacity": 0.5, "color": "#ff0000", "mirror": True}
        out, errors = check(look(tattoos=[layer]))
        self.assertEqual(errors, [])
        self.assertEqual(out["tattoos"][0], {"decal": "tat_skull", "region": "leftUpperArm", "x": 1.0, "y": 0.0,
                                             "scale": 1.0, "rotation": -90.0, "color": "#ff0000", "opacity": 0.5,
                                             "mirror": True})
        self.assertIn("can't be placed", check(look(tattoos=[{"decal": "tat_teardrop", "region": "back"}]))[1][0])
        self.assertEqual(check(look(tattoos=[{"decal": "tat_dragon", "region": "back"}]))[1],
                         ["Dragon unlocks at rank 50"])
        too_many = [{"decal": "tat_stars", "region": "chest"}] * (CATALOG.max_tattoos + 1)
        self.assertIn("At most", check(look(tattoos=too_many))[1][0])

    def test_garbage(self):
        self.assertEqual(check("{nope")[1], ["Appearance is not valid JSON"])
        self.assertIn("Unknown body type", check(look(body="robot"))[1][0])
        self.assertIn("Unsupported appearance version", check(look(version=7))[1][0])


if __name__ == "__main__":
    unittest.main()
