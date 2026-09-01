# Rental Battle UI Polish - Design

Date: 2026-09-01
Status: Approved (design), pending implementation plan

## Goal

Make the rental battle mode's "beginning" (loaner-floor setup) and the per-battle
"pick your team" screen look and behave as polished as the existing draft belt
screen, and fix a control trap where pressing B on the pick screen accidentally
ends the whole run.

## Context (current state)

The rental flow, driven by `BattleFrontier_BattleTowerLobby_EventScript_RentalAttendant`
in `data/maps/BattleFrontier_BattleTowerLobby/scripts.inc`:

1. Keeper's opening line (msgbox `RentalDraftIntro`).
2. Format prompt (vanilla multichoice: Singles / Doubles) -> `VAR_0x8004`.
3. Restricted-cap prompt (vanilla multichoice: None / One / Two) -> `VAR_0x8005`.
4. `special StartRentalDraft` -> draft belt screen (`src/rental_select_screen.c`,
   battle-factory-derived). Pick 6 of 12. **Looks good, unchanged.**
5. Per battle: `special DoRentalTeamPreview` (`src/rental_preview_screen.c`) ->
   pick which 3 (singles) / 4 (doubles) to bring, then fight.

Problems:
- The pick/preview screen flat-fills one color plus text windows plus mon icons;
  no frames or graphics, so it reads as unpolished next to the belt draft screen.
- On the pick screen **B = Retire**: it sets result FALSE, returns to the hub, and
  the hub asks "another run?". Trivial to trigger by accident. There is no undo and
  no dedicated, guarded retire.
- The setup step is two plain list menus floating on the overworld, with no visual
  identity and no echo of the chosen options.

## Scope

In scope:
- New **Setup screen** replacing the two multichoice menus (Format + Restricted cap).
- **Redesign of the pick/preview screen** to "Direction A / Tower Terminal" look.
- **New control scheme** on the pick screen: B = undo, SELECT = retire (confirmed).

Out of scope (leave as-is this pass):
- The draft belt screen (`rental_select_screen.c`) - already matches the target look.
- The post-win recruit screen (`rental_recruit_screen.c`) - also bare, but not
  requested. Candidate for a later matching pass.
- The keeper's opening line and all existing rental flavor text (writing is fine).

## Visual language (shared)

Reuse the battle-factory menu tileset already in ROM
(`gFrontierFactoryMenu_Gfx` and `graphics/battle_frontier/factory_screen/*`) so the
new screens match the draft belt at zero new-asset cost. ROM is ~82% full; do not
author new large tilesets.

Palette / motifs, matching the draft screen:
- Navy backdrop.
- Framed "bays": yellow frame for the CHALLENGER (foe) row, cyan frame for YOUR TEAM.
- Gold accent text for HUD numbers (streak, bring count, order badges).
- White cursor ring on the highlighted icon.
- Gold circular order badge on each picked mon (send order 1..N).

## Screen 1: Setup screen (new)

Replaces steps 2 and 3 above with a single themed screen.

Layout (240x160):
- Header: "LOANER FLOOR" (left), "SET YOUR RUN" (gold, right).
- Framed panel with two selectable rows:
  - **FORMAT**: pill selector `< SINGLES >` / `< DOUBLES >`; right note shows
    "bring 3" / "bring 4".
  - **RESTRICTED**: pill selector `< 0 >` / `< 1 >` / `< 2 >`; right note
    "legendary-class".
- One help line under the panel, text depends on the active row.
- Footer: "Pad Move  <> Change  START Begin draft  B Back".

Controls:
- D-Pad Up/Down: move between the two rows (active row gets the white highlight).
- D-Pad Left/Right (or A): cycle the active row's value.
- START: commit -> write `VAR_0x8004` (format), `VAR_0x8005` (cap), set
  `gSpecialVar_Result = 1`, begin the draft.
- B: back out -> `gSpecialVar_Result = 0`, leave rental mode (soft reset to title,
  matching the current format-menu B behavior).

Wiring: a new `special DoRentalSetup` runs the screen. The script replaces the two
`message` + `dynmultipush` blocks with:
```
DoRentalSetup            @ writes VAR_0x8004, VAR_0x8005; VAR_RESULT = 1 begin / 0 exit
goto_if_eq VAR_RESULT, 0, RentalExitMode
StartRentalDraft
```

Implementation note: prefer a new file `src/rental_setup_screen.c` mirroring the
existing rental screen structure (BG0 + windows + the factory tileset), rather than
growing an existing file.

## Screen 2: Pick / preview screen redesign (Direction A)

Same data contract as today (`src/rental_preview_screen.c` header comment): reads
`gParties[B_TRAINER_PLAYER]`, `gRentalRun`, `gRentalMons`; writes
`gSelectedOrderFromParty[]` and `gSpecialVar_Result`.

Layout (240x160):
- Header: "CHALLENGER" (left), "STREAK NN  <FORMAT>  R<cap>" (gold, right) - keep.
- **Foe bay** (yellow frame): 6 mon icons in a slatted strip.
- Mid row: "YOUR TEAM" (left), "BRING n/N" (gold, right) - keep.
- **Player bay** (cyan frame): up to 6 mon icons; picked mons show a gold order badge.
- Cursor is a white ring on the active icon (replace / augment the current raise).
- Info box at bottom: framed dialog-style box holding the control hints, and the
  scout panel content when scouting a foe.

Controls (new):
- D-Pad: move cursor across icons and between rows (unchanged).
- A: on foe row -> open Scout panel (moves/item/ability, as today); on your row ->
  Pick/Drop the cursor mon (unchanged toggle + order shuffle).
- **B: Undo.** If the Scout panel is open, B closes it. Otherwise B pops the most
  recently picked mon (the one whose order == broughtCount): clear its order,
  decrement broughtCount, refresh. If nothing is picked and no scout is open, B is a
  soft no-op (failure beep). **B no longer retires.**
- **SELECT: Retire.** Opens a Yes/No confirm in the info box, default cursor on NO.
  - A on YES -> set `gSpecialVar_Result = FALSE`, exit (existing retire path).
  - A on NO / B -> close the confirm, return to picking.
- START: Begin, only when broughtCount == bringCount (unchanged; failure beep
  otherwise).

Retire still routes to the hub's existing `RentalRetire` -> "another run?" flow; it
just can no longer be reached by accident.

## Data flow / state

- Setup screen owns a tiny transient struct (format, cap, active row) and writes the
  two script vars on commit. No new saved state.
- Pick screen: add a small confirm sub-state (`bool8 retireConfirmOpen`, cursor y/n)
  to the existing `struct RentalPreview`. Undo reuses the existing order array and the
  same shuffle logic already used by drop.

## Testing / verification

- Build: `make firered -j$(sysctl -n hw.ncpu)` clean, no `-Werror` regressions.
- Manual playtest checklist (mGBA):
  - Setup: toggle Singles/Doubles updates the "bring N" note; cap cycles 0/1/2;
    START begins with the chosen values; B exits.
  - Pick: pick to full, verify badges 1..N and send order; drop mid-order and
    confirm later badges renumber; B undoes last pick; B with none picked beeps;
    Scout opens/closes with A/B; SELECT shows confirm defaulting to NO; NO returns to
    picking; YES retires to the "another run?" prompt; START only fires when full.
  - Doubles: bring 4, first two are the lead pair.
- No new battle-test needed (UI only, no move/ability changes).

## Future (not now)

- Give the recruit screen the same Tower Terminal treatment for full consistency.
