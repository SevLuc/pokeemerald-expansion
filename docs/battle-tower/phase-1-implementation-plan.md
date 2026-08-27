# Phase 1 Implementation Plan - Rental Battle Mode

Status: DRAFT for approval. No engine code is written yet. This plan turns the
locked design (see `design-questions.md`) and the moveset library
(`movesets/*.json`, 6,229 sets over 769 rentals) into a concrete, small-PR
build order, grounded in how this build's engine actually works.

Provisional in-game name: the base build already renames the Factory to
"Battle Swap" in its text. We can keep or replace that name later; it does not
affect the plan.

---

## 1. What Phase 1 delivers (plain terms)

A standalone rental mode you launch from the **main menu** (no story progress
required). It drops you into a dedicated in-game hub. There you:

1. Pick a **format**: Singles or Doubles, and a restricted cap (0 / 1 / 2).
2. **Draft a roster of 6** rentals from an **offer of 12** drawn from the
   moveset library, under Species Clause + Item Clause + the restricted cap.
3. Fight a series of battles. Before each, **both sides' full 6 are shown**
   (team preview); you choose which to **bring** (3 in Singles, 4 in Doubles)
   and may open a **scout summary** on any opponent mon to read its build.
4. After each win, **recruit one of the opponent's brought mons** in exchange
   for one of yours (never creating a duplicate species or item).
5. **One Mega Evolution per battle** is allowed (Mega is off in the main game,
   on only inside this mode).
6. Everything runs at **flat Lv50**, and **Hidden Power shows its real type**
   everywhere a move is viewed.

---

## 2. Locked inputs this plan is built on

From `design-questions.md` and this session's four decisions:

- Rental-draft mode first (roguelike layer is Phase 2, not built now).
- Formats: Singles = roster 6, bring 3. Doubles = roster 6, bring 4. **Both are
  in Phase 1.**
- Team preview both sides; scout summary on opponent mons.
- Post-battle recruit from the opponent's BROUGHT mons (the 3 or 4), swap one
  of yours out for one of theirs.
- Frontier preset: Species Clause + Item Clause on your roster.
- Three restricted-cap formats: 0 / 1 / 2 restricted mons per team.
- "Restricted" = legendary + sub-legendary + mythical + paradox + ultra beast
  (roster.md section D) **plus** legendary-based Megas. (This is already the
  definition locked in `roster.md`.)
- One Mega Evolution per battle.
- **Flat Lv50.**
- **Opponents draw from the same moveset library** you rent from.
- **Entry: a new main-menu mode** that warps into an in-game hub, available
  without finishing the story.
- **Own save region** for the mode, independent of story progress.
- **Draft: offer 12, pick 6.**
- Hidden Power displays its real IV-derived type everywhere.

---

## 3. What the engine already gives us (reuse, do not rebuild)

The existing Battle Factory / Frontier code is a strong template. We reuse the
building blocks, not the story Frontier itself.

- **Recruit-swap is already modeled.** `struct RentalMon`
  (`include/global.h:434`) stores the player's rentals AND the just-defeated
  opponent's mons as swap candidates in one array; `CopySwappedMonData`
  (`src/battle_factory_screen.c:2304`) already performs the "take one of theirs
  for one of yours" copy. Our recruit-from-brought is an adaptation of this.
- **Rental select + swap screens exist.** `DoBattleFactorySelectScreen` and
  `DoBattleFactorySwapScreen` (`src/battle_factory_screen.c`) are the UI we
  adapt for draft and recruit.
- **Bring-N already exists.** `ChooseHalfPartyForBattle`
  (`src/script_pokemon_util.c:206`, `src/party_menu.c:7402`) lets a player pick
  a subset of their party; results land in `frontier.selectedPartyMons[]`. This
  is the backbone of bring-3 / bring-4.
- **Party materialization exists.** `CreateFacilityMon` builds a live battle mon
  from a compact rental record (species, moves, item, ability, nature, EVs,
  IVs, fixed level). We feed it our library entries.
- **Flat Lv50 exists.** `GetFrontierEnemyMonLevel` + the Factory's own
  `SetPlayerAndOpponentParties` already force Lv50 via `FRONTIER_MAX_LEVEL_50`.
- **Hidden Power real type already exists** in code, behind a flag. This build
  computes dynamic move types via `CheckDynamicMoveType` (`src/pokemon.c:6774`)
  and the summary/battle UIs already call it when `P_SHOW_DYNAMIC_TYPES` is
  `TRUE` (`include/config/pokemon.h:63`, currently `FALSE`). Turning HP real-type
  on is mostly flipping that flag and verifying the scout-summary path.

---

## 4. What is genuinely new

