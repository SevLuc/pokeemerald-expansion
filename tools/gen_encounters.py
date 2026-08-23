#!/usr/bin/env python3
"""
Wild-encounter generator for the FairRed hack.

Rebuilds every FireRed (and mirrored LeafGreen) wild-encounter table in
src/data/wild_encounters.json per docs/design/encounter-tables.md:

 - base forms only (family roots); every kept root catchable before the E4
 - grass vs water split; water unified across Old/Good/Super Rod + Surf
 - equal chance (flat encounter_rates; fishing rod-groups unified)
 - difficulty tiered by EFFECTIVE BST at each split (level cap + item access;
   stone/trade/item evos unlock at the Erika split)
 - vanilla per-area level bands kept (species swapped slot-by-slot)

Run:  python3 tools/gen_encounters.py
Idempotent; reproducible; prints coverage + per-split fairness report.
"""
import re, glob, json, os, sys, collections, itertools, statistics as st

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SPECIES_DIR = os.path.join(ROOT, "src/data/pokemon/species_info")
POOL_DOC = os.path.join(ROOT, "docs/overview/encounters-candidates.md")
WILD_JSON = os.path.join(ROOT, "src/data/wild_encounters.json")

# ---------------------------------------------------------------- species data
def first_int(expr):
    s = re.sub(r'[A-Za-z_][A-Za-z0-9_]*', '', expr)
    m = re.search(r'\d+', s)
    return int(m.group(0)) if m else None

def load_species():
    files = sorted(glob.glob(os.path.join(SPECIES_DIR, "gen_*_families.h")))
    defines = {}
    for f in files:
        for dm in re.finditer(r'#define\s+([A-Z_][A-Z0-9_]*)\s+(.+)$',
                              open(f, encoding="utf-8", errors="replace").read(), re.M):
            v = first_int(dm.group(2))
            if v is not None:
                defines[dm.group(1)] = v
    block_re = re.compile(r'\[(SPECIES_[A-Z0-9_]+)\]\s*=\s*\{', re.M)
    sp = {}
    for f in files:
        txt = open(f, encoding="utf-8", errors="replace").read()
        for m in block_re.finditer(txt):
            name = m.group(1)
            i = m.end() - 1; depth = 0
            while i < len(txt):
                c = txt[i]
                if c == '{': depth += 1
                elif c == '}':
                    depth -= 1
                    if depth == 0: break
                i += 1
            body = txt[m.end():i]
            def num(field):
                mm = re.search(r'\.%s\s*=\s*([^,\n]+)' % field, body)
                if not mm: return 0
                rhs = re.sub(r'[A-Za-z_][A-Za-z0-9_]*',
                             lambda x: str(defines.get(x.group(0), x.group(0))), mm.group(1))
                v = first_int(rhs)
                return v if v is not None else 0
            bst = sum(num(k) for k in ("baseHP", "baseAttack", "baseDefense",
                                       "baseSpeed", "baseSpAttack", "baseSpDefense"))
            if bst == 0:
                continue
            tm = re.search(r'\.types\s*=\s*MON_TYPES\(([^)]*)\)', body)
            types = [t.strip().replace("TYPE_", "") for t in tm.group(1).split(',')] if tm else []
            edges = []
            ev = re.search(r'\.evolutions\s*=\s*EVOLUTION\(', body)
            if ev:
                j = ev.end() - 1; d = 0
                while j < len(body):
                    if body[j] == '(': d += 1
                    elif body[j] == ')':
                        d -= 1
                        if d == 0: break
                    j += 1
                region = re.sub(r'CONDITIONS\([^)]*\)', '', body[ev.end():j])
                for tup in re.findall(r'\{([^{}]*)\}', region):
                    fields = [x.strip() for x in tup.split(',')]
                    tgt = fields[2] if len(fields) >= 3 and fields[2].startswith('SPECIES_') else None
                    if not tgt:
                        s2 = re.findall(r'SPECIES_[A-Z0-9_]+', tup)
                        tgt = s2[-1] if s2 else None
                    if tgt:
                        edges.append((fields[0] if fields else '',
                                      fields[1] if len(fields) > 1 else '', tgt))
            if name not in sp:
                sp[name] = {"bst": bst, "types": types, "edges": edges}
    return sp

