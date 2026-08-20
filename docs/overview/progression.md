# Progression

The critical path through Kanto: towns, gyms, story gates, and HM requirements
in order. Plot stays vanilla FRLG.

> STATUS: stub. Generate the baseline from vanilla data after the first build
> (trace map connections + story flags). Keep in sync with any change to gates.

## Order (vanilla FRLG baseline — fill in)
1. Pallet Town — starter, Oak's parcel
2. Viridian City → Route 1/2/22
3. Pewter City — **Gym 1: Brock** (Boulder Badge)
4. ... (Cerulean/Misty, Vermilion/Lt. Surge, Celadon/Erika, Fuchsia/Koga,
   Saffron/Sabrina, Cinnabar/Blaine, Viridian/Giovanni, Elite Four)

Gate note - Vermilion/Surge: the gym is gated behind HM01 Cut (vanilla: the
cuttable tree at Vermilion (19,24) is the only way into the gym pocket, and Cut
comes only from the S.S. Anne Captain). We reflavor this as Surge's "S.S. Anne
trial" - cross the ship, reach the Captain, earn Cut. No mechanical change to the
gate itself. See SURGE-06 in docs/writing/lore-ledger.md.

Recurring antagonist - Giovanni: unlike the seven leaders you meet once, Giovanni
is fought THREE times along the critical path (Rocket Hideout B4F under the Celadon
Game Corner -> Silph Co 11F in Saffron -> Viridian Gym for the Earth Badge), and
Team Rocket seeds him all game (Mt Moon, Game Corner, Pokemon Tower, Silph Co). The
Viridian Gym is LOCKED until badges 2-7 are earned (vanilla), so it is always the
last gym; the reveal that the ROCKET boss and the absent Viridian LEADER are one man
lands when the gym finally opens. Lore delivery spans the whole game. See GIOVANNI-*
in docs/writing/lore-ledger.md.

## Level cap (hard, badge-gated)
Hard caps are ON (`B_EXP_CAP_TYPE = EXP_CAP_HARD`,
`B_LEVEL_CAP_TYPE = LEVEL_CAP_FLAG_LIST`, `B_RARE_CANDY_CAP = TRUE`). Over-cap
mons gain 0 battle EXP and Rare Candy is blocked at the cap. The cap is the
value for the first badge you have NOT yet earned, from the table in
`src/caps.c`:

| Progress point | Cap |
|---|---|
| Before Boulder (Brock) | 15 |
| Before Cascade (Misty) | 19 |
| Before Thunder (Surge) | 24 |
| Before Rainbow (Erika) | 29 |
| Before Soul (Koga) | 31 |
| Before Marsh (Sabrina) | 33 |
| Before Volcano (Blaine) | 42 |
| Before Earth (Giovanni) | 46 |
| Before Champion | 58 |
| Champion onward | 100 |

The field party menu also offers a `LEVEL` option (`LEVEL UP` / `LEVEL TO CAP`)
that levels a mon for free but never past the current cap.

## Mid-game forced route + finer level caps (PLANNED - needs implementation sign-off)

Problem: the Lt. Surge -> Erika stretch is long and non-linear. Silph Co (and the
rival fight on 7F) can be reached with just a vending-machine drink for the Saffron
gate guard, so a player can hit that rival BEFORE Erika/Koga. Because the cap is
badge-gated, the rival's difficulty then swings on how many optional badges the
player grabbed first: rush player = cap 29 (so it must be tuned trivially low),
thorough player = overleveled and bored. Fix: force the mid-game into a fixed order
so the player's state at Silph is known, and add finer caps so they cannot overlevel
within the long stretch.

### Forced order (decided w/ user)
Erika -> Rocket Hideout -> Pokemon Tower -> Koga -> Silph Co -> Sabrina.

