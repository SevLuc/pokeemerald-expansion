# Build & Playtest Verification

Living checklist of merged changes that have **not yet been compiled or playtested**.

## Why this exists
Web sessions can't build the ROM (no devkitARM in that environment) and GitHub
Actions CI has not run on this fork (0 runs; Actions appears disabled). So every
code/data change is merged **unverified** until it is built and playtested on the
Mac (`make firered -j$(sysctl -n hw.ncpu)`, test in mGBA).

Work each item on the next local build:
1. `[ ] builds` - compiles clean with no new warnings/errors.
2. `[ ] playtested` - the in-game behavior below actually works.

Check items off (or delete the row) once verified. Newest PR first.

## ⚠️ Known interaction to verify first
**Party-menu action-list overflow (PR #6 + PR #10).** Both PRs add entries to
`SetPartyMonFieldSelectionActions` in `src/party_menu.c`: #6 adds `LEVEL`, #10
adds `Fly`/`Flash`. The selection window is drawn bottom-anchored at
`top = 19 - numActions*2`, so it only fits up to 9 rows (top = 1). Worst case now
reaches 10 rows - e.g. a mon with 4 learned field moves, outdoors, holding HM Fly
(so `Fly` is offered), plus `Summary`, `Switch`, `Item`, `LEVEL`, `Cancel` - which
makes `top = -1` and the menu renders off-screen/garbled. The `actions[]` array
was enlarged to 10 so there is no memory overflow, but the *window geometry* can't
fit 10. Verify in-game with that setup; if it breaks, the fix is to cap the field
list at 9 (e.g. fold `LEVEL` in only when there's room, or move Fly/Flash into a
submenu too). Flagged to the user 2026-08-19.

## Pending verification

### PR #11 - Giovanni "the man who was here all along" lore  (compile risk: MEDIUM - map scripts + fame checker text)
- Files: `data/maps/*/scripts.inc` (RocketHideout_B4F, SilphCo_11F, ViridianCity_Gym,
  ViridianCity, MtMoon_B2F, RocketHideout_B1F, PokemonTower_7F, SilphCo_5F, SilphCo_8F,
  FiveIsland_RocketWarehouse) + `data/text/fame_checker_frlg.inc` + `docs/writing/*`.
- NOTE: draft PR #11 is still OPEN; this branch already carries it. Build & playtest
  here, then it can merge. (Move this row up to normal "merged" status once merged.)
- `[ ] builds` - text/flavor reflavors + appended `.string` lines only, no new objects
  or scripts. The badge-fanfare control codes in the Viridian defeat line
  (`{PAUSE_MUSIC}` / `{MUS_OBTAIN_BADGE}` / `{PLAY_BGM}`) and the gym-intro
  `{PLAY_BGM}{MUS_RG_ENCOUNTER_ROCKET}` are preserved verbatim. Assembler catches any
  typo'd label / unterminated string. (Pre-checked here: no em dashes, every `.string`
  terminates, control codes intact.)
- `[ ] playtested`:
  - All three Giovanni battles read right, no overflow / bad control codes:
    Rocket Hideout B4F, Silph Co 11F, Viridian Gym (intro / defeat / post-battle).
  - Viridian Gym defeat still awards the EARTHBADGE with its jingle; TM26 (EARTHQUAKE)
    is still given afterward.
  - Viridian City civic lines fire: locked-door "away... on business"; Old Man "who
    the LEADER is"; Woman "a fine fellow, I'm sure"; and the "LEADER returned!" line
    once the gym unlocks (after badges 2-7).
  - Fame Checker Giovanni entries + his letter display correctly as they unlock.
  - Viridian Gym trainers (now Ground-grit reflavors) + ambient NPC appends (Mt Moon,
    Rocket Hideout B1F, Pokemon Tower 7F, Silph Co 5F/8F, Five Island warehouse) read
    right, no overflow.

### PR #10 - HMs usable without learning  (compile risk: HIGH - multi-file C)
- Files: `include/config/overworld.h`, `include/field_move.h`, `src/field_move.c`,
  `src/field_control_avatar.c`, `src/party_menu.c`, `src/scrcmd.c`.
- `[ ] builds` - new `IsHMUnlocked()` gate, per-move `hmItemId`, `checkfieldmove`
  fallback to the first non-egg mon, and the Fly/Flash party-menu entries.
- `[ ] playtested`:
  - With the right Badge + HM in the bag but no mon that learned the move, the
    obstacle move still triggers (Cut/Rock Smash/Strength/Surf/Waterfall/Dive).
  - Without the HM (or without the Badge), it does not.
  - Fly/Flash appear in the party menu only outdoors / in a dark cave respectively.
  - See the overflow warning above.

