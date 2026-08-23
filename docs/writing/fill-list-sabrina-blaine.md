# NPC Fill List: SABRINA + BLAINE (planning)

> Planning doc only. Enumerates the REMAINING vanilla NPCs in each leader's
> territory whose lines should carry that leader's flavor. Angles are drawn from
> drafts/sabrina.md, drafts/blaine.md, and the lore-ledger (SABRINA-*, BLAINE-*).
> This doc writes NO game script. No em dashes anywhere per style-guide §2.

## Method

- VANILLA BASELINE for the diff: fork-point commit `0cb07cec…`. For every
  territory map I ran `git diff <baseline> HEAD -- <map>/scripts.inc` and read the
  current scripts.inc plus map.json (graphicsId = persona).
- NPC text UNCHANGED vs baseline = still vanilla = a FILL TARGET (listed below).
- NPC text CHANGED vs baseline = already reflavored = SKIPPED (see "Already done").
- EXCLUDED (left vanilla, per brief): gym guides, Nurse/heal counters, Mart
  clerks, the Cinnabar move-tutor / fossil-revive / in-game-trade service NPCs,
  pure tutorial/mechanic NPCs, trainers, signs, item objects, Pokemon-cry pets,
  and anything already reflavored.
- SUBTLE + VARIED: no repeated beats. Angles cite the ledger row they extend.
- CROSS-NUDGE: 1-2 NPCs per city point (obliquely, never spoilery) at a DIFFERENT
  memorable character to foreshadow/callback.

### Already done in these territories (skip, for reference)

- SABRINA: Saffron overworld Lass (SABRINA-01) + WorkerM (SABRINA-02); Mr Psychic
  (SABRINA-WARN / FREED); Copycat's House 2F doll + Copycat (SABRINA-03 / 04);
  all Saffron Gym trainers + Gym Guide + Sabrina herself (SABRINA-GYM / SELF);
  the Saffron PC 1F "Pokemon Journal (Sabrina)" object; the Saffron LANCE superfan
  text (LANCE-02, a Lance target).
- BLAINE: Cinnabar Woman (BLAINE-01) + Old Man (BLAINE-02); Mansion 3F + B1F
  signed diary fragments (BLAINE-DIARY); Lab Entrance scientist + Fuji photo
  (BLAINE-PAYOFF); Lab Research Room scientist (LANCE-05, a Lance target); Cinnabar
  Gym Blaine himself (BLAINE-QUIZ / SELF); the Cinnabar PC 1F "Pokemon Journal
  (Mr Fuji)" object.

### Counts

- SABRINA: 9 primary fill targets (+ optionals + a light-touch note on Silph Co).
- BLAINE: 4 primary fill targets (+ optionals). Cinnabar is already heavily covered.

---

# SABRINA (Saffron territory)

Arc: the sunny child who went cold; the town lives half-possessed; beating her makes
her LAUGH and breaks the spell. Before-branches carry DREAD; after-branches carry
RELIEF (no grudges, no memory). Gate the two-state ones on `FLAG_DEFEATED_SABRINA`.

## SaffronCity_Frlg (overworld)

| EventScript | Persona (gfx) | Current vanilla line (paraphrase) | Suggested fill angle |
|---|---|---|---|
| `SaffronCity_EventScript_Youngster` | Youngster (`YOUNGSTER_FRLG`) | "Rockets are gone, safe to go out again!" | Relief that curdles. The Rockets left, but the streets feel wrong-quiet, like the town is holding its breath. A first dread seed (extends SABRINA-02). After-branch optional: honest relief once she's freed. |
| `SaffronCity_EventScript_Boy` | Boy (`BOY`) | Flew in on his Pidgeot for the Silph news, "missed the media action." | Outsider's eye: the city looks fine, but people move like sleepwalkers and no one will say why. Coy, un-alarmed (he is a tourist), which makes it eerier. |
| `SaffronCity_EventScript_Man` | Man (`MAN`) | "I saw the ROCKET BOSS escaping SILPH's building." | CROSS-NUDGE -> GIOVANNI. Keep the sighting, add that he only caught the face for a second and it looked too ordinary, "a face you'd pass in any city." Feeds GIOVANNI-04 (the clean face none of them have seen). Do NOT connect it to Viridian; player connects it. |

