# Rival encounters - worksheet (for the epic rival lines)

> Purpose: every RIVAL beat on the FRLG critical path, in story order, with the
> map/file, the trainer battle constants, and the VERBATIM current text. Draft the
> epic per-rival lines against this scaffold.
>
> Implementation note: the parked intro (drafts/intro-and-rival.md) makes the rival a
> FORCED 2-option pick (Buhrito / Twitch) stored in VAR_RIVAL_ID. So each text beat
> below is one BRANCH POINT: today the script does `msgbox <Map>_Text_Rival*`; for
> per-rival personality you branch on VAR_RIVAL_ID to a Buhrito / Twitch variant of
> that string. This file is the shared skeleton + the vanilla baseline to fork.
>
> Battle text is starter-agnostic: the SAME rival lines show regardless of your
> starter; only the rival's TEAM differs, hence three trainer constants per fight
> (…_BULBASAUR / _CHARMANDER / _SQUIRTLE). Write one set of lines per beat.
>
> NEVER em dashes. Gen-3 rhythm (short two-line pages, \p new page, \n 2nd line,
> \l 3rd continued line). Catchphrase to own or replace per rival: "Smell ya later!"

---

## 0. Oak's Lab - naming, starter pick, first battle
File: `data/maps/PalletTown_ProfessorOaksLab_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_OAKS_LAB_{BULBASAUR,CHARMANDER,SQUIRTLE}`
(Rival name is set here via the intro's forced pick; Oak/starter lines are functional
and mostly stay, but the RIVAL lines below are all yours to personalize.)

- **RivalGrampsIsntAround:** `{RIVAL}: What, it's only {PLAYER}? / Gramps isn't around.`
- **RivalFedUpWithWaiting:** `{RIVAL}: Gramps! / I'm fed up with waiting!`
- **RivalNoFairWhatAboutMe:** `{RIVAL}: Hey! Gramps! No fair! / What about me?`
- **RivalGoChoosePlayer:** `{RIVAL}: Heh, I don't need to be greedy like you. I'm mature! / Go ahead and choose, {PLAYER}!`
- **RivalIllTakeThisOneThen:** `{RIVAL}: I'll take this one, then!`
- **RivalMyMonLooksTougher:** `{RIVAL}: My POKéMON looks a lot tougher than yours.`
- **RivalLetsCheckOutMons (battle challenge):** `{RIVAL}: Wait, {PLAYER}! / Let's check out our POKéMON! / Come on, I'll take you on!`
- **RivalDefeat (you win):** `WHAT? / Unbelievable! / I picked the wrong POKéMON!`
- **RivalGoToughenMyMon:** `{RIVAL}: Okay! I'll make my POKéMON battle to toughen it up! / {PLAYER}! Gramps! / Smell you later!`
- **RivalJustLetMeHandleEverything (later, dex charge):** `{RIVAL}: Hey, I heard that! / Gramps, what's with favoring {PLAYER} over me all the time? / I went and collected more POKéMON, and faster, too. / You should just let me handle everything.`
- **RivalIllCompleteThePokedex:** `{RIVAL}: Gramps, calm down. Don't get so excited. / I'll get the POKéDEX completed, don't you worry about a thing. / I think I'll try looking around ONE ISLAND first… / Anyways, I'm outta here!`
- (Oak-side, functional, likely keep: OakThreeMonsChooseOne, OakWhichOneWillYouChoose, OakChoosing{Charmander,Squirtle,Bulbasaur}, OakThisMonIsEnergetic.)

## 1. Route 22 - first battle (before Viridian gate)
File: `data/maps/Route22_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_ROUTE22_EARLY_{BULBASAUR,CHARMANDER,SQUIRTLE}`

- **EarlyRivalIntro:** `{RIVAL}: Hey! {PLAYER}! / You're off to the POKéMON LEAGUE? Forget about it! / You probably don't have any BADGES, do you? / The guard won't let you through without them. / By the way, did your POKéMON get any stronger?`
- **RivalShouldCatchSomeMons:** ⚠️ UNTRANSLATED (Japanese placeholder in repo) - rival's "you have two POKéMON, why not catch some?" line. NEEDS an English line.
- (Early has no unique post-battle text in vanilla; rival just leaves.)

