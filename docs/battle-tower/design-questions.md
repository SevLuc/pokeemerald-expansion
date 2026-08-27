# Battle Tower - Design Interrogation & Open Questions

Status: brainstorming. Nothing here is decided. This doc restates your ideas,
then grills each one with the questions and trade-offs we need to settle before
any code is written. Answer the **Q** prompts inline or in chat.

The moveset/roster data (`roster.md`, `movesets/*.json`) is done and is the raw
material this mode runs on. This doc is about the mode itself.

---

## 0. The identity question (settle this first, everything hangs off it)

You keep saying "Battle Tower AND Factory." Those are two opposite things in the
base engine:
- **Tower** = you bring your **own** trained team.
- **Factory** = you get **rental** Pokemon you didn't train.

Your rules (roster of 6, team preview, swap an opponent's mon after a win, no
duplicate items/species) read like a **rental-draft roguelike**, not classic
Tower. The huge moveset library we built only makes sense if the game is handing
players pre-built rentals.

- **Q0.1** Where does the roster of 6 come from at the start of a run?
  - (A) **Draft** from the rental pool (pick 6 from an offered set, Factory-style)
  - (B) **Pre-made rental teams** you choose between
  - (C) Your **own caught team** (classic Tower; then the swap/roguelike rules mostly don't apply)
  - (D) **Draft, then improve mid-run** via the roguelike rewards (my read of your intent)
- **Q0.2** Is "Tower" vs "Factory" two separate modes, or one mode with the
  draft style as a toggle? I'd fold them into **one** roguelike mode with a
  draft step; "Tower/Factory" become flavor names for sub-variants. Agree?
- **Q0.3** Level rule: **flat Lv50** (VGC standard, cleanest for balance),
  flat Lv100, or **scaling per act**? Flat 50 is my recommendation.

---

## 1. Structure: 7-floor acts

You want runs built from acts of 7 floors, boss at the end.

- **Q1.1** What is a "floor"? One battle, or a **node** you route through (see
  section 4)? If floors are nodes, "7 floors" is really "7 rows of a map."
- **Q1.2** How many acts per run? (3 acts x 7 floors = 21 fights feels right for
  a session; more = a marathon.)
- **Q1.3** Is a run **roguelike-terminal** (one loss ends the run) or do you get
  **lives / a whiteout buffer** (`B_FLAG_NO_WHITEOUT` exists)? Hard-but-fair
  suggests maybe 1-2 lives, not instant death.
- **Q1.4** Difficulty curve across the 7 floors + boss: flat, or ramping (AI
  smartness, better opponent sets, more restricteds allowed deeper in)?
- **Q1.5** Save/checkpoint: can you quit mid-run and resume, or is a run a single
  sitting? (Factory saves challenge state; we can mirror that.)
- **Q1.6** Streak vs completion: is the score "acts cleared," a win streak, or
  both? Does clearing all acts loop into a harder New Game+?

---

## 2. Boss acts: gym leaders / rivals / recurring characters

End-of-act bosses drawn from the FRLG cast (Kanto-authentic, per project rules).

- **Q2.1** Which roster of bosses? Gym leaders (8) + rivals (Blue) + E4 + villain
  (Giovanni) is ~14. Do bosses **repeat** across acts (Brock act 1, harder Brock
  act 3) or is each act a **different** character?
- **Q2.2** Themed teams: gym leaders run their type (Brock = Rock, etc.). Do
  bosses ignore the roguelike ruleset and just bring a fixed 6, or do they also
  team-preview and bring 3/4?
- **Q2.3** Do bosses get a signature twist (a field effect, a forced weather, an
  extra restricted, a "boss buff")? Careful: this fights "hard but fair."
- **Q2.4** Rewards for a boss kill: a rare rental, a mega stone unlock, BP, a
  relic (section 4), a heal? Bosses should feel worth it.
- **Q2.5** Lore hook: CLAUDE.md wants gym-leader histories revealed in fragments.
  Do boss encounters here **surface lore** (intro/defeat lines, a fragment per
  boss cleared)? This is where the writer agent plugs in.
- **Q2.6** Do bosses respect Item/Species clause too, or are they allowed
  "illegal" boss teams (duplicate items, a restricted over the player's cap) as
  a difficulty lever?

---

## 3. Mono & other creative challenges

- **Q3.1** Are challenges **run modifiers** (pick before a run: Mono-Fire, etc.)
  or **separate ladders**?
- **Q3.2** Mono-type: does it restrict your **roster** to one type, your
  **opponents**, or both? Reward for the added constraint?
- Candidate challenge modifiers (tick the ones you want):
  - Mono-type / Mono-generation / Mono-color
  - **Inverse** battles (type chart flipped)
  - **Level cap** run (opponents overleveled, you capped)
  - **No-item** / **No-setup-moves** / **Weather-locked** (perma sun/rain/sand)
  - **Restricted-only** (draft only from the legendary tier) or **NFE-only**
    (Eviolite mons only)
  - **Nuzlocke-lite**: a fainted rental is **removed** from your roster for the
    rest of the run (raises stakes without permadeath of the run)
  - **Boss rush**: all 7 floors are bosses
  - **Blind**: team preview disabled (removes the scouting layer)
- **Q3.3** Roguelike "ascension"-style stacking difficulty: unlock harder
  modifiers as you win, opt in for more reward? Or keep challenges flat?

---

## 4. Roguelike between-floor options (routing)

- **Q4.1** Do you want a **branching map** (Slay-the-Spire: you see the next few
  nodes and choose your path) or a **linear** floor-by-floor with a **reward
  choice** after each fight? Branching is more roguelike but more UI.
- **Q4.2** Node types to include (pick a set):
  - **Battle** (normal), **Elite** (harder, better reward), **Boss** (act end)
  - **Heal** (restore your team's HP/PP between fights)
  - **Swap / Recruit** (take one of the last opponent's mons, Factory-style)
  - **Shop** (spend BP: items, a rental, a re-roll, a mega stone)
  - **Tutor / Reforge** (change a mon's moves / nature / EV spread / ability)
  - **Event / Mystery** (random risk-reward, roguelike flavor)
- **Q4.3** Persistent **relics/buffs** (roguelike staple: "your leads get +1
  priority turn 1," etc.)? This is the biggest departure from clean competitive
  and could undercut "fair." My lean: **skip relics**, keep power in the
  Pokemon/sets, use routing + swaps + shop as the roguelike layer. Agree?
- **Q4.4** Economy: is there a currency (BP), and is it earned per win / per
  floor / per style points? What does it buy?
- **Q4.5** How do the **swap rules** (section 5) interact with routing? Is the
  post-battle swap always available, or only at Swap nodes?

---

## 5. The ruleset (your rules, corrected and expanded)

### What you specified
- **Singles**: roster of 6, **bring 3** per battle.
- **VGC/Doubles**: roster of 6, **bring 4** per battle.
- **Team preview** both ways: you see the opponent's 6 and pick your bring based
  on it (and they see/pick against yours).
- **Summary access**: you can open a summary on the opponent's Pokemon to see
  their builds.
- **Mega**: multiple mega-capable mons allowed on the roster, but **only one
  Mega Evolution per battle**.
- **Restricted count** depends on format.
- **Post-battle swap**: after each battle you may swap one Pokemon, but you may
  **not** end up with two of the same **item** or two of the same **species**.

### Grill on your rules
- **Q5.1 (the swap wording)** "You can only swap out pokemon that the opponent
  brings at the end." Do you mean: after a win, the pool you may **recruit from**
  is limited to the mons the opponent actually **brought** (3 or 4), not their
  full 6? And you swap one of yours **out** for one of theirs? Confirm the exact
  mechanic, because it defines the whole progression loop.
- **Q5.2 (Item Clause is NOT a VGC rule)** Real VGC has **Species Clause** but
  **allows duplicate items** (two Life Orbs is legal). Your "no duplicate items"
  is a **Battle Frontier / old Battle Spot** rule. Is that intentional
  (Frontier-flavored) or do you want VGC-accurate (drop item clause for the VGC
  format, keep it only for a "Frontier" format)?
- **Q5.3 (mega stones vs item clause)** A Mega Stone **is** a held item. Item
  clause already forces different stones per mon, so multiple mega-capable mons
  is fine. But it also means a mega mon **cannot** hold Life Orb, etc. Confirm
  that's understood/intended.
- **Q5.4 (restricted per format)** Give me the exact caps. Suggested, VGC-style:
  - Singles-standard: **0** restricted
  - Singles-restricted: **1**
  - VGC Reg-style: **0 / 1 / 2** as three sub-formats (matches your earlier 3
    tower modes)
  Are "restricted" here = our `restricted-legendary` tag only, or also
  sub-legendaries / paradox / ultra beasts / mythicals? We tagged all of those.

### VGC / doubles rules you did not list (decide each)
- **Flat Level 50** (all mons set to 50). **Recommend on.**
- **Bring 4, lead 2**: in doubles you pick 4 and the first 2 are your leads.
  Does team preview let you also pick lead order?
- **Species Clause** (no two of the same National Dex number). You have this.
- **Item Clause**: OFF for true VGC (see Q5.2).
- **Restricted/Mythical banlist** per format (mythicals are usually VGC-illegal;
  we tagged 26 mythicals - are they in, capped, or banned?).
- **Terastal / Dynamax / Z-Moves**: OFF (project gimmicks-off). Mega is the only
  gimmick, 1/battle. Confirm.
- **Timer**: a battle turn/time limit? Frontier has none; VGC has a clock.
  Probably skip for a single-player PvE tower.
- **Draw / tie resolution**: last-Pokemon ties, self-KO moves (Explosion, Final
  Gambit, Misty Explosion), Perish Song, timer expiry. Base engine has rules;
  we just confirm we use them.
- **Duplicate held Mega Stone / duplicate form**: covered by item + species
  clause.

### Singles rules you did not list (these are Smogon-style, not VGC)
If the "singles" format should feel like Smogon singles rather than Frontier,
these clauses matter. Tell me which you want:
- **Sleep Clause** (only one opponent Pokemon asleep at a time by your moves)
- **Evasion Clause** (ban Double Team / Minimize)
- **OHKO Clause** (ban Fissure / Sheer Cold / Guillotine / Horn Drill)
- **Moody Clause**, **Endless Battle Clause**, **Baton Pass** restrictions
- Modern Smogon singles has **no item clause** (dup items allowed)

My read: you may actually want **two rule presets** - a "Frontier" preset
(Species + Item clause, no Smogon clauses) and a "Competitive" preset (Species +
Sleep/Evasion/OHKO, no Item clause). Confirm and I'll spec both.

---

## 6. Hidden Power shows its real type (your explicit request)

Requirement: everywhere the player can view a move, **Hidden Power displays the
type it will actually deal damage as** (from the Pokemon's IVs), not "Normal."

- Where this must apply: the **party/summary screen** move list, the **in-battle
  move-select** menu, the **opponent summary** (Q5 lets players scout builds),
  and any move-info popup.
- Our data already stores each HP set's IVs and type, and the build computes HP
  type from IVs, so the value is available; this is a **display** change in the
  UI code.
- **Q6.1** Also **recolor** the move's type badge to the real type (not just the
  text)? (Recommended - players read the color first.)
- **Q6.2** Show base power as **60** (this build fixes HP power) in the info, or
  leave it hidden as vanilla does?
- **Q6.3** Apply this globally (overworld/main game too) or only inside the tower
  mode? Global is simpler and harmless.

---

## 7. Things I want you to decide that you have not mentioned

- **Q7.1** How is a rental's **nature/EVs/IVs** shown to the player when scouting
  (full stat spread, or just the "build" summary)? Full transparency changes how
  players draft/counter.
- **Q7.2** AI level: do opponents use the smart-AI flags (predict switches, know
  your sets)? For a scouting-based mode, a sharp AI is the point.
- **Q7.3** Do **opponent** teams draw from the **same** moveset library we built
  (so the player can face the exact sets they can rent), or a separate boss pool?
- **Q7.4** Rewards persistence: does anything carry **between runs** (unlocked
  rentals, cosmetic, harder tiers), or is every run from scratch?
- **Q7.5** Entry point: new main-menu option, or an in-world building? (Affects
  whether we touch the title menu or just a map + scripts.)

---

## Answer these first (the load-bearing four)
1. **Q0.1 / Q0.2** - draft-rental roguelike, own-team tower, or both as one mode?
2. **Q5.1** - exact post-battle swap/recruit mechanic.
3. **Q5.2 / Q5.4** - Item Clause yes/no per format, and restricted caps.
4. **Q4.1 / Q4.3** - branching roguelike map + relics, or linear with reward
   choices and no relics?

Everything else can follow once these are set.
