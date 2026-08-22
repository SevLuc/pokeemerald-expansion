# Project: Fair Red (provisional name)

Base: rh-hideout/pokeemerald-expansion, compiled to **FireRed**.
This is a from-source build; there is NO base ROM in this repo and there
must never be one.

## Build
- Local (Mac): `make firered -j$(sysctl -n hw.ncpu)` — requires devkitARM.
  (Use `leafgreen` for LeafGreen. Plain `make` builds Emerald — don't.)
- Run `make clean` when switching between Emerald and FRLG.
- Output: `build/firered.gba`, built from source. Test in mGBA.
- Never commit .gba, .sav, .bps, .ips, or any Nintendo asset.

## Upstream
- `RHH` remote tracks rh-hideout. Pull periodically (`git pull RHH master`);
  resolve conflicts manually.
- Keep RHH in the credits and keep CI green — release is undecided, so stay
  release-ready rather than stripping anything a public patch would need.

## What I'm building
An enhanced-vanilla, KANTO-AUTHENTIC, HARD-BUT-FAIR hack of FireRed.
Keep the Kanto story/region and a gen-3-era feel; add QoL and tighter balance;
make it meaningfully harder without being unfair.

### Mechanics: Kanto-authentic
- Gimmicks OFF: no Mega Evolution, Z-Moves, Dynamax, or Terastal. Confirm/disable
  in include/config/ (check FEATURES.md for the exact flags) before enabling.
- Keep the roster/feel gen-3-era. Newer moves/abilities only if they fit Kanto.
- **DECIDED: physical/special split is ON** (modern QoL). This is the expansion
  default — `B_PHYSICAL_SPECIAL_SPLIT GEN_LATEST` in include/config/battle.h.
  Damage category is per-move, not per-type.

### Difficulty: hard but fair (intent — flags NOT yet flipped, ask before changing)
- Enable the smart trainer AI flags globally (not Kaizo, not forced encounters).
- Level cap to stop overleveling: set `B_LEVEL_CAP_TYPE` to `LEVEL_CAP_VARIABLE`
  + a `B_LEVEL_CAP_VARIABLE` event var + `B_RARE_CANDY_CAP TRUE`
  (all in include/config/caps.h — currently at defaults / OFF).
- `B_VAR_DIFFICULTY` (battle.h) available if we want multiple difficulty versions.
- `B_FLAG_NO_WHITEOUT` (battle.h) optional.
- Do NOT bake in Nuzlocke clauses (set battle style, species clause, etc.) —
  "fair" means the player still has normal options.

### Story & characters (creative direction — see docs/writing/)
- Plot progression stays vanilla FRLG. Characters are the canvas, not the plot.
- Reflavor every returning character with a distinct personality + an arc mapped
  onto their EXISTING encounters (never add or move story beats).
- Gym leaders (fought once) get a HISTORY revealed in fragments through other
  NPCs, gated by progression. Track every fragment in docs/writing/lore-ledger.md.
- Sensibility: silly overall, but silly-through-CONTRAST (e.g. a character who
  takes something too seriously paired with a big lug), not blanket goofiness.
- Do NOT lock tone globally — each character gets its own voice; your job is
  tonal control so comedy never deflates a hard-but-fair fight that should land.
- Text & flavor only: never propose sprites, tilesets, portraits, maps, or music.
- NEVER write text with em dashes (—), anywhere in the project (in-game text,
  docs, PRs). Use commas, periods, ellipses (…), or a single hyphen "-". See
  docs/writing/style-guide.md §2.

## How we work
- I mostly can't read C — explain changes in plain terms and keep PRs small.
- Trainer teams: use Pokémon Showdown syntax in src/data/trainers.party
  (FRLG trainers may live in src/data/trainers_frlg.h — check before editing).
- New move/ability => also add a battle test in test/battle/ and run it.
- Maps: I edit layouts/placement in Porymap; you write the scripts.pory files.
- Prefer web sessions for battle/data/balance work; I build & playtest on my Mac.
- Approval protocol: for any non-trivial change, follow Question -> Options ->
  Decision -> Draft -> Approval, and ask "May I write to <filepath>?" before
  editing. Show a draft/summary before large or multi-file changes.

## Living overview docs (keep these in sync)
- Maintain /docs/overview/: progression.md, gyms.md, routes.md, trainers.md,
  encounters.md, changelog.md.
- After ANY change to trainers, maps, encounters, or config, update the
  relevant overview doc IN THE SAME PR so the overview never drifts.
- When I ask "what trainers are before Brock?" etc., read the data and, if the
  doc is stale, refresh it.

## Guardrails
- Don't refactor the battle engine wholesale.
- Ask before touching linker scripts or the Makefile.
- Ask before enabling any gimmick system (Mega/Z/Dynamax/Tera) — those are OFF.
