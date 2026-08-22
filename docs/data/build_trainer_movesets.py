#!/usr/bin/env python3
"""Build docs/data/trainer-movesets.json: a species-keyed index of trainer
movesets scraped from three community hard-mode romhack datasets.

Sources (public Google Docs):
  - Run & Bun         (xlsx workbook, one "<Leader> Split" tab per gym)
  - Platinum Kaizo    (xlsx workbook, one "<Leader> Split" tab per gym)
  - Emerald Kaizo     (EK Mastersheet.txt + Rival Teams.txt)

Output shape (keyed by this build's species constant, e.g. "ONIX"):
  { "ONIX": [ { "source","hack","trainer","location","level",
               "item","ability","nature","gender","moves":[...] }, ... ] }

Zero third-party deps (stdlib xlsx reader). Re-run to refresh:
  python3 docs/data/build_trainer_movesets.py
Add --local <dir> to parse already-downloaded files instead of fetching.
"""
import argparse, io, json, os, re, sys, urllib.request, zipfile
import xml.etree.ElementTree as ET

HERE = os.path.dirname(os.path.abspath(__file__))
INDEX_JSON = os.path.join(HERE, "pokedex-index.json")
OUT_JSON = os.path.join(HERE, "trainer-movesets.json")

RUNBUN_XLSX = "https://docs.google.com/spreadsheets/d/1Ezdd8k-pDlVocd0NHUkGwZXcegfG-KTOraM_uZUsr6s/export?format=xlsx"
PLAT_XLSX = "https://docs.google.com/spreadsheets/d/1FDPAoLT9Qoj-gTzosvwzcNCRxVcURgUT7TsfW69DHaA/export?format=xlsx"
EK_MASTER_TXT = "https://drive.google.com/uc?export=download&id=19wT-_XMv53T6nITQs4dZEsY-Mof_vTh_"
EK_RIVAL_TXT = "https://drive.google.com/uc?export=download&id=1q_V4w7-f2Gx3c9efjQrVUcy3ORMo7EjA"

# ---------------------------------------------------------------- fetch ------
def fetch(url):
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    return urllib.request.urlopen(req, timeout=60).read()

def load_bytes(url, local, name):
    if local:
        with open(os.path.join(local, name), "rb") as f:
            return f.read()
    return fetch(url)

# ------------------------------------------------------- stdlib xlsx reader --
_NS = {"m": "http://schemas.openxmlformats.org/spreadsheetml/2006/main",
       "r": "http://schemas.openxmlformats.org/officeDocument/2006/relationships"}

def _col(ref):
    c = 0
    for ch in re.match(r"([A-Z]+)", ref).group(1):
        c = c * 26 + (ord(ch) - 64)
    return c - 1

def read_xlsx(data):
    z = zipfile.ZipFile(io.BytesIO(data))
    shared = []
    if "xl/sharedStrings.xml" in z.namelist():
        for si in ET.fromstring(z.read("xl/sharedStrings.xml")).findall("m:si", _NS):
            shared.append("".join(t.text or "" for t in si.iter("{%s}t" % _NS["m"])))
    wb = ET.fromstring(z.read("xl/workbook.xml"))
    idk = "{%s}id" % _NS["r"]
    sheets = [(s.get("name"), s.get(idk)) for s in wb.find("m:sheets", _NS)]
    rels = {rel.get("Id"): rel.get("Target")
            for rel in ET.fromstring(z.read("xl/_rels/workbook.xml.rels"))}
    out = {}
    for name, rid in sheets:
        tgt = rels[rid]
        tgt = tgt if tgt.startswith("xl/") else "xl/" + tgt
        rows = []
        data_el = ET.fromstring(z.read(tgt)).find("m:sheetData", _NS)
        if data_el is not None:
            for row in data_el.findall("m:row", _NS):
                cells, maxc = {}, -1
                for c in row.findall("m:c", _NS):
                    ci = _col(c.get("r"))
                    t = c.get("t")
                    v = c.find("m:v", _NS)
                    if t == "s" and v is not None:
                        val = shared[int(v.text)]
                    elif t == "inlineStr":
                        isv = c.find("m:is", _NS)
                        val = "".join(x.text or "" for x in isv.iter("{%s}t" % _NS["m"])) if isv is not None else ""
                    else:
                        val = v.text if v is not None else ""
                    cells[ci] = (val or "").strip()
                    maxc = max(maxc, ci)
                rows.append([cells.get(i, "") for i in range(maxc + 1)])
        out[name] = rows
    return out

# ------------------------------------------------- species -> constant map ---
def norm(s):
    s = s.replace("♀", "F").replace("♂", "M")
    return re.sub(r"[^A-Z0-9]", "", s.upper())

