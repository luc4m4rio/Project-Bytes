"""
Character appearance validation, shared rules with the game (FBytesAppearanceCatalog::Validate in C++).

The appearance is a JSON document stored on the character (see Content/Data/AppearanceCatalog.json for what
is available):

    {
      "version": 1,
      "body": "male",
      "morphs":  {"height": 0.2, "noseWidth": -0.4},           # slider values, clamped to the morph's range
      "colors":  {"skin": "#8d5524", "hair": "#2b1b10"},       # #rrggbb, palette-restricted where defined
      "parts":   {"top": {"id": "tshirt", "colors": ["#202020", "#a00000"]}},
      "tattoos": [{"decal": "tat_skull", "region": "leftUpperArm", "x": 0.5, "y": 0.4,
                   "scale": 0.3, "rotation": 15, "color": "#101010", "opacity": 0.9, "mirror": false}]
    }

Numbers are clamped (a slider nudged out of range is not worth rejecting). Anything that would let a client
wear something it hasn't earned - an unknown or rank/faction-locked part or decal, a colour outside a palette,
too many tattoos - is an error, so the backend stays the authority on unlocks.
"""
from __future__ import annotations

import json
import os
import re

HEX_RE = re.compile(r"^#[0-9a-fA-F]{6}$")
MAX_APPEARANCE_BYTES = 16384


class Catalog:
    def __init__(self, data: dict):
        self.version = int(data.get("version", 1))
        self.max_tattoos = int(data.get("maxTattoos", 16))
        self.tattoo_min_scale = float(data.get("tattooMinScale", 0.05))
        self.tattoo_max_scale = float(data.get("tattooMaxScale", 1.0))
        self.bodies = {b["id"]: b for b in data.get("bodies", [])}
        self.morphs = {m["id"]: m for m in data.get("morphs", [])}
        self.colors = {c["id"]: c for c in data.get("colors", [])}
        self.slots = {s["id"]: s for s in data.get("slots", [])}
        self.parts = {p["id"]: p for p in data.get("parts", [])}
        self.regions = {r["id"]: r for r in data.get("regions", [])}
        self.decals = {d["id"]: d for d in data.get("decals", [])}

    @classmethod
    def load(cls, path: str) -> "Catalog":
        with open(path, "r", encoding="utf-8") as f:
            return cls(json.load(f))

    def default_part(self, slot: str, body: str) -> dict | None:
        """First part flagged default (else first rank-0 part) that fits the body. Mirrors C++ FindDefaultPart."""
        fitting = [p for p in self.parts.values()
                   if p["slot"] == slot and (not p.get("bodies") or body in p["bodies"]) and not p.get("minRank")
                   and not p.get("factions")]
        for p in fitting:
            if p.get("default"):
                return p
        return fitting[0] if fitting else None


def _clamp(value: float, lo: float, hi: float) -> float:
    return max(lo, min(hi, value))


def _number(value, what: str, errors: list[str]) -> float | None:
    if isinstance(value, bool) or not isinstance(value, (int, float)):
        errors.append(f"{what} must be a number")
        return None
    return float(value)


def _hex(value, what: str, errors: list[str]) -> str | None:
    if not isinstance(value, str) or not HEX_RE.match(value):
        errors.append(f"{what} must be a colour like #a1b2c3")
        return None
    return value.lower()


def _unlock_errors(item: dict, rank: int, faction: str) -> list[str]:
    """Wording mirrored in C++ (UnlockErrors in BytesAppearanceTypes.cpp)."""
    errors = []
    if int(item.get("minRank") or 0) > rank:
        errors.append(f"{item['displayName']} unlocks at rank {item['minRank']}")
    factions = item.get("factions") or []
    if factions and faction not in factions:
        errors.append(f"{item['displayName']} is {'/'.join(factions)} only")
    return errors


