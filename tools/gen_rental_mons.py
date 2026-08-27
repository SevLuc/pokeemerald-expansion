#!/usr/bin/env python3
"""Generate the rental-mode Pokemon table from the moveset library.

Reads docs/battle-tower/movesets/*.json (the validated competitive sets) and
writes src/data/battle_tower/rental_mons.h: a const struct TrainerMon table where
each set becomes one rentable entry, plus a parallel tier array and per-tier index
ranges.

Option A (see the Phase 1 plan): the output .h is committed to the repo and this
script is run by hand when the JSON changes. It is NOT wired into the build.

Usage:
    python3 tools/gen_rental_mons.py

Run from the repo root. Exits non-zero on any inconsistency (e.g. the emitted
entry count not matching NUM_RENTAL_MONS in include/battle_tower_rental.h), so a
stale table is caught rather than silently shipped.
"""

import glob
import json
import os
import re
import sys

REPO_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MOVESET_DIR = os.path.join(REPO_ROOT, "docs", "battle-tower", "movesets")
OUT_PATH = os.path.join(REPO_ROOT, "src", "data", "battle_tower", "rental_mons.h")
PUBLIC_HEADER = os.path.join(REPO_ROOT, "include", "battle_tower_rental.h")

MAX_MON_MOVES = 4

# Pokemon-level JSON "tier" string -> RentalTier enum suffix. The order of this list
# is the RentalTier enum order and the sort order of the emitted table; all the
# restricted tiers must stay contiguous at the end (see FIRST_RESTRICTED below).
TIER_ORDER = [
    ("standard", "STANDARD"),
    ("regional", "REGIONAL"),
    ("altforme", "ALTFORME"),
    ("eviolite-nfe", "EVIOLITE"),
    ("mega", "MEGA"),
    ("restricted-legendary", "RESTRICTED_LEGENDARY"),
    ("sub-legendary", "SUB_LEGENDARY"),
    ("mythical", "MYTHICAL"),
    ("paradox", "PARADOX"),
    ("ultra-beast", "ULTRA_BEAST"),
    ("mega-restricted", "MEGA_RESTRICTED"),
]
JSON_TIER_TO_INDEX = {name: i for i, (name, _) in enumerate(TIER_ORDER)}
FIRST_RESTRICTED = JSON_TIER_TO_INDEX["restricted-legendary"]


def read_num_rental_mons():
    with open(PUBLIC_HEADER, encoding="utf-8") as fh:
        text = fh.read()
    m = re.search(r"#define\s+NUM_RENTAL_MONS\s+(\d+)", text)
    if not m:
        sys.exit("error: could not find #define NUM_RENTAL_MONS in %s" % PUBLIC_HEADER)
    return int(m.group(1))


def load_entries():
    """Return a flat list of entry dicts, one per set, tagged with tier index."""
    entries = []
    files = sorted(f for f in glob.glob(os.path.join(MOVESET_DIR, "*.json"))
                   if "_report" not in os.path.basename(f))
    for path in files:
        with open(path, encoding="utf-8") as fh:
            data = json.load(fh)
        for mon in data.get("pokemon", []):
            tier_str = mon.get("tier")
            if tier_str not in JSON_TIER_TO_INDEX:
                sys.exit("error: %s: unknown tier %r on %s"
                         % (os.path.basename(path), tier_str, mon.get("species")))
            tier_idx = JSON_TIER_TO_INDEX[tier_str]
            for s in mon.get("sets", []):
                entries.append(build_entry(mon["species"], tier_idx, s))
    return entries


def build_entry(species, tier_idx, s):
    moves = list(s.get("moves", []))
    moves = [m for m in moves if m and m != "MOVE_NONE"]
    moves = (moves + ["MOVE_NONE"] * MAX_MON_MOVES)[:MAX_MON_MOVES]

    ev = s.get("evs") or {}
    ivs = s.get("ivs") or {}
    return {
        "species": species,
        "tier": tier_idx,
        "moves": moves,
        "item": s.get("item") or "ITEM_NONE",
        "ability": s.get("ability") or "ABILITY_NONE",
        "nature": s.get("nature") or "NATURE_HARDY",
        # macro arg order is (hp, atk, def, speed, spatk, spdef)
        "ev": tuple(int(ev.get(k, 0)) for k in ("hp", "atk", "def", "speed", "spatk", "spdef")),
        # HP sets carry a real spread; everything else is flat 31 (a non-zero packed
        # value, so CreateFacilityMon applies it instead of the flat fixedIV).
        "iv": tuple(int(ivs.get(k, 31)) for k in ("hp", "atk", "def", "speed", "spatk", "spdef")),
    }