REGION = {"ALOLAN": "ALOLAN", "GALARIAN": "GALARIAN", "HISUIAN": "HISUIAN", "PALDEAN": "PALDEAN"}

def build_species_resolver():
    with open(INDEX_JSON) as f:
        idx = json.load(f)
    by_norm = {norm(k): k for k in idx}
    items = list(by_norm.items())
    def resolve(name, gender=None):
        raw = name.strip()
        # strip trailing gender / slash junk ("Swablu ♀/", "Buneary ♀/♂")
        raw = re.sub(r"[\s♂♀/()mfMF]+$", "", raw).strip() or name.strip()
        # Nidoran gender split
        if raw.lower().startswith("nidoran"):
            g = (gender or "").lower()
            if "f" in g or "♀" in name:
                return "NIDORAN_F"
            if "m" in g or "♂" in name:
                return "NIDORAN_M"
        n = norm(raw)
        if n in by_norm:
            return by_norm[n]
        # regional prefix -> try SPECIES_REGION
        parts = raw.split()
        if len(parts) >= 2 and parts[0].upper() in REGION:
            cand = norm(" ".join(parts[1:]) + " " + parts[0])
            if cand in by_norm:
                return by_norm[cand]
        # Showdown-style form name "Silvally-Grass" / "Zygarde-10%" -> base
        base = re.split(r"[-]", raw)[0].strip()
        nb = norm(base)
        if nb and nb in by_norm:
            return by_norm[nb]
        # form fallback: pick shortest constant whose norm starts with the name
        # (e.g. "Indeedee" -> INDEEDEE_M, "Lycanroc" -> LYCANROC_MIDDAY)
        pref = [k for nk, k in items if nk.startswith(nb or n)]
        if pref:
            return min(pref, key=len)
        # typo / plural: constant norm is a near-prefix of the name (Pidgeott->PIDGEOT)
        near = [k for nk, k in items if (n.startswith(nk) and len(n) - len(nk) <= 1 and len(nk) >= 5)]
        if near:
            return max(near, key=len)
        return None
    return resolve, idx

# ------------------------------------------------------------- collectors ----
class Store:
    def __init__(self, resolve):
        self.resolve = resolve
        self.data = {}
        self.unmatched = {}
    def add(self, species_name, entry, gender=None):
        key = self.resolve(species_name, gender)
        if key is None:
            key = "?" + re.sub(r"[^A-Za-z0-9]", "_", species_name.strip()).upper()
            self.unmatched[species_name.strip()] = self.unmatched.get(species_name.strip(), 0) + 1
        self.data.setdefault(key, []).append(entry)

def clean_moves(moves):
    out = []
    for m in moves:
        m = (m or "").strip().strip(":@").strip()
        if not m or m in ("-----", "----", "---", "-", "(None)"):
            continue
        out.append(m)
    return out

def clean(v):
    v = (v or "").strip()
    return "" if v in ("(None)", "-----", "----", "-", "") else v

# --------------------------------------------------- Run & Bun (xlsx) --------
FIELD = {"Level", "Held Item", "Ability", "Nature", "Moves", "Pokémon", "Name"}

def parse_runbun(book, store):
    hack = "Run & Bun"
    for tab, rows in book.items():
        if not tab.endswith("Split"):
            continue
        gym = tab[:-6].strip()  # "Roxanne Split" -> "Roxanne"
        location = ""
        i = 0
        n = len(rows)
        while i < n:
            r = rows[i]
            a = r[0] if r else ""
            nonempty = [c for c in r if c.strip()]
            # lone location line: col A empty, only col B set
            if a == "" and len(nonempty) == 1 and len(r) > 1 and r[1].strip():
                location = r[1].strip()
                i += 1
                continue
            if a == "Name":
                trainer = r[1].strip() if len(r) > 1 else ""
                # collect block
                species = levels = items = abilities = natures = None
                move_rows = []
                j = i + 1
                seen_moves = False
                move_cont = 0
                while j < n:
                    rr = rows[j]
                    aa = rr[0] if rr else ""
                    if aa == "Name":
                        break
                    if aa == "Pokémon":
                        if j + 1 < n:
                            species = rows[j + 1]
                        j += 2
                        continue
                    if aa == "Level":
                        levels = rr; j += 1; continue
                    if aa == "Held Item":
                        items = rr; j += 1; continue
                    if aa == "Ability":
                        abilities = rr; j += 1; continue
                    if aa == "Nature":
                        natures = rr; j += 1; continue
                    if aa == "Moves":
                        move_rows.append(rr); seen_moves = True; j += 1; continue
                    if aa == "" and seen_moves and move_cont < 3:
                        # continuation move row (cap 3 to avoid eating next location)
                        ne = [c for c in rr if c.strip()]
                        if len(ne) == 1 and rr[1].strip() and move_cont == 0:
                            break  # actually a location line
                        if not ne:
                            break
                        move_rows.append(rr); move_cont += 1; j += 1; continue
                    break
                if species:
                    ncols = len(species)
                    for col in range(1, ncols):
                        sp = species[col].strip()
                        if not sp:
                            continue
                        def cell(rowlist):
                            return clean(rowlist[col]) if rowlist and col < len(rowlist) else ""
                        moves = clean_moves([mr[col] if col < len(mr) else "" for mr in move_rows])
                        lvl = cell(levels)
                        store.add(sp, {
                            "source": "Run&Bun", "hack": hack,
                            "trainer": trainer, "gym": gym, "location": location,
                            "level": int(lvl) if lvl.isdigit() else lvl,
                            "item": cell(items), "ability": cell(abilities),
                            "nature": cell(natures), "moves": moves,
                        })
                i = j
                continue
            i += 1