Not targets here: RocketGrunt1-7 (occupation NPCs, they leave after liberation, not
persistent); DoorGuardGrunt (Silph gate, functional); all signs.

## SaffronCity_House_Frlg

| EventScript | Persona (gfx) | Current vanilla line | Suggested fill angle |
|---|---|---|---|
| `SaffronCity_House_EventScript_Lass` | Lass (`LASS_FRLG`) | Writing a warm letter, "don't look at my letter!" | Silly-through-contrast warmth in a cooling town: she keeps a small light on. Coy dread option: her pen-pal across town "stopped writing back the week the vanishings started." Restrained. |
| `SaffronCity_House_EventScript_Youngster` | Youngster (`YOUNGSTER_FRLG`) | "The COPYCAT is cute! I'm getting her a POKe DOLL." | Dolls thread (extends SABRINA-03): a child cheerfully buying a doll while the town whispers about dolls that keep people. Keep it light and innocent; the reader supplies the chill. |

Not targets: Pidgey pet cry; the PP UP letter sign.

## SaffronCity_CopycatsHouse_1F_Frlg

| EventScript | Persona (gfx) | Current vanilla line | Suggested fill angle |
|---|---|---|---|
| `SaffronCity_CopycatsHouse_1F_EventScript_CopycatsMom` | Copycat's Mom (`WOMAN_3_FRLG`) | "My daughter is self-centered, few friends." | A mother's worry, deepened: lately the girl won't go out, just mimics faces in the mirror "like she's keeping hold of herself." Coy town-unease, no naming Sabrina. |
| `SaffronCity_CopycatsHouse_1F_EventScript_CopycatsDad` | Copycat's Dad (`BALDING_MAN`) | "My daughter mimics everyone, hence COPYCAT." | Sets up SABRINA-04 (the un-mimicable face): "She can do anyone in SAFFRON. Anyone. There's just one face she won't even try." Player meets the payoff upstairs (Copycat / doll). |

Not targets: Chansey pet cry.

## SaffronCity_PokemonTrainerFanClub_Frlg

| EventScript | Persona (gfx) | Current vanilla line | Suggested fill angle |
|---|---|---|---|
| `SaffronCity_PokemonTrainerFanClub_EventScript_LittleGirl` | Little Girl (`LITTLE_GIRL_FRLG`) | Vanilla: "I want to be like SABRINA! A psychic girl!" / "I won't stop being SABRINA's fan." | STRONGEST in-territory target. A child who adores Sabrina AS SHE WAS: the emotional counterweight to the dread. Pre-defeat base line: bright admiration with one worried flicker ("she seems so sad now"). Reflavor the base admiration line only; preserve the fan/non-fan/champion branch flow. After-branch optional: pure delight that "SABRINA smiled today." |

Not targets: the other fan-club members (BattleGirl, Youngster, Gentleman, Woman,
Rocker, Beauty, BlackBelt) are generic and sit behind the multi-branch fan mechanic;
listed as OPTIONAL below. The "Pokemon Journal (Bruno)" object is already themed.

## SaffronCity_PokemonCenter_1F_Frlg

| EventScript | Persona (gfx) | Current vanilla line | Suggested fill angle |
|---|---|---|---|
| `SaffronCity_PokemonCenter_1F_EventScript_Woman` | Woman (`WOMAN_3_FRLG`) | "POKeMON growth rates differ by species." | Marsh-Badge tie (per Sabrina consistency note): reframe the mechanic-flavor toward "power that grows past the trainer's hand turns on them. They say that is what happened to HER." Ties the badge's over-level disobedience to Sabrina's cold. Semi-optional (line is close to tutorial). |