SPECIES = load_species()

def types_of(s): return SPECIES[s]["types"]
def bst_of(s):   return SPECIES[s]["bst"]

# parent / root over the full graph
PARENT = {}
for s, d in SPECIES.items():
    for _, _, t in d["edges"]:
        if t in SPECIES:
            PARENT.setdefault(t, s)
def root_of(x):
    seen = set()
    while x in PARENT and x not in seen:
        seen.add(x); x = PARENT[x]
    return x

# ---------------------------------------------------------------- effective BST
ITEM_METHODS = {'EVO_ITEM', 'EVO_TRADE', 'EVO_SPIN', 'EVO_TRIGGER_DARK_SCROLL',
                'EVO_TRIGGER_WATER_SCROLL', 'EVO_TRIGGER_TABLET_CURSE', 'EVO_SCRIPT_TRIGGER'}
def reachable(method, param, cap, items):
    if method in ITEM_METHODS:
        return items
    if method == 'EVO_LEVEL':
        return int(param) <= cap if param.isdigit() and int(param) > 0 else True
    if method in ('EVO_LEVEL_BATTLE_ONLY', 'EVO_THRESHOLD', 'EVO_BATTLE_END'):
        return int(param) <= cap if param.isdigit() and int(param) > 0 else True
    if method == 'EVO_NONE':
        return False
    return True
_effcache = {}
def eff_bst(sp, cap, items):
    key = (sp, cap, items)
    if key in _effcache: return _effcache[key]
    def walk(s, seen):
        best = bst_of(s)
        for method, param, tgt in SPECIES[s]["edges"]:
            if tgt in SPECIES and tgt not in seen and reachable(method, param, cap, items):
                best = max(best, walk(tgt, seen | {tgt}))
        return best
    v = walk(sp, {sp})
    _effcache[key] = v
    return v

# ---------------------------------------------------------------- kept pool
REGION = {"alolan": "ALOLA", "galarian": "GALAR", "hisuian": "HISUI", "paldean": "PALDEA",
          "kalosian": "", "unovan": "", "kantonian": ""}
def normalize(tok):
    t = tok.strip()
    if not t: return None
    region = ""
    low = t.lower()
    for pre, suf in REGION.items():
        if low.startswith(pre + " "):
            region = suf; t = t[len(pre) + 1:]; break
    form = ""
    pm = re.search(r'\(([^)]*)\)', t)
    if pm:
        form = pm.group(1); t = t[:pm.start()].strip()
    base = t.upper().replace("'", "").replace(".", "").replace(":", "")
    base = base.replace("♀", "_F").replace("♂", "_M")
    base = re.sub(r'[\s\-]+', "_", base).strip("_")
    cand = "SPECIES_" + base
    tries = ([cand + "_" + region] if region else []) + [cand]
    if form:
        tries.append(cand + "_" + re.sub(r'[\s\-]+', "_", form.upper()))
    # also try known form suffixes for bare bases
    for suf in ("", "_CHEST", "_PHONY", "_RED_STRIPED", "_FULL_BELLY", "_DISGUISED",
                "_WEST", "_STANDARD_MODE", "_MALE", "_FAMILY_OF_FOUR", "_SHIELD", "_MIDDAY"):
        tries.append(cand + suf)
    for c in tries:
        if c in SPECIES: return c
    return None

def load_pool():
    doc = open(POOL_DOC, encoding="utf-8").read()
    matched = set()
    for line in doc.splitlines():
        s = line.strip()
        if not s or s.startswith("#") or s.startswith("---") or s.startswith("_") or s.startswith(">"):
            continue
        if s.startswith("**") and s.endswith("**"):
            continue
        for tok in s.split(","):
            tok = tok.strip().rstrip(".")
            if not tok or len(tok.split()) > 3:
                continue
            r = normalize(tok)
            if r: matched.add(r)
    return matched

POOL = load_pool()
ROOTS = sorted({root_of(p) for p in POOL})
LAND_ROOTS  = [r for r in ROOTS if "WATER" not in types_of(r)]
WATER_ROOTS = [r for r in ROOTS if "WATER" in types_of(r)]

