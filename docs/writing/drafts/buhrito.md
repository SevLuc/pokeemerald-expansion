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

## Character core (derived from the dialogue written so far)

**Buhrito** - streamer / online-gamer handle. [FLAG: release-swap] [FLAG: dated]

**One line:** the backseat theorist who knows everything ABOUT Pokemon and has
never actually played it.

**The engine (silly-through-contrast):** all theory, no practice. He absorbed the
entire competitive meta second-hand (tier talk, "broken" mons, "the tech") from
streams and chat, but has genuinely never touched the game. So he is at once the
most and least knowledgeable guy in the room: he can tell you Bulbasaur "cooks on
Brock and Misty," yet he forgets he is in a battle, is baffled that status sticks
around, and expected different starters. Armchair analyst brain meets a
single-player RPG he does not understand.
- Knows the tier list, not the game: "I literally never played this game" vs
  "Bulbasaur is broken because he cooks on brock and he cooks on misty" / "that's
  the tech."
- Learned Pokemon as a competitive ladder, not a world: "what is the level cap
  right now?... how this pre status thing works... why am I playing this game blind?"
- The game surprises the theory: "the starters are different..."

**How he sees the world:** as a game client, not a place. He speaks in
Showdown/ladder terms ("level cap," "pre status," "preslept," "misclicked,"
"botted out," "start over"). NPC kindness reads as a scam: the Cerulean trade guy
is "trying to hit a lick on me." Wholesome mechanics look like grifts to a ladder
grinder.

**Losing:** never his fault, never a big deal. Every loss is a technicality he
waves off: "I misclicked," "You just lucked out" energy, "I preslept an insomnia
guy!?" (blames a mechanic he did not know), "its all good though. Time to start
over!" He reboots the run like a roguelike instead of taking the L.

**Attention span:** goldfish. He keeps forgetting the battle is happening
mid-sentence: "oh this is a battle?", "Oh... I forgot this was a fight... we good
though!" Low stakes, high chill.

