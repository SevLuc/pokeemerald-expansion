#!/usr/bin/env python3
"""Regenerate docs/data/pokedex-index.json + movepools.json from repo source.

Run from repo root:  python3 docs/data/build_dex.py
Rebuild after pulling RHH (species/learnset data may change).

Sources (hack-accurate, so teams built from this always work in the build):
  src/data/pokemon/species_info/gen_*_families.h  -> typing + generation
  src/data/pokemon/all_learnables.json            -> full learnable movepool
"""
import re, json, os, shutil, unicodedata

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
SPECIES_DIR = os.path.join(ROOT, "src/data/pokemon/species_info")
LEARN = os.path.join(ROOT, "src/data/pokemon/all_learnables.json")
OUTDIR = os.path.join(ROOT, "docs/data")
os.makedirs(OUTDIR, exist_ok=True)

with open(LEARN) as f:
    learnables = json.load(f)

def clean_type(t):
    return t.strip().replace("TYPE_", "")

block_re = re.compile(r"\[SPECIES_([A-Z0-9_]+)\]\s*=\s*\{")
# accept MON_TYPES(...), { TYPE_A, TYPE_B }, or a *_FAMILY_TYPES macro
types_re = re.compile(r"\.types\s*=\s*(MON_TYPES\(([^)]*)\)|\{([^}]*)\}|([A-Z0-9_]+_FAMILY_TYPES))")

# resolve *_FAMILY_TYPES macros, taking the P_UPDATED_TYPES >= GEN_6 branch
# (build has P_UPDATED_TYPES = GEN_LATEST). Definitions appear Fairy-branch first.
macros = {}
def_re = re.compile(r"#define\s+([A-Z0-9_]+_FAMILY_TYPES)\s*\{([^}]*)\}")
for gen in range(1, 10):
    p = os.path.join(SPECIES_DIR, f"gen_{gen}_families.h")
    if not os.path.exists(p):
        continue
    for m in def_re.finditer(open(p).read()):
        name = m.group(1)
        if name not in macros:  # first def = GEN_6+ (Fairy) branch
            macros[name] = [clean_type(a) for a in m.group(2).split(",") if a.strip()]

def dedupe(args):
    out = []
    for a in args:
        if a not in out:
            out.append(a)
    return out

index = {}
counts = {}
for gen in range(1, 10):
    path = os.path.join(SPECIES_DIR, f"gen_{gen}_families.h")
    if not os.path.exists(path):
        continue
    text = open(path).read()
    positions = [(m.group(1), m.start()) for m in block_re.finditer(text)]
    for i, (name, start) in enumerate(positions):
        end = positions[i+1][1] if i+1 < len(positions) else len(text)
        chunk = text[start:end]
        tm = types_re.search(chunk)
        if not tm:
            continue
        if tm.group(2) is not None:      # MON_TYPES(...)
            raw = tm.group(2)
        elif tm.group(3) is not None:    # { TYPE_A, TYPE_B }
            raw = tm.group(3)
        else:                            # *_FAMILY_TYPES macro
            types = dedupe(macros.get(tm.group(4), []))
            index[name] = {"gen": gen, "types": types, "hasMovepool": name in learnables}
            counts[gen] = counts.get(gen, 0) + 1
            continue
        types = dedupe([clean_type(a) for a in raw.split(",") if a.strip()])
        index[name] = {"gen": gen, "types": types, "hasMovepool": name in learnables}
        counts[gen] = counts.get(gen, 0) + 1

# movepool keys that only exist as forms in species_info (GASTRODON -> GASTRODON_WEST)
for k in list(learnables.keys()):
    if k in index:
        continue
    match = next((n for n in index if n.startswith(k + "_")), None)
    if match:
        src = index[match]
        index[k] = {"gen": src["gen"], "types": list(src["types"]),
                    "hasMovepool": True, "baseFormAlias": match}

# macro-defined species (UNOWN/ARCEUS/etc.) hide types in expansion macros the
# block parser can't read. Canonical base-form types, hardcoded.
def fold(s):
    return "".join(c for c in unicodedata.normalize("NFKD", s) if not unicodedata.combining(c))
FALLBACK = {
    "UNOWN": (2, ["PSYCHIC"]),      "MOTHIM": (4, ["BUG", "FLYING"]),
    "GENESECT": (5, ["BUG", "STEEL"]), "SCATTERBUG": (6, ["BUG"]),
    "SPEWPA": (6, ["BUG"]),         "VIVILLON": (6, ["BUG", "FLYING"]),
    "FLABEBE": (6, ["FAIRY"]),      "FLORGES": (6, ["FAIRY"]),
    "FURFROU": (6, ["NORMAL"]),     "MINIOR": (7, ["ROCK", "FLYING"]),
    "SILVALLY": (7, ["NORMAL"]),    "ALCREMIE": (8, ["FAIRY"]),
    "ARCEUS": (4, ["NORMAL"]),      "OGERPON": (9, ["GRASS"]),
}
for k in list(learnables.keys()):
    if k in index:
        continue
    fb = FALLBACK.get(fold(k))
    if fb:
        index[k] = {"gen": fb[0], "types": fb[1], "hasMovepool": True,
                    "typesFromExpansionMacro": True}

idx_path = os.path.join(OUTDIR, "pokedex-index.json")
with open(idx_path, "w") as f:
    json.dump(index, f, indent=1, sort_keys=True)
shutil.copyfile(LEARN, os.path.join(OUTDIR, "movepools.json"))

orphans = [k for k in learnables if k not in index]
print("TOTAL_SPECIES", len(index))
print("PER_GEN", json.dumps(counts, sort_keys=True))
print("WITH_MOVEPOOL", sum(1 for e in index.values() if e["hasMovepool"]))
print("MOVES_KEYS", len(learnables))
print("ORPHANS", len(orphans), orphans[:15])
