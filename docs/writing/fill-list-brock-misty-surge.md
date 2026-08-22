# NPC Fill List - Brock, Misty, Surge

> PLANNING doc. Enumerates the REMAINING VANILLA flavor NPCs in each leader's
> territory that should have their existing lines REPLACED with that leader's
> flavor. These are REPLACE-vanilla targets only: no new map objects, no new
> sprites. The writer swaps the text on an object that is already on the map.

## Diff method

- VANILLA BASELINE = git commit `0cb07cece14bd363d85e731dfe43b093f050c478`
  (the upstream fork point).
- For each map: `git diff 0cb07... HEAD -- data/maps/<map>/scripts.inc` shows
  which EventScripts already changed (DONE = skip) vs unchanged (still VANILLA
  = a fill target). `map.json` gives each object's `graphics_id` (the persona
  the fill copy has to fit).
- An NPC whose text is UNCHANGED vs baseline is still vanilla = a fill target.
  NPCs already reflavored (Brock/Misty/Surge lines, Blaine rumors, the Twitch
  rival, etc.) are DONE and excluded.

## Excluded (left vanilla on purpose)

Gym guides / "Gym Guy", Nurse Joy and heal counters, Mart clerks and merchants,
museum ticket/tour + fossil-tutorial flow, move tutors, mechanics/tutorial NPCs
(catch tips, obedience/badge explainers, held-item tips), trade-offer and
cable-club NPCs, plot NPCs mid-quest, trainers (their post-battle chorus lines
are handled separately in the Misty/Surge arcs), signs, and item balls.

## Cross-nudges

Each city carries 1-2 CROSS-NUDGE slots: instead of its own leader's lore, the
NPC drops a subtle, non-spoilery foreshadow or callback to a DIFFERENT
character. Marked `X-NUDGE: <character>` in the angle cell.

Angle rule (from the style guide): imply, never explain. Keep every angle coy
and VARIED so no two NPCs parrot the same fact.

---

# BROCK - Pewter City

Already done (skip): Lass, Fat Man, Bug Catcher (progressive gossip
01/08/09/10), Museum Guide (carries the Blaine "island that burned" rumor),
Pewter House 2 Old Man (the "payment every month" alimony line), and the gym
(Brock + Liam). Brock's coy rule holds: never state "divorce/ex-wife", and keep
the alimony arc entirely OFF children.

### PewterCity_Museum_1F_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| Museum_1F | `PewterCity_Museum_1F_EventScript_Scientist2` | OBJ_EVENT_GFX_SCIENTIST | Two rare fossils are on exhibit here. | Brock the rock man: patience is a mineral thing; "ROCK taught him to wait." Coy nod that he knows every stone in this room by name. |
| Museum_1F | `PewterCity_Museum_1F_EventScript_OldMan` | OBJ_EVENT_GFX_OLD_MAN_1 | Grateful for a long life; got to see a dragon's bones. | Old-timer who "remembers Brock before the phones started ringing." Coy "the man's got history" without the punchline. |

### PewterCity_Museum_2F_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| Museum_2F | `PewterCity_Museum_2F_EventScript_Man` | OBJ_EVENT_GFX_MAN | Moon Stone? Looks like an ordinary rock to me. | Brock could tell you it isn't. Rock literacy as his quiet expertise; "hardest thing in this city, that man's exterior." |
| Museum_2F | `PewterCity_Museum_2F_EventScript_OldMan` | OBJ_EVENT_GFX_OLD_MAN_2 | Bought a color TV in '69 just to watch the moon landing. | The phones, obliquely: back then one telephone was a marvel; "you should see the wall of them over at the GYM now." |
| Museum_2F | `PewterCity_Museum_2F_EventScript_LittleGirl` | OBJ_EVENT_GFX_LITTLE_GIRL_FRLG | Wants her daddy to catch her a Pikachu. | X-NUDGE: Misty. Keep it a child-safe daydream: "when I'm big I'll train water POKéMON up in CERULEAN, like the tomboy girl." (No Brock lore on a child.) |
| Museum_2F | `PewterCity_Museum_2F_EventScript_BaldingMan` | OBJ_EVENT_GFX_BALDING_MAN | "A Pikachu soon, I promise." (the dad) | LOW / keep light. A wholesome Brock-as-nurturer beat if used ("BROCK'd catch her one in a heartbeat, soft touch with POKéMON"); no divorce angle near the kid. |

