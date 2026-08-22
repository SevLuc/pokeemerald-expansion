# Fill list: ERIKA and KOGA territories

Planning doc only. This enumerates the VANILLA NPCs still left in each leader's
territory whose lines are candidates to carry that leader's flavor. It is not a
script edit and nothing here has been written into the game.

## Method

- **Vanilla baseline:** git commit `0cb07cece14bd363d85e731dfe43b093f050c478`
  (fork point). An NPC whose text is byte-identical to that commit is still
  vanilla and therefore a fill target. An NPC whose text already changed is
  treated as DONE and skipped.
- **How "done" was detected:** `git diff <baseline> -- data/maps/<Map>/scripts.inc`
  per territory map, cross-read against the current `scripts.inc` and each
  `map.json` (for the `graphics_id` persona of each object).
- **Angles** are drawn from `docs/writing/drafts/erika.md`, `.../koga.md`, and the
  `ERIKA-*` / `KOGA-*` rows in `docs/writing/lore-ledger.md`. Kept subtle and
  varied: no facet is repeated across two fill targets in the same area.
- **Excluded (left vanilla):** gym guides, Nurse Joy/heal counters, Mart and
  service-counter clerks, dept-store sales clerks, Game Corner staff and slot
  mechanics, move tutors / Move Deleter, mechanic-hint and directions NPCs,
  tutorial NPCs, story/quest-item givers, the Game Freak dev-room NPCs, signs,
  item balls, and anything already reflavored.
- **Style:** no em dashes anywhere (project rule). Fill angles below are
  directions, not final copy.

## Headline finding

Both arcs are already ~90% placed in-game. The bulk of each leader's ambient
lore (all the facets, the two gimmicks, the route stance-choruses, the gym and
interior payoffs) is DONE. What remains is a short tail of genuinely-vanilla
flavor NPCs plus a handful of cross-nudge opportunities. Recommend restraint:
adding more than the "primary" rows risks turning a curated chorus one-note.

### Target counts

| Leader | Primary fill targets | Optional / low-priority | Cross-nudges |
|---|---|---|---|
| ERIKA | 4 | 4 | 2 (+1 optional) |
| KOGA  | 0 | 2 | 1 |

Nearly every Fuchsia and Celadon interior/route NPC that suits a leader beat has
already been reflavored (see the DONE notes under each map).

---

# ERIKA (Celadon territory)

Facet legend (from erika.md): poison/medicine master; perfume-calms-the-city;
once-fearsome battler; ladies-only refuge; even-Rocket-steers-clear; the-bikers-
who-fled gimmick; Brock's-exes-take-refuge gimmick. Poison/medicine and the
exes/bikers gimmicks are already saturated, so the open angles below lean on the
LESS-used facets (perfume-calms, refuge, bikers-from-outside).

## Primary fill targets

| Map | EventScript label | Persona (graphics_id) | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| CeladonCity_Hotel_Frlg | `CeladonCity_Hotel_EventScript_Beauty` | Beauty | On vacation with her brother and boyfriend; "CELADON is such a pretty city!" | Perfume-calms facet (ERIKA-02 reach). She cannot say why the city feels so lovely; a coy "they say it is on the wind" beat. Under-used facet, good fit for a vacationer. |
| CeladonCity_PokemonCenter_1F_Frlg | `CeladonCity_PokemonCenter_1F_EventScript_Youngster` | Youngster | "If I had a BIKE, I would go to CYCLING ROAD!" | The-bikers-who-fled, seen from the inside (ERIKA-BIKERS). He is keen on the road gang; hint that they will not come back into town, and he does not quite know why. |
| Route17_Frlg | `Route17_Text_Billy*` (intro/defeat/post) | Biker | "We're BIKERS! We rule the roads, man!" then "Are you looking for adventure?" | Fled-Celadon bravado covering fear (ERIKA-BIKERS). They "rule the road" because they will not set foot back in the flower district. Keep it swagger-over-dread; distinct from Route 16's carriers. |
| Route17_Frlg | `Route17_Text_Corey*` (intro/defeat/post) | Biker | "Be a rebel!" / "Be ready to fight for your beliefs!" | The tax-dodge running gag (ERIKA-BIKERS). His "rebellion" is really skipping CELADON taxes out on the slope. Comic, oblique, keeps the gag varied from Lao's version. |

Route 17 is the Cycling Road mid-point between Celadon and Fuchsia and is
entirely un-reflavored trainer flavor at present. Treat it as the natural
overflow for the fled-bikers gag, but seed only a FEW carriers (above) so the
route does not repeat one beat ten times; leave the rest vanilla.

## Optional / low-priority (only if you want more density)

| Map | EventScript label | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| CeladonCity_DepartmentStore_4F_Frlg | `..._4F_EventScript_Man` | Man | Buying a POKé DOLL as a present for his girlfriend, "the popular thing." | Perfume-as-the-real-Celadon-gift nudge; a doll is fine, but the thing everyone actually wants is one of HER scents, and you cannot buy those here. |
| CeladonCity_DepartmentStore_Roof_Frlg | `..._Roof_EventScript_CooltrainerM` | Cooltrainer M | "My sister is a TRAINER, but so immature she drives me nuts." | Ladies-only-refuge facet (ERIKA-04). His sister went off to "that flower gym" and came back different; he cannot say what she learns there. |
| Route16_Frlg | `Route16_Text_Koji*` | Biker | "Nice BIKE! Hand it over!" / "who needs your BIKE!" | Fled-bikers extension. NOTE: four Route 16 bikers (Lao, Ruben, Hideo, Camron) are already DONE; only add Koji/Luke if you want a fuller camp, each with a fresh angle. |
| Route16_Frlg | `Route16_Text_Luke*` | Biker | "Come out and play, little mouse!" / "I hate losing!" | As above. Keep distinct (e.g. he misses the city and will not admit it). |

