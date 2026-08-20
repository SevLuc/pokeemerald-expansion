# Buhrito - rival voice (WORKING DRAFT)

> Rival: **Buhrito** (one of the two forced picks; the other is Twitch).
> Voice: extremely-online / meta gamer ("what's good", "he cooks", "that's the
> tech", "we about to ball", "lockity splockity"). Character direction is the
> USER's; this file only HOLDS the lines and keeps the scaffolding straight.
>
> Status: user is writing in batches; anything here can change. Wording is kept
> VERBATIM as the user wrote it. Placeholders normalize to the engine tokens
> {PLAYER} / {RIVAL} at implementation; gen-3 line breaks (\n \p \l) get added
> when we wire the branches, not now.
>
> Scaffold + vanilla baseline to fork from: drafts/rival-encounters.md
> Plumbing: each beat branches on VAR_RIVAL_ID to this Buhrito variant.
> RULES that still apply to every line: no em dashes; short gen-3 pages.

---

## 0. Oak's Lab - naming, starter pick, first battle
File: `data/maps/PalletTown_ProfessorOaksLab_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_OAKS_LAB_{BULBASAUR,CHARMANDER,SQUIRTLE}`

- **RivalGrampsIsntAround:** `Yo {PLAYER} what's good, I literally never played this game`
- **RivalFedUpWithWaiting:** `Yeah give me bulbasaur bro!`
- **RivalNoFairWhatAboutMe:** `Bulbasaur is broken because he cooks on brock and he cooks on misty`
- **RivalGoChoosePlayer:** `Bulbasaur that's the tech!`
- **RivalIllTakeThisOneThen:** `Hold up! we got a problem... the starters are different...`
- **RivalMyMonLooksTougher:** `Lets go bro! lets fight`
- **RivalLetsCheckOutMons (battle challenge):** `Wait, {PLAYER}! We are about to ball! Let's gooo!`
- **RivalDefeat (you WIN the tutorial battle):** `They didnt get rid of the tutorial bro!? I know how fighting works, I am not that rusty`
- **RivalVictory (you LOSE the tutorial battle):** `They didnt get rid of the tutorial bro!? I know how fighting works, I am not that rusty` _(same line as RivalDefeat - the tutorial joke lands win or lose)_
- **RivalGoToughenMyMon (he leaves):** `alright bet {Player}, time to lockity splockity blobbity`

> That is the COMPLETE set of rival beats before Route 1. After this he leaves;
> you head to Route 1. The initial Pokedex (parcel delivery in Viridian, then back
> to Oak) has NO rival dialogue in vanilla, so nothing to write there.

## 1. Route 22 - first battle (before Viridian gate)
File: `data/maps/Route22_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_ROUTE22_EARLY_*`
First meeting outside the lab; he blocks the road to the League (likely 0 badges).
- **EarlyRivalIntro (pre-battle):** _GAP - still to write._
- **EarlyRivalDefeat (you win):** _GAP - still to write._
- **EarlyRivalPostBattle (after you win):** _GAP - still to write._
- **Lose = shared Text_RivalVictory** (optional Buhrito-specific gloat, else reuse).
- NOTE: Route22_Text_RivalShouldCatchSomeMons is a DEAD string (defined, never
  called in FRLG; leftover from RGB). Not on the worklist unless you revive it.

## 2. Cerulean City - after the robbed house
File: `data/maps/CeruleanCity_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_CERULEAN_*`
- _GAP - RivalIntro, RivalPostBattle, ExplainFameCheckerSmellYa._

## 3. S.S. Anne - 2F corridor
File: `data/maps/SSAnne_2F_Corridor_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_SS_ANNE_*`
- _GAP - RivalIntro, RivalPostBattle._

## 4. Pokemon Tower 2F - Lavender
File: `data/maps/PokemonTower_2F_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_POKEMON_TOWER_*`
- _GAP - RivalIntro, RivalPostBattle._

## 5. Silph Co. 7F - Saffron
File: `data/maps/SilphCo_7F_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_SILPH_*`
- _GAP - RivalWhatKeptYou, RivalIntro, RivalPostBattle._

## 6. Route 22 - rematch (Earth Badge, before Victory Road)
File: `data/maps/Route22_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_ROUTE22_LATE_*`
- _GAP - LateRivalIntro, LateRivalPostBattle, LateRivalVictory (untranslated in repo)._

## 7. Champion - Indigo Plateau (the final battle)
File: `data/maps/PokemonLeague_ChampionsRoom_Frlg/scripts.inc`
- _GAP - Intro, RematchIntro, Victory (untranslated in repo), PostBattle._

## POST-GAME. Oak's Lab - National Dex upgrade (NOT an intro beat)
File: `data/maps/PalletTown_ProfessorOaksLab_Frlg/scripts.inc`
(`EventScript_NationalDexScene`, map scene 7; runs `special EnableNationalPokedex`.)
Triggered after becoming Champion + 60 species seen, when you return to Oak; opens
the Sevii Islands ("ONE ISLAND first"). The rival is present for it.
- **RivalJustLetMeHandleEverything:** _GAP - still to write._
- **RivalIllCompleteThePokedex:** _GAP - still to write._

---

## Mechanical notes (scaffolding, not character direction)
- Battle text is STARTER-AGNOSTIC: the same Buhrito lines show no matter which
  starter the player took; only his TEAM swaps (3 trainer constants per fight).
  Heads-up on the Oak's Lab Bulbasaur lines: in the vanilla beat order he hypes a
  Pokemon BEFORE anyone picks, then at RivalIllTakeThisOneThen he grabs whatever
  counters YOUR choice. So if the player takes Bulbasaur, his earlier "give me
  bulbasaur" reads as you-took-my-pick (works fine), but he won't literally end up
  with Bulbasaur. Not a problem to fix now, just flagging how the beat resolves.
- Untranslated placeholders in the repo (need SOME English regardless of voice):
  the rival-WINS lines (Route 22 early/late, Champion) + RivalShouldCatchSomeMons.
- Catchphrase slot: vanilla ends most beats with "Smell ya later!" - open for a
  Buhrito signature sign-off if you want one.