### PewterCity_House1_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| House1 | `PewterCity_House1_EventScript_BaldingMan` | OBJ_EVENT_GFX_BALDING_MAN | Traded ("outsider") mons are finicky; "if only we had some badges." | X-NUDGE: Giovanni. Keep the badge/obedience hint, add a coy note about the VIRIDIAN GYM you passed that's "always shut, LEADER never in. Away on business, they say." |

### PewterCity_PokemonCenter_1F_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| PokeCenter_1F | `PewterCity_PokemonCenter_1F_EventScript_Gentleman` | OBJ_EVENT_GFX_GENTLEMAN_FRLG | "Team Rocket at Mt. Moon? I'm on the phone, scram!" | The phones gag by contrast: an ordinary man flustered by ONE call. "One call rattles me. BROCK's got a whole wall of them and never blinks." (Keep it Brock; the Rocket beat can stay as his flavor.) |
| PokeCenter_1F | `PewterCity_PokemonCenter_1F_EventScript_Youngster` | OBJ_EVENT_GFX_YOUNGSTER_FRLG | Jigglypuff's song makes everyone drowsy. | LOW. Optional coy Brock beat ("BROCK could sleep through anything... except a ringing phone"). |

### PewterCity_Mart_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| Mart | `PewterCity_Mart_EventScript_Youngster` | OBJ_EVENT_GFX_YOUNGSTER_FRLG | A shady guy talked me into buying a weak Magikarp for 500. | Brock's contract wisdom, played for buyer's remorse: "should've read the fine print. BROCK'd tell you: always read the whole contract before you say yes." |
| Mart | `PewterCity_Mart_EventScript_Boy` | OBJ_EVENT_GFX_BOY | Raise mons diligently; even weak ones surprise you. | Brock's patience creed: "BROCK never gives up on a POKéMON. On people, well... that's another story." (coy, stops short of the punchline). |

**Also left vanilla (excluded):** Museum_2F Scientist (space-exhibit info) and
Space-Shuttle/Moon-Stone signs; House1 Little Boy + Nidoran (pet gag); House2
Little Boy (catch-mechanics tutorial, and a child); PokeCenter GBA Kids (cable
club); Running-Shoes aide, Gym Guide, all clerks/nurse.

**BROCK total: 11 fill targets** (2 of them cross-nudges: 1 Misty, 1 Giovanni).

---

# MISTY - Cerulean City + Routes 24/25

