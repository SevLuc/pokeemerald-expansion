# M2 Spec - Mode entry skeleton

Status: DRAFT for approval. No code written yet. This is the spec for milestone
M2 of the Phase 1 plan: get from the main menu into a hub and prove the rental
data reaches a real Lv50 battle. It is deliberately a skeleton, not the finished
mode.

## Goal

Prove the vertical slice end to end:
1. A new option on the **main menu** launches the rental mode.
2. It drops you into a **hub map** (the existing Battle Tower Lobby).
3. Talking to the **attendant** builds a small team from the generated
   `gRentalMons` table (M0) at flat Lv50 and starts **one battle**.

If that works, every later milestone (draft, preview, recruit, etc.) is building
UI and rules on top of a proven data-to-battle path.

## Non-goals for M2 (these come later)

- No draft screen, no team preview, no recruit, no clauses/caps (M3 to M7).
- No run persistence, streak, or resume yet (M8). The battle is a throwaway.
- No new map art or object placement (we reuse an existing map and NPC).

## The three pieces

### A. Main-menu option + boot

- Add a new row to the main menu (alongside New Game / Continue / Options), e.g.
  "RENTAL BATTLE". Selecting it runs a small boot routine instead of the story
  intro.
- **The hard part:** warping into a map needs a valid player and save context,
  which the story normally sets up during the Birch/Oak intro. The mode must not
  require playing the story, so the boot creates the minimum needed state and
  warps straight to the hub.
- For M2 this boot is intentionally minimal (see Decision 1): a default player,
  no naming intro, warp to the Battle Tower Lobby.

### B. Hub = reuse the Battle Tower Lobby

- Use `BattleFrontier_BattleTowerLobby` (already compiled and warp-able in this
  build) as the hub. No Porymap work needed.
- Repurpose the lobby's existing attendant NPC
  (`..._EventScript_SinglesAttendant`) as the rental attendant by pointing it at
  a new script. No new object events, so no map-layout edits.
- The attendant script (for M2) just launches the stub battle. Later milestones
  replace it with format select -> draft -> preview.

### C. Stub battle from gRentalMons

- Build a few entries from `gRentalMons` into the player party and an opponent
  party using the existing `CreateFacilityMon` path, forced to Lv50, then start a
  standard trainer battle.
- Success = you can see and fight with library Pokemon (correct moves, items,
  and Hidden Power showing its real type from M1).

## Save: none in M2 (playable now, persist later)

Research finding: the cartridge flash is 100% allocated (32/32 sectors), so a
truly separate save profile means reclaiming an unused feature's sector (Trainer
Hill is the candidate). And the save format depends on what a run stores, which
is not settled until M3 to M7. So persistence is deferred to its own later
milestone, designed once the run data shape is fixed.

For M2 the rental profile lives **in memory only**:
- A name/gender pick seeds an in-RAM profile.
- The mode **never writes to flash**. This is the key safety invariant: the
  player's story save on the cartridge is never touched or overwritten. Exiting
  the mode simply discards the in-RAM profile.
- Enterable from the menu regardless of whether a story save exists.

The dedicated persistent save area (likely reclaiming the Trainer Hill sector via
the special-sector I/O pattern) is a separate milestone after M7.

## Files this milestone touches

- `src/main_menu.c` - add the menu row + boot hook. **(Title/main-menu code -
  needs your OK before I write it.)**
- A new mode-controller source, e.g. `src/rental_mode.c` (+ a header) - the boot
  routine (in-RAM profile, name/gender, warp) and the stub battle setup. Reuses
  `CreateFacilityMon`. **No save-system files are touched.**
- `data/maps/BattleFrontier_BattleTowerLobby/scripts.inc` - repoint the attendant
  to the rental stub script. Scripts only, no object placement.
- `docs/overview/changelog.md` - record the new mode entry.

## Verification (on your Mac build)

1. Boot the game: the main menu shows the new "RENTAL BATTLE" option.
2. Select it: you warp into the Battle Tower Lobby with a usable player.
3. Talk to the attendant: a Lv50 battle starts using Pokemon from the library,
   with correct movesets and Hidden Power showing its real type.
4. Win/lose returns you to the menu or lobby. Confirm a pre-existing story save
   still loads intact afterward (the mode must never write flash).

## Decisions

1. **M2 boot scope: DECIDED - playable now, persist later.** M2 gives a
   name/gender pick and an in-memory profile that can enter the hub and fight,
   with no save-system changes (see "Save" above). The persistent save area is a
   separate later milestone.
2. Everything else (menu label, which attendant, how the stub battle is wired) I
   handle as engineering calls unless you want a say.

## Save-profile design (pending research + your approval)

"Save profile" has two readings that differ hugely in effort and risk:
- **Own region in the single save file (recommended, pending confirmation):** the
  mode stores its own persistent data (name/gender for the mode, current run,
  streak, roster) inside the existing save, loadable from the menu without
  needing or disturbing the story save. Delivers persistence + own identity +
  resume + no-story-required, with far less save-core risk.
- **A fully separate second save file/slot:** a large rewrite of the GBA save
  architecture (sector allocation, slot rotation, load/verify), and riskier for
  save stability.

I am mapping the save system now and will present the concrete design (which
sectors/struct, how the menu loads it, name/gender flow, resume) for your OK
before writing any save code.

Deferred, unchanged from the plan's section 9: run length/scoring, AI flags,
doubles lead order, scout transparency.