# ---------------------------------------------------------------- splits
# (name, level cap, items?, player group target effective-BST)
SPLITS = [
    ("Brock",     14, False, 355),
    ("Misty",     23, False, 380),
    ("Surge",     27, False, 410),
    ("Erika",     29, True,  440),
    ("Koga",      43, True,  480),
    ("Sabrina",   43, True,  495),
    ("Blaine",    47, True,  510),
    ("Giovanni",  50, True,  530),
    ("EliteFour", 63, True,  560),
]
def split_for_level(maxlv):
    for i, (_, cap, _, _) in enumerate(SPLITS):
        if maxlv <= cap:
            return i
    return len(SPLITS) - 1

def biome_of(mapname):
    n = mapname.lower()
    if "forest" in n or "berryforest" in n: return "forest"
    if any(k in n for k in ("cave", "tunnel", "mtmoon", "mtember", "diglett", "sevault", "canyon", "ruinvalley")): return "cave"
    if "tower" in n: return "tower"
    if "mansion" in n: return "volcanic"
    if "seafoam" in n or "icefall" in n: return "ice"
    if "safari" in n: return "safari"
    if "powerplant" in n: return "electric"
    if "tanoby" in n or "ruins" in n: return "cave"
    return "field"

BIOME_PREF = {
    "field":   ["NORMAL", "FAIRY", "FLYING", "GRASS", "ELECTRIC", "BUG", "GROUND", "POISON", "PSYCHIC", "FIGHTING", "DARK", "FIRE", "ICE", "STEEL", "ROCK", "GHOST", "DRAGON"],
    "forest":  ["BUG", "GRASS", "POISON", "FLYING", "FAIRY", "NORMAL", "GHOST", "DARK", "PSYCHIC"],
    "cave":    ["ROCK", "GROUND", "STEEL", "FIGHTING", "POISON", "DARK", "DRAGON", "GHOST", "BUG", "NORMAL", "PSYCHIC"],
    "tower":   ["GHOST", "POISON", "PSYCHIC", "DARK", "FAIRY", "NORMAL", "FIGHTING"],
    "volcanic":["FIRE", "ROCK", "GROUND", "POISON", "DARK", "STEEL", "DRAGON", "FIGHTING"],
    "ice":     ["ICE", "ROCK", "GROUND", "STEEL", "PSYCHIC", "FAIRY", "DARK", "GHOST", "WATER"],
    "safari":  ["NORMAL", "GROUND", "GRASS", "BUG", "PSYCHIC", "FAIRY", "FIGHTING", "ROCK", "POISON", "FLYING", "DARK", "DRAGON"],
    "electric":["ELECTRIC", "STEEL", "POISON", "NORMAL", "GROUND", "FIRE", "PSYCHIC", "GHOST"],
}
def biome_ok(sp, biome):
    return any(t in BIOME_PREF.get(biome, []) for t in types_of(sp))

# ---------------------------------------------------------------- build tables
enc_data = json.load(open(WILD_JSON))
group = enc_data["wild_encounter_groups"][0]

# equal chance: flatten shared field rates (fishing groups kept as-is; the engine's
# ChooseWildMonIndex_Fishing already makes every rod roll the super-rod slots 5-9,
# so we author fishing species into slots 5-9 and match Surf water_mons to them)
for fld in group["fields"]:
    fld["encounter_rates"] = [1] * len(fld["encounter_rates"])

def levels_of(mons):
    xs = [m["min_level"] for m in mons] + [m["max_level"] for m in mons]
    return min(xs), max(xs)

# gather FireRed encounter maps, tag each with split + biome, process EARLY-FIRST
fr_entries = []
for e in group["encounters"]:
    if not e.get("base_label", "").endswith("_FireRed"):
        continue
    name = e["base_label"][1:-8]
    ref = e.get("land_mons", e.get("water_mons", e.get("fishing_mons", e.get("rock_smash_mons"))))
    _, maxlv = levels_of(ref["mons"])
    si = split_for_level(maxlv)
    fr_entries.append((si, name, e))
fr_entries.sort(key=lambda x: (x[0], x[1]))