Already done (skip): City Youngster (MISTY-01), City Balding Man (MISTY-03 +
post-badge 06), Cerulean Cave Guard (carries the Blaine/Mewtwo "came up from
the south over the sea" rumor), the gym (Misty + Diana + Luis + bug-ban gate),
the Route 24 Nugget Bridge gauntlet trainers and Route 25 trainers (the Misty
"chorus" post-battle lines), and Bill (the Sea Cottage payoff). Keep the
water-only reveal OBLIQUE; never name Togepi for the "egg" beats.

### CeruleanCity_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| Cerulean City | `CeruleanCity_EventScript_Woman` | OBJ_EVENT_GFX_WOMAN_1_FRLG | Wants a bright red bicycle; will keep it clean at home. | Sisters/looks angle: the Sensational Sisters keep everything spotless and dry for the shows; "MISTY? Always soaked. She lives in that pool." |
| Cerulean City | `CeruleanCity_EventScript_Lass` | OBJ_EVENT_GFX_LASS_FRLG | Barks battle commands at a Slowbro that keeps ignoring her. | The duck, by rhyme: a water mon that won't obey. "Even MISTY can't make her silly one mind. At least a SLOWBRO just loafs; hers wanders off." |
| Cerulean City | `CeruleanCity_EventScript_Policeman` | OBJ_EVENT_GFX_POLICEMAN | "The people here were robbed. Team Rocket is behind it." | X-NUDGE: Giovanni. Keep the Rocket-robbery beat, add coy weight: "and the one giving the orders? Nobody's ever seen his face. A clean-handed man somewhere." |
| Cerulean City | `CeruleanCity_EventScript_LittleBoy` | OBJ_EVENT_GFX_LITTLE_BOY_FRLG | If the Slowbro weren't there you could Cut the tree. | LOW / utility Cut hint. Optional light duck aside ("that SLOWBRO's nearly as stubborn as MISTY's duck"). |

### CeruleanCity_PokemonCenter_1F_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| PokeCenter_1F | `CeruleanCity_PokemonCenter_1F_EventScript_Gentleman` | OBJ_EVENT_GFX_GENTLEMAN_FRLG | People call Bill a Pokemaniac; it's just jealousy. | Chasing-the-duck angle: "you'll not find MISTY in town half the time. Off retrieving that PSYDUCK again. It never stays put." |
| PokeCenter_1F | `CeruleanCity_PokemonCenter_1F_EventScript_Rocker` | OBJ_EVENT_GFX_ROCKER | Bill will do whatever it takes to get rare mons. | X-NUDGE: Surge. Foreshadow Vermilion: "Rare? Head south to VERMILION sometime. Loud fella runs the gym there. City wasn't always so free, they say." |
| PokeCenter_1F | `CeruleanCity_PokemonCenter_1F_EventScript_Youngster` | OBJ_EVENT_GFX_YOUNGSTER_FRLG | (famechecker Bill) Bill collects rare mons. | LOW. Keep the famechecker call; optional only-water aside ("MISTY only ever keeps water types. Wonder why."). |

### Route25_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| Route 25 | `Route25_EventScript_Man` | OBJ_EVENT_GFX_MAN | "Cerulean's cape should be visited as a couple. You alone?" | Sisters/romance + egg, oblique: "the sisters bring dates up to the cape. MISTY brings that duck. And whatever she's been guarding down by the shore." |

**Also left vanilla (excluded, utility/trade/plot):** PokeCenter Lass (trade
tutorial); Mart Repel/Rare-Candy tutorial NPCs (a Repel-keeps-bugs-away line is
a tempting bug-ban nudge but it's a mechanics NPC - LOW); House1 badge-secrets
man; House2 robbed-house Rocket plot (Hiker + Lass); House3 trade offer; House4
Wonder-News/berry man; House5 berry-powder man; Route 24 is fully trainers +
item + Rocket (all done or excluded).

**MISTY total: 8 fill targets** (2 of them cross-nudges: 1 Giovanni, 1 Surge).

---

# SURGE - Vermilion City + S.S. Anne

Already done (skip): City Woman (SURGE-01 + post-badge 08), Old Man 2
(SURGE-02), Sailor (SURGE-03), Old Man 1 (carries the Blaine/Mewtwo "a sea
sailors won't cross" rumor); the gym (Surge + Dwayne/Baily/Tucker + trash-can
trial); S.S. Anne Deck Sailor (SURGE-04), 1F Corridor Sailor (SURGE-05), and
the Captain (SURGE-06 payoff). Keep the history VAGUE: "the regime", "the old
bosses", "back then", "the war" - never claim Rocket is finished. On the ship,
crew/passengers show present-day PRIDE and relief, they never explain the
history (that is the Captain's job).

### VermilionCity_Mart_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| Mart | `VermilionCity_Mart_EventScript_CooltrainerF` | OBJ_EVENT_GFX_COOLTRAINER_F | A mon is only as good or bad as its trainer. | Surge judged by deeds, not volume: "the LT's all noise until it counts. Then you understand why VERMILION sleeps easy." |
| Mart | `VermilionCity_Mart_EventScript_BaldingMan` | OBJ_EVENT_GFX_BALDING_MAN | Team Rocket traffics rare mons and dumps the rest. | X-NUDGE: Giovanni/Rocket. Coy: "the trade never really stopped, just changed hands. And the man at the top? None of us have seen his face." |

### VermilionCity_PokemonFanClub_Frlg

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| Fan Club | `VermilionCity_PokemonFanClub_EventScript_Woman` | OBJ_EVENT_GFX_WOMAN | Gushes about how much she adores her Seel. | X-NUDGE: Misty. Water-mon dote that points north: "a Seel never wanders off, that's why I love it. Heard a gym leader up in CERULEAN feels the same." |
| Fan Club | `VermilionCity_PokemonFanClub_EventScript_FatMan` | OBJ_EVENT_GFX_FAT_MAN_FRLG | Boasts about his Pikachu's beautiful tail. | The freed electric mons: "you notice this whole city loves an electric POKéMON? There's a reason for that. Ask the LT. Or don't." |
| Fan Club | `VermilionCity_PokemonFanClub_EventScript_WorkerF` | OBJ_EVENT_GFX_WOMAN_2 (verify id) | Remarks the Chairman is very vocal about his mons. | Silly-through-contrast: "loud men, this city. The Chairman, the LT... you get used to it. The loud ones did the quiet work once." |

### VermilionCity houses

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| House3 | `VermilionCity_House3_EventScript_Boy` | OBJ_EVENT_GFX_LITTLE_BOY_FRLG | Sends a Pidgey off carrying mail. | LOW. Optional present-day-freedom aside ("mail flies out of VERMILION free as anything now. Wasn't always so, my grandpa says"). |
| House3 | `VermilionCity_House3_EventScript_Lass` | OBJ_EVENT_GFX_LASS_FRLG | Chatter about mail / the Pidgey. | LOW / optional. |

### S.S. Anne (crew present-day pride; passengers oblique)

| Map | EventScript | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| 1F_Corridor | `SSAnne_1F_Corridor_EventScript_Waiter` (WorkerM) | OBJ_EVENT_GFX_WORKER_M | Waiter does the "strong silent type" bit. | Crew service pride: "this ship runs proud these days. Wasn't always a place you'd want to serve on. …Ask no more." |
| 2F_Corridor | `SSAnne_2F_Corridor_EventScript_Sailor` | OBJ_EVENT_GFX_SAILOR | Boasts the S.S. Anne is a fine luxury liner. | Present-day, oblique: "she runs clean now, top to keel. Took a hard hand to make her so." |
| 3F_Corridor | `SSAnne_3F_Corridor_EventScript_Sailor` | OBJ_EVENT_GFX_SAILOR | The Captain is a sword master; he can teach Cut. | Build the Captain payoff: "the CAPTAIN was here through it all. If anyone can tell you how VERMILION turned, it's him." |
| Deck | `SSAnne_Deck_EventScript_Youngster` | OBJ_EVENT_GFX_YOUNGSTER_FRLG | The party's over; the ship is about to depart. | Freedom beat: "she sails out of VERMILION free as you please now. My dad says that used to mean something." |
| Deck | `SSAnne_Deck_EventScript_BaldingMan` | OBJ_EVENT_GFX_BALDING_MAN | Seasick; came out for air. | LOW / optional. |
| 1F_Room1 | `SSAnne_1F_Room1_EventScript_Gentleman` | OBJ_EVENT_GFX_GENTLEMAN_FRLG | Is on the Global Police, on Team Rocket's trail. | X-NUDGE: Giovanni. Keep the Rocket-hunt beat, add coy: "we know the face he shows the world. Not the one underneath. This ship remembers the underneath." |
| 1F_Room2 | `SSAnne_1F_Room2_EventScript_Woman` | OBJ_EVENT_GFX_WOMAN_2 (verify id) | Cruising the world with her children. | LOW. Optional free-passage aside ("anyone can book this cruise now. That's newer than you'd think"). |
| 2F_Room6 | `SSAnne_2F_Room6_EventScript_Woman1` | OBJ_EVENT_GFX_WOMAN_1_FRLG | The Captain looks awfully pale/ill. | Ties to the Captain payoff: "he carries a lot, that man. This whole ship owes him, and he knows it." |

**Also left vanilla (LOW-fit / keep-vanilla candidates):** the remaining S.S.
Anne passenger rooms (1F Room3/4/5, 2F Room1/3/5, B1F Room5 leisure banter) and
the Kitchen chefs read as pure holiday filler - reflavoring all of them would
over-saturate Surge's arc, so leave most vanilla and cherry-pick only if a room
feels empty. **Excluded outright:** 2F Room3 Old Man (Cut/HM tutorial), Fan
Club Chairman (Bike Voucher), House1 fishing guru (Old Rod), House2 Elyssa
(Farfetch'd trade), all clerks/nurse/gym guide, and every trainer/item ball.

**SURGE total: 15 fill targets** (3 of them cross-nudges: 2 Giovanni/Rocket,
1 Misty).

---

## Notes for the writer

- Persona ids marked "(verify id)" are Fan Club / S.S. Anne room objects whose
  exact `graphics_id` should be re-read from that map's `map.json` at write
  time; the label and vanilla line are confirmed.
- Match each fill to the persona and to the width/rhythm of the vanilla string
  it replaces (short two-line gen-3 pages). No em dashes anywhere.
- Log any new fragment as a row in `lore-ledger.md` in the same PR, per the
  project rule.