**Voice + tics:** lowercase, breathless, friendly. "Yo," "bro," "what's good /
whats poppin," "we good though," "bet," "Let's gooo," "Peaceeee." Meta jargon
dropped casually mid-chatter. Signs off chill, not with a taunt (contrast with
vanilla's "Smell ya later!").

**Contrast with vanilla Gary:** vanilla is arrogant about ACHIEVEMENTS (dex,
badges) and tries hard. Buhrito is arrogant about KNOWLEDGE while winning by
accident, and barely notices he is playing.

**Arc fit (plot fixed; tone is the user's):** the skeleton is locked - he climbs to
Champion, then Oak calls him out for neglecting the bond with his Pokemon. This
voice sets that up on its own: a guy who treats mons as meta picks and the whole
game as content to react to is exactly the guy who "forgot to treat his POKéMON
with love and trust." How hard that lands, and whether he grows, stays your call.

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
- **EarlyRivalIntro (pre-battle):** `Yo what's up {Player}, oh this is a battle? what is the level cap right now? ... And how this pre status thing works. bro why am I playing this game blind?`
- **EarlyRivalDefeat (you win):** `wait I preslept an insomnia guy!? whats going on man??`
- **EarlyRivalPostBattle (after you win):** `Huh!?? bro what is the point of pre status, why is this in my game? what is the point of being preslept... if your just sleeping? Alright I botted out, its all good though. Time to start over! Peaceeee!`
- **Lose = shared Text_RivalVictory** (optional Buhrito-specific gloat, else reuse).
- Note: vanilla EarlyRivalDefeat/PostBattle carry NO "{RIVAL}:" speaker tag; the
  "Rival:" you prefixed is just marking the speaker. Tag handled at wiring time.
- NOTE: Route22_Text_RivalShouldCatchSomeMons is a DEAD string (defined, never
  called in FRLG; leftover from RGB). Not on the worklist unless you revive it.

## 2. Cerulean City - after the robbed house
File: `data/maps/CeruleanCity_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_CERULEAN_*`
5-beat scene. No lose-line (no_intro battle). Two functional hooks noted below.
- **RivalIntro (pre-battle):** `Yo{Player} whats poppin? you talked to the old guy in the house next to the pokecenter? proposing a trade RALTS for Lickytung? this guy is trying to hit a lick on me Oh... I forgot this was a fight... we good though!`
- **RivalDefeat (you win):** `Wait wait wait wait wait I misclicked.`
- **RivalPostBattle (after you win):** `Oh yo, real quick, go find the Bill guy up north. He just shows you his rare mons for free, absolute cinema. Watch out though, even with my goated movement I ran into some demon optionals. Aight, Peaceeee!`
  _(HOOK preserved: "go find the Bill guy up north" nudges to Route 25 / Sea Cottage;
  "demon optionals" = the Nugget Bridge / Route 24-25 optional-trainer gauntlet.)_
- **OhRightLittlePresentAsFavor:** `Oh wait, hold up. Ngl I kinda feel bad, you're playing this thing totally blind. Here, take this, on me.`
  _(HOOK preserved: "here, take this" -> `giveitem ITEM_FAME_CHECKER` fires next.)_
- **ExplainFameCheckerSmellYa:** `It's basically the wiki, pulls up intel on all the big-name trainers. I don't need it, I got the whole meta memorized already. You a bum though... Aight, for real this time. Peaceeee!`
  _(Buhrito-ized; replaces the earlier generic coy line. Keeps the item's real
  function - intel on famous trainers - and swaps "Smell ya!" for "Peaceeee!")_

## 3. S.S. Anne - 2F corridor
File: `data/maps/SSAnne_2F_Corridor_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_SS_ANNE_*`
3-beat scene, no lose-line (no_intro). Fancy cruise ship (vanilla opens "Bonjour!").
- **RivalIntro (pre-battle):** `Yooo whats good my guy? You got past the gauntlet too?? You are him bro! Thats some good calculations with the dome piece! .... a fight? alright betski, I accidentally edged my pokemon, now I got to use the homeless version of my team`
- **RivalDefeat (you win):** `W fight`
- **RivalPostBattle (after you win):** `Oh yo, theres a CUT master on this boat, so CUT in. Do I actually need to teach a guy CUT? Like come on bro. Alright we are outta here!`
  _(HOOK preserved: nudges to the Captain / HM01 CUT. SURGE-safe: no seasick/old-man.
  QoL claim is ACCURATE: OW_HMS_USABLE_WITHOUT_LEARNING TRUE in overworld.h - field
  HMs usable from the bag with badge + HM, no party mon needs to learn them.)_
- Dead string: SSAnne_2F_Corridor_Text_RivalVictory (Japanese, unreferenced). Off worklist.

## 4. Pokemon Tower 2F - Lavender
File: `data/maps/PokemonTower_2F_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_POKEMON_TOWER_*`
3-beat scene, no lose-line (no_intro). Spooky graveyard tower; vanilla opens with the
blunt "Is your POKeMON dead?" dark-humor line. No plot hook (pure fight).
Buhrito reflavor: he's stuck on the TEA gate (the Saffron gate guards; TEA is the
FRLG key item that lets you into Saffron). Ties into the forced route (Saffron/Silph
is gated later). TEA source: CeladonCity_Condominiums_1F (the "Celadon Mansion" old
lady); consumed at the Route 5/6/7/8 Saffron gate guards.
- **RivalIntro (pre-battle):** `{PLAYER}! Yo where's the TEA bro? How do I get the TEA? you got TEA?`
- **RivalDefeat (you win):** `If I was tea... where would I be?`
- **RivalPostBattle (after you win):** `Wait really? Old lady in the mansion? Oh Cinnabar Island!!`
  _(CONSISTENCY FLAG: the TEA old lady is in the CELADON Condominiums, NOT Cinnabar.
  "Oh Cinnabar Island!!" is geographically wrong. PENDING: intentional Buhrito
  wrong-guess gag (in-character, keep) vs. slip (fix to Celadon).)_

## 5. Silph Co. 7F - Saffron
File: `data/maps/SilphCo_7F_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_SILPH_*`
4-beat scene, no lose-line (no_intro). Rocket-occupied Silph, right before Giovanni.
Forced-route position: AFTER Koga (5 badges, cap ~33).
- **RivalWhatKeptYou (walk-up opener):** `tea speedrun WR` _(callback to the Pokemon Tower TEA gate)_
- **RivalIntro (pre-battle):** `So this is a fight? ... I hope I have 6 mons in my party... Its all good though they dont know I got fart lead on deck.`
- **RivalDefeat (you win):** `okay we're trolling, what was I cooking...?`
- **RivalPostBattle (after you win):** `Giovanni? Giovanni is not a thread bro. Honestly bro, I prepped for like... 2 minutes. Get his bum ass`
  _(Naming Giovanni here is fine/in-character meta-knowledge; canon-safe because it names
  the Rocket boss only, not the protected boss=Viridian-leader reveal.)_

## 6. Route 22 - rematch (all 8 badges, before Victory Road / League gate)
File: `data/maps/Route22_Frlg/scripts.inc` · Battle: `TRAINER_RIVAL_ROUTE22_LATE_*`
3-beat scene, no lose-line (no_intro). Last fight before the League; both of you have
all badges; he frames it as a "warm-up." High cap (~58 before Champion).
- **LateRivalIntro (pre-battle):** `Yo {PLAYER}?? no wayyy you actually made it to the endgame. you got all 8 too? ok ok. aight run me one real quick, im just warming up before I go deathless E4 baby. lets gooo!`
- **LateRivalDefeat (you win):** `bro that was literally a warmup match, doesnt count. I dont even have any pokeballs.`
- **LateRivalPostBattle (after you win):** `bro I dont even know what the e4 is but there must be some. But Im running it back right now. Infinite mental. I N F I N I T E   S U P A G U Y S`
- Dead string: Route22_Text_LateRivalVictory (Japanese, unreferenced). Off worklist.

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