# --------------------------------------------------- Platinum Kaizo (xlsx) ---
SP_RE = re.compile(r"Lv\.?\s*(\d+)\s+(.+?)\s*([♂♀])?\s*$")

def parse_platinum(book, store):
    hack = "Platinum Kaizo"
    for tab, rows in book.items():
        if not re.search(r"\bSplit$", tab):  # skip "Split." / "Split.." dupes
            continue
        gym = re.sub(r"\s*Split$", "", tab).strip()
        n = len(rows)
        def rowtype(idx):
            r = rows[idx]
            ne = [c for c in r if c.strip()]
            if not ne:
                return ("blank", None)
            # species row: any cell matches "Lv N ..."
            for c in r:
                if re.match(r"Lv\.?\s*\d+\s+\S", c.strip()):
                    return ("species", None)
            # header line: only col 4 (E) carries text, rest empty
            if len(ne) == 1 and len(r) > 4 and r[4].strip():
                return ("header", r[4].strip())
            return ("other", None)
        location = ""
        i = 0
        while i < n:
            rt, txt = rowtype(i)
            if rt == "header":
                # look ahead to next non-blank row
                k = i + 1
                while k < n and rowtype(k)[0] == "blank":
                    k += 1
                nxt = rowtype(k)[0] if k < n else "eof"
                if nxt == "species":
                    trainer = txt
                    # parse the block starting at species row k
                    i = parse_plat_block(rows, k, store, hack, gym, location, trainer)
                    continue
                else:
                    # header followed by another header => this is a location
                    if txt not in ("PLATINUM KAIZO", "AI Flag Key:") and not txt.upper().startswith("PLATINUM KAIZO"):
                        location = txt
                    i += 1
                    continue
            i += 1

def parse_plat_block(rows, k, store, hack, gym, location, trainer):
    n = len(rows)
    species_row = rows[k]
    # mon columns: 4,6,8,10,12,14 that carry a species
    moncols = [c for c in range(4, min(len(species_row), 16), 2)
               if c < len(species_row) and re.match(r"Lv\.?\s*\d+\s+\S", species_row[c].strip())]
    nat_row = rows[k + 1] if k + 1 < n else []
    item_row = rows[k + 2] if k + 2 < n else []
    move_rows = []
    j = k + 3
    while j < n:
        r = rows[j]
        ne = [c for c in r if c.strip()]
        if not ne:
            break
        # stop if next block/header/species begins
        if any(re.match(r"Lv\.?\s*\d+\s+\S", c.strip()) for c in r):
            break
        if len([c for c in r if c.strip()]) == 1 and len(r) > 4 and r[4].strip():
            break
        move_rows.append(r)
        j += 1
    for col in moncols:
        m = SP_RE.match(species_row[col].strip())
        if not m:
            continue
        lvl, sp, gsym = m.group(1), m.group(2).strip(), m.group(3)
        gender = {"♂": "M", "♀": "F"}.get(gsym or "", "")
        nature = clean(nat_row[col]) if col < len(nat_row) else ""
        ability = clean(nat_row[col + 1]) if col + 1 < len(nat_row) else ""
        item = clean(item_row[col]) if col < len(item_row) else ""
        moves = clean_moves([mr[col] if col < len(mr) else "" for mr in move_rows])
        store.add(sp, {
            "source": "PlatinumKaizo", "hack": hack,
            "trainer": trainer, "gym": gym, "location": location,
            "level": int(lvl), "item": item, "ability": ability,
            "nature": nature, "gender": gender, "moves": moves,
        }, gender=gender)
    return j

