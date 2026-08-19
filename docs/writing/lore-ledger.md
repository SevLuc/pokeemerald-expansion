# Lore Ledger (keystone)

> Purpose: the master consistency map for distributed storytelling. Every history
> fragment revealed through an NPC gets one row so nothing contradicts and the
> story unlocks in a sensible order.
> Rule: add/update a row in the same PR as any new lore line.

## How to read a row
- ID - stable fragment id, e.g. BROCK-03.
- Subject - who/what the fragment is about.
- Reveal - what the player learns (one line).
- Source NPC - who says it (or object/sign).
- Map - where they are.
- Gate - progression condition (badge count, flag, story beat).
- Order - intended discovery order within the subject's arc.
- Status - idea / drafted / in-game.
- Flags - release/consistency tags from the style guide.

## Brock - "the phones" gag + serial-divorcé history
Concept: Brock's gym is cluttered with ringing phones. Surface gag: he's always
"on a call" (the "Brock is calling" meme). The hidden layer, revealed COYLY: the
phones are his ex-wives, and he runs the gym mostly for the challenge fees -
alimony doesn't pay itself. Engine of the joke = the anime "hopeless romantic"
Brock: he keeps falling in love, keeps marrying, keeps divorcing, keeps paying.
Uses existing vanilla phone/PC objects only - no new art.

Reveal is COY throughout (player choice): NPCs never say "divorce" or "ex-wife"
outright. They say "previous sponsors," "generous every single month," ringtones
as a "filing system." The player connects the dots. Brock himself plays it
straight (one wink) so the FIGHT still lands.

> Reference check: the "Brock is calling" bit rides on the meme + the anime
> womanizer trait. Keep all wording in our own voice - no verbatim anime lines.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| BROCK-01 | Brock (path, vague) | Lass: "Big heart, that one. Gives it away a little too easy." | Lass (existing) | Pewter City | none (pre-gym) | 1 | in-game | - |
| BROCK-02 | Brock (path, vague) | Fat Man (append to his Brock praise): "Mind you, the man's got history. You'll see." | Fat Man (existing) | Pewter City | none (pre-gym) | 2 | in-game | - |
| BROCK-03 | Brock (path, vague) | "Off to challenge BROCK? Everyone wants a piece of him. His lawyers, mostly." | new NPC near gym | Pewter City | none (pre-gym) | 3 | drafted | - |
| BROCK-03b | Brock (path, vague) | Woman: "Oh, I knew BROCK. Once. …Briefly." | new NPC (woman) | Pewter City | none (pre-gym) | 3 | drafted | - |
| BROCK-03c | Brock (path, vague) | Kid: "Mom says BROCK's real generous. Every single month. I don't get it." | new NPC (kid) | Pewter City | none (pre-gym) | 3 | drafted | - |
| BROCK-04 | Brock (gag) | Gym guide: the phones ring constantly; Brock says just let 'em ring. | Gym guide | Pewter Gym | none | 4 | in-game | - |
| BROCK-05 | Brock (gag) | Trainer (Liam): each phone has its own ringtone, "that's a filing system." | Pewter Gym trainer | Pewter Gym | none | 5 | in-game | - |
| BROCK-06 | Brock (reveal, coy) | Trainer (Liam) on defeat: "Six phones, six... 'previous sponsors.'" | Pewter Gym trainer | Pewter Gym | none | 6 | in-game | [FLAG: canon-check] |
| BROCK-07 | Brock (intro) | Goofy-romantic ramble ("a marriage or two"; contract advice) cut off by ringing phones, then "...Ignore that. Let's battle." | Brock | Pewter Gym | none | 7 | in-game | [FLAG: canon-check] |
| BROCK-08 | Brock (why leader) | "Ever wonder why he takes on every trainer? Challenge fees. Alimony doesn't pay itself." | Pewter City NPC | Pewter City | after 1st badge | 8 | drafted | [FLAG: canon-check] |
| BROCK-09 | Brock (throwback) | "Heard he's fielding challengers day and night. Heard he got married again, too." | later-town NPC | TBD | after ~6th badge | 9 | idea | [FLAG: canon-check] |
| BROCK-10 | Brock (throwback) | "Brock's still at that gym. Still on the phone. Some things are eternal." | later-town NPC | TBD | post-E4 | 10 | idea | - |

Consistency notes:
- Path fragments (01-03) are UNGATED and pre-gym, and stay vague so the punchline
  only clicks once the player reaches the gym and sees the phones (04-07).
- Reveal never states "divorce/ex-wife" - coy euphemism only (decided w/ user).
- Why-leader (08) and throwbacks (09-10) unlock post-progression as callbacks.
- Brock's own battle lines stay archetypal Gym-Leader; comedy lives in the room
  around him, not in his threats, so the hard-but-fair fight still reads as real.
- RETIRED earlier draft: "raising younger siblings / father left to train."
  Replaced by the divorce/alimony arc. The anime hopeless-romantic trait is the
  only kept thread (it powers the divorces).