### PR #9 - Character lore: Surge/Erika/Koga/Sabrina/Blaine (+ rumors)  (compile risk: MEDIUM - map scripts)
- Files: many `data/maps/*/scripts.inc` (Vermilion, S.S. Anne, Celadon, Fuchsia,
  Saffron gym, Cinnabar/Mansion, Routes, Lavender, etc.) + `docs/writing/*`.
- `[ ] builds` - Sabrina's possessed gym adds forced-fight/false-direction script
  branches; Blaine/Fuji journal fragments; new `.string` labels. Assembler catches typos.
- `[ ] playtested`:
  - Saffron gym forced fights + contradictory directions work; Sabrina defeat
    breaks the spell (before/after NPC branches on `FLAG_DEFEATED_SABRINA`).
  - Surge S.S. Anne Captain awards HM01 CUT; new NPC lore lines read correctly.
  - Mansion journal fragments + rumor NPCs display right across Kanto.

### PR #8 - Rivals draft (Buhrito + Twitch)
- Files: `docs/writing/drafts/intro-and-rival.md` only. Docs-only, nothing to compile.

### PR #6 - Hard level caps + party-menu leveling  (compile risk: HIGH - new C code)
- Files: `include/config/caps.h`, `src/party_menu.c`, `src/data/party_menu.h`.
- `[ ] builds` - new functions `LevelUpMonFromMenu`, `CursorCb_Level/LevelUp/LevelToCap`;
  `PartyMenuInternal.actions[]` enlarged 8 -> 10; new `MENU_LEVEL*` enum entries.
- `[ ] playtested`:
  - Over-cap mons gain 0 EXP in battle; under-cap mons level normally.
  - Rare Candy refuses to raise a mon at the cap.
  - Party menu shows `LEVEL` -> `LEVEL UP` / `LEVEL TO CAP`; both level for free,
    learn moves / evolve correctly, and never pass the current cap.
  - Cap advances with each badge (15/19/24/29/31/33/42/46/58, then 100).
  - Check the selection window with a 4-field-move HM slave (max-length action list).

### PR #5 - Auto-heal after battle  (compile risk: MEDIUM - new C function)
- Files: `include/config/overworld.h`, `src/battle_setup.c`.
- `[ ] builds` - new `ShouldAutoHealPartyAfterBattle()` + `HealPlayerParty()` calls
  in the wild/scripted/Marowak/trainer/rematch end callbacks.
- `[ ] playtested`:
  - After a normal wild/trainer fight the party is full HP/status/PP.
  - Inside Trainer Tower/Hill, Frontier, Safari, link, recorded, tutorial: NOT healed.

### PR #4 - Disable EVs game-wide  (compile risk: LOW - config + data)
- Files: `include/config/caps.h`, `src/data/battle_partners.party`.
- `[ ] builds` - also fixed a previously malformed `B_EV_CAP_TYPE`/`B_EV_CAP_VARIABLE`
  line in caps.h; double-battle ally EV spreads removed from the .party file.
- `[ ] playtested` - defeating mons grants no EVs; vitamins/EV items can't add EVs.

### PR #2 - Character arcs: Brock + Misty (text/flavor)  (compile risk: MEDIUM - new map script)
- Files: many `data/maps/*/scripts.inc` (Pewter City/Gym, Cerulean City/Gym,
  Route 24/25, Sea Cottage), plus `docs/writing/*` (docs, no compile).
- `[ ] builds` - Pewter Gym gains a real `ON_FRAME` map script (phone-ringing:
  `map_script_2`, `playse`, `msgbox`, flag gate); many new `.string` labels are
  referenced by scripts. Assembler will catch any mismatched label/typo.
- `[ ] playtested`:
  - Pewter Gym phones ring on entry pre-badge, stop after `FLAG_BADGE01_GET`.
  - Brock / Misty intro + defeat lines display correctly (no overflow / bad control codes).
  - Bill's Sea Cottage payoff text fires; new NPC lines on Route 24/25 read right.

### PR #1 - Project scaffolding
- Files: `CLAUDE.md`, `docs/`, initial config. No ROM code expected; nothing to verify.

## Not yet merged (will need verification when merged)
- **PR #3 (OPEN)** - Bill polish + Misty bug-ban gym gimmick. Includes a planned
  party-type-check script (code) for the Cerulean bug ban. Add its rows here once merged.