## 2. Cerulean City - after the robbed house
File: `data/maps/CeruleanCity_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_CERULEAN_{BULBASAUR,CHARMANDER,SQUIRTLE}`

- **RivalIntro:** `{RIVAL}: Yo! {PLAYER}! / You're still struggling along back here? / I'm doing great! I caught a bunch of strong and smart POKéMON! / Here, let me see what you caught, {PLAYER}!`
- **RivalPostBattle:** `{RIVAL}: Hey, guess what? / I went to BILL's and got him to show me his rare POKéMON. That added a lot of pages to my POKéDEX! / After all, BILL's world famous as a POKéMANIAC. He invented the POKéMON Storage System on PC, too. / Since you're using his system, you should go thank him. / Well, I better get rolling! Smell ya later!`
- **ExplainFameCheckerSmellYa** (already reflavored by you, coy): `A chatty gossip like you… That thing's perfect. / I don't need it because I don't give a hoot about others. / All right, this time I really am gone. Smell ya!`
- (Note: `ThisIsCeruleanCave` is NOT rival text - it's the guard, already reflavored by you to seed the Mewtwo/"over the sea" thread. Left alone.)

## 3. S.S. Anne - 2F corridor
File: `data/maps/SSAnne_2F_Corridor_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_SS_ANNE_{BULBASAUR,CHARMANDER,SQUIRTLE}`

- **RivalIntro:** `{RIVAL}: Bonjour! {PLAYER}! / Imagine seeing you here! {PLAYER}, were you really invited? / So how's your POKéDEX coming? / I already caught 40 kinds, pal. Different kinds are everywhere. / Crawl around in grassy areas, and look hard for them.`
- **RivalPostBattle:** `{RIVAL}: I heard there was a CUT master on board. But he was just a seasick old man! / CUT itself is really useful. Yup, it'll be handy. / You should go see him, too. Smell ya!`

## 4. Pokémon Tower 2F - Lavender
File: `data/maps/PokemonTower_2F_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_POKEMON_TOWER_{BULBASAUR,CHARMANDER,SQUIRTLE}`

- **RivalIntro:** `{RIVAL}: Hey, {PLAYER}! What brings you here? Is your POKéMON dead? / Hey! It's alive! / I can at least make them faint! Let's go!`
- **RivalPostBattle:** `How's your POKéDEX coming? I just caught a CUBONE! / I can't find the bigger MAROWAK. Where could they be? / I bet there aren't any left! / Well, I better get going. I've got a lot to accomplish, unlike you. / Smell ya later!`

## 5. Silph Co. 7F - Saffron
File: `data/maps/SilphCo_7F_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_SILPH_{BULBASAUR,CHARMANDER,SQUIRTLE}`

- **RivalWhatKeptYou:** `{RIVAL}: What kept you, {PLAYER}?`
- **RivalIntro:** `{RIVAL}: Hahaha! I thought you'd turn up if I waited here! / I guess TEAM ROCKET slowed you down! Not that I care! / I saw you in SAFFRON, so I decided to see if you got better!`
- **RivalPostBattle:** `Well, {PLAYER}! I'm moving on up and ahead! / By checking my POKéDEX, I'm starting to see what's strong and how they evolve! / Am I a genius or what? / I'm going to the POKéMON LEAGUE to boot out the ELITE FOUR. I'll become the world's most powerful TRAINER! / {PLAYER}, well, good luck to you! Don't sweat it! Smell ya!`

## 6. Route 22 - rematch (Earth Badge, before Victory Road)
File: `data/maps/Route22_Frlg/scripts.inc`
Battle: `TRAINER_RIVAL_ROUTE22_LATE_{BULBASAUR,CHARMANDER,SQUIRTLE}`

- **LateRivalIntro:** `{RIVAL}: What? {PLAYER}! What a surprise to see you here! / So you're going to the POKéMON LEAGUE? / You collected all the BADGES, too? That's cool! / Then I'll whip you, {PLAYER}, as a warm-up for the POKéMON LEAGUE! Come on!`
- **LateRivalPostBattle (you win):** `That loosened me up. I'm ready for the POKéMON LEAGUE! / {PLAYER}, you need more practice. / But hey, you know that! I'm out of here. Smell ya!`
- **LateRivalVictory (you lose):** ⚠️ UNTRANSLATED (Japanese placeholder) - his gloat if he beats you. NEEDS an English line.

## 7. Champion - Indigo Plateau (the final battle)
File: `data/maps/PokemonLeague_ChampionsRoom_Frlg/scripts.inc`
Battle: `TRAINER_CHAMPION_{FIRST,REMATCH}_{BULBASAUR,CHARMANDER,SQUIRTLE}` (confirm exact
constants in src/data/trainers_frlg.party)

- **Intro (the big one):** `{RIVAL}: Hey, {PLAYER}! I was looking forward to seeing you, {PLAYER}. / My rival should be strong to keep me sharp. / While working on my POKéDEX, I looked all over for POKéMON. / Not only that, I assembled teams that would beat any POKéMON type. / And now… I'm the POKéMON LEAGUE CHAMPION! / {PLAYER}! Do you know what that means? I'll tell you. / I am the most powerful TRAINER in the world!`
- **RematchIntro:** near-identical ("You came back, {PLAYER}! Hahah, that is so great!" then the same speech).
- **Victory (you lose):** ⚠️ UNTRANSLATED (Japanese placeholder) - his winning gloat. NEEDS an English line.
- **PostBattle (you win):** `Why? Why did I lose? / I never made any mistakes raising my POKéMON… / Darn it! You're the new POKéMON LEAGUE CHAMPION!`

## 8. Post-Champion - Oak arrives (Champion's Room) + Hall of Fame
File: `data/maps/PokemonLeague_ChampionsRoom_Frlg/scripts.inc` then
`data/maps/PokemonLeague_HallOfFame_Frlg/scripts.inc`
(Oak's lines - not the rival - but they FRAME the rival's defeat; the
"I'm disappointed in you" speech is the thematic capstone of the rivalry.)

- **OakPlayer:** `OAK: {PLAYER}!`
- **OakCongratulations:** `OAK: So, you've won! Sincerely, congratulations! / You're the new POKéMON LEAGUE CHAMPION! / You've grown up so much since you first left with {STR_VAR_1} to work on the POKéDEX. / {PLAYER}, you have come of age!`
- **OakImDisappointedRival (the rivalry capstone):** `OAK: {RIVAL}… I'm disappointed in you. / I came when I heard you'd beaten the ELITE FOUR. But, when I got here, you had already lost! / {RIVAL}, do you understand why you lost? / You have forgotten to treat your POKéMON with love and trust. / Without them, you will never become a CHAMP again!`
- **OakPlayerComeWithMe:** `OAK: {PLAYER}. You understand that your victory was not just your own doing. / The bond you share with your POKéMON is marvelous. / {PLAYER}! Come with me!`
- **HallOfFame OakCongratulations:** the Hall of Fame induction (functional; keep).

---

## Cross-cutting notes for the rewrite
- **Catchphrase:** vanilla rival ends nearly every beat with "Smell ya (later)!" Great
  spot to give Buhrito / Twitch each their own signature sign-off.
- **Untranslated placeholders (⚠️):** the "rival WINS" lines are Japanese in this repo
  (Route22 early/late Victory, Champion Victory, RivalShouldCatchSomeMons). These need
  English text regardless of flavor. Flag if you want me to stub clean English first.
- **Already reflavored (leave or build on):** Cerulean's Fame Checker hand-off
  (ExplainFameCheckerSmellYa) and the Cerulean Cave guard (Mewtwo/"over the sea" seed).
- **Arc shape to play with:** vanilla rival = cocky Pokédex-braggart who peaks as
  Champion for five minutes, then Oak calls him out for neglecting the bond. Whatever
  Buhrito / Twitch become, that rise-and-humbling skeleton is fixed by the plot.
- **Per-rival branching:** wiring VAR_RIVAL_ID variants is a small script change per
  beat (Phase 2 in intro-and-rival.md). I can wire the branches once you've written
  the two voices; you write the lines, I do the plumbing.
