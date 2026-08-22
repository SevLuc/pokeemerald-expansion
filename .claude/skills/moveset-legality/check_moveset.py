#!/usr/bin/env python3
"""
Moveset legality report for a single species at a level cap.

Usage:
    python3 .claude/skills/moveset-legality/check_moveset.py SPECIES [LEVEL_CAP]

    SPECIES     species constant WITHOUT the SPECIES_ prefix, e.g. ONIX,
                GEODUDE_ALOLA, GROWLITHE_HISUI, CHEWTLE.
    LEVEL_CAP   integer, default 14.

Outputs (all sourced from THIS build's data, no external assumptions):
  - the level cap used
  - the legal move pool at that cap, split into:
      level-up (<= cap), egg moves, TM moves, tutor/other teachable moves
  - the higher-level level-up moves that are OUT (locked by the cap)
  - every advised set for the species from docs/data/trainer-movesets.json,
    with per-move legality and the reason

Data sources:
  include/config/pokemon.h        -> configured level-up learnset gen
  include/config/general.h        -> GEN_LATEST value
  src/data/pokemon/level_up_learnsets/gen_N.h
  src/data/pokemon/egg_moves.h
  include/constants/tms_hms.h     -> this build's TM/HM list
  src/data/pokemon/all_learnables.json -> full legal pool (level-up+egg+TM+tutor)
  docs/data/trainer-movesets.json -> advised sets from other hard romhacks
"""
import re, json, sys, os

def norm(m):
    m = m.upper().replace('MOVE_', '').replace('-', ' ').replace('_', ' ')
    return ''.join(ch for ch in m if ch.isalnum())

def pretty(move_const):
    return move_const.replace('MOVE_', '').replace('_', ' ').title()

def camel(species):
    return ''.join(tok.capitalize() for tok in species.split('_'))

def resolve_gen(root):
    cfg = open(os.path.join(root, 'include/config/pokemon.h')).read()
    val = re.search(r'#define P_LVL_UP_LEARNSETS\s+(\S+)', cfg).group(1)
    if val == 'GEN_LATEST':
        gl = open(os.path.join(root, 'include/config/general.h')).read()
        val = re.search(r'#define GEN_LATEST\s+GEN_(\d+)', gl).group(1)
        return int(val)
    m = re.match(r'GEN_(\d+)', val)
    return int(m.group(1)) if m else 9

def find_block(text, symbol):
    m = re.search(re.escape(symbol) + r'\[\]\s*=\s*\{(.*?)\};', text, re.S)
    return m.group(1) if m else None

def get_levelup(root, species, gen):
    path = os.path.join(root, f'src/data/pokemon/level_up_learnsets/gen_{gen}.h')
    text = open(path).read()
    sym = f's{camel(species)}LevelUpLearnset'
    blk = find_block(text, sym)
    if blk is None:  # fallback: match by normalized symbol
        for m in re.finditer(r'(s\w+LevelUpLearnset)\[\]', text):
            if norm(m.group(1).replace('LevelUpLearnset','').lstrip('s')) == norm(species):
                blk = find_block(text, m.group(1)); break
    out = {}
    if blk:
        for lv, mv in re.findall(r'LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*(MOVE_[A-Z0-9_]+)\s*\)', blk):
            out.setdefault(norm(mv), (int(lv), mv))
            # keep earliest level
            if int(lv) < out[norm(mv)][0]:
                out[norm(mv)] = (int(lv), mv)
    return out

def get_egg(root, species):
    text = open(os.path.join(root, 'src/data/pokemon/egg_moves.h')).read()
    sym = f's{camel(species)}EggMoveLearnset'
    blk = find_block(text, sym)
    if blk is None:
        return {}
    return {norm(mv): mv for mv in re.findall(r'MOVE_[A-Z0-9_]+', blk) if mv != 'MOVE_UNAVAILABLE'}

def get_tms(root):
    text = open(os.path.join(root, 'include/constants/tms_hms.h')).read()
    return {norm('MOVE_' + m): 'MOVE_' + m for m in re.findall(r'F\((\w+)\)', text)}

def get_full_pool(root, species):
    d = json.load(open(os.path.join(root, 'src/data/pokemon/all_learnables.json')))
    key = species if species in d else next((k for k in d if k.upper() == species.upper()), None)
    return {norm(x): x for x in d.get(key, [])}, key

def _load_json_local_or_git(root, relpath):
    """Read a JSON data file from the working tree, or fall back to
    origin/master (the branch that ships the docs/data guide)."""
    path = os.path.join(root, relpath)
    if os.path.exists(path):
        return json.load(open(path))
    import subprocess
    for ref in ('origin/master', 'master'):
        try:
            out = subprocess.run(['git', 'show', f'{ref}:{relpath}'],
                                 cwd=root, capture_output=True, text=True)
            if out.returncode == 0 and out.stdout.strip():
                return json.loads(out.stdout)
        except Exception:
            pass
    return None

