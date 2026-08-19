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
- Erika's own gym lines stay archetypal vanilla (dozing princess); the mystique
  lives in the town around her, so the hard-but-fair fight still reads real.
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