## Misty - tomboy battler + Psyduck (her first POKéMON)
Concept: youngest Sensational Sister who does the real battling (sisters do the
water shows). PSYDUCK is her first POKéMON: she loves it, it drives her crazy
(everything she's not). Payoff reveal: she went all-WATER because water types
CAN'T RUN AWAY like Psyduck does. Cerulean respects her strength, jokes about the
bug fear, and treats Psyduck as a beloved town jester. GIMMICK: no bug-types in
the gym (guide blocks at the door). Lore is told in steps by the mandatory gym
trainers; town NPCs carry ambient respect/jokes. Full lines: drafts/misty.md.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| MISTY-01 | Misty (respect) | "She runs that gym alone. Has for years. Say what you want about her." | Youngster (existing) | Cerulean City | none (pre-gym) | 1 | in-game | - |
| MISTY-02 | Misty (bug, oblique) | Cale the BUG CATCHER: "Me and the CERULEAN gym have an… understanding." | Cale (Route 24) | Nugget Bridge | none | 2 | in-game | - |
| MISTY-03 | Psyduck (jester) | "That PSYDUCK answers to no one. …Not even her." | Balding Man (existing) | Cerulean City | none (pre-gym) | 3 | in-game | - |
| MISTY-04 | Psyduck (long bond) | Reli: "That PSYDUCK's older than her badges." | Reli (Route 24) | Nugget Bridge | none | 4 | in-game | - |
| MISTY-05 | Misty (why water, oblique payoff) | Nob: "She only keeps what can't leave the water. …Never says why." | Nob (Route 25) | Route 25 | none | 5 | in-game | - |
| MISTY-06 | Misty (heart) | "Everyone thinks that PSYDUCK is the joke. …I think it's the one thing she'd never replace." | Balding Man (existing; post-badge branch) | Cerulean City | FLAG_BADGE02_GET | 6 | in-game | - |
| MISTY-07 | Misty (gimmick) | Bug-ban gate: on gym entry, if any party mon is BUG type (EGGs judged by hatch species too), the Gym Guy walks over, tells you ("she's up on a chair for the afternoon"), shoves you back out the door. New special PartyHasBugType + ON_FRAME map script; always-on. | Gym Guy | Cerulean Gym | none | 7 | in-game | - |
| MISTY-CHORUS | whole-area gag | Every road trainer drops one oblique Misty/PSYDUCK line (Timmy, Ali=egg, Ethan, Shane on Rt24; Dan, Flint, Kelsey, Haley, Franklin=egg on Rt25) + Diana/Luis verify. Full list: drafts/misty.md. | Route 24/25 + gym trainers | Cerulean area | none | - | in-game | - |
| MISTY-EGG | deniable Togepi seed | Ali (Rt24): "Found an EGG by the pool once. She took it before I could blink." / Franklin (Rt25): "She's been guarding something down by the shore." | Ali, Franklin | Nugget Bridge / Route 25 | none | - | in-game | [FLAG: canon-check] |
| MISTY-BILL | PAYOFF (the one non-coy telling) | Freed Bill explains the whole Misty/PSYDUCK story in depth: her PSYDUCK wandered into his Cell Separation System, mashed buttons, fused him with a CLEFAIRY, walked out. Psyduck = her first mon + opposite; why she trains only WATER (a Psyduck wanders off, a GOLDEEN stays in the pool, "a zen state of mind"); never lets it go. Re-talk button: "…don't ask me why the machine was set to a CLEFAIRY." | Bill (Sea Cottage) | Route 25 Sea Cottage | after freeing Bill | 8 | in-game | - |

## Lt. Surge - goofy war-hero + secret liberator of Vermilion
Concept: loud macho war-hero on the surface ("HYPER BEAM to the dome-ski"); under
it, a slums kid ("Private" Surge) who signed onto the S.S. ANNE, rose to the
ship's Lieutenant, freed the electric POKéMON in its hold, and with them struck
LIGHTNING fast to drive Rocket from Vermilion. He then let the people govern
themselves and stayed only as the city's guard, taking the gym. "Not a king. A
shield." Delivery mirrors Misty: Vermilion City NPCs drip vague regime/Private-
Surge references; the S.S. ANNE crew show present-day pride/freedom; the S.S.
ANNE CAPTAIN (HM01 CUT) is the payoff who tells it plainly.

REFRAME (this PR): the S.S. ANNE is now Surge's OWN proving trial. Vanilla FRLG
already gates his gym behind Cut (the cuttable tree at Vermilion (19,24) is the
only way into the gym pocket, and Cut only comes from the ship). We make that
gate legible: crossing the ship to REACH the Captain = passing "the first trial";
the Captain rewards Cut and tells the reveal, framing the whole thing as Surge's
decree ("cross my ship, prove your resolve"). The seasick/back-rub gag is dropped.
CANON: Rocket is driven from VERMILION locally only; Rocket still active in the
mainline plot - never claim Rocket is finished. Full lines: drafts/surge.md.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| SURGE-01 | Surge (regime, vague) | Woman (append): "Mind, it was worse once. The whole city was. …Different management, back then." | Woman (existing) | Vermilion City | none | 1 | in-game | [FLAG: canon-check] |
| SURGE-02 | Surge (regime, vague) | Old Man 2 (append): folks here owned nothing under "the old bosses." "…Then they didn't. Ask the LT. Or don't." | Old Man 2 (existing) | Vermilion City | none | 2 | in-game | [FLAG: canon-check] |
| SURGE-03 | "Private" Surge | Sailor (append): "Some of us knew him before the stripes. Back when they just called him 'Private.'" | Sailor (existing) | Vermilion City | none | 3 | in-game | [FLAG: canon-check] |
| SURGE-04 | S.S. Anne (praise) | Deck Sailor (append): "I sailed under the LT once. Loudest officer I ever knew. …Best, too. This ship owes him plenty." | Deck Sailor (existing) | S.S. Anne Deck | none | 4 | in-game | - |
| SURGE-05 | S.S. Anne (freedom) | 1F Corridor Sailor (append): "Sails clean out of VERMILION, free as you please. Wasn't always so. …You're too young to know it." | 1F Corridor Sailor (existing) | S.S. Anne 1F | none | 5 | in-game | - |
| SURGE-06 | PAYOFF (plain telling) | Captain tells it plainly: Rocket ran the docks; a slums boy signed on as a private, rose to the ship's Lieutenant, freed the electric POKéMON in the hold and struck lightning fast, drove Rocket from Vermilion, then let the people govern and stayed only to guard them. "Not a king. A shield." Frames the ship-crossing as Surge's trial; rewards HM01 CUT. Re-talk: "I owe that man a lot. …We all do." | S.S. Anne Captain (HM01 CUT) | S.S. Anne Captain's Office | reach the Captain | 6 | in-game | [FLAG: canon-check] |
| SURGE-07 | Surge himself | Intro: loud macho ("HYPER BEAM to the dome-ski"; "Not on my turf. Not anymore."). Defeat: "Reminds me of me. Back when it counted." History only leaks. | Lt. Surge | Vermilion Gym | none | 7 | in-game | - |
| SURGE-07b | Surge (via ex-soldier) | Tucker (served under Surge) defeat: "…But the LT's faced worse. Far worse." | Tucker (gym trainer) | Vermilion Gym | none | 7 | in-game | [FLAG: canon-check] |
| SURGE-08 | Why gym leader | Woman post-badge branch: "He could have run this city. Chose to mind a gym instead. …Him all over." | Woman (existing; post-badge) | Vermilion City | FLAG_BADGE03_GET | 8 | in-game | [FLAG: canon-check] |
| SURGE-GATE | S.S. Anne trial / gym gate | Gym-gate guard voices the vanilla Cut-tree gate as Surge's decree. Pre-Cut: "That tree's not for the unproven. Cross the S.S. ANNE. Reach her CAPTAIN. LT's own rules." Post-Cut (FLAG_GOT_HM01): "So you walked the whole ship and lived. Then the LT will see you." Script `VermilionCity_EventScript_GymGateGuard` written; NEEDS a Porymap object placed near the gym tree (~x20,y25) to go live. | Gym-gate guard (NEW, Porymap TODO) | Vermilion City | none | 6 | drafted | - |
| SURGE-GIMMICK | Trash-can trial | The famous "hated" trash-can puzzle reframed as Surge's deliberate TEST OF DISCIPLINE + ENDURANCE. All gym trainers + Gym Guy + the puzzle messages sell it ("Not cruelty. Discipline." / "locked to see if you'll quit." / "Composure, or start over."). Functional hints (2nd lock adjacent, switches in cans, type tip) preserved. | Dwayne/Baily/Tucker/Gym Guy/puzzle | Vermilion Gym | none | 7 | in-game | - |

Consistency notes:
- The S.S. ANNE trial and the gym trash-can trial now rhyme: both are Surge testing
  resolve/discipline before he'll face you. The Captain's reveal is the "why."
- SURGE-06 is the one non-coy telling (Bill-equivalent). City/crew lines (01-05)
  stay vague so the Captain's payoff is the click.
- SURGE-08 gates on FLAG_BADGE03_GET (Surge's own Thunder Badge) - it reflects on
  him only after you've beaten him.
- SURGE-GATE guard is the only piece needing a Porymap placement; the mechanical
  gate (Cut-tree) already works without it, so nothing is blocked meanwhile.

## Template: new gym leader
Copy per leader. Keep fragments optional and gated so a rushing player still
finishes and a curious one gets the hidden layer.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| XXXX-01 | <leader> | <hook the player notices first> | | | none | 1 | idea | - |
| XXXX-02 | <leader> | <deeper detail> | | | after Nth badge | 2 | idea | - |
| XXXX-03 | <leader> | <the payoff / reframe> | | | late-game flag | 3 | idea | - |

## Optional: in-world aggregator (decide later)
FRLG has no quest log, so players piece histories together from memory. If that's
too easy to miss, add a light aggregator - a gossip or librarian per town who
recaps what you've uncovered. Not committing yet; noted so it isn't forgotten.