## Cross-nudges (Celadon -> a different character)

| Map | EventScript label | Persona | Vanilla line (paraphrase) | Cross-nudge target and angle |
|---|---|---|---|---|
| CeladonCity_PokemonCenter_1F_Frlg | `..._EventScript_CooltrainerF` | Cooltrainer F | "I rode here from FUCHSIA. Uphill on CYCLING ROAD, so I'm exhausted." | **KOGA.** She has come up from Fuchsia; a subtle "you can still smell his smoke on my jacket" / rode out from under his lamplight. Oblique industrial foreshadow, no names. |
| CeladonCity_House1_Frlg | `..._EventScript_RocketChief` | Rocket boss (OLD_MAN_2 gfx) | "Hehehe! The slots just reel in the dough, big-time!" | **GIOVANNI.** The Game Corner is his money engine; a whisper that the BOSS "came up from nothing" and is hungry for more (GIOVANNI-01 seed). Do NOT name him as the Viridian leader. |

Optional third cross-nudge: `Route17_Text_Virgil*` (Biker, intro "You heading to
FUCHSIA?") can point south toward **KOGA's** smoke on the horizon, since Route 17
is the transition toward Fuchsia. Use only if Route 17 is not already carrying
the Erika biker gag on Billy/Corey nearby.

## Celadon DONE (skip, already reflavored)

Little Girl, Old Man 1 (+ post-badge wink), Woman, Fat Man, Rocket Grunt 1 & 2,
Boy (city); Restaurant Woman (drugstore); Condominiums 1F tea lady; Dept Store
2F and 5F carriers; Gym (Lisa aggregator + Kay/Lori/Mary exes + trainers);
Route 16 bikers Lao/Ruben/Hideo/Camron; Route 18 (assigned to Koga, see below).

Left vanilla by category (not fill targets): Old Man 2 and Restaurant Fat Man
(slots gamblers), Silph Scope scientist and Restaurant Coin Case man (quest),
Game Corner NPCs (staff/mechanics), Condo 3F Game Freak dev-room NPCs, Softboiled
/ Counter move tutors, Dept Store receptionists/clerks, Thirsty Girl (item quest),
all signs. Condominiums 2F/3F/Roof, Dept Store 1F/3F, PokemonCenter 2F, Game
Corner Prize Room: no eligible flavor NPCs.

---

# KOGA (Fuchsia territory)

Stance legend (from koga.md): PRO/dependent; ANTI/nature-loss; RESIGNED/cynical;
TRUE BELIEVER (Janine); the MAYOR (balanced); gym INSIDERS (spin-doctor payoff).
Every stance is already placed across the city, both houses, the Mart, the Safari
staff, the Warden, the gym, and Routes 15/18/19. Fuchsia is effectively saturated.

## Primary fill targets

None. Every Fuchsia flavor NPC that fits a stance is already DONE.

## Optional / low-priority (thin; only if you want the last two voices)

| Map | EventScript label | Persona | Vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|---|
| FuchsiaCity_PokemonCenter_1F_Frlg | `..._EventScript_Man` | Man | "You can't be a good TRAINER with one strong POKéMON; raising many evenly is hard." | RESIGNED ambient stance. A grid runs the same way: everything draws off one source, and you learn to live under it. Keep it a shrug, not a speech. |
| FuchsiaCity_Frlg | `FuchsiaCity_EventScript_Youngster` | Youngster | Item-ball gag: "That item ball... huh? That's a POKéMON?" | Light ANTI/comic nudge: hard to tell what is what in this haze. Very optional; the gag is self-contained and may read better left alone. |

## Cross-nudge (Fuchsia -> a different character)

| Map | EventScript label | Persona | Vanilla line (paraphrase) | Cross-nudge target and angle |
|---|---|---|---|---|
| Route19_Frlg | `Route19_Text_Douglas*` | Swimmer M | Intro "What's beyond the horizon?" / post "I see a couple of islands over yonder!" | **BLAINE.** Oblique reach of the BLAINE-RUMORS telephone: one of those islands to the west burned, and something rose out of the smoke and went north over the sea. Never name Blaine/Mewtwo. Ties Fuchsia's south coast into the Cinnabar rumor without stepping on Route 20's eyewitness (Missy, already DONE). |

Fuchsia proper has no free CITY NPC for a second clean cross-nudge; the Team
Rocket flavor on Route 15 (Ernest, "TEAM ROCKET RULES") already latently gestures
at **Giovanni** but is DONE as Koga's resigned stance, so leave it.

## Fuchsia DONE (skip, already reflavored)

City: Little Boy, Old Man, Erik, Lass/Janine. Houses: House1 Woman, House2
fishing guru's brother. Mart: Gentleman (= Mayor) and Cooltrainer F. Safari
Office Workers 1/2/3. Safari Entrance info attendant. Warden's House Warden
(post-gold-teeth). Gym: Koga + Kirk/Gym Guy/Shawn. Routes: 15 (Chester/Olivia/
Ernest), 18 (Wilton/Ramiro/Jacob), 19 (Richard/Reece/Tony).

Left vanilla by category (not fill targets): House3 Move Deleter, House1 Old Man
& Little Boy (Bill-arc / famechecker NPCs, not Koga's), PokemonCenter directions
NPCs (League HQ, Safari-for-Pokedex) and Nurse, Safari Office Worker 4 and Safari
Entrance game mechanics, Mart clerk, Substitute move tutor, all species/city
signs. Route 20 is the Blaine-rumor + Misty coast (Missy DONE; "MISTY trains here"
is an existing Misty cross-reference, leave vanilla); it carries NO Koga fill.