def validate(catalog: Catalog, raw: str, rank: int, faction: str) -> tuple[str, list[str]]:
    """Returns (normalized JSON string, errors). An empty appearance means "default look" and is kept empty."""
    if raw is None or raw == "":
        return "", []
    if not isinstance(raw, str) or len(raw.encode("utf-8")) > MAX_APPEARANCE_BYTES:
        return "", [f"Appearance must be a JSON string of at most {MAX_APPEARANCE_BYTES} bytes"]
    try:
        data = json.loads(raw)
    except ValueError:
        return "", ["Appearance is not valid JSON"]
    if not isinstance(data, dict):
        return "", ["Appearance must be a JSON object"]

    errors: list[str] = []
    if data.get("version") != catalog.version:
        errors.append(f"Unsupported appearance version {data.get('version')!r} (expected {catalog.version})")

    body = data.get("body")
    if body not in catalog.bodies:
        errors.append(f"Unknown body type {body!r}")
        return "", errors

    # Morphs: unknown sliders are dropped (old saves after a slider was removed), values clamped.
    morphs = {}
    for morph_id, value in (data.get("morphs") or {}).items():
        definition = catalog.morphs.get(morph_id)
        if not definition:
            continue
        number = _number(value, f"Morph '{morph_id}'", errors)
        if number is not None:
            morphs[morph_id] = round(_clamp(number, definition["min"], definition["max"]), 3)

    colors = {}
    for color_id, value in (data.get("colors") or {}).items():
        definition = catalog.colors.get(color_id)
        if not definition:
            continue
        color = _hex(value, definition["displayName"], errors)
        if color is None:
            continue
        palette = [c.lower() for c in definition.get("palette") or []]
        if palette and color not in palette:
            errors.append(f"{definition['displayName']} must be one of the preset colours")
            continue
        colors[color_id] = color

    parts = {}
    for slot_id, entry in (data.get("parts") or {}).items():
        slot = catalog.slots.get(slot_id)
        if not slot:
            errors.append(f"Unknown clothing slot '{slot_id}'")
            continue
        if not isinstance(entry, dict) or not entry.get("id"):
            continue  # empty slot
        part = catalog.parts.get(entry["id"])
        if not part:
            errors.append(f"Unknown item '{entry['id']}'")
            continue
        if part["slot"] != slot_id:
            errors.append(f"{part['displayName']} doesn't go in the {slot['displayName']} slot")
            continue
        if part.get("bodies") and body not in part["bodies"]:
            errors.append(f"{part['displayName']} isn't available for {catalog.bodies[body]['displayName']}")
            continue
        unlock = _unlock_errors(part, rank, faction)
        if unlock:
            errors.extend(unlock)
            continue
        part_colors = []
        for i, value in enumerate((entry.get("colors") or [])[:int(slot.get("colorChannels", 0))]):
            color = _hex(value, f"{part['displayName']} colour {i + 1}", errors)
            if color is not None:
                part_colors.append(color)
        parts[slot_id] = {"id": part["id"], "colors": part_colors}

    for slot_id, slot in catalog.slots.items():
        if slot.get("required") and slot_id not in parts:
            fallback = catalog.default_part(slot_id, body)
            if fallback:
                parts[slot_id] = {"id": fallback["id"], "colors": []}

    tattoos = []
    raw_tattoos = data.get("tattoos") or []
    if not isinstance(raw_tattoos, list):
        errors.append("tattoos must be a list")
        raw_tattoos = []
    if len(raw_tattoos) > catalog.max_tattoos:
        errors.append(f"At most {catalog.max_tattoos} tattoo layers")
    for index, layer in enumerate(raw_tattoos[:catalog.max_tattoos]):
        what = f"Tattoo layer {index + 1}"
        if not isinstance(layer, dict):
            errors.append(f"{what} must be an object")
            continue
        decal = catalog.decals.get(layer.get("decal"))
        if not decal:
            errors.append(f"{what}: unknown design '{layer.get('decal')}'")
            continue
        region = catalog.regions.get(layer.get("region"))
        if not region:
            errors.append(f"{what}: unknown body region '{layer.get('region')}'")
            continue
        if decal.get("regions") and region["id"] not in decal["regions"]:
            errors.append(f"{decal['displayName']} can't be placed on the {region['displayName']}")
            continue
        unlock = _unlock_errors(decal, rank, faction)
        if unlock:
            errors.extend(unlock)
            continue
        values = {}
        for key, default in (("x", 0.5), ("y", 0.5), ("scale", 0.3), ("rotation", 0.0), ("opacity", 1.0)):
            number = _number(layer.get(key, default), f"{what} {key}", errors)
            values[key] = default if number is None else number
        rotation = ((values["rotation"] + 180.0) % 360.0) - 180.0
        color = _hex(layer.get("color", "#101010"), f"{what} colour", errors) or "#101010"
        tattoos.append({
            "decal": decal["id"],
            "region": region["id"],
            "x": round(_clamp(values["x"], 0.0, 1.0), 4),
            "y": round(_clamp(values["y"], 0.0, 1.0), 4),
            "scale": round(_clamp(values["scale"], catalog.tattoo_min_scale, catalog.tattoo_max_scale), 4),
            "rotation": round(rotation, 2),
            "color": color,
            "opacity": round(_clamp(values["opacity"], 0.0, 1.0), 3),
            "mirror": bool(layer.get("mirror", False)),
        })

    normalized = {"version": catalog.version, "body": body, "morphs": morphs, "colors": colors,
                  "parts": parts, "tattoos": tattoos}
    return json.dumps(normalized, separators=(",", ":")), errors


def default_catalog_path() -> str:
    return os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                        "Content", "Data", "AppearanceCatalog.json")