| Step | Gate today | New gate needed? |
|---|---|---|
| 1. Erika (Rainbow, Celadon) | skippable in vanilla | YES - require before Rocket Hideout |
| 2. Rocket Hideout -> Silph Scope | canon: under Celadon Game Corner | no |
| 3. Pokemon Tower -> Poke Flute (Mr. Fuji) | canon: Silph Scope gates the tower ghosts | no |
| 4. Koga (Soul, Fuchsia) | canon: Poke Flute wakes Snorlax to reach Fuchsia | no |
| 5. Silph Co (rival 7F + Giovanni 11F) | canon: Saffron only needs a drink for the guard | YES - require Soul Badge (Koga) first |
| 6. Sabrina (Marsh, Saffron Gym) | canon: after Silph liberation | no (already after Silph) |

Only TWO new gates are needed: Rainbow-before-Hideout, and Soul-before-Silph.
Everything else is already enforced by key items (Silph Scope, Poke Flute/Snorlax).

Gate mechanism (decided w/ user): a BLOCKER NPC (existing sprite, placed in Porymap
by the user) stands in front of each entrance and is removed once the story flag is
set. Standard FRLG pattern: the object is hidden via a FLAG_HIDE_* toggled when the
gate condition is met; while visible, its script plays a short "you can't pass yet"
line. User places the object; I write the script.
- Gate 1: blocker at the Rocket Hideout entrance (Celadon Game Corner), removed once
  FLAG_BADGE04_GET (Rainbow / Erika) is set. Also keeps the cap-ladder ordering valid
  (Erika must precede the Hideout step).
- Gate 2: blocker at the Silph Co entrance (Saffron), removed once FLAG_BADGE05_GET
  (Soul / Koga) is set. Blocking the Silph door (not the whole city) keeps Saffron's
  other functions and route pass-through open.

### Level-cap refinement
Finer story-gated steps across the long stretch so the player cannot overlevel
between badges. Proposed ladder (numbers to confirm; endpoints match today's
29/31/33 so the overall curve is unchanged, just more granular):

| Trigger (flag/event) | Cap |
|---|---|
| Before Erika | 29 |
| Erika beaten (Rainbow) -> Rocket Hideout | 30 |
| Poke Flute obtained (Tower cleared) | 31 |
| Koga beaten (Soul) | 32 |
| Silph rival / Giovanni #2 cleared | 33 |
| Before Blaine (Volcano) and later | 42 -> unchanged |

### Cap mechanism - OPEN DECISION (new info from src/caps.c)
User picked LEVEL_CAP_VARIABLE. Reading GetCurrentLevelCap() changes the tradeoff:
- VARIABLE: the function just returns `VarGet(cap var)`. NOTHING sets it
  automatically, so we must `setvar` the cap at EVERY point (all 8 badges + champion
  + each new story step). One missed setvar freezes the cap; an unset var reads 0,
  which means no mon gains EXP at all. Powerful but fragile, lots of script wiring.
- FLAG_LIST + story flags (RECOMMENDED): the current mode already returns the cap for
  the first UNSET flag in an ordered list (`sLevelCapFlagMap`). Because the route is
  now FORCED (order guaranteed), we can just insert story-flag rows (Rocket Hideout
  done, Poke Flute got, Silph done) between the badge rows. Fully automatic (those
  events already set their flags), no per-point setvar, no freeze risk. Same result.
Recommendation: extend the flag-list, not VARIABLE. Confirm before implementing.

### Implementation checklist (NOT started - needs sign-off per guardrails)
- [ ] Cap mechanism: extend sLevelCapFlagMap in src/caps.c with story-flag rows
      (or, if VARIABLE is chosen, flip caps.h + wire setvar at every cap point).
- [ ] Gate 1: blocker NPC at the Rocket Hideout entrance, hidden once FLAG_BADGE04_GET
      (Rainbow) is set. User places the object in Porymap; I write the script.
- [ ] Gate 2: blocker NPC at the Silph Co entrance, hidden once FLAG_BADGE05_GET
      (Soul) is set. User places the object in Porymap; I write the script.
- [ ] Pick the exact story flags to hang caps on; verify they exist and are set at
      the right moment; confirm ordering holds under the forced route.
- [ ] Update this doc + changelog.md in the same PR.
- [ ] Keep the rival DIALOGUE work (drafts/buhrito.md) separate from this systems PR.
