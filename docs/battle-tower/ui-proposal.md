# RENTAL BATTLE - UI / Presentation Proposal

Status: PROPOSAL for approval. No engine code written yet. This turns the
logic-complete rental mode (see `phase-1-implementation-plan.md`,
`design-questions.md`) into a set of real screens, built on the Battle
Factory UI already in the tree and composed entirely from existing FRLG
tiles, sprites, and window frames (NO new art, per project rules).

Decisions locked with the director this session:
- Deliverable: **proposal first**, approval before any engine edit.
- Ambition: **full custom screens** (a real team-preview board, a recruit
  board, a format/cap menu, a streak HUD), no new art.
- Menu name: **keep "RENTAL BATTLE".** The creative director pitched
  "Battle Swap" (the base build's Factory rename) and a Kanto-flavored
  "loaner floor"; we keep RENTAL BATTLE on the menu and use the **Steward /
  loaner-floor** voice only as in-mode diction.

---

## 1. Where the mode is today

The rules are done; the presentation is almost all bare text boxes.

| Beat | Today | Verdict |
|---|---|---|
| Entry | Boots into a reused Viridian Poke Center 1F (FRLG has no Frontier maps) | Generic, unthemed |
| Format + cap | Three plain YES/NO message boxes | No menu, no state shown |
| Draft (12 -> 6) | Reuses the Battle Factory select screen (Poke Ball grid, sprite preview, summary) | Already Factory-quality; only needs a 6-slot tray + counter |
| Team preview | One message box: a comma-separated list of the opponent's species names | The weakest screen; no sprites at all |
| Bring N | Standard party menu | Functional, off-theme, disconnected from preview |
| Recruit | Linear YES/NO per opponent mon, then the party menu | Tedious, no at-a-glance compare |
| Run status | Win streak appears only inside message text | No persistent readout |

So the draft is fine, and everything around it is a wall of text.

## 2. What the engine already hands us (compose, do not draw)

- `CreateMonPicSprite(species, shiny, pid, ..., x, y, palSlot, ...)` -
  full front sprite anywhere on screen. The draft confirm tray already lays
  three of these in a row (`src/rental_select_screen.c:2034`).
- `CreateMonIcon(species, cb, x, y, subpriority, pid)`
  (`src/pokemon_icon.c:137`) - a 32x32 party icon. Six across is 192px,
  inside the 240px screen with room for markers. This is the primitive for
  both new boards.
- The Poke Ball sprites (gray = unpicked / lit = picked) and the Factory
  menu background + `mon_pic_bg` card, all already loaded by the draft
  screen.
- A full two-pane swap picker with summary hooks already exists in
  `rental_select_screen.c` (`SWAP_ENEMY_SCREEN` / `SWAP_PLAYER_SCREEN`,
  `Swap_ShowSummaryMonSprite`). The recruit board is an adaptation of it,
  not new code.
- `ShowPokemonSummaryScreen(SUMMARY_MODE_NORMAL, party, pos, last, cb)` for
  the scout summary (`rental_select_screen.c:2372`).
- The standard multichoice / list-menu window for the format+cap menu.

Net: every proposed screen is a rearrangement of parts already compiled in.

## 3. The identity layer (from the creative director)

- **Host: the Steward.** A night-shift Poke Center steward who has crowned
  himself master of ceremonies over a back-room league of borrowed Pokemon,
  and runs this scrub-tier loaner circuit with Indigo-finals gravity.
  Speech: a heightened Gentleman register ("challenger", "into your
  keeping", "by house custom"). Silly-through-contrast: one grandee in an
  earnest, ordinary lobby.
- **Tonal control:** the pomp lives in the lobby beats (draft, preview,
  win, recruit, run-end). At **battle-start the ceremony drops** and he goes
  terse and plain, so a hard-but-fair Lv50 fight is never deflated.
- **Framing (one line, kept coy):** by old house custom on the after-hours
  loaner floor, nothing you field is truly yours; the night's victor may
  take a rival's battler into their keeping, leaving one of their own in
  trade. We never say where the pool comes from (mystique, not a ledger).

Full copy in section 6.

## 4. The screens

### S1 - Setup panel (replaces the three YES/NO boxes)

One menu over the Factory background. The Steward's intro prints, then a
compact list the player scrolls:

```
  FORMAT      < SINGLES >     (bring 3 / bring 4)
  RESTRICTED  <   1     >     (0 / 1 / 2 legendary-tier per team)
  [ BEGIN DRAFT ]
```

- Left/right cycles a field; A on BEGIN starts the draft.
- A one-line helper under the list restates the current pick ("Singles:
  draft six, send three.").
- Built from a list-menu window + the Factory bg. Writes the same
  `VAR_0x8004` (format) / `VAR_0x8005` (cap) the script already reads, so
  the downstream flow is unchanged.

### S2 - Draft board (keep, extend to six)

The existing draft screen is good. Two changes:
- The confirm tray shows **six** picked mon pics, not three (the screen is
  already a rental copy with `SELECT_PICK_COUNT 6`; the tray art currently
  mirrors the 3-slot Factory layout).
- Add a live **"PICKED 4/6"** counter and a small clause legend ("no repeat
  species or items") so a rejected pick reads as a rule, not a bug.

### S3 - Team-preview board (the headline new screen)

Replaces the comma-separated text. A single board:

```
  CHALLENGER            [ STREAK 03 · SINGLES · R1 ]
  ( ) ( ) ( ) ( ) ( ) ( )      <- opponent's six icons, scout cursor
  ------------------------------------------------
  YOUR TEAM            BRING 3
  [o][o][ ][o][ ][ ]           <- your six icons, lit ball = bringing
```

- **Top row:** the opponent's full six as mon icons. A cursor moves along
  them; **A opens a scout summary** (moves, item, ability, and Hidden Power
  shows its real type per M1). The Steward's lead-in reminds you they only
  field *some* of these, so you scout all six but cannot know which subset
  you will face.
- **Bottom row:** your six drafted icons. A toggles a lit Poke Ball marker
  to pick your bring; the **BRING N** target (3 singles / 4 doubles) and a
  live count gate confirm.
- **Doubles:** the player sets which two of the bring-4 lead, and can change
  that lead pair **every battle** on this board; a small "1 / 2" tag marks
  the chosen leads.
- Confirm writes the same `frontier.selectedPartyMons[]` the battle path
  already consumes, so **this board replaces the separate party menu** for
  bring-N (one screen instead of textbox -> party menu).
- Built from `CreateMonIcon` x12 + ball sprites + the summary hook + the
  Factory bg. No new art.

### S4 - Recruit board (replaces the YES/NO-per-mon loop)

After a win, one board adapted from the Factory swap picker:

```
  TAKE INTO YOUR KEEPING        (opponent's brought mons: 3 or 4)
  ( ) ( ) ( )
  ------------------------------------------------
  RETURN TO THE POOL            (your six)
  [o][o][o][o][o][o]
```

- Pick one opponent mon (top), then one of yours to trade out (bottom).
- Icons that would break Species/Item clause or the restricted cap are
  **dimmed and unselectable**, so the rule is visible instead of a failure
  message after the fact.
- A/summary works on both rows for a last look before trading.
- Reuses `SWAP_ENEMY_SCREEN` / `SWAP_PLAYER_SCREEN` and their summary code
  directly; recruit-clause dimming is the one new check
  (`RentalRecruitClauseOK` already exists in `src/rental_mode.c:268`).

### S5 - Run-status HUD

A small persistent window on S3 and S4, read as the Steward's honor-board
tally (label, not prose):

```
STREAK 07 · SINGLES · R1
```

- `STREAK` zero-padded 2 digits; `SINGLES`/`DOUBLES`; `R0/R1/R2` for the
  cap (keep the coy "restricted" register, never the word "legendary").
- One small window, drawn on the boards that have room; not shown in battle.

## 5. Flow, before and after

```
BEFORE:  menu -> [Doubles? Y/N] -> [Restricted? Y/N] -> [Two? Y/N]
         -> Factory draft -> [text list of 6 names] -> party menu (bring)
         -> battle -> [win text] -> [Recruit? Y/N] -> per-mon [This one? Y/N]
         -> party menu (release) -> loop

AFTER:   menu -> S1 setup panel -> S2 draft board (6/6 + legend)
         -> S3 preview board (scout + bring in one) -> battle
         -> S4 recruit board (compare + clause-dimmed) -> loop
         with S5 streak HUD on S3/S4 throughout
```

Same script specials, same battle path; the message boxes become screens.

## 6. On-screen copy (Steward voice, gen-3 two-line pages, no em dashes)

Drops into the existing `Text_Rental*` labels in
`data/maps/BattleFrontier_BattleTowerLobby/scripts.inc` (the `\n \p`
structure is unchanged so wiring is untouched).

- **Intro / draft:** "Welcome to the loaner floor, / challenger. Nothing
  here is yours…" \p "…yet all of it answers to you tonight. / Choose six of
  these twelve."
- **Format (YES = Doubles):** "How shall we stage the bout? DOUBLES? /
  (Choose NO for SINGLES.)"
- **Cap:** "Shall RESTRICTED POKeMON, the / legendary sort, take the floor?"
- **Cap two (YES = 2):** "As many as two per side? / (Choose NO to allow but
  one.)"
- **Preview lead-in:** "Your challenger fields these six: / {STR_VAR_1}." \p
  "Only some will take the floor. / Choose your answer with care."
- **Bring:** "Now name the team you will send out, / from the six in your
  keeping."
- **Battle-start (ceremony drops):** "Your team stands ready. So does
  theirs. / Begin, challenger."
- **Win / streak:** "A clean bout. {STR_VAR_1} straight now. / The floor
  takes note."
- **Recruit offer:** "They fought well. By house custom you / may take one
  into your keeping. Do so?"
- **Recruit which:** "Take {STR_VAR_1} into your keeping?"
- **Recruit release:** "And which of yours returns to the / loaner pool in
  trade?"
- **Recruit done:** "{STR_VAR_1} is entrusted to you!"
- **Recruit rule-break:** "House rules forbid it: two alike in / kind or in
  gear. Choose again."
- **Run-over:** "Your run closes at {STR_VAR_1} win(s). / Honorably fought.
  The floor remembers."
- **Play-again:** "Another run upon the floor? / (Choose NO to take your
  leave.)"
- **Leaving (new page before EndRentalMode):** "Then the floor is yours no
  longer. / Go well, challenger."

## 7a. Implementation status (live)

- **U1 - Copy + Steward pass: DONE.** Strings rewritten, intro wired in, leaving
  line added, Steward logged in the ledger.
- **U2 - Setup menu: DONE.** Format + cap are two framed dynmultichoice menus;
  shared RentalExitMode for both exits.
- **U3 - Draft board: EFFECTIVELY DONE, one flourish deferred.** The screen
  already has the live "Draft n/6" counter, and the offer is pre-filtered to
  distinct species + items, so any six picks are legal by construction (no
  in-draft clause rejection is even possible). The only remaining item is the
  confirm reveal showing all six pics instead of three; that lives in fragile
  affine/WIN0 code the original copy deliberately left as "later polish," so it
  is deferred rather than reworked blind.
- **U4 - Team-preview board: DONE (needs a build check).** New self-contained
  screen `src/rental_preview_screen.c` (special `DoRentalTeamPreview`): both
  rosters as party icons, A scouts an opponent's moves/item/ability in a panel,
  bring-N picked on the board (pick order = send/lead order), and the streak HUD
  (folds in U6). Written but not compiled in this environment.
- **U5 - Recruit board: DONE (needs a build check).** New screen
  `src/rental_recruit_screen.c` (special `DoRentalRecruit`): pick an opponent's
  fielded mon, then one of yours to release, with rule-breaking swaps blocked.
  Written but not compiled in this environment.
- **U6 - Streak HUD: DONE** (folded into the U4 preview board and the U5 recruit
  board).

All six steps are now implemented. None are compiled here (no devkitARM), so the
first local `make firered` will likely surface mechanical fixes across U4/U5.

## 7. Build order (each its own small PR, if approved)

- **U1 - Copy + Steward pass.** Swap the placeholder `Text_Rental*` strings
  for the section 6 copy; add the missing "leaving" page. Add a lore-ledger
  row for the Steward. No screen code; lowest risk, ships the voice first.
- **U2 - Setup panel (S1).** List menu for format + cap; writes the same
  vars. Retire the three YES/NO boxes.
- **U3 - Draft tray to six + counter (S2).** Extend the confirm tray and add
  the picked-count / clause legend.
- **U4 - Team-preview board (S3).** The headline screen; folds bring-N in.
  Requires M1 (Hidden Power real type) for the scout summary.
- **U5 - Recruit board (S4).** Adapt the swap picker; add clause dimming.
- **U6 - Streak HUD (S5)** + polish.

## 8. Decisions (resolved this review)

1. **Scout depth (S3/S4 summary):** show **moves + item + ability only** -
   no nature / EV / IV spread. (Settles design-questions Q7.1.)
2. **Doubles lead order (S3):** the **player sets the two leads on the
   preview board, and may change them every battle** (not fixed by pick
   order). (Settles the Q4 / M4 lead-order item.)
3. **Setup panel (S1):** build it as a **real menu**, not improved YES/NO
   boxes.
4. **HUD reach:** the run-status window shows on **S3 and S4 only** (the two
   in-run screens); no draft-board readout.
5. **Hub dressing:** **leave the reused Poke Center backdrop as-is.** The
   mode spends its time on custom screens, not the map; no themed map pass.

## 9. Guardrails honored

- No new art: every screen composes existing tiles/sprites/windows.
- No em dashes anywhere in copy or docs.
- Mega stays local to this mode; gimmicks-off elsewhere unchanged.
- Same script specials and battle path; message boxes become screens.
- Update the relevant `docs/overview/` doc in the PR that adds a screen.