# --only <substr>[,<substr>...]  (freeze / add-a-map mode)
# Only (re)fill FireRed maps whose base_label name contains one of the given
# substrings; treat every species already assigned to the other maps as "placed"
# so their tables stay byte-for-byte identical. Lets us add a new encounter map
# without reshuffling the whole world. Without --only, the full holistic rebuild
# runs as before.
ONLY = None
_argv = sys.argv[1:]
for _i, _a in enumerate(_argv):
    if _a.startswith("--only="):
        ONLY = [s for s in _a[len("--only="):].split(",") if s]
    elif _a == "--only" and _i + 1 < len(_argv):
        ONLY = [s for s in _argv[_i + 1].split(",") if s]
def is_target(name):
    return ONLY is not None and any(sub in name for sub in ONLY)

placed_land, placed_water = set(), set()
report_rows = []

if ONLY is not None:
    for _si, _name, _e in fr_entries:
        if is_target(_name):
            continue
        for _meth in ("land_mons", "rock_smash_mons"):
            if _meth in _e:
                placed_land.update(m["species"] for m in _e[_meth]["mons"])
        for _meth in ("water_mons", "fishing_mons"):
            if _meth in _e:
                placed_water.update(m["species"] for m in _e[_meth]["mons"])
    process_entries = [t for t in fr_entries if is_target(t[1])]
    print(f"--only {ONLY}: freezing existing tables, filling "
          f"{[t[1] for t in process_entries]}")
else:
    process_entries = fr_entries

def fill_table(roots, placed, biome, k, cap, items, target):
    """pick k distinct roots: eff@cap nearest target, globally-unplaced first, biome-pref."""
    ranked = sorted(roots, key=lambda r: abs(eff_bst(r, cap, items) - target))
    out = []
    def take(cond):
        for r in ranked:
            if len(out) == k: break
            if r in out: continue
            if cond(r): out.append(r)
    take(lambda r: r not in placed and biome_ok(r, biome))   # coverage + flavor
    take(lambda r: r not in placed)                          # coverage
    take(lambda r: biome_ok(r, biome))                       # flavor (repeat ok)
    take(lambda r: True)                                     # anything
    return out

for si, name, e in process_entries:
    _, cap, items, target = SPLITS[si]
    biome = biome_of(name)
    for meth in ("land_mons", "rock_smash_mons"):
        if meth not in e: continue
        mons = e[meth]["mons"]
        for slot, r in zip(mons, fill_table(LAND_ROOTS, placed_land, biome, len(mons), cap, items, target)):
            slot["species"] = r; placed_land.add(r)
    if "water_mons" in e or "fishing_mons" in e:
        # one shared set W of 5 species; Surf == fishing (engine rolls fishing slots 5-9)
        W = fill_table(WATER_ROOTS, placed_water, "ice", 5, cap, items, target)
        if "water_mons" in e:
            for i, slot in enumerate(e["water_mons"]["mons"]):
                slot["species"] = W[i % len(W)]
        if "fishing_mons" in e:
            for i, slot in enumerate(e["fishing_mons"]["mons"]):
                slot["species"] = W[i % len(W)]   # slots 0-4 mirror; 5-9 = W (the rolled set)
        for r in W:
            placed_water.add(r)
    report_rows.append((name, si, biome))

# coverage sweep: force any never-placed root into the nearest-fitting area of its split
def sweep(roots, placed, is_water):
    for r in roots:
        if r in placed: continue
        # find split whose target best matches this root's eff, then any area in it
        best = min(range(len(SPLITS)), key=lambda i: abs(eff_bst(r, SPLITS[i][1], SPLITS[i][2]) - SPLITS[i][3]))
        for si, name, e in fr_entries:
            if si != best: continue
            meths = (("water_mons","fishing_mons") if is_water else ("land_mons","rock_smash_mons"))
            for meth in meths:
                if meth in e and e[meth]["mons"]:
                    e[meth]["mons"][-1]["species"] = r; placed.add(r)
                    return_ok = True
                    break
            else:
                continue
            break
if ONLY is None:
    sweep(LAND_ROOTS, placed_land, False)
    sweep(WATER_ROOTS, placed_water, True)

# mirror FireRed -> LeafGreen (identical species+levels per map)
byname = {}
for e in group["encounters"]:
    bl = e.get("base_label", "")
    if bl.endswith("_FireRed"):
        byname[bl[:-8]] = e
