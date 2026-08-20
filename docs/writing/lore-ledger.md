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
- CROSS-LINK (Celadon payoff): Brock's "previous sponsors" take refuge in ERIKA's
  gym. See ERIKA-EXES. Kept coy in both places ("PEWTER number," "let it ring,"
  "generous every single month") so the phones in Pewter and the ladies in Celadon
  quietly rhyme. This is the distributed answer to "where do the exes go."

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
only way into the gym pocket, and Cut only comes from the ship), so the gate needs
no new enforcement. We make it legible in dialogue: crossing the ship to REACH the
Captain = passing "the first trial"; the Captain rewards Cut and tells the reveal,
framing the whole thing as Surge's decree ("cross my ship, prove your resolve").
The seasick/back-rub gag is dropped.
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
| SURGE-GIMMICK | Trash-can trial | The famous "hated" trash-can puzzle reframed as Surge's deliberate TEST OF DISCIPLINE + ENDURANCE. All gym trainers + Gym Guy + the puzzle messages sell it ("Not cruelty. Discipline." / "locked to see if you'll quit." / "Composure, or start over."). Functional hints (2nd lock adjacent, switches in cans, type tip) preserved. | Dwayne/Baily/Tucker/Gym Guy/puzzle | Vermilion Gym | none | 7 | in-game | - |

Consistency notes:
- The S.S. ANNE trial and the gym trash-can trial now rhyme: both are Surge testing
  resolve/discipline before he'll face you. The Captain's reveal is the "why."
- SURGE-06 is the one non-coy telling (Bill-equivalent). City/crew lines (01-05)
  stay vague so the Captain's payoff is the click.