def get_advised(root, species):
    d = _load_json_local_or_git(root, 'docs/data/trainer-movesets.json')
    if d is None:
        return None
    key = next((k for k in d if k.upper() == species.upper()), None)
    return d.get(key, []) if key else []

def main():
    if len(sys.argv) < 2:
        print(__doc__); sys.exit(1)
    species = sys.argv[1].upper().replace('SPECIES_', '')
    cap = int(sys.argv[2]) if len(sys.argv) > 2 else 14
    root = os.getcwd()

    gen = resolve_gen(root)
    lu = get_levelup(root, species, gen)
    egg = get_egg(root, species)
    tms = get_tms(root)
    full, full_key = get_full_pool(root, species)

    lu_le = {k: v for k, v in lu.items() if v[0] <= cap}
    lu_over = {k: v for k, v in lu.items() if v[0] > cap}
    tm_pool = {k: full[k] for k in full if k in tms}            # TM moves the species can learn
    # tutor/other = in full pool, not any-level level-up, not egg, not TM
    tutor_pool = {k: full[k] for k in full if k not in lu and k not in egg and k not in tm_pool}

    def legal_reason(move):
        k = norm(move)
        if k in lu_le:   return True,  f"level-up L{lu_le[k][0]} (<= cap)"
        if k in egg:     return True,  "egg move"
        if k in tm_pool: return True,  "TM"
        if k in tutor_pool: return True, "move tutor"
        if k in lu_over: return False, f"level-up L{lu_over[k][0]} only (> cap, no TM/tutor/egg path)"
        return False, "not learnable by this species in this build"

    OK = "✓"   # checkmark
    NO = "✗"   # cross

    print("=" * 70)
    print(f"SPECIES: {species}   (all_learnables key: {full_key})")
    print(f"LEVEL CAP: {cap}   |   level-up learnset gen: GEN_{gen}")
    print("=" * 70)

    # ---- advised sets first, with checkmarks ---------------------------------
    print(f"\nADVISED SETS   ({OK} = possible at cap {cap}, {NO} = not possible)")
    print("-" * 70)
    advised = get_advised(root, species)
    if advised is None:
        print("   trainer-movesets.json not present on this branch.")
    elif not advised:
        print("   No advised sets recorded for this species.")
    else:
        for i, e in enumerate(advised, 1):
            moves = e.get('moves', [])
            verds = [legal_reason(mv) for mv in moves]
            ok = sum(1 for good, _ in verds if good)
            print(f"\n[{i}] {e.get('hack','?')} | {e.get('trainer','?')} "
                  f"| gym {e.get('gym','?')} | Lv {e.get('level','?')} "
                  f"| ability {e.get('ability','?')} | nature {e.get('nature','?')}"
                  f"   ->  {ok}/{len(moves)} possible")
            for mv, (good, reason) in zip(moves, verds):
                mark = OK if good else NO
                note = reason if good else f"NOT POSSIBLE - {reason}"
                print(f"      {mark} {pretty(mv):<16} {note}")

    # ---- swap menu: every legal move, to replace any cross above -------------
    print(f"\nSWAP MENU - all moves POSSIBLE at cap {cap} (pick replacements for any {NO})")
    print("-" * 70)
    print("Level-up (<= %d):" % cap)
    for k, (lv, mv) in sorted(lu_le.items(), key=lambda x: x[1][0]):
        print(f"   {OK} L{lv:<3} {pretty(mv)}")
    print("Egg moves:")
    for v in sorted(pretty(v) for v in egg.values()):
        print(f"   {OK} {v}")
    if not egg:
        print("   (none)")
    print("TM moves (learnable):")
    for v in sorted(pretty(v) for v in tm_pool.values()):
        print(f"   {OK} {v}")
    if not tm_pool:
        print("   (none)")
    print("Tutor / other teachable moves:")
    for v in sorted(pretty(v) for v in tutor_pool.values()):
        print(f"   {OK} {v}")
    if not tutor_pool:
        print("   (none)")

    # ---- what the cap removes (context) --------------------------------------
    print(f"\nNOT POSSIBLE - locked by cap (level-up above L{cap}, no TM/tutor/egg path)")
    print("-" * 70)
    locked = {k: v for k, v in lu_over.items()
              if k not in egg and k not in tm_pool and k not in tutor_pool}
    if locked:
        for k, (lv, mv) in sorted(locked.items(), key=lambda x: x[1][0]):
            print(f"   {NO} L{lv:<3} {pretty(mv)}")
    else:
        print("   (none)")

if __name__ == '__main__':
    main()