Optional / lower priority (Saffron):
- `..._PokemonCenter_1F_EventScript_Gentleman` (Gentleman, `GENTLEMAN_FRLG`) "SILPH,
  victim of its own fame, attracted TEAM ROCKET." Light Rocket/Silph flavor; if used,
  a coy tail: "and when they left, something quieter stayed." Otherwise leave.
- `..._PokemonCenter_1F_EventScript_Youngster` (Youngster) has a before/after Rocket
  branch and already name-drops the ELITE FOUR. CROSS-NUDGE candidate (see below).
- FanClub generic members (as noted above).
- Silph Co. workers (see the Silph note below).

## Mr Psychic's House

Fully covered (Mr Psychic = SABRINA-WARN / FREED). No remaining targets.

## Silph Co. (judgment call: this is primarily GIOVANNI's tower)

Silph is Giovanni's arc and is already partly wired (GIOVANNI-05 / 05b / 05c on the
5F / 8F / 11F employees). Recommendation: DO NOT crowd it with Sabrina lore. Its
flavor NPCs (Receptionist 1F; WorkerM 3F; HealWoman 9F, functional; WorkerF 10F;
plus the Rocket-grunt / employee before-after pairs) belong to the Rocket / Giovanni
beat.

OPTIONAL light touch only: on 1-2 POST-liberation Silph workers
(`SilphCo_3F_EventScript_WorkerMRocketsGone`, `SilphCo_10F_EventScript_WorkerFRocketsGone`)
a single "I lost an afternoon and can't say where it went" line would quietly rhyme
with the town's half-possession, since Silph sits inside Saffron. Flag as optional;
keep it to one worker so it does not read as a Sabrina beat inside Giovanni's tower.

## Saffron cross-nudges

1. PRIMARY: `SaffronCity_EventScript_Man` -> GIOVANNI (the too-ordinary escaping
   face; feeds GIOVANNI-04). Coy, unconnected to Viridian.
2. OPTIONAL: `SaffronCity_PokemonCenter_1F_EventScript_Youngster` -> the ELITE FOUR /
   finale. It already sighs "wouldn't it be great if the ELITE FOUR came." A natural
   spot to foreshadow the League ahead (a nod to LANCE-01's dragon gospel, or the
   cold ones at the top). Keep it a wish, not a fact.

---

# BLAINE (Cinnabar territory)

Arc: the red-hot quiz-master was a Mansion researcher on Dr Fuji's team who helped
make MEWTWO; guilt sits under the bluster. Journals are the coy anchor; the Lab is
the plain payoff; townsfolk stay coy. Cinnabar is ALREADY heavily covered, so the
remaining targets are few.

## PokemonMansion_2F_Frlg (the canon MEW diary, pre-fragments)

The signed "-F." / "-B." fragments already sit on 3F (Feb 6) and B1F (Sep 1). The 2F
entries are the earlier canon diary and are still vanilla. Treat as anchor journals
(the brief treats Mansion journals as flavor, not wayfinding signs).

| EventScript | Object | Current vanilla line | Suggested fill angle |
|---|---|---|---|
| `PokemonMansion_2F_EventScript_DiaryJuly5th` | Diary object | "July 5, Guyana: a new POKeMON discovered." | Keep the canon entry; optionally add a faint UNSIGNED margin of the young team's hope ("a whole new life. we could learn everything") so the later signed regret lands harder. Do NOT reuse "-B." / "-F." here (no repeated beat). |
| `PokemonMansion_2F_EventScript_DiaryJuly10th` | Diary object | "July 10: we christened it MEW." | A hair of foreshadow only, unsigned ("we should be careful with something this rare"). Restraint: the emotional signed beats stay on 3F / B1F. Optional / light. |

Not targets: Mansion trainers (Ted, Johnson, Arnie, Simon, Braydon, Lewis, Ivan) and
the secret-switch statues. Note Braydon's canon "my mentor once lived here" is a
Blaine-adjacent hook but he is a trainer (excluded).