- SURGE-08 gates on FLAG_BADGE03_GET (Surge's own Thunder Badge) - it reflects on
  him only after you've beaten him.
- No gym-gate guard NPC: the vanilla Cut-tree already gates the gym (HM01 is only
  usable once the Captain awards it), so the trial framing lives entirely in the
  Captain's reveal and the ambient lines - no extra enforcement object needed.

## Erika - the Sleeping Enigma (mystique by design; no plain telling)
Concept: the gentle, ever-dozing flower-princess is the subject of Kanto's wildest
contradictory legends, and NONE is ever confirmed in-game. That is the character:
she cultivates her own mystery like she cultivates flowers. Unlike Brock/Misty/
Surge, there is deliberately NO payoff NPC who explains her plainly (decided w/
user). The "payoff" is a gym devotee who gathers the rumors and refuses to settle
them ("ask ten of us, you'll get ten ERIKAs").

ANCHOR (the one thing everyone agrees on): she's never seen awake, and her garden
grows flowers found nowhere else. Every rumor hangs off that; each is a FACET a
different kind of person believes. Delivery = coy ambient chorus across Celadon
City NPCs (append to existing lines), plus the aggregator inside the gym. Full
lines: drafts/erika.md.
CANON: the Rocket line stays canon-safe - grunts AVOID her garden ("Boss's
orders"); it never says she fights or beats Team Rocket. Silly-through-contrast: a
menacing grunt spooked by a florist; a dozer who gave an old man insomnia.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| ERIKA-01 | Facet: poison/medicine | Little Girl (has a KOFFING): "ERIKA grows flowers like that. Pretty. But mom says never sniff one twice. …I forget why." | Little Girl (existing) | Celadon City | none | 1 | in-game | [FLAG: canon-check] |
| ERIKA-02 | Facet: perfume calms city | Woman (civic-pride append): "Some say it's no accident we stay so lovely. ERIKA's perfumes, on the wind. …I don't ask." | Woman (existing) | Celadon City | none | 2 | in-game | - |
| ERIKA-03 | Facet: once-fearsome battler | Fat Man (Poliwrath owner): "I saw her battle once, years back. …I've slept poorly ever since." | Fat Man (existing) | Celadon City | none | 3 | in-game | - |
| ERIKA-04 | Facet: ladies-only refuge | Old Man 1 (append to "full of women!"): "…I hear she teaches them more than flowers. Never got past the door." | Old Man 1 (existing) | Celadon City | none | 4 | in-game | - |
| ERIKA-05 | Facet: even Rocket steers clear | Rocket Grunt (append): "Keep clear of that GYM too. Boss's orders. Something about her garden. I don't ask twice." | Rocket Grunt 1 (existing) | Celadon City | none | 5 | in-game | [FLAG: canon-check] |
| ERIKA-06 | Anchor: the impossible garden | Boy (tea append): "They say her tea leaves come from ERIKA's garden. Maybe that's why I saw colors that don't have names." | Boy (existing) | Celadon City | none | 6 | in-game | - |
| ERIKA-PAYOFF | The non-answer (aggregator) | Gym trainer Lisa (post-battle): "The truth about her? Ask ten of us, you'll get ten ERIKAs. …She likes it that way." | Lisa (gym trainer) | Celadon Gym | after her battle | 7 | in-game | - |
| ERIKA-08 | Post-badge wink | Old Man 1 (post-badge branch): "You beat ERIKA? And you still can't tell me one true thing about her. …That's ERIKA." | Old Man 1 (existing; post-badge) | Celadon City | FLAG_BADGE04_GET | 8 | in-game | - |
| ERIKA-POISON+ | Facet spread: poison/medicine (~40%) | Poison/medicine is the DOMINANT city legend. Extra coy carriers: Restaurant drugstore woman ("the DRUGSTORE's best cures aren't on any shelf; ERIKA decides who gets those"), Dept Store 2F Lass ("one petal does more; you don't find it, it finds you"), Dept Store 5F drugstore Sailor ("none of it matches one vial of hers"), Condominiums tea lady ("leaves from a garden I'm not allowed to name; sleep like the dead, the good kind"). | Restaurant Woman, Dept Store 2F/5F, Condo Tea Lady (existing) | Celadon City + interiors | none | 1 | in-game | [FLAG: canon-check] |
| ERIKA-FAME | Facet reach: perfume legend spreads far | Her fame crosses Kanto. Lavender grave-keeper: "when the wind turns from CELADON, the spirits settle." Route 10 (Rock Tunnel mouth) Trent: "one breath of that city's air can talk a man out of a fight." Route 10 Carol: "a lady in CELADON grows flowers stranger than any POKéMON." | Lavender WorkerM, Route 10 Trent/Carol (existing) | Lavender Town, Route 10 | none | 2 | in-game | - |
| ERIKA-ROCKET+ | Facet: even Rocket steers clear (2nd) | Rocket Grunt 2 (city): "Not near the flower district. We don't go there. Boss's rule. Don't ask." | Rocket Grunt 2 (existing) | Celadon City | none | 5 | in-game | [FLAG: canon-check] |
| ERIKA-BIKERS | GIMMICK: the bikers who fled | The Route 16 (Cycling Road, west of Celadon) bikers abandoned the city in terror of the perfume/medicine master and now camp happily on the route with their beloved POISON types. Light running gag: they gloat about dodging CELADON taxes. Lao (fled + tax wink), Ruben ("my GRIMER hid behind me"), Hideo (keeps the VERMILION-detour hint + "gives me the shivers"), Camron ("poison that scared off even US"). Reflavor of existing biker trainers; no relocation needed (they're already on Rt16). | Route 16 bikers (Lao/Ruben/Hideo/Camron) | Route 16 | none | 6 | in-game | - |
| ERIKA-EXES | GIMMICK: Brock's exes take refuge | The "ladies only" gym is where Brock's "previous sponsors" end up; ERIKA hosts them all and is NOT one herself. COY per the Brock arc (never "ex-wife/divorce"): Kay ("she never had a PEWTER number herself; just keeps the door open"), Lori ("the last one? generous, every single month, even now"), Mary ("let it ring, dear; a man in PEWTER, he always calls"). "PEWTER number" + "let it ring" tie straight back to Brock's ringing-phone gym. CROSS-LINK: BROCK arc (this is the distributed payoff for "where the exes go"). | Gym trainers Kay/Lori/Mary | Celadon Gym | none | 7 | in-game | [FLAG: canon-check] |

Consistency notes:
- NO plain telling anywhere - that is the whole point. If a future line "solves"
  Erika, it's wrong. Keep every facet coy and mutually contradictory.
- All facets share the ANCHOR (never awake + impossible garden), so the rumors
  feel like one mystery viewed from many angles, not a random grab-bag.
- ERIKA-08 gates on FLAG_BADGE04_GET (her own Rainbow Badge): the wink only lands
  after you've beaten her and STILL know nothing.
- Erika's own gym lines are now reflavored to a soft, HYPNOTIC-AURA voice: a sweet
  young woman who has tended this garden since childhood, whose scent makes callers
  drowsy ("few ever notice they've dozed"). Grounded, never occult/medium. The edge
  stays under the sweetness ("mind the thorns"; "it will do anything for you.
  …Anything at all"). Beating her = resisting the garden's pull ("you never once
  drifted off"), NOT a spell. Functional info kept (Lv50 obey + STRENGTH; GIGA
  DRAIN). The town chorus still carries the unconfirmable legends; her own voice
  adds aura, not answers.
- The two GIMMICKS (ERIKA-BIKERS, ERIKA-EXES) give the GYM/town concrete, funny
  truths, but say nothing certain about ERIKA HERSELF - she stays unknowable. The
  bikers even reinforce the poison/medicine legend from the outside (they fled
  HER). Keep it that way: gags about the room, mystery about the woman.
- Weighting (per user): poison/medicine is the dominant city legend (~40% of
  carriers), once-fearsome and ladies-only about ~20% each, perfume-calms threaded
  through the "thoughtful" NPCs and out past Celadon (Lavender, Rock Tunnel mouth).

## Koga - the flamboyant CEO (necessary evil; the whole town has an opinion)
Concept: surface stays canon - the terrifying, theatrical "Poisonous Ninja Master."
Hidden layer: he is the extravagant CEO of KOGA INDUSTRIES, Kanto's POWER/ENERGY
utility. His poison-gas POKéMON (Koffing/Weezing/Muk) run the refineries; the smog
over Fuchsia is the price of the whole region's electricity. He is a NECESSARY EVIL
- the nature town (and the SAFARI ZONE) resents his pollution, but everyone depends
on his power (you can't boycott your own lights). Two deeper layers, revealed by gym
insiders: (a) the invisible-wall gym is a PROTESTER-REPELLENT (petitioners get lost,
give up); (b) he is a master SPIN DOCTOR - the costume and gimmick gym are deliberate
misdirection to keep people entertained instead of angry. He sincerely believes he is
the hero of his own story. Silly-through-contrast: a pantomime ninja who is quietly a
polluting power baron; the "creeping horror of poison" is literally industrial smog.

DELIVERY (per user: the WHOLE area weighs in). Ambient opinions saturate Fuchsia City,
its interiors, the Safari Zone, and the bordering routes, spread across distinct
STANCES so it reads as a real civic argument: PRO/dependent, ANTI/nature, RESIGNED/
cynical, plus the true-believer daughter, the spin-doctor insiders, and the MAYOR who
admits both sides have a point. Payoff is semi-plain (not mystique like Erika): the
pollution/dependence is openly discussed; the spin-doctor twist is the reveal (Kirk).
CANON: original worldbuilding (Koga Industries), touches no FRLG plot beats; the
Safari-Zone-nature contrast is all vanilla. No Rocket overlap.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| KOGA-01 | The true believer | Lass = Janine (his daughter): "Father keeps the lights on for all of KANTO. They should thank him. …He says so himself." | Lass/Janine (existing) | Fuchsia City | none | 1 | in-game | [FLAG: canon-check] |
| KOGA-02 | Nature loss (ANTI) | City Old Man: "It was greener once. Before KOGA's smokestacks." City Little Boy: "Fewer rare POKéMON, since the smoke came." | Old Man, Little Boy (existing) | Fuchsia City | none | 2 | in-game | - |
| KOGA-03 | Dependence (PRO) | Erik: "Her shift at the plant ran long. KOGA INDUSTRIES never sleeps. …Pays well." Mart CooltrainerF: "KOGA's power runs cheap. One good thing." | Erik, Mart CooltrainerF (existing) | Fuchsia City / Mart | none | 3 | in-game | - |
| KOGA-04 | Resigned old-timer | House1 Woman: the WARDEN "fought KOGA's plants for years. Lost most. We still flip his switches every morning." | House1 Woman (existing) | Fuchsia House 1 | none | 3 | in-game | - |
| KOGA-05 | The fisher (ANTI/water) | House2 fishing guru's brother: "Poorly, downstream of the plant. KOGA's runoff took the poetry clean out of the water." | House2 (existing) | Fuchsia House 2 | after Good Rod talk | 4 | in-game | - |
| KOGA-SAFARI | The preserve staff | Safari Office Workers: haze reached the zone (W1); fossils "a warning, what the smoke does given time" (W2); the NECESSARY-EVIL twist - "KOGA INDUSTRIES funds half this preserve. We bite the hand and feed from it." (W3). Entrance attendant: "the haze thins them every year." | Safari Office W1/W2/W3, Entrance attendant (existing) | Safari Zone Office/Entrance | none | 5 | in-game | - |
| KOGA-WARDEN | Nature guardian | Warden (post-gold-teeth): "Guard this zone, kid. KOGA's smoke creeps closer. It's the last green thing that man hasn't switched off." | Warden (existing; post-teeth) | Warden's House | FLAG_GOT_HM04 (natural) | 6 | in-game | - |
| KOGA-MAYOR | The balanced view | Mart Gentleman = the MAYOR: "KOGA's stacks foul our air. KOGA's power runs our homes. Both are true. Neither side is wrong. …That is what keeps me up." | Mart Gentleman (existing, reflavored as Mayor) | Fuchsia Mart | none | 7 | in-game | - |
| KOGA-REVEAL | Gym insiders = the twist | Kirk (ex-magician): "He hired me for the old trade. Misdirection. The costume, the maze. Look here, so you don't look there." Gym Guy: the invisible walls repel protesters ("they wander an hour and leave too hoarse to bother"). Shawn: "Spectacle and smoke. One you watch. One you breathe." | Kirk, Gym Guy, Shawn (gym trainers) | Fuchsia Gym | after their battle | 8 | in-game | - |
| KOGA-SELF | The mask slips | Koga (post-battle, after the archetypal terror intro): "You fight well. KOGA INDUSTRIES could use talent. The lights of KANTO won't keep themselves lit." | Koga | Fuchsia Gym | after his battle | 9 | in-game | [FLAG: canon-check] |
| KOGA-ROUTES | The whole area argues | Bordering routes each carry all three stances. Route 15: Olivia (PRO), Chester (ANTI, "smokestacks from the rise"), Ernest (RESIGNED, "you'll do it by his lamplight"). Route 18: Ramiro (PRO), Wilton (ANTI), Jacob (RESIGNED). Route 19 (water): Richard (PRO), Reece (ANTI, "something's in the water"), Tony (RESIGNED, "the tide still comes in gray"). | Route 15/18/19 trainers | Routes 15, 18, 19 | none | 10 | in-game | - |

Consistency notes:
- Koga's own battle intro/defeat stay archetypal ninja-terror; the CEO only leaks
  AFTER you beat him (KOGA-SELF), so the hard-but-fair fight still lands.
- NECESSARY EVIL, not villain: keep the pro/dependent and mayor voices real. The
  Safari-funding twist (KOGA-SAFARI W3) is the sharpest "it's complicated" beat.
- The spin-doctor reveal (KOGA-REVEAL, esp. Kirk) is the payoff; the ambient town
  opinions are the setup. This is a semi-plain arc, NOT an Erika-style mystique.
- CANON-CHECK tags: Janine-as-daughter and the CEO framing are reflavor; log any
  future contradiction here. Company = power/energy (locked w/ user).

## Sabrina - the girl who went cold (possession arc; the laugh breaks it)
Concept: Sabrina was a sunny, laughing child. Her psychic gift grew past her, so to
cage it she let her heart go cold, and the cold thing she became began to REACH: she
folds people's minds into her own, and the vanished "sleep" inside her and in her
dolls. All of SAFFRON lives half-possessed. The pivot (from the anime, adapted): she
has not felt anything in years, and losing to the player makes her LAUGH for the first
time in ages. That laugh cracks the seal, the cold lets go, every vanished person wakes
unharmed with no memory of the dark, and no one bears a grudge. She is the sunny girl
again. Full lines: drafts/sabrina.md.

GIMMICK (gym): everyone inside is possessed and forced to fight you, and each puppet
gives a DIFFERENT false direction to reach her (north / south / left / right / stand
still / center panel / turn back) - contradictory on purpose, so the hints are useless.
Each trainer's DEFEAT is a brief lucid flicker ("that was not me"; "believe nothing we
tell you"). The Gym Guide is possessed too but warns you to trust no one here, not even
him, and lets ONE true thing slip (FIGHTING folds fast to PSYCHIC). Post-victory, heads
clear and the town exhales.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| SABRINA-01 | The sunny child (memory) | Saffron Lass (before): "I knew her small. She laughed like a bell. …What became of that girl?" | Lass (existing; pre-defeat branch) | Saffron City | before FLAG_DEFEATED_SABRINA | 1 | in-game | - |
| SABRINA-02 | The vanishings / dolls (dread) | Saffron Worker (before): people vanish with no Rocket to blame; "They say SABRINA keeps people. Inside dolls." | Worker (existing; pre-defeat branch) | Saffron City | before FLAG_DEFEATED_SABRINA | 2 | in-game | - |
| SABRINA-03 | The warm doll (anchor) | Copycat's doll (before): "It's warm, though. Dolls shouldn't be warm. COPYCAT found it the week the vanishings began." After defeat: "just a doll now. Cold. Ordinary." | Doll object (existing; before/after branch) | Copycat's House 2F | branch on FLAG_DEFEATED_SABRINA | 3 | in-game | - |
| SABRINA-04 | The un-mimicable face | Copycat: "I can copy anybody. Except SABRINA. There's nothing in her face to catch." | Copycat (existing) | Copycat's House 2F | none | 4 | in-game | - |
| SABRINA-WARN | Mr. Psychic (the plain telling) | Her old teacher warns: sunny child, gift grew past her, the vanished sleep within her and her dolls, her heart went cold to cage the power, "only warmth can thaw it. Make her FEEL something. Surprise her." | Mr. Psychic (existing; pre-defeat branch) | Mr. Psychic's House | before FLAG_DEFEATED_SABRINA | 5 | in-game | - |
| SABRINA-GYM | Possessed puppets / false hints | 7 gym trainers each give a contradictory false direction; defeats are lucid flickers. Gym Guide: "Trust NO ONE in this gym. …Not even me." (one truth slips: FIGHTING folds to PSYCHIC). | Gym trainers + Gym Guide | Saffron Gym | none | 6 | in-game | - |
| SABRINA-SELF | Cold intro -> the laugh | Intro: cold possessor ("All of SAFFRON, folded quiet within me… a small, still place for you"). Defeat: she LAUGHS, blurts "Absolute cinema!!" in the delirium, then eases into sincere surprise/relief ("I can FEEL again… that warmth, it is feeling itself… surprise, true surprise… it does not hurt"); the seal breaks, the vanished wake unharmed ("You broke the spell"). Post: warm, restored, "no one recalls the dark. …my last gift to them." | Sabrina | Saffron Gym | none | 7 | in-game | [FLAG: dated] |
| SABRINA-FREED | Payoff / restoration | Mr. Psychic (after): "You made her LAUGH… the vanished woke. The sunny girl is in there still. You gave SAFFRON back its daughter." Lass/Worker after: everyone home, no memory, no grudges. Gym Guide post-victory: "the whole town just breathed out." | Mr. Psychic, Lass, Worker, Gym Guide (after) | Saffron City / Gym | after FLAG_DEFEATED_SABRINA | 8 | in-game | - |

Consistency notes:
- The Marsh Badge mechanic (over-level POKéMON turn disobedient) is tied to her arc:
  "Power without a warm hand goes cold. …No one knows that better."
- No grudges by design (user): the vanished wake unharmed with no memory; her post-
  battle wipes the trauma ("my last gift to them"). Keep all after-lines warm/relieved.
- Saffron is Rocket-occupied earlier in the plot; these fragments layer AFTER the
  liberation NPCs (they keep their Rocket line, then add the Sabrina dread), so the
  timeline reads: Rocket driven out, then the town realizes something worse is HER,
  then the player frees them by beating her. Canon-safe (touches no plot beats).
- The laugh-breaks-the-spell logic is conveyed through dialogue + before/after NPC
  branches on FLAG_DEFEATED_SABRINA (no new objects), since the anime's literal
  transformation can't be staged; beating her IS the surprise that thaws her.
- [FLAG: dated] Her defeat blurts the "Absolute cinema!!" meme at the laugh's peak
  (user-requested). It reads as her overwhelmed, feeling-drunk delirium before she
  eases into sincere awakening. Tag for a release pass to review/genericize; the
  surrounding lines stand on their own if it is ever cut.

## Blaine - the man who made the fire (Mewtwo guilt behind the bluster)
Concept: the red-hot quiz-master was once a lead researcher at the Cinnabar POKéMON
MANSION, on DR. FUJI's team. They cloned MEW and pushed too far, making MEWTWO. It
broke loose, burned the mansion (and Blaine), and vanished. His loud fire-and-bluster
persona is the fire he unleashed; the QUIZ gimmick is reframed as testing for the
WISDOM they lacked - raw power without judgment made a monster, so he asks questions
first. Behind it all: guilt and penance. The game already supports this (an in-repo
line: "a photo of BLAINE and MR. FUJI, shoulder to shoulder"; townsfolk say Blaine
predates the LAB). Reflavor only; the mansion still burned, MEWTWO is still in Cerulean
Cave. Full lines: drafts/blaine.md.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| BLAINE-01 | He predates the Lab (coy) | Cinnabar Woman (append): "He was a scientist then, you know. A brilliant one. …He does not speak of then." | Woman (existing) | Cinnabar Island | none | 1 | in-game | [FLAG: canon-check] |
| BLAINE-02 | The burned mansion (coy) | Cinnabar Old Man (append): "BLAINE took the GYM after it burned. Some say he lit it. …Some say he just could not put it out." | Old Man (existing) | Cinnabar Island | none | 2 | in-game | [FLAG: canon-check] |
| BLAINE-QUIZ | The quiz = testing wisdom | Blaine's intro honors the quiz as the mind-test: "You unraveled every riddle to stand before me. …Few reach BLAINE with their wits still about them. You have proven your mind. Now prove your flame." (grand-virtuoso climax; the wisdom-over-power theme lives fuller in his defeat/badge lines) | Blaine | Cinnabar Gym | none | 3 | in-game | - |
| BLAINE-DIARY | The Mansion journals (anchor) | Alongside the canon MEWTWO diary: 3F (early wonder) "BLAINE says it looked at him, and he wept. So did I. -F." B1F (the confession) "We could make it. No one asked if we should. Forgive me. -B." | Mansion journals (existing) | Pokemon Mansion 3F / B1F | none | 4 | in-game | [FLAG: canon-check] |
| BLAINE-PAYOFF | Old colleague tells it plainly | Lab Entrance scientist: "BLAINE? He was one of us. FUJI's sharpest. The old MANSION team. Then the thing we grew slipped its chains and burned it all down. He never touched science again. …Only questions now." Fuji photo: "…beside him, younger, unburned: BLAINE. Two friends who made something they could not unmake." | Lab scientist + Fuji photo (existing) | Cinnabar Pokemon Lab | none | 5 | in-game | [FLAG: canon-check] |
| BLAINE-SELF | The guilt leaks | Intro leak, one clean image ("I have seen it warm a home… and swallow one whole"). Defeat: "burned down to nothing… I have watched that happen before. To everything I built." Badge: "Great power, in a young hand. …Mind what you do with it. I did not, once." TM: "never forget it can burn more than you aim it at." | Blaine | Cinnabar Gym | none | 6 | in-game | - |
| BLAINE-RUMORS | Kanto-wide rumor decay | The mansion fire + the fleeing creature become a game of telephone across Kanto, decaying by distance; none name Blaine/Fuji/Mewtwo. EYE-WITNESSES (vivid, first-hand) on the water by Cinnabar: Swimmer Missy (Rt20), Swimmer Spencer (Rt21 N), Fisher Jack (Rt21 S) - "something rose from the smoke, went north over the sea, never came down." GARBLED (far -> more wrong): Pallet Fat Man (researchers built something they couldn't hold; Oak goes quiet), Vermilion Old Man 1 (a stretch of sea sailors won't cross), Viridian Boy ("a POKéMON did it, swam off"), Cerulean Cave Guard (whispered: the strongest thing in the cave "isn't native, came up from the south over the sea… leave it be"), Pewter Museum Guide ("the island that burned itself"; a tall tale), Lavender Boy (a demon/curse born of fire that haunts a cave). | 9 vanilla NPCs (append) | Rt 20/21, Pallet, Vermilion, Viridian, Cerulean, Pewter, Lavender | none | 7 | in-game | [FLAG: canon-check] |

Consistency notes:
- The quiz reframe (BLAINE-QUIZ) changes the MEANING of the gimmick, not the mechanic;
  the trivia doors are untouched. "Wisdom before power" is his penance.
- Canon-blend: Blaine-on-Fuji's-team + Blaine helping make Mewtwo is Adventures-manga
  flavor, supported by the in-repo Blaine+Fuji photo text. It contradicts no game plot
  (mansion still burned, Mewtwo still in Cerulean Cave). Tag canon-check throughout.
- The "-B." / "-F." diary initials are the coy signatures (Blaine / Fuji); the player
  connects them to the Lab payoff and the photo. Never spelled out in the journals.
- His battle stays red-hot and hard (BURN HEAL bluster intact); the guilt only leaks in
  the quieter beats (defeat, badge, TM), so the fight still lands.

## Giovanni - the man who was here all along (self-made; hiding in plain sight)
Concept: UNIQUE among the leaders. Not fought once, but the recurring antagonist
you battle THREE times (Rocket Hideout -> Silph Co -> Viridian Gym) and hear about
all game through Team Rocket. Surface stays canon: the ROCKET boss, the Master Ball
deal, the disbanding, the EARTHQUAKE TM. Hidden layer: the most-wanted man in Kanto
has spent the whole game HIDING IN PLAIN SIGHT as the absent GYM LEADER of the
sleepy first city you walked through. The region carries two absences, an unseen
ROCKET BOSS and a never-there 8th LEADER, and the fragments slowly rhyme them until
the PLAYER (never the NPCs) connects that they are one man. Canon does the payoff
for you: the gym is locked all game and only opens at the end. Engine (NO son
thread, decided w/ user): the SELF-MADE MAN FROM THE DIRT. He came up from nothing;
strength IS worth; being weak once was terror. GROUND-type is thematically exact.
When he finally loses, the empire was never the point (power was), so he gives it up
without a fight and walks off to chase strength for its own sake. Full lines:
drafts/giovanni.md.

DELIVERY: dominant region-wide "who is the LEADER? / who is the BOSS?" ambient
mystery (coy, appends to existing Rocket-beat + Viridian NPCs), the three battles
reflavored to escalate the self-made + double-life weight (straight/menacing;
humanity only in post-battle), and a semi-plain payoff (like Koga) that canon
already lands inside the gym. SILLY-THROUGH-CONTRAST: Viridian's earnest civic
devotion to a LEADER nobody has ever met (locked door "away… on business";
townsfolk sure he's "a fine fellow"), while the danger stays straight in the
fights. CANON-SAFE: touches no FRLG plot beats; reflavor + appends only, no new
objects/art.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| GIOVANNI-01 | Boss (unseen, self-made seed) | Rocket grunt append: "Our BOSS came up from nothing. Nothing makes a man hungry." | Grunt2 (existing) | Mt Moon B2F | none (first brush) | 1 | in-game | - |
| GIOVANNI-02 | Viridian gym (civic blind spot) | Old Man (append): "…Away for years, and we're proud of him all the same. …Whoever he is." | Old Man (existing) | Viridian City | none (pre-gym) | 2 | in-game | - |
| GIOVANNI-02b | Viridian gym (civic blind spot) | Woman (append): "Our GYM LEADER? Never met the man. …A fine fellow, I'm sure." | Woman (existing) | Viridian City | none | 2 | in-game | - |
| GIOVANNI-02c | Viridian gym (locked door, irony) | Locked-door line/sign: "…The LEADER is away… on business." (his business is crime) | Gym door/sign | Viridian City | none | 2 | in-game | - |
| GIOVANNI-03 | Boss (self-made) | Hideout grunt (append): "He built all this from nothing. Don't expect him to go easy." | Grunt4 (existing) | Rocket Hideout B1F | reached hideout | 3 | in-game | - |
| GIOVANNI-04 | Boss (double life, coy) | Tower grunt (append): "You think the BOSS dirties his own hands? He's got a clean face somewhere none of us have seen." | Grunt2 (existing) | Pokemon Tower 7F | Silph Scope arc | 4 | in-game | [FLAG: canon-check] |
| GIOVANNI-B1 | Giovanni (1st fight) | Hideout B4F intro reflavored self-made ("I built TEAM ROCKET from nothing… the weak get ground under. So I made myself strong."); "step aside this time." | Giovanni | Rocket Hideout B4F | story | 5 | in-game | - |
| GIOVANNI-05 | Boss (businessman veneer) | Silph NPC (append): "Talks like he was born to the boardroom. …He wasn't, I hear." | Silph employee (existing) | Silph Co 5F | Silph arc | 6 | in-game | - |
| GIOVANNI-05b | Boss (owns everything) | Silph NPC (append): "…carries himself like he owns the place. Like he owns everything." | Silph employee (existing) | Silph Co 8F | Silph arc | 6 | in-game | - |
| GIOVANNI-05c | Boss grunt (self-made) | Silph door grunt (append): "He had to be tough. Where he's from, soft things don't last." | Grunt1 (existing) | Silph Co 11F | Silph arc | 6 | in-game | - |
| GIOVANNI-B2 | Giovanni (2nd fight) | Silph 11F intro reflavored double-life ("A man can wear more than one face. You would be amazed which mine open."); post: "I have climbed from far lower." | Giovanni | Silph Co 11F | story | 7 | in-game | [FLAG: canon-check] |
| GIOVANNI-GYM | Viridian Gym (payoff chorus) | All 8 gym trainers reflavored off vanilla karate/whip filler onto GROUND-grit + reverence for the self-made mystery LEADER (Kiyo/Takashi/Warren "claw up from the dirt, same as the LEADER"; Jason "landslide"; Cole "bury yours"; Samuel "where the LEADER went, none of us dared ask… but now he is back"). Gym Guy's canon "like GROUND-type" tip and the statue "LEADER: ?" -> "GIOVANNI" flip kept as functional payoff. | Gym trainers + Gym Guy + statue | Viridian Gym | gym open | 8 | in-game | - |
| GIOVANNI-RETURNED | Viridian (civic joy, irony) | On gym unlock: "VIRIDIAN GYM's LEADER returned! …After all these years! I knew he'd come back to us." | Old Man (existing) | Viridian City | gym unlocks (badges 2-7) | 8 | in-game | - |
| GIOVANNI-B3 | Giovanni (THE REVEAL / final) | Gym intro: "…I have stood in VIRIDIAN all along. The LEADER no one ever met. Hidden in plain sight, while I built ROCKET up from nothing." Post: "I chased power my whole life. I thought an empire was the road to it. I was wrong. Strength is a road you walk alone. I shall walk it again, from nothing, as I began." Defeat/badge/TM all reflavored: "So the dirt breeds strength after all… take the EARTHBADGE"; "Power answers to the one who earns it"; TM26 "The ground itself, turned into a weapon… I forged it when I first held this GYM. …Before the other life." | Giovanni | Viridian Gym | reach gym (all badges) | 9 | in-game | - |
| GIOVANNI-PAYOFF | Reveal lands (semi-plain) | Gym Guy post-victory (canon): "Blow me away! GIOVANNI was the GYM LEADER of VIRIDIAN?" Statue flips to "LEADER: GIOVANNI." | Gym Guy + statue | Viridian Gym | FLAG_DEFEATED_LEADER_GIOVANNI | 10 | in-game | - |
| GIOVANNI-FAME | Fame Checker (progressive who's-who) | ALL beats reflavored to the self-made / hidden-leader arc: beat 0 "I built TEAM ROCKET from nothing"; 1 "a man from nothing trusts nothing but strength"; 2 "hard as stone… people are tools too"; 3 "the LEADER no one ever met, while I built ROCKET from nothing"; 4 reveal "GIOVANNI, the ROCKET BOSS, was our GYM LEADER all along?"; 5 (was red-hair kid) -> self-made loner "came up from the gutter alone… no one has ever met" (removes the son). The letter quote -> "I go back to the dirt I came from, to make myself stronger. Alone." | Fame Checker | (menu) | famechecker unlocks | - | in-game | - |
| GIOVANNI-POST | Post-game (walk-away pays off) | Warehouse grunt (append): "Even if it did… the BOSS wouldn't quit. He'd start over. From nothing, like he always has." Remnant Admins still search for him. The old red-hair-kid gag NPC reflavored to the self-made loner ("answered to nobody. Had nobody. Came up from the dirt alone.") so no son thread remains anywhere. | Rocket remnant (existing) | Five Island Rocket Warehouse | post-E4 | 11 | in-game | - |

Consistency notes:
- The engine is SELF-MADE STRENGTH, NO son thread (decided w/ user). The two
  vanilla "GIOVANNI's kid has red hair" references (Fame Checker beat 5 + the Five
  Island warehouse scientist) were REFLAVORED AWAY to a self-made-loner note
  ("came up alone, had nobody"), so no son thread survives anywhere. If a future
  line reintroduces the kid, it's wrong for this arc.
- NO GIOVANNI LINE IS LEFT VANILLA (decided w/ user): all three intros, defeats,
  and post-battles, the badge + TM text, every Fame Checker beat + the letter
  quote, and all 8 gym trainers are reflavored. Only pure mechanical strings stay
  generic (the "received TM26" item receipt; Samuel's "beat the LEADER to reach the
  LEAGUE" gate hint; the statue/Gym-Guy functional payoff).
- The two absences (unseen BOSS / never-there LEADER) must stay UNCONNECTED in NPC
  mouths. No NPC says Giovanni is the Viridian leader before the gym reveal; the
  player connects it. The rhyme is carried by ambient coy lines ("clean face
  somewhere," "owns everything," "away… on business," "who the LEADER is?").
- His three battle intros stay archetypal and DANGEROUS (hard-but-fair). The
  self-made/double-life weight leaks in intros lightly and in POST-battle fully,
  so the fights still land. Escalation: from-nothing (B1) -> two-faces (B2) ->
  hidden-in-plain-sight + the walk-away (B3).
- Payoff is SEMI-PLAIN (Koga-model), not Erika-mystique: canon itself reveals "he
  was the leader" at the gym. We only add the self-made grace note and align the
  Fame Checker. Do not over-explain in the ambient chorus.
- CROSS-LINK (Blaine arc): Viridian City's Boy already carries the Blaine/Mewtwo
  "island that burned, a POKéMON flew north" rumor (BLAINE-RUMORS). Keep Giovanni's
  Viridian fragments on OTHER NPCs (Old Man, Woman, gym door) so the two arcs don't
  crowd one speaker.
- GROUND-type theming is the through-line ("from the dirt," "ground under," "from
  the ground up," EARTHQUAKE). The Gym Guy's canon type-tip ("like GROUND-type") is
  preserved as functional info.

## Lorelei (Elite Four, Ice) - the Ice type's fiercest evangelist
Concept: everyone "knows" ICE is a weak type. Lorelei has given her life to
disproving that, because as a child she was drowning in the freezing sea off
FOUR ISLAND and a wild LAPRAS rose out of the cold and carried her home. She owes
the type her life. Her Elite Four ace is a LAPRAS (Lv 54), so the rescue quietly
rhymes with her team and with the bald, over-hugged LAPRAS doll in her house.

Engine of the comedy = the seriousness itself (silly-through-contrast): she is
DEADLY earnest about Ice's honor and nurses petty grudges against anything that
makes the type look weak, above all a soft no-account she only calls "VANILLA."
She meets challengers with an "ice bucket" trial. The gags are seasoning scoped
to her; the crusade and the rescue play STRAIGHT so the hard-but-fair fight lands.

Delivery = DISTRIBUTED (Elite Four cluster at Indigo, no home town each). Lorelei
is the easy case: FOUR ISLAND (canon FRLG Sevii) is her home, full of NPCs, plus
her doll house and the Icefall Cave. Reveal is COY throughout: NPCs mention the
cold sea, the thing that rose from it, the LAPRAS doll, the grudge list. NOBODY
states "a LAPRAS saved her." The player connects it. Uses existing NPCs/objects
only, no new art, no moved story beats.

> Reference check: VANILLA and the ICE BUCKET CHALLENGE are real-world nods. Keep
> them in our own voice, deniable, and strip-safe (see flags). Battle voice LOCKED
> to Option A (full voice); line bank in drafts/lorelei.md.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| LORELEI-01 | Lorelei (crusade) | Reception NPC: "LORELEI takes ICE personally. Call the type weak near her once. …I did." | reception NPC (existing/new) | Indigo Plateau reception | reached League | 1 | drafted | - |
| LORELEI-02 | Lorelei (history, coy) | Islander: "Island girl. The cold sea near took her as a child. Something rose out of it and carried her back. …She never forgot what." | Four Island NPC (existing) | Four Island | reached Four Island | 2 | drafted | - |
| LORELEI-03 | Lorelei (crusade origin) | Islander: "Ever since, she'll not hear one bad word about ICE types. Owes them everything, she says. Won't say more." | Four Island NPC (existing) | Four Island | reached Four Island | 3 | drafted | - |
| LORELEI-04 | Lorelei (the doll shrine) | Doll object (reflavor): "Shelves of stuffed ICE POKéMON. One LAPRAS doll sits above them all, old and hugged near bald." | doll object (existing) | Four Island, Lorelei's House | reached Four Island | 4 | drafted | - |
| LORELEI-05 | Lorelei (home vs. duty) | Her vanilla "the island where I was born…" lines, logged as-is (the fierce-defender core). | Lorelei (vanilla) | Four Island, Lorelei's House | vanilla | 5 | in-game | - |
| LORELEI-06 | Lorelei (where it happened) | In the cave: "Cold, isn't it? This is where it happened. A child, the ice, the water. …She came back." | Icefall Cave NPC (existing/new) | Four Island, Icefall Cave | reached Four Island | 6 | drafted | - |
| LORELEI-07 | Lorelei (fierce defender) | Islander (after Rocket beat): "She left the LEAGUE the moment we were threatened. Came home cold and furious. We were glad of it." | Four Island NPC (existing) | Four Island | FLAG_DEFEATED_ROCKETS_IN_WAREHOUSE | 7 | drafted | - |
| LORELEI-08 | Lorelei (the grudge, coy) | Islander: "She keeps a list. Every ICE type folks call weak, she'll prove wrong. Top of it? Some soft no-account she just calls VANILLA." | Four Island NPC (existing) | Four Island | reached Four Island | 8 | drafted | [FLAG: dated] [FLAG: release-swap] |
| LORELEI-09 | Lorelei (post-defeat) | Reception callback: "Beat LORELEI? She'll not sleep a month. She'll say ICE can always get stronger. …She's not wrong." | reception NPC (existing/new) | Indigo Plateau reception | FLAG_DEFEATED_LORELEI | 9 | drafted | - |
| LORELEI-10 | Lorelei (battle voice) | Intro (crusade + ICE BUCKET CHALLENGE + VANILLA jab); defeat kept vanilla; post-battle "you beat ME, not ICE." Option A. | Lorelei | Indigo Plateau, Lorelei's Room | at the battle | 10 | drafted | [FLAG: dated] [FLAG: release-swap] |

Consistency notes:
- The LAPRAS rescue is NEVER stated by Lorelei or spelled out by any NPC. Fragments
  say "something rose out of the cold" / show the enshrined LAPRAS doll; the player
  ties it to her Lv 54 LAPRAS ace. Keep it coy in every source.
- Her battle lines carry the crusade AND the gags, but the LOSS stays straight
  (defeat line unchanged; post-battle is fierce, not comic) so the fight lands.
- VANILLA and the ICE BUCKET CHALLENGE are the only flagged lines. Both are
  strip-safe: VANILLA reads in-world as bland/weak ice; the bucket line generalizes
  to plain ice water. A release pass can genericize them without touching the arc.
- CONTRAST (quiet rhyme with SABRINA): Lorelei's dolls are a WARM honor-guard for a
  disrespected type; Sabrina's dolls are COLD puppets. Same prop, opposite meaning.
  Never drawn attention to in-game; just kept consistent.
- Four Island / Icefall Cave / the Rocket warehouse are all canon FRLG (Sevii ships
  with FireRed), so the home arc is Kanto-authentic, not an invented region.

## Bruno (Elite Four, Fighting) - the calm giant whose stillness is his strength
Concept: the gentle giant in a permanent state of calm. Stand near Bruno and your
nerves settle. That stillness IS his strength: no ego, no anger, no noise, so he
pours everything into pure power. He never explains himself; his demeanor is the
whole message. Humble and patient, he lives up in the wild among free POKéMON that
do not fear him, and quietly tends the land around him. The one thing that draws
him down from the quiet is the pure joy of meeting someone truly strong (canon: he
joined the ELITE FOUR "out of his burning ambition to battle the best").

He is the roster's SINCERE ANCHOR: the deliberate straight foil to Lorelei's
silly-through-contrast crusade. ZERO gags. His method is SHOW, NEVER TELL, so every
fragment reports what an NPC SAW (the ease near him, the calm wild POKéMON, the
cleaned trail, the power that followed the peace) and NEVER states "calm is his
strength." The player links calm -> power. His power is only ever implied ALONGSIDE
his stillness. His one light beat (the RAGE CANDYBAR) shows non-attachment, not
gluttony.

Delivery = DISTRIBUTED across the Sevii "training circuit" his canon footprint
already occupies (Ember Spa on One Island, Two Island, Sevault Canyon on Seven
Island), plus the wild areas he lives in and the Indigo reception. Vanilla NPCs at
the spa, Two Island, and Sevault Canyon already reference BRUNO, so those get
reflavored directly. Uses existing NPCs only, no new art, no moved beats.

> Battle voice LOCKED (revised): his vanilla boast ("grind you down… Hoo hah!") and
> ego-shock defeat ("Why? How could I lose?") are off-brand for the zen giant and
> are replaced with calm-welcome / gracious-loss / respectful-send-off. Line bank
> in drafts/bruno.md.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| BRUNO-01 | Bruno (the care) | Black Belt: "Senior tends his POKéMON's hurts before his own, every time. …I try to be like that." | Black Belt (existing, reflavor) | One Island, Ember Spa | reached One Island | 1 | drafted | - |
| BRUNO-02 | Bruno (the aura) | Black Belt: "Sat with him in the spring once. He said maybe three words the whole hour. Best hour of my life." | Black Belt (existing, reflavor) | One Island, Ember Spa | reached One Island | 2 | drafted | - |
| BRUNO-03 | Bruno (lives in the wild) | Hiker: "Up the mountain the wild POKéMON don't run from him. They sit with him. I've seen it." | Hiker (existing/new) | One Island, Kindle Road / Mt. Ember | reached One Island | 3 | drafted | - |
| BRUNO-04 | Bruno (steward) | Wanderer: "Every trail that man walks comes back cleaner. Never says a word about it. Just does it." | wild-area NPC (existing/new) | One Island, Kindle Road | reached One Island | 4 | drafted | - |
| BRUNO-05 | Bruno (equanimity) | Islander (candybar, reframed): "One of the ELITE FOUR came all this way for a RAGE CANDYBAR. Sold out. He just smiled, thanked us, and left. Not a flicker." | Two Island NPC (existing, reflavor) | Two Island | reached Two Island | 5 | drafted | - |
| BRUNO-06 | Bruno (honors every path) | Sevault NPC: "Folk think he trains alone by creed. He'll tell you every path has worth. He walked one once with a fellow called BRAWLY." | Sevault NPC (existing, reflavor) | Seven Island, Sevault Canyon | reached Seven Island | 6 | drafted | [FLAG: canon-check] |
| BRUNO-07 | Bruno (why the League) | Sevault NPC: "Why leave his quiet mountain for the LEAGUE? One thing moves him. The chance to meet someone truly strong." | Sevault NPC (existing, reflavor) | Seven Island, Sevault Canyon | reached Seven Island | 7 | drafted | - |
| BRUNO-08 | Bruno (the room) | Reception NPC: "You will feel at peace in the second room. …That peace is the last thing a lot of challengers remember." | reception NPC (existing/new) | Indigo Plateau reception | reached League | 8 | drafted | - |
| BRUNO-09 | Bruno (battle voice) | Intro (calm welcome, "no anger, only strength meeting strength"); gracious defeat ("the strength I came looking for. Thank you"); send-off ("Meet it as you met me"). | Bruno | Indigo Plateau, Bruno's Room | at the battle | 9 | drafted | - |
| BRUNO-10 | Bruno (post-defeat) | Reception callback: "You beat BRUNO? And he thanked you for it, didn't he. …That's just who he is." | reception NPC (existing/new) | Indigo Plateau reception | FLAG_DEFEATED_BRUNO | 10 | drafted | - |

Consistency notes:
- SHOW, NEVER TELL is the hard rule for every Bruno fragment. Observations of
  demeanor and effect only; NEVER a stated philosophy. His power is always implied
  next to his calm so the player draws the line himself.
- His battle lines carry the calm AND the graciousness; the loss is met with
  thanks, not shock, because meeting the truly strong is his whole reason for being
  at the LEAGUE (keep consistent with BRUNO-07 and BRUNO-10).
- The RAGE CANDYBAR (05) stays WARM, not a gag: it demonstrates non-attachment. Do
  not play Bruno for comedy; he is the roster's sincere anchor against Lorelei's
  silliness (tonal control).
- BRAWLY (06) is a Hoenn character (cross-region), tag [FLAG: canon-check]. Keep it
  a one-line grace note (he honors other paths), not a plot thread.
- Ember Spa, Two Island, and Sevault Canyon already reference BRUNO in vanilla, so
  reflavor those existing NPCs rather than adding new ones where possible.

## Agatha (Elite Four, Ghost) - study vs. battle (the old lady on your side)
Concept (SPINE = the schism with OAK): decades ago Agatha and a young OAK were the
two fiercest trainers in Kanto. Then OAK laid down his team to catalogue POKéMON in
a book. To Agatha that was surrender: you do not prove a POKéMON's worth by writing
it down, you prove it in battle. Her vanilla intro IS this thesis, verbatim: "He's
wrong. POKéMON are for battling!" She stayed in the arena OAK left and kept winning
until she became the oldest ELITE FOUR member who ever lived, as if daring age to
make her quit the way he did.

THE WARMTH IS MOTIVATED. Agatha has no patience for POKéDEX-fillers and
catch-everything busywork. But a trainer who fights to prove herself, who chases
strength instead of pages, is exactly what OAK stopped being. When the player turns
out to be that trainer, Agatha lights up, calls you "child," tells you to live long,
and means it: a kindred spirit, maybe the successor OAK never made. She is the
sweet-old-lady-with-bite who is quietly, wholly on the battler's side.

COY UNDERLAYER (kept, demoted from the spine): whether she and OAK were ever more
than rivals. NEVER answered, a photo of two young trainers, OAK going quiet at her
name, "we were young." The grief is real but hidden now; the study-vs-battle rift is
the surface the player actually reads. She is the MAINLAND-rooted E4 member
(Lavender Ghost lore + Pallet/OAK), a geographic contrast to Lorelei (Four Island)
and Bruno (the Sevii circuit).

> Battle voice LOCKED: KEEP VANILLA. Her canon intro states the axis thesis verbatim
> ("He's wrong. POKéMON are for battling!"); her defeat ("You're something special,
> child!") and post-battle ("I see what the old duff sees in you now") are her warmth
> recognizing a fellow battler. All unchanged; new work is the distributed history.
> Line bank in drafts/agatha.md.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| AGATHA-01 | Agatha (the terror) | Indigo PC (reflavor): her GHOST types are terror, and "that old lady's got a short fuse. …Bless her." | trainer NPC (existing, reflavor) | Indigo Plateau PC | reached League | 1 | drafted | - |
| AGATHA-02 | Agatha (the philosophy) | Six Island Mart (reflavor): oldest-ever E4 member. "Fill a book with POKéMON? She'd sooner fill a graveyard. Battle, prove it, live long. …Then she'll end you." | Mart NPC (existing, reflavor) | Six Island Mart | reached Six Island | 2 | drafted | - |
| AGATHA-03 | Agatha (history, coy) | Lavender old-timer: young Agatha trained among the Tower's spirits, "back when someone she knew chose books over battle." | Lavender NPC (existing/new) | Lavender Town | after Pokémon Tower | 3 | drafted | - |
| AGATHA-04 | Agatha (the grief, coy) | Oak's aide: "The PROFESSOR goes quiet when her name comes up. …I've learned not to ask." | Oak's Lab aide (existing) | Pallet, Oak's Lab | after ~5th badge | 4 | drafted | - |
| AGATHA-05 | Agatha (the photo, coy) | Old photo at the Lab: two young trainers squaring off, grinning like they meant it. No names written. | photo object (existing/new) | Pallet, Oak's Lab | after ~5th badge | 5 | drafted | - |
| AGATHA-06 | Agatha (why she stays) | Islander: "She could have retired a legend. She stays in the ring. Like she's proving something to somebody." | Six Island NPC (existing/new) | Six Island | reached Six Island | 6 | drafted | - |
| AGATHA-07 | Agatha (who she respects) | Reception NPC: "She's got no time for POKéDEX-fillers. But a trainer who battles to prove herself? …That one she'll respect to the grave." | reception NPC (existing/new) | Indigo Plateau reception | reached League | 7 | drafted | - |
| AGATHA-08 | Agatha + Oak (capstone) | OAK, coy: "AGATHA? …We were young. She never forgave me for putting my POKéBALLS down. …Perhaps she was right." | Prof. Oak | Pallet, Oak's Lab | post-E4 | 8 | drafted | [FLAG: canon-check] |
| AGATHA-09 | Agatha (battle voice) | KEPT VANILLA: roasts OAK; defeat "You're something special, child!"; post "I see what the old duff sees in you now." | Agatha | Indigo Plateau, Agatha's Room | at the battle | 9 | in-game | - |
| AGATHA-10 | Agatha (post-defeat) | Reception callback: "She called you 'something special,' did she? From that one, that's a love letter." | reception NPC (existing/new) | Indigo Plateau reception | FLAG_DEFEATED_AGATHA | 10 | drafted | - |

Consistency notes:
- SPINE is study vs. battle: OAK catalogues, Agatha fights, and she believes worth
  is proven in the arena, not on a page. This is the surface the player reads. Her
  warmth toward the player is MOTIVATED: she recognizes a fellow battler (02, 06, 07,
  10). Cross-links to OAK-07 / OAK-10 (the man who quit still admires the woman who
  did not).
- COY UNDERLAYER (romance) is kept but demoted: NEVER confirm it. The photo (05,
  squaring off but grinning like they meant it), OAK's silence (04), and "we were
  young" (08) imply without stating. It is the hidden layer, not the headline.
- Battle voice stays VANILLA (09): her intro is the axis thesis verbatim; her "child"
  and the warmth on the loss are recognition of a real battler. Do not rewrite.
- The OAK capstone (08) is character flavor on an existing NPC, gated post-E4, NOT a
  new plot beat. Tag [FLAG: canon-check] and keep it coy.
- Keep her barbs sharp and the grief buried; her readable emotion is WARMTH toward
  the fighter in front of her, not heartbreak.
- Reflavor the existing Agatha-referencing NPCs (Indigo PC, Six Island Mart) rather
  than adding new ones where possible.

## Professor Oak (central character) - the data-hungry completionist gremlin
Concept: Kanto reveres Professor Oak; Oak reveres DATA. His dream is to study every
POKéMON that exists, and he has cheerfully decided the player is the instrument of
that dream, a one-person catching machine who will fill his POKéDEX to the last
entry. Warm, brilliant, tangent-prone, and completely unable to imagine why anyone
would catch LESS than everything. Trainers who deliberately limit themselves (one
POKéMON per route, retire the fallen) leave him baffled and comically IN DENIAL:
surely the player won't do that to him. Surely you'll catch them all. …You will,
won't you? Silly-through-contrast: the dignified mentor is a data gremlin; his aides
are a long-suffering chorus for a man who will not stop phoning them.

Tonal scope LOCKED: FULL gremlin from his first in-world line (Route 1), escalating
to mania at the LAB dex charge. The new-game professor NARRATION is NOT this, it is
parked separately (drafts/intro-and-rival.md) as an author-welcome with Oak SILENT;
do not touch it. The nuzlocke gag is IN-WORLD and UN-NAMED (describe the practice,
never the word), kept GENERIC (an anonymous "some trainers"), NEVER the rivals
(Buhrito/Twitch are the user's to characterize).

The Agatha axis: Oak = catalogue everything (study/breadth); Agatha = prove your
power (battle/depth). Oak is a little wounded that an old rival thinks he "went soft"
when he put his POKéBALLS down for a notebook. His coy hook (OAK-07) mirrors
AGATHA-03/04/08 ("chose books over battle" / "chose battle over books"), never
naming her. FOLLOW-UP: realign Agatha's ledger spine to foreground this axis
(Agatha as the old lady who GETS the player's drive), keeping the coy grief beneath.

> Fourth roster voice: Lorelei goofy-obsessive, Bruno serene, Agatha sardonic, Oak
> the completionist gremlin. Line bank in drafts/oak.md. All lines map onto EXISTING
> beats, no new or moved plot.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| OAK-01 | Oak (gremlin intro) | Route 1 rescue: "Wild POKéMON in that grass! Fascinating ones! Uncatalogued ones! And you'd walk in with nothing to catch them in? …Come, come. We have an encyclopedia to fill." | Prof. Oak | Route 1 / Pallet | story (Route 1 rescue) | 1 | drafted | - |
| OAK-02 | Oak (dex mania) | Lab dex charge: "Every species. Every last one. Leave NO gaps, NO blank pages! …You'll catch them all. I can feel it. Off you go!" | Prof. Oak | Pallet, Oak's Lab | story (starter/dex) | 2 | drafted | - |
| OAK-03 | Oak (the DEX) | Parcel/POKéDEX handoff: "A POKéDEX! High-tech, hand-picked, and horribly, wonderfully EMPTY. Fill it. For science. For me. …Mostly for me." | Prof. Oak | Pallet, Oak's Lab | story (parcel) | 3 | drafted | - |
| OAK-04 | Oak (nuzlocke denial, coy) | Aide: "He heard a rumor that spooked him. Some trainers keep but ONE POKéMON per route. Retire it if it falls. He went pale. 'Not {PLAYER},' he said. …You will catch them all. Won't you?" | Oak's Aide (existing, reflavor) | Route 2 / 10 / 11 aide buildings | dex milestone / reached route | 4 | drafted | [FLAG: dated] |
| OAK-05 | Oak (the horror, coy) | Aide: "Some trainer breezed through. Caught one POKéMON. ONE. Then left. The PROFESSOR hasn't slept. …Please. Catch two. For me." | Oak's Aide (existing, reflavor) | Route aide building | dex milestone / reached route | 5 | drafted | [FLAG: dated] |
| OAK-06 | Oak (the ratings) | Aide/lab: "He rates every DEX personally. Out loud. At length. To anyone. Bring him a full one and I think the poor man might weep." | Oak's Aide (existing/new) | route aide / Oak's Lab | dex progress | 6 | drafted | - |
| OAK-07 | Oak + Agatha (hook, coy) | Lab: "An old friend once told me a scholar is a trainer who gave up. …She wasn't entirely wrong. But SOMEONE must write it all down! …Where was I. Yes! Your DEX!" | Prof. Oak | Pallet, Oak's Lab | after dex started | 7 | drafted | [FLAG: canon-check] |
| OAK-08 | Oak (post-game) | After Hall of Fame: "CHAMPION, and my DEX still has gaps. …You see my problem. No rest for either of us! Now, about those blank pages-" | Prof. Oak | Pallet, Oak's Lab | FLAG_SYS_GAME_CLEAR | 8 | drafted | - |
| OAK-09 | Oak (reverence vs. gremlin) | Pallet townsperson: "PROF. OAK? A great man. A genius. …Also he once called my house at 3 AM to ask if my PIDGEY was 'new.'" | Pallet NPC (existing/new) | Pallet Town | none | 9 | drafted | - |
| OAK-10 | Oak (bridge to Agatha) | Aide: "Between us? He knows not everyone catches for science. Some battle to prove themselves. He respects it, though he'll never say. …An old rival of his would adore you." | Oak's Aide (existing/new) | route aide building | mid-game | 10 | drafted | [FLAG: canon-check] |

Consistency notes:
- Oak's own lines go FULL comedy from Route 1; the new-game narration stays the
  parked silent-Oak author-welcome (untouched). Keep the two separate.
- The nuzlocke fad stays IN-WORLD, UN-NAMED, and GENERIC. Never the literal word,
  never the rivals. Buhrito/Twitch are out of Oak's lore entirely (user writes them).
- CROSS-LINK to Agatha: OAK-07 ("a scholar is a trainer who gave up… she wasn't
  entirely wrong") mirrors AGATHA-03 ("chose books over battle") and AGATHA-08
  (Oak: "putting my POKéBALLS down"). Keep both coy; never name each other plainly on
  the mainland path except Agatha's own canon intro and the gated OAK capstone.
- OAK-10 plants the Agatha-axis bridge (he respects battling to prove oneself). This
  is the seam Agatha's realigned arc will pay off. Tag canon-check.
- Comedy lives in Oak and the chorus around him; do NOT let it deflate the DEX charge
  so hard the mission reads as a joke. He believes in the great work; that sincerity
  under the mania is what makes the gremlin funny rather than tiresome.

## Lance (Elite Four leader, Dragon, the FINALE) - "everything is a dragon"
Concept: Lance sorts the whole world into two kinds of POKéMON, dragons and dragons
that don't know it yet. GYARADOS = sea dragon. AERODACTYL = ancient dragon. MAGIKARP
= a dragon in waiting (and he is right, it becomes GYARADOS). He does not lecture you
into it, he shows you the dragon hidden in your own team until you cannot unsee it,
and it is oddly beautiful. Grounded in his real FRLG team: GYARADOS (Water/Flying)
and AERODACTYL (Rock/Flying) are NOT Dragon-type, and he fields them as aces anyway.
He is not wrong, to him.

He is the FINAL wall because his belief is total: his dragons fight like they are
truly indestructible because HE believes it, so THEY believe it. Keep that awe so
the last fight lands even as he is a goofball. UPLIFTING, NOT KICKING DOWN (hard
rule): his dragon-love is infectious and wholesome, every NPC comes away converted
and charmed. Comedy is his boundless conviction, never his expense. No degenerate /
pathetic angle.

Fifth roster voice and the finale: Lorelei goofy-obsessive, Bruno serene, Agatha
sardonic-warm, Oak completionist gremlin, Lance the uplifting dragon evangelist. He
is famous region-wide (E4 leader + a canon Saffron fan club), so his gospel seeds
through NPCs everywhere who have a Lance story or have been happily converted.

> Battle voice LOCKED. INTRO is the entire box: "I like dragons." DEFEAT (D-C):
> "…You DO like dragons, though? …Say you like dragons." POST-BATTLE is the "draggin
> deez nuts" meme, then a nudge to the CHAMPION. The meme post-battle lands AFTER the
> fight so it never deflates the climb. Line bank in drafts/lance.md.

| ID | Subject | Reveal | Source NPC | Map | Gate | Order | Status | Flags |
|---|---|---|---|---|---|---|---|---|
| LANCE-01 | Lance (the gospel) | Reception: "The fourth room is LANCE, the dragon master. He'll tell you your POKéMON is a dragon. All of them. …Just nod. He's usually right, somehow." | reception NPC (existing/new) | Indigo Plateau reception | reached League | 1 | drafted | - |
| LANCE-02 | Lance (the convert) | Saffron fan (reflavor canon): "LANCE showed me my GYARADOS is a SEA DRAGON. Now I can't UNSEE it! He's the greatest, LANCE!" | Saffron fan (existing, reflavor) | Saffron City | after Saffron | 2 | drafted | - |
| LANCE-03 | Lance (dragon in waiting) | Fisher: "LANCE called my MAGIKARP 'a dragon in waiting.' …It's a GYARADOS now. The man SEES it." | Fisher (existing/new) | Route / Cerulean | none | 3 | drafted | - |
| LANCE-04 | Lance (the taxonomy) | Trainer: "To LANCE there are two kinds of POKéMON. Dragons, and dragons that don't know it yet. …I'm starting to think he's onto something." | trainer NPC (existing/new) | any town | reached League | 4 | drafted | - |
| LANCE-05 | Lance (ancient dragon) | Fossil NPC: "Told LANCE his AERODACTYL is a ROCK type. He just smiled. 'An ANCIENT dragon,' he said. …You can't argue that smile." | Cinnabar / Fossil NPC (existing/new) | Cinnabar / Fossil | none | 5 | drafted | - |
| LANCE-06 | Lance + Oak (cross-link) | Oak's aide: "PROF. OAK showed him the type charts for an hour. LANCE nodded. Said, 'So… a dragon.' OAK had to go lie down." | Oak's Lab aide (existing) | Pallet, Oak's Lab | mid-game | 6 | drafted | [FLAG: canon-check] |
| LANCE-07 | Lance (bloodline) | NPC (reflavor canon cousin): "It runs in the blood. A cousin of his leads a gym far away. Same gift, sees the dragon in everything. …Holidays there sound exhausting." | Indigo NPC (existing, reflavor) | Indigo Plateau / town | reached League | 7 | drafted | [FLAG: canon-check] |
| LANCE-08 | Lance (the belief / awe) | Reception: "His dragons fight like they can't be hurt. Because HE believes it. So THEY believe it. …That's the wall you're climbing." | reception NPC (existing/new) | Indigo Plateau reception | reached League | 8 | drafted | - |
| LANCE-09 | Lance (battle voice) | INTRO "I like dragons." / DEFEAT (D-C) "…You DO like dragons, though? …Say you like dragons." / POST "…DRAGGIN DEEZ NUTS!! …Go on. The CHAMPION waits." | Lance | Indigo Plateau, Lance's Room | at the battle | 9 | drafted | [FLAG: dated] |
| LANCE-10 | Lance (post-defeat) | Reception callback: "You beat LANCE? Did he tell you that you battle like a young dragon? …From him, that is everything." | reception NPC (existing/new) | Indigo Plateau reception | FLAG_DEFEATED_LANCE | 10 | drafted | - |

Consistency notes:
- UPLIFTING, NOT KICKING DOWN is the hard rule. Every fragment shows an NPC
  converted or charmed. Never pathetic, never mocking. His conviction is the joke.
- Keep the FINALE AWE (08): his belief is why his dragons are the wall. The comedy
  (the "draggin deez nuts" post-battle) lands AFTER the fight so it never deflates
  the climb. His intro is a single deadpan line against the whole grand build-up.
- The POST-BATTLE meme is tagged [FLAG: dated]; a release pass can swap it. The
  intro ("I like dragons") and the gospel carry no meme risk.
- CROSS-LINK to Oak: LANCE-06 is the OAK-vs-LANCE beat (catalogue everything vs.
  reject the taxonomy for love). Mirrors the Oak arc; tag canon-check. See OAK-*.
- The cousin (07) is Clair of Blackthorn (Johto), kept coy and un-named
  (cross-region); tag canon-check.
- Reflavor the existing canon references (Saffron LANCE superfan, the Indigo cousin
  line) rather than adding new NPCs where possible.

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
