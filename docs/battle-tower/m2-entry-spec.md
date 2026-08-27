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

## Own save region (shown early for your approval)

Even though M2 does not persist a run, I want to introduce the mode's **own save
region** now so you can review the save-format change while it is tiny, rather
than as a surprise later. Proposed: a single new struct in the save block holding
only what a run needs, added without disturbing existing fields.

```c
// sketch, not final - the real field list grows with M3 to M8
struct RentalModeSave
{
    u8  format;            // singles/doubles + restricted cap 0/1/2
    u8  battlesWon;        // streak within the current run
    u8  rosterCount;       // how many of the 6 are filled
    // roster entries (species/set/ivs/personality) added at M3
    // ... reserved padding for forward growth ...
};
```

Save-format changes are sensitive, so I will show the exact diff to
`include/global.h` before writing it, and keep it additive (no reordering or
resizing of existing fields).

## Files this milestone touches

- `src/main_menu.c` - add the menu row + boot hook. **(Title/main-menu code - I
  asked before touching this; you said go.)**
- `include/global.h` - add the `RentalModeSave` region. **(Save format - I will
  show the diff first.)**
- A new mode-controller source, e.g. `src/rental_mode.c` (+ a header) - the boot
  routine and the stub battle setup. Reuses `CreateFacilityMon`.
- `data/maps/BattleFrontier_BattleTowerLobby/scripts.inc` - repoint the attendant
  to the rental stub script. Scripts only, no object placement.
- `docs/overview/changelog.md` - record the new mode entry.

## Verification (on your Mac build)

1. Boot the game: the main menu shows the new "RENTAL BATTLE" option.
2. Select it: you warp into the Battle Tower Lobby with a usable player.
3. Talk to the attendant: a Lv50 battle starts using Pokemon from the library,
   with correct movesets and Hidden Power showing its real type.
4. Win/lose returns you to the menu or lobby without corrupting a story save.

## Decisions I need from you

1. **How real should M2's boot be?** (see Decision 1 below)
2. Everything else (menu label, which attendant, how the stub battle is wired) I
   will handle as engineering calls unless you want a say.

Deferred, unchanged from the plan's section 9: run length/scoring, AI flags,
doubles lead order, scout transparency.