# --------------------------------------------------- Emerald Kaizo (txt) -----
MON_RE = re.compile(
    r"^(?P<sp>[A-Za-z][A-Za-z0-9'.\- ]*?)\s*"      # species
    r"(?:\((?P<g>[mf])\))?\s*"                        # optional (m)/(f) before Lv
    r"Lv\.?\s*(?P<lvl>\d+)\s*"                        # level
    r"(?:\((?P<g2>[mf])\))?\s*[:;]?\s*"              # optional (m)/(f) after Lv + sep
    r"(?:@\s*(?P<item>[^:@]+?)\s*:+\s*)?"            # optional @item: (colon-terminated)
    r":*\s*(?P<moves>.+?)\s*"                         # moves (tolerate stray leading colon)
    r"(?:\[(?P<tail>[^\]]*)\])?\s*"                   # optional [iv|nature]
    r"(?:\+\s*\d+)?\s*$")                             # optional +BST junk
DASHES = re.compile(r"^-{3,}$")

def parse_emerald_text(text, store, source, hack):
    lines = text.replace("\r\n", "\n").replace("﻿", "").split("\n")
    n = len(lines)
    location = ""
    trainer = ""
    branch = ""
    for i, raw in enumerate(lines):
        line = raw.strip()
        if not line:
            continue
        if DASHES.match(line) or set(line) <= set(">"):
            continue
        m = MON_RE.match(line)
        if m:
            sp = m.group("sp").strip()
            gender = (m.group("g") or m.group("g2") or "").upper()
            item = clean((m.group("item") or "").strip())
            moves = clean_moves([x.strip() for x in m.group("moves").split(",")])
            tail = (m.group("tail") or "").strip()
            nature = ""
            if tail:
                for part in re.split(r"[|/]", tail):
                    p = part.strip()
                    if p and not p.isdigit():
                        nature = p
            loc = location + (" (" + branch + ")" if branch else "")
            tname = trainer or ("Rival" if source.endswith("Rival") else "")
            store.add(sp, {
                "source": source, "hack": hack,
                "trainer": tname, "location": loc,
                "level": int(m.group("lvl")), "item": item,
                "nature": nature, "gender": gender, "moves": moves,
            }, gender=gender)
            continue
        # non-mon text line: location if next non-blank line is dashes, else trainer/branch
        nxt = ""
        for j in range(i + 1, min(i + 3, n)):
            if lines[j].strip():
                nxt = lines[j].strip(); break
        if DASHES.match(nxt) and len(nxt) >= 5:
            location = line
            branch = ""
        elif re.match(r"^(Male|Female)\b", line) or line.lower().startswith(("male,", "female,")):
            branch = line
        else:
            # a plain text line preceding mon lines = trainer name
            # (ignore encounter/statistics lines and any stray mon-ish line)
            if re.search(r"\b(Grass|Surfing|Rod|Cave|Rock Smash|Headbutt trees?)\b", line) or "%" in line:
                continue
            if re.search(r"Lv\.?\s*\d", line):
                continue
            trainer = line

# ---------------------------------------------------------------- main -------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--local", help="dir with pre-downloaded source files")
    args = ap.parse_args()

    resolve, idx = build_species_resolver()
    store = Store(resolve)

    print("Fetching / loading sources ...", file=sys.stderr)
    rb = read_xlsx(load_bytes(RUNBUN_XLSX, args.local, "runbun.xlsx"))
    pk = read_xlsx(load_bytes(PLAT_XLSX, args.local, "plat.xlsx"))
    ek_master = load_bytes(EK_MASTER_TXT, args.local, "ek_master.txt").decode("utf-8", "replace")
    ek_rival = load_bytes(EK_RIVAL_TXT, args.local, "ek_rival.txt").decode("utf-8", "replace")

    parse_runbun(rb, store)
    parse_platinum(pk, store)
    parse_emerald_text(ek_master, store, "EmeraldKaizo", "Emerald Kaizo")
    parse_emerald_text(ek_rival, store, "EmeraldKaizo-Rival", "Emerald Kaizo")

    # dedupe identical entries per species
    for key, lst in store.data.items():
        seen, uniq = set(), []
        for e in lst:
            sig = json.dumps(e, sort_keys=True)
            if sig in seen:
                continue
            seen.add(sig); uniq.append(e)
        store.data[key] = uniq

    ordered = {k: store.data[k] for k in sorted(store.data)}
    with open(OUT_JSON, "w") as f:
        json.dump(ordered, f, ensure_ascii=False, indent=1)

    total = sum(len(v) for v in ordered.values())
    matched = [k for k in ordered if not k.startswith("?")]
    print(f"species keys: {len(ordered)} ({len(matched)} matched to constants)", file=sys.stderr)
    print(f"total moveset entries: {total}", file=sys.stderr)
    if store.unmatched:
        print("UNMATCHED species names:", file=sys.stderr)
        for name, c in sorted(store.unmatched.items(), key=lambda x: -x[1]):
            print(f"  {name} x{c}", file=sys.stderr)
    print(f"wrote {OUT_JSON}", file=sys.stderr)

if __name__ == "__main__":
    main()