for e in group["encounters"]:
    bl = e.get("base_label", "")
    if bl.endswith("_LeafGreen"):
        fr = byname.get(bl[:-10])
        if not fr: continue
        for meth in ("land_mons", "water_mons", "fishing_mons", "rock_smash_mons"):
            if meth in e and meth in fr:
                for a, b in zip(e[meth]["mons"], fr[meth]["mons"]):
                    a["species"] = b["species"]

json.dump(enc_data, open(WILD_JSON, "w"), indent=2)

# ---------------------------------------------------------------- verify/report
missing_land  = [r for r in LAND_ROOTS  if r not in placed_land]
missing_water = [r for r in WATER_ROOTS if r not in placed_water]
print(f"species parsed: {len(SPECIES)}  pool: {len(POOL)}  roots: {len(ROOTS)} "
      f"(land {len(LAND_ROOTS)}, water {len(WATER_ROOTS)})")
print(f"placed land {len(placed_land)}/{len(LAND_ROOTS)}  water {len(placed_water)}/{len(WATER_ROOTS)}")
if missing_land:  print("  MISSING LAND :", [x.replace('SPECIES_','') for x in missing_land])
if missing_water: print("  MISSING WATER:", [x.replace('SPECIES_','') for x in missing_water])

# per-split fairness: actual eff-BST of placed grass mons at that split's cap
bysplit = collections.defaultdict(list)
for si, name, e in fr_entries:
    cap, items = SPLITS[si][1], SPLITS[si][2]
    if "land_mons" in e:
        for m in e["land_mons"]["mons"]:
            bysplit[si].append(eff_bst(m["species"], cap, items))
print("\nper-split grass difficulty (effective BST at split cap):")
for i, (nm, cap, items, tgt) in enumerate(SPLITS):
    v = bysplit.get(i, [])
    if v:
        print(f"  {i} {nm:9} cap{cap:2} items={str(items):5} target{tgt}  "
              f"pool mean {st.mean(v):.0f} (n={len(v)}, {min(v)}-{max(v)})")
    else:
        print(f"  {i} {nm:9} cap{cap:2} target{tgt}  (no grass maps at this level tier)")
print(f"\nwrote {WILD_JSON}")

# ---------------------------------------------------------------- overview doc
OVERVIEW = os.path.join(ROOT, "docs/overview/encounters.md")
lines = ["# Wild Encounters (generated)\n",
         "Auto-generated by `tools/gen_encounters.py` from `src/data/wild_encounters.json`.",
         "Do not edit by hand; re-run the generator. Method/approach: "
         "`docs/design/encounter-tables.md`.\n",
         f"Base forms only (family roots); {len(placed_land)} land + {len(placed_water)} water "
         f"roots, all catchable before the E4. Equal chance per slot; water table shared across "
         f"Old/Good/Super Rod + Surf. Levels are vanilla per area.\n"]
def sp_list(mons):
    return ", ".join(m["species"].replace("SPECIES_", "") for m in mons)
cur_split = None
for si, name, e in fr_entries:
    if si != cur_split:
        cur_split = si
        nm, cap, items, tgt = SPLITS[si]
        lines.append(f"\n## Split {si}: {nm}  (cap {cap}, items={'yes' if items else 'no'}, target {tgt})\n")
    lines.append(f"### {name}  ({biome_of(name)})")
    if "land_mons" in e:
        lo, hi = levels_of(e["land_mons"]["mons"])
        lines.append(f"- grass Lv{lo}-{hi}: {sp_list(e['land_mons']['mons'])}")
    if "rock_smash_mons" in e:
        lines.append(f"- rock-smash: {sp_list(e['rock_smash_mons']['mons'])}")
    if "fishing_mons" in e or "water_mons" in e:
        wm = e.get("fishing_mons", e.get("water_mons"))
        lo, hi = levels_of(wm["mons"])
        uniq = list(dict.fromkeys(m["species"].replace("SPECIES_", "") for m in wm["mons"]))
        lines.append(f"- water (rods+Surf) Lv{lo}-{hi}: {', '.join(uniq)}")
    lines.append("")
open(OVERVIEW, "w").write("\n".join(lines))
print(f"wrote {OVERVIEW}")
