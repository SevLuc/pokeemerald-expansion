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

## Pending verification

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