- A **ROM data table generated from the JSON library** (the foundational piece).
- A **persistent roster of 6** across a run (the Factory keeps a fixed 3).
- **Team preview** (see both sides' 6 and pick your bring). The base engine has
  no team preview; this is new UI.
- **Clause + cap + one-Mega enforcement** at draft, recruit, and battle-start.
- **Main-menu mode entry** plus a dedicated hub map and warp.
- **Doubles (bring 4)** running alongside Singles.

---

## 5. Architecture recommendation (my call, stated not asked)

Build a **self-contained rental-mode module that reuses the Frontier building
blocks**, rather than mutating the story Battle Factory in place or hanging the
mode off the `FRONTIER_FACILITY_*` machinery.

Why:
- The rules diverge from Factory (persistent 6, team preview, bring-N, two
  formats, restricted caps), so mutating Factory in place would tangle two
  different rule sets in one code path.
- This is a FireRed build and the Frontier maps are **not wired into the FireRed
  world** (the Factory pre-battle-room layout constant is absent from this
  build's `layouts.h`). Launching from the main menu into our own hub sidesteps
  that entirely.
- Reusing `RentalMon`-style records, `CreateFacilityMon`, the select/swap
  screen code, and `ChooseHalfPartyForBattle` still saves the vast majority of
  the work.

Net: our own mode controller + our own save region, entered from the main menu,
driving reused UI and party-building helpers. The story Frontier code stays
untouched.

---

## 6. The data pipeline (foundation - Milestone 0)

The 6,229-set JSON must become ROM data.

- **Input:** `docs/battle-tower/movesets/*.json`.
- **Output:** a generated C header with (a) a flat table of all sets and (b) an
  index by species and by tier, so the draft/opponent code can pull "a random
  standard mon" or "a legal restricted mon" cheaply.
- **Per-set fields to preserve:** species, up to 4 moves, item, ability, nature,
  EVs (6 stats), and **per-set IVs** (only Hidden Power sets carry a non-default
  spread; everything else is 31s). Tier tag drives the restricted cap. Level is
  fixed at 50 so it is not stored per set.
- **Generator:** a committed Python script plus a **checked-in generated
  header**, with a `make`-style regen target. I will **ask before touching the
  Makefile**; if you prefer zero build-tool changes, we keep the generated
  header checked in and regenerate it by hand-run script.
- **ROM budget:** the full table is large. I will measure the byte size in M0
  and, if needed, propose trimming sets per mon (the library allows up to 14
  each; 2 to 4 is plenty for a rental pool) rather than shipping all 6,229 at
  once. The vertical slice (M2) can run on a small subset first.

---

## 7. Milestones (small PRs, in order)

Each is its own PR. Each is independently testable. I follow the approval
protocol and ask before every engine-file edit.

- **M0 - Data pipeline.** JSON to generated C table + species/tier index + regen
  script. Deliverable compiles; set/mon counts verified against the JSON. No
  gameplay yet.
- **M1 - Hidden Power real type.** Flip `P_SHOW_DYNAMIC_TYPES`, verify the
  party/summary move list, the in-battle move-select window, and add/verify the
  scout-summary path. Tiny standalone PR.
- **M2 - Mode entry skeleton.** New main-menu option, a hub map, and a stub that
  starts one fixed test battle using library mons at Lv50. Proves entry + our
  data reaching a real battle.
- **M3 - Draft screen.** Offer **12** and let the player pick 6, enforcing
  Species Clause + Item Clause + the restricted cap, with the format selector
  (Singles/Doubles, cap 0/1/2).
- **M4 - Team preview + bring-N.** Show both sides' 6; pick bring 3 (Singles) /
  4 (Doubles) with Doubles lead order; scout summary on opponent mons (with HP
  real type from M1).
- **M5 - Opponent generation** from the same library, with the smart-AI flags.
- **M6 - Battle loop + recruit swap.** Run the battle series; after each win,
  recruit one of the opponent's brought mons for one of yours, clause-safe.
- **M7 - One Mega per battle.** Enable Mega locally to this mode and cap it at
  one evolution per battle.
- **M8 - Run structure + polish.** Length/scoring, save + resume, retire flow,
  text.

Doubles is folded into M3/M4/M6 rather than bolted on later, per your "both
formats in Phase 1" decision.

---

## 8. Enforcement logic (the rules, precisely)

- **Species Clause:** no two rentals sharing a National Dex number (formes of
  one species count as the same species for this).
- **Item Clause:** no two rentals sharing a held item. Mega Stones are held
  items, so distinct stones are automatically forced.
- **Restricted cap:** count rentals whose tier is in {restricted-legendary,
  sub-legendary, mythical, paradox, ultra beast, legendary-based Mega} and
  enforce <= the format cap (0/1/2).
- **One Mega per battle:** a per-battle "mega already used" flag; the mode
  enables the Mega mechanic locally without turning it on for the main game.
- **Recruit safety:** the recruit picker hides any opponent mon whose species or
  item would duplicate one already on your roster after the swap.

---

## 9. Open questions to settle before or during Phase 1

Two were decided at approval time:

- **Save architecture: DECIDED - its own save region.** The mode gets its own
  region in the save block, independent of story progress, so a fresh player can
  use it and a run cannot corrupt story data.
- **Draft offer size: DECIDED - offer 12, pick 6.** Each draft presents 12 legal
  rentals and you keep 6, for real drafting tension.

Still open, each needed before the milestone that depends on it:

- **Run length + scoring (needed by M8).** How many battles per run, win-streak
  vs completion, and any lives / whiteout buffer.
- **AI flag set (needed by M5).** Which smart-AI flags exactly (predict
  switches, knows your sets, etc.).
- **Doubles lead order (needed by M4).** Does team preview also let you set which
  2 of your 4 lead?
- **Scout transparency (needed by M4).** Does the opponent scout summary show
  full nature/EV/IV spread, or just moves + item + ability?

---

## 10. Guardrails I will honor

- Ask before touching the **Makefile / build scripts** (data pipeline) and
  before any **title/main-menu code** (entry point).
- Enable Mega **only inside this mode**; the main Kanto game stays gimmicks-off.
- No em dashes anywhere; no committed ROM/save/Nintendo assets.
- Keep RHH intact and stay release-ready.
- Update the relevant `docs/overview/` docs in the same PR when a milestone
  changes config or adds data.

---

## 11. Next step

If you approve this plan and milestone order, I start with **M0 (data
pipeline)** as a small PR, and I will ask "May I write to <file>?" before each
engine edit. If any of the section 9 questions should be answered up front, tell
me and I will fold the answers in first.