def format_entry(e):
    hp, atk, df, spd, spa, spdf = e["ev"]
    ihp, iatk, idf, ispd, ispa, ispdf = e["iv"]
    lines = [
        "    {",
        "        .species = %s," % e["species"],
        "        .moves = {%s}," % ", ".join(e["moves"]),
        "        .heldItem = %s," % e["item"],
        "        .ability = %s," % e["ability"],
        "        .nature = %s," % e["nature"],
        "        .ev = TRAINER_PARTY_EVS(%d, %d, %d, %d, %d, %d)," % (hp, atk, df, spd, spa, spdf),
        "        .iv = TRAINER_PARTY_IVS(%d, %d, %d, %d, %d, %d)," % (ihp, iatk, idf, ispd, ispa, ispdf),
        "        .lvl = 50,",
        "        .ball = BALL_POKE,",
        "    },",
    ]
    return "\n".join(lines)


def main():
    entries = load_entries()
    # Stable sort by tier keeps library order within a tier and makes every tier a
    # contiguous slice.
    entries.sort(key=lambda e: e["tier"])

    expected = read_num_rental_mons()
    if len(entries) != expected:
        sys.exit("error: emitted %d entries but NUM_RENTAL_MONS is %d. Update the "
                 "#define in include/battle_tower_rental.h to %d."
                 % (len(entries), expected, len(entries)))

    # Per-tier [start, count) ranges over the sorted table.
    ranges = []
    for tier_idx, (_, suffix) in enumerate(TIER_ORDER):
        idxs = [i for i, e in enumerate(entries) if e["tier"] == tier_idx]
        start = idxs[0] if idxs else 0
        ranges.append((suffix, start, len(idxs)))

    out = []
    out.append("// Generated by tools/gen_rental_mons.py from docs/battle-tower/movesets/*.json")
    out.append("// Do not edit by hand. Re-run the script to regenerate.")
    out.append("")
    out.append("const struct TrainerMon gRentalMons[NUM_RENTAL_MONS] =")
    out.append("{")
    out.append("\n".join(format_entry(e) for e in entries))
    out.append("};")
    out.append("")
    out.append("const u8 gRentalMonTier[NUM_RENTAL_MONS] =")
    out.append("{")
    # 20 tier bytes per line for readability.
    tiers = ["RENTAL_TIER_" + TIER_ORDER[e["tier"]][1] for e in entries]
    for i in range(0, len(tiers), 8):
        out.append("    " + ", ".join(tiers[i:i + 8]) + ",")
    out.append("};")
    out.append("")
    out.append("const struct RentalTierRange gRentalTierRanges[RENTAL_TIER_COUNT] =")
    out.append("{")
    for suffix, start, count in ranges:
        out.append("    [RENTAL_TIER_%s] = { %d, %d }," % (suffix, start, count))
    out.append("};")
    out.append("")

    os.makedirs(os.path.dirname(OUT_PATH), exist_ok=True)
    with open(OUT_PATH, "w", encoding="utf-8") as fh:
        fh.write("\n".join(out))

    # Report.
    print("wrote %s" % os.path.relpath(OUT_PATH, REPO_ROOT))
    print("  %d rental sets" % len(entries))
    restricted = sum(1 for e in entries if e["tier"] >= FIRST_RESTRICTED)
    print("  %d restricted, %d non-restricted" % (restricted, len(entries) - restricted))
    for suffix, start, count in ranges:
        print("    %-22s %5d  [%d, %d)" % (suffix, count, start, start + count))


if __name__ == "__main__":
    main()