## CinnabarIsland_PokemonLab_Lounge_Frlg

| EventScript | Persona (gfx) | Current vanilla line | Suggested fill angle |
|---|---|---|---|
| `CinnabarIsland_PokemonLab_Lounge_EventScript_Scientist` | Scientist (`SCIENTIST`) | "I found a remarkable prehistoric fossil in MT. MOON." | Blaine's science-culture, oblique: the lab his old team built still reaches for ancient, powerful life. "The founders chased older and stranger things than fossils, once." Never spell out MEWTWO. Extends the BLAINE-PAYOFF atmosphere from next door. |

Not targets: Clifton / Norma (in-game trades, functional).

## CinnabarIsland_PokemonCenter_1F_Frlg

| EventScript | Persona (gfx) | Current vanilla line | Suggested fill angle |
|---|---|---|---|
| `CinnabarIsland_PokemonCenter_1F_EventScript_CooltrainerF` | Cooltrainer F (`COOLTRAINER_F`) | Gym is locked; the key may be in the burned mansion; "the GYM LEADER's friend used to live there." | STRONG Blaine target + CROSS-NUDGE. Deepen "the Leader's friend" coyly without naming Fuji: "Two of them worked in that mansion, before the fire. Only one walked out of it whole." PRESERVE the functional key hint (mansion). |

Optional / lower priority (Cinnabar):
- `..._PokemonCenter_1F` Gentleman (Union Room promo) and Youngster
  (evolution-vs-moves tutorial): functional / tutorial, leave vanilla.
- `CinnabarIsland_Mart_EventScript_Woman` (X ATTACK) and `..._Scientist` (extra
  items): mart tutorial flavor, low value; recommend leave vanilla. The Scientist is
  a possible thin E4/League nudge (see cross-nudges).
- Cinnabar Gym `EventScript_Derek` post-battle already tells the canon MOLTRES story
  (a fiery bird lit lost Blaine's way down): a genuine Blaine hook, but he is a
  trainer (excluded). Flagged in case the trainer-exclusion is relaxed for gyms.

## Cinnabar overworld / other lab rooms

- CinnabarIsland_Frlg: fully covered (Woman + Old Man). Remaining objects are Bill
  (plot), signs, and the gym door. No targets.
- Lab Entrance + Research Room: fully covered (BLAINE-PAYOFF + LANCE-05). Tutor,
  fossil email, amber-pipe are functional / signs.
- Lab Experiment Room: fossil-revive + trade only, all functional. No targets.
- Mansion 1F / 3F / B1F: trainers + statues + done fragments. No new targets.

## Cinnabar cross-nudges

1. PRIMARY: `CinnabarIsland_PokemonCenter_1F_EventScript_CooltrainerF` -> MR. FUJI
   (the unnamed friend from the mansion). Coy; leaves room for the player to meet
   Fuji's thread elsewhere. Keeps the key hint intact.
2. OPTIONAL: `CinnabarIsland_Mart_EventScript_Scientist` -> the ELITE FOUR / League
   ahead. With the 7th badge in hand, a light "stock up, the ones at the top do not
   go easy" forward-nod (a distant nod to Lorelei's ice at the League's door). Thin;
   optional.

---

## Notes for the writer

- Keep every Sabrina before-line DREAD and every after-line RELIEF; gate two-state
  NPCs on `FLAG_DEFEATED_SABRINA`. No grudges, no memory in the after-state.
- Keep every Blaine leak COY (journals unsigned or initialed; townsfolk never name
  Fuji / Mewtwo). The plain telling already lives in the Lab; ambient stays oblique.
- Log any new fragment as a new ledger row (SABRINA-* / BLAINE-*) in the same PR that
  writes the line, per the ledger rule. Tag canon-blend lines `[FLAG: canon-check]`.
- Cinnabar is nearly complete; resist over-filling. Saffron has the most open room
  (the houses, the fan club, the overworld).
