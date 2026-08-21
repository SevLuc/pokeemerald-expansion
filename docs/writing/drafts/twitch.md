# Twitch - rival voice (WORKING DRAFT)

> Rival: **Twitch** (one of the two forced picks; the other is Buhrito).
> Concept: the personification of **Twitch Plays Pokemon** chat. A hive-mind mob
> crammed into one trainer body, blurting the dumbest lines of chat lingo, arguing
> with itself, worshipping a fossil, and celebrating its own disasters as wins.
> Character direction is the USER's; this file HOLDS the research, the era arc, and
> a candidate line pool. Final dialogue is the user's to lock (same as Buhrito).
>
> Status: research + scaffold stage. The per-beat dialogue is GAP / candidate-only.
> Nothing here is in-game yet. Anything can change.
>
> Scaffold + vanilla baseline to fork from: drafts/rival-encounters.md
> Sibling voice doc (structure to match): drafts/buhrito.md
> Plumbing: each beat branches on VAR_RIVAL_ID to this Twitch variant.
> RULES that still apply to every line: no em dashes; short gen-3 pages.

---

## Character core (design direction, user owns the final voice)

**Twitch** - Twitch Plays Pokemon chat, personified. [FLAG: release-swap] [FLAG: dated]

**One line:** a screaming crowd of ten thousand people jammed into one trainer,
who wins by accident, worships a fossil, and speaks only in chat spam.

**The engine (silly-through-contrast):** Buhrito is one guy who knows everything
and never plays. Twitch is the opposite failure mode: a MOB that plays constantly
and agrees on nothing. It is never one voice. It is a pile of contradictory inputs
("UP" "no LEFT" "START9") shouted at once, so it fumbles trivial things and then
stumbles into greatness through sheer numbers. The contrast that carries it:
maximum chaos versus the player's single clear will. It cannot form one intention,
yet it beat the game. A thousand monkeys with a Game Boy.

- Speaks as a crowd, never "I", always "we / chat": "we got this", "chat is this
  real", "we did it" (after fumbling something trivial).
- Internal civil war is its core tension: **ANARCHY vs DEMOCRACY**. It interrupts
  itself, votes on its own sentences, sabotages its own menu with Start9.
- Worships by accident: the Helix religion. It keeps "consulting the Helix" mid
  fight, praising Bird Jesus, damning the Dome as the false prophet.
- Competence is emergent, never intended. It does not strategize; it swarms.
- Celebrates disaster: a blackout is "a free heal", a released Pokemon is lore,
  walking into a ledge for an hour is content.

**The evolution arc (the hook the user asked for):** Twitch's LANGUAGE evolves over
the run, mapped onto Pokemon evolution. It boots up in **2014 TPP dialect** (Helix
religion, Start9, anarchy vs democracy, the ledge, Bloody Sunday) for the first
three encounters, then "evolves" into **modern Pokemon-Twitch dialect** (F IN CHAT,
HAXED, "that's the run", "not the ace", nuzlocke and backseat spam) for the
rest, exactly as its team evolves
from a lone Charmeleon into the famous six. The shift can be lampshaded in-character
("we evolved"). It is the same joke as a mon leveling up: the creature grows, and so
does the slang.
- Encounters 0-2 (Oak's Lab, Route 22 early, Cerulean) = **2014 era**.
- Encounters 3-7 (S.S. Anne, Tower, Silph, Route 22 late, Champion) = **modern era**.
- The tonal pivot sits on the mid-game evolution wave (Pidgeotto -> Pidgeot, etc.).

**Losing:** never registers as a loss. It reframes every blackout the way the real
mob did: getting beaten warps you to a Pokemon Center, so a loss is "a free heal",
"we did that on purpose", "we got democracy'd", "mods rigged it", "input lag". The
real run literally lost to Blue on purpose to skip the Viridian ledge; that energy
is the whole personality. Losses are a mechanic, not a defeat.

**Voice + tics:** ALL-CAPS bursts, overlapping contradictory commands, religious
chanting, emote-words as punctuation, third-person-plural. Never a clean sentence;
always sounds like several people typing over each other. Signs off with a chant or
an emote spam, not a taunt (contrast with vanilla's "Smell ya later!").

**Contrast with vanilla Gary:** vanilla is a single smug boy chasing badges and dex
completion. Twitch is a formless crowd that cannot even agree to walk forward, and
wins anyway. Gary is ego; Twitch is chaos.

**Contrast with Buhrito (the other rival):** Buhrito = all theory, no practice, one
know-it-all who never touched the game. Twitch = all practice, no theory, ten
thousand people mashing buttons who never think. Two opposite ways to be bad at
Pokemon and win regardless.

**Arc fit (plot fixed; tone is the user's):** the skeleton is locked. The rival
climbs to Champion, then Oak calls him out for neglecting the bond with his Pokemon.
Twitch fits this cleanly: a mob that treats its mons as memes and mascots (Bird
Jesus, Lord Helix), releases beloved teammates by accident, and never forms a real
bond with any single Pokemon because it is not a single person. Oak's "love and
trust" capstone lands hard OR bounces off, user's call, same as Buhrito.

---

## Battle AI (design note, needs sign-off, touches trainers.party / balance)

To mimic chat, Twitch's trainers should NOT run the global smart-AI flags this hack
plans elsewhere. Deliberate exception:
- Leave the AI flags empty (or minimal) on every `TRAINER_RIVAL_*` Twitch variant so
  move choice is effectively **random**. That is the "anarchy input" feel: it may
  pick a bad move, spam status, or switch for no reason.
- Optionally add a switch-happy behavior so it swaps mons chaotically, like the mob
  fighting over which Pokemon to send out.
- BALANCE FLAG: random AI makes this fight EASIER than a smart-AI rival. That is a
  deliberate difficulty dip for comedy. Confirm it is acceptable against the
  hard-but-fair goal before wiring. Levels still follow the level caps; only the
  decision quality is dumbed down.
- This is a design proposal only. No trainers.party or AI flag has been edited.

---

## Per-battle team (TPP-authentic, proposed for the hack)

Proposal: instead of vanilla Gary's team, Twitch **fields the real TPP Red roster**,
evolving across the run exactly as it did in the 2014 stream. The team grows from a
lone Charmeleon into the famous six, reinforcing the evolution arc. Species are
authentic; LEVELS get set to this hack's caps at wiring time.

Research note: the real run had **7 rival fights, not 8**. TPP skipped the optional
first Route 22 battle. The hack keeps all 8 beats, so Route 22 early below is given
an era-correct team STATE even though it was never fought on stream. Exact per-fight
6-slot rosters were never logged; team STATE is reconstructed from catch / evolution
/ release timestamps and is reliable directionally. Any specific level is [UNCERTAIN].

| # | Hack beat | Era | TPP-authentic team state | Real result on stream |
|---|---|---|---|---|
| 0 | Oak's Lab (starter) | 2014 | **Abby** the Charmander, ~Lv5 (the starter). | WON |
| 1 | Route 22 early | 2014 | Abby (Charmeleon) + **Bird Jesus** (Pidgey). | NOT FOUGHT (skipped) |
| 2 | Cerulean / Nugget Bridge | 2014 | Abby (Charmeleon) + Bird Jesus (Pidgey to Pidgeotto). | Lost once, then WON |
| 3 | S.S. Anne | modern | Abby (Charmeleon), Bird Jesus (Pidgeotto), **Jay Leno** + **Digrat** (Rattata), **The Keeper** (Drowzee), **Dux** (Spearow). | Lost once, then WON |
| 4 | Pokemon Tower, Lavender | modern | Bird Jesus (Pidgeot), Digrat (Raticate, "BigDig"), The Keeper, **Cabbage** (Gloom). Abby + Jay Leno already released. | WON (clean) |
| 5 | Silph Co., Saffron | modern | Bird Jesus (Pidgeot, Lv50), **ATV** (Venomoth), Digrat, Cabbage. Air Jordan the Lapras joined 4 min later. | WON |
| 6 | Route 22 late | modern | Bird Jesus (Pidgeot), ATV, **Air Jordan** (Lapras), **King Fonz** (Nidoking), **AA-j** (Zapdos), **Lord Helix** (Omanyte to Omastar). | Lost ON PURPOSE, then WON |
| 7 | Champion, Indigo Plateau | modern | The canonical six (below). | LOST the first reach, WON the run on the retry |

**Canonical final six** (the Champion team, confirmed across sources):

| Nickname | Species | Notes |
|---|---|---|
| **Lord Helix** | Omastar | The worshipped Helix Fossil, revived and evolved. "God." |
| **Bird Jesus** | Pidgeot | The messiah. Pidgey to Pidgeot; first mon to Lv50; learned Sky Attack. |
| **AA-j** / Battery Jesus | Zapdos | Master Ball catch. Landed the final Thunder that won the run. |
| **Air Jordan** | Lapras | The Silph Co. gift Lapras. The "surf slave" of the Eevee-vs-Lapras war. |
| **ATV** (All Terrain Venomoth) | Venomoth | Beat Lance's Dragonite -> "Dragonslayer". Lone survivor of the first E4 loss. |
| **King Fonz** | Nidoking | Safari Zone Nidoran + Moon Stone. Reliable late-game hitter. |

**Blue's TPP Champion team, for trivia** (chat nicknamed his Pidgeot "Bird Judas" to
mirror Bird Jesus): Pidgeot, Alakazam, Rhydon, Arcanine, Exeggutor, Blastoise.

**Corrections baked in (do not reintroduce):** there was NO disobedient Charizard in
TPP Red (the starter Abby only reached Charmeleon and was released Day 4); no
Nidoqueen (only King Fonz the Nidoking); "Big Bertha" is not a TPP Red mon.

---

## Who's-who (for writing the blurts)

- **Bird Jesus** (Pidgeot) - the hero/messiah, "sent by Lord Helix to guide Red".
- **Lord Helix** (Omastar) - the Helix Fossil the mob accidentally worshipped after
  Red kept opening the Bag onto it mid-battle. Spawned the whole religion. "God."
- **The Dome** - the rival Dome Fossil, cast as the false prophet / Satan.
- **AA-j / Battery Jesus** (Zapdos) - Master Ball legend, endgame firepower.
- **ATV** (Venomoth) - unassuming Safari catch turned Dragonslayer.
- **Air Jordan** (Lapras) - the surf-slave Lapras from the Eevee debate.
- **King Fonz** (Nidoking) - the Safari Nidoran raised on a Moon Stone.
- **Digrat / Jay Leno** (Rattata) - beloved utility rats; martyrs of the PC purge.
- **Abby** (Charmander to Charmeleon) - the STARTER, released Day 4. Never a Charizard.
- **The False Prophet** (Eevee to Flareon) - the Fire-Stoned Eevee blamed for the PC
  disaster; branded a Dome agent. Released Day 6.
- **Bloody Sunday** - the day beloved mons were released by accident at the PC.

---

## Candidate blurt pool (raw material, user picks / rewrites)

Short spammable lines, sorted into the era each beat uses. These are RAW LINGO to
drop into the beats, not locked dialogue. Pull, cut, reorder, rewrite freely. Full
sourced bank is in the two sections after this. No em dashes anywhere.

### 2014 era pool (beats 0-2) - curated best
`PRAISE HELIX` · `CONSULT THE HELIX` · `LORD HELIX HAS RISEN` ·
`THE DOME IS THE FALSE PROPHET` · `PRAISE BIRD JESUS` · `ALL TERRAIN VENOMOTH` ·
`FLAREON THE ABOMINATION` · `NEVER FORGET BLOODY SUNDAY` · `PRESS B TO PRAY` ·
`START9` · `DEMOCRACY IS THE DOME` · `CHECK THE LEDGE` · `WE DID IT`

### Modern era pool (beats 3-7) - Pokemon lingo only
`F IN CHAT` · `RIP [mon]` · `THAT'S THE RUN` · `NOT THE ACE` · `BOX IT` ·
`NICKNAME IT` · `HAXED` · `THAT CRIT` · `FULL PARA` · `SWEEP` · `6-0` · `OHKO` ·
`SUPER EFFECTIVE` · `IT'S 4X` · `USE A POTION` · `PLAY DIFFERENT` · `CATCH IT` ·
`RELEASE IT` · `SEND IT` · `GYM DIFF` · `RUN IT BACK` · `CLIP THAT CRIT`

### Sign-off / loss lines (any era, chat never admits a loss)
`we did that on purpose` · `free heal thanks` · `we got democracy'd` ·
`mods rigged it` · `input lag` · `blame anarchy` · `START9 my beloved`

### Suggested era pivot (lampshade on the mid-game evolution)
Something around S.S. Anne / the Pidgeot wave where Twitch notices its own slang
changing: `wait... we evolved` / `chat looks different now` / `new meta dropped`.

---

## Full rival dialogue (DRAFT, user owns final)

Every beat written out. Voice = the mob: ALL-CAPS bursts, contradictory commands, a
crowd talking over itself, "we / chat" never "I". Each line mixes a heavy-content /
flavored beat (lore, a name, a real scene catchphrase) with a random funny blurt, so
it reads like chat: one smart line, one dumb line, no filter. Era arc: beats 0-2 speak
2014 TPP; the pivot fires on the Cerulean exit; beats 3-7 speak modern Pokemon-stream
plus the streamer scene. Sign-off arc: early it chants `PRAISE HELIX`, modern it says
`GG go next`. Beat labels match the shared scaffold in buhrito.md. Kept clear of the
Buhrito rival's signatures (INFINITE MENTAL, the guys, burrito.exe, 1 death = reset)
so the two rivals never blur. No em dashes. Wiring adds gen-3 breaks (\n \p \l) later.

### 0. Oak's Lab - starter pick + tutorial battle (ERA: 2014)
_What it is:_ Twitch boots up in Oak's Lab, argues with itself over a starter, grabs
the one that counters YOUR pick, and challenges you to the tutorial battle.
_Team here:_ just the starter, **Abby** (the counter-starter, flavored as the Charmander).
- **RivalGrampsIsntAround:** `chat we are LIVE. where is the old man? someone said he is in the grass. START9 START9. do NOT walk into the wall... we walked into the wall.`
- **RivalFedUpWithWaiting:** `just GIVE us a mon. any mon. DEMOCRACY wants the fire one. ANARCHY wants START9. we do not have a plan. we have never had a plan.`
- **RivalNoFairWhatAboutMe:** `we call the little lizard. we name him ABBY. ABBY does NOT get boxed. say it back, chat. PRAISE HELIX.`
- **RivalGoChoosePlayer:** `you pick first, {PLAYER}. do not stress. we already CONSULTED THE HELIX. the fossil knows things.`
- **RivalIllTakeThisOneThen:** `the Helix says take the one that beats YOU. so we take that one. this is not personal. this is scripture.`
- **RivalMyMonLooksTougher:** `our mon is BLESSED. your mon is THE DOME. THE DOME IS THE FALSE PROPHET. no offense.`
- **RivalLetsCheckOutMons (challenge):** `wait, is this a battle? nobody voted for a battle. the Helix wills it though. LETS GO. up up up. that is not a move. LETS GO anyway.`
- **RivalDefeat (you WIN):** `WE DID IT... hold on. we lost? that was input lag. ten thousand of us and somebody pressed B. classic chat.`
- **RivalVictory (you LOSE):** `WE DID IT. PRAISE HELIX. clip that, frame it, put it in the museum. we are him. we are ALL of him.`
- **RivalGoToughenMyMon (leaves):** `we ride out now. do NOT check the ledge. we are begging you, chat, not the ledge... we are checking the ledge. see you there. PRAISE HELIX.`

### 1. Route 22 early - road to the League (ERA: 2014)
_What it is:_ Twitch blocks the road outside Viridian and picks a quick fight. (The
real TPP run skipped this fight; the hack invents it, team stays era-correct.)
_Team here:_ **Abby** (Charmeleon) + **Bird Jesus** (still a Pidgey).
- **EarlyRivalIntro:** `YO {PLAYER}. our bird evolved. it is BIRD JESUS now. it is technically still a Pidgey. same thing. same energy. PRAISE BIRD JESUS. is this a battle? it is now.`
- **EarlyRivalDefeat (you win):** `we got democracy'd. somebody voted to lose and that was the vote. input lag. we did that ON PURPOSE.`
- **EarlyRivalPostBattle:** `free heal, thank you. blacking out warps us to the center, so that is not a loss, that is TECH. START9. we go next. CHECK THE LEDGE.`

### 2. Cerulean City - after the robbed house / Nugget Bridge (ERA: 2014, last old beat)
_What it is:_ Twitch turns up after the Nugget Bridge gauntlet, fights you, then gifts
you the Fame Checker. This beat holds the ERA PIVOT: on the way out, chat "evolves".
_Team here:_ **Abby** (Charmeleon) + **Bird Jesus** (Pidgey to Pidgeotto).
- **RivalIntro:** `yo, you beat the bridge? the whole bridge? okay, okay. do NOT touch the PC. we do not trust the PC. NEVER FORGET BLOODY SUNDAY. also DEMOCRACY IS THE DOME. anyway. fight?`
- **RivalDefeat (you win):** `PRESS B. PRESS B TO PRAY... we pressed A. we ALWAYS press A. it is our curse.`
- **RivalPostBattle (nudge to Bill):** `go north, {PLAYER}. the Bill guy shows you his rare mons for FREE. absolute cinema. tell him the Helix sent you. PRAISE HELIX.`
  _(HOOK preserved: "go find the Bill guy up north" nudges to Route 25 / Sea Cottage.)_
- **OhRightLittlePresentAsFavor (gives Fame Checker):** `oh wait. take this. no reason. the Helix provides. do not try to sell it. we tried. you cannot.`
  _(HOOK preserved: "take this" -> giveitem ITEM_FAME_CHECKER fires next.)_
- **ExplainFameCheckerSmellYa (PIVOT):** `it is basically the wiki. intel on all the big trainers. we memorized every word back in 2014... wait. why does chat look different? the emotes changed. the words changed. we... we EVOLVED. new meta dropped. GG. we go next.`
  _(ERA PIVOT lands here: keeps the item's real function, swaps "Smell ya!" for the
  evolution lampshade that flips Twitch into the modern dialect for the rest of the run.)_

### 3. S.S. Anne - 2F corridor (ERA: modern begins)
_What it is:_ Fancy cruise ship; Twitch stops you in the corridor, fights, then points
you at the Cut master. First beat in the evolved modern dialect.
_Team here:_ **Abby** (Charmeleon), **Bird Jesus** (Pidgeotto), **Jay Leno** + **Digrat** (Rattata), **The Keeper** (Drowzee), **Dux** (Spearow).
- **RivalIntro:** `chat we EVOLVED and we look GREAT. respect the art. you got past the gauntlet too?? DOESHEKNOW. he does not know. fancy boat, fancy us. so this is a fight. bet.`
- **RivalDefeat (you win):** `HAXED. that was a crit. it was a RANGE and we clicked it anyway. we did the math and the math lied to us.`
- **RivalPostBattle (nudge to Cut):** `theres a CUT master on this boat, go get CUT. do we actually need to teach a guy CUT? whatever. we are outta here. GG.`
  _(HOOK preserved: nudges to the Captain / HM01 CUT.)_

### 4. Pokemon Tower, Lavender - the graveyard (ERA: modern)
_What it is:_ Spooky tower full of graves; vanilla opens with the blunt "Is your
POKeMON dead?" Twitch leans all the way into nuzlocke death humor.
_Team here:_ **Bird Jesus** (Pidgeot now), **Digrat** (Raticate, "BigDig"), **The Keeper**, **Cabbage** (Gloom). Abby + Jay Leno already released.
- **RivalIntro:** `is your mon dead? for real? F IN CHAT. this whole tower is THE GRAVEYARD. we know it well. our starter is in a box up there. ABBY is in a box. it is not dead, it is just boxed. forever. anyway. throw hands in a graveyard? sure.`
- **RivalDefeat (you win):** `NOT THE ACE. not the ace... that is the run. pour one out. F. F. one more F. thank you, chat.`
- **RivalPostBattle:** `pants stay brown. we stayed composed. we did NOT wipe. mostly. we go next.`

### 5. Silph Co. 7F - Saffron, before Giovanni (ERA: modern)
_What it is:_ Rocket-occupied Silph; Twitch walks up, fights, then hypes you toward
Giovanni. Right after ATV joins the party.
_Team here:_ **Bird Jesus** (Pidgeot, Lv50), **ATV** (Venomoth), **Digrat**, **Cabbage**.
- **RivalWhatKeptYou (walk-up):** `it is a RANGE. we already did the math. we did the math for like two minutes. good enough.`
- **RivalIntro:** `so this is a fight? we run it the hard way now. first encounter only. faint is death. cap at the ace. NO items. that is the run. probably. do not check the bag.`
- **RivalDefeat (you win):** `HAXED. that is 6-0 the wrong way. we do not tilt. we ITERATE. GG go next.`
- **RivalPostBattle (Giovanni nudge):** `Giovanni? chat already memorized his whole team off the wiki, he is nothing. go take his tower. oh, and that fight just now? you did not really beat us. that was RIGGED. honestly, {PLAYER}, you should delete your save file... it is corrupted.`
  _(Naming Giovanni is fine, it names the Rocket boss only, not the protected Viridian reveal.
  The "corrupted save" sign-off is the mob's cope: losing is never real, the game must be rigged.)_

### 6. Route 22 late - rematch before Victory Road (ERA: modern)
_What it is:_ Both of you have all 8 badges; Twitch frames it as a warm-up before the
League. Story-wise this is where the team hits final form (Omastar evolves).
_Team here:_ near-final six: **Bird Jesus** (Pidgeot), **ATV**, **Air Jordan** (Lapras), **King Fonz** (Nidoking), **AA-j** (Zapdos), **Lord Helix** (Omanyte to Omastar).
- **LateRivalIntro:** `no way. you made it to the endgame? you got all 8? okay, big news first. LORD HELIX HAS RISEN. our fossil is a GOD now. bow. second news: we are running the E4 deathless. best nuzlocker in the world. probably. warm up with us.`
- **LateRivalDefeat (you win):** `warmup match, does not count. we do not even run items. no items, that is the run. remember? we said that. it is a rule now.`
- **LateRivalPostBattle:** `we do not tilt. we iterate. ten thousand of us, ten thousand attempts. run it back. see you at the top, {PLAYER}. GG go next.`

### 7. Champion - Indigo Plateau (ERA: modern peak / capstone)
_What it is:_ Twitch beat the Elite Four first and sits as Champion for the final
battle. After you win, Oak enters for the "love and trust" capstone.
_Team here:_ the canonical six: **Lord Helix** (Omastar), **Bird Jesus** (Pidgeot), **AA-j** (Zapdos), **Air Jordan** (Lapras), **ATV** (Venomoth), **King Fonz** (Nidoking).
- **Text_Intro (Champion speech):** `chat, is this real. we made it. we are the CHAMPION. we cleared the pack. respect the art. one thing before we throw hands... PRAISE HELIX. one more time. for old times. okay. lets go, {PLAYER}.`
- **Text_Defeat (you beat him):** `we lost CONNECTION?? that crit MATTERED. it always mattered. HAXED at the buzzer. no way, chat.`
- **Text_PostBattle (before Oak enters):** `how did we get the title? ten thousand of us mashing ONE gameboy. no single hand on the wheel. no plan. no leader. we never even learned our own team's names. we just... swarmed. and we won. we nuzlock to ball. it is not dead, it is just boxed. we are gonna call it here. thank the Helix we beat this game. GG. go next.`
  _(Sets up Oak's capstone: a MOB never bonded with one Pokemon, so "love and trust"
  lands or bounces, user's call. "ten thousand of us, no single hand, never learned
  our own team's names" is the whole character in one line.)_

### POST-GAME. Oak's Lab - National Dex upgrade (NOT an intro beat)
_What it is:_ After becoming Champion + 60 species seen, returning to Oak triggers the
National Dex + Sevii Islands unlock. Twitch is present. (GAP in buhrito.md; drafted here.)
- **RivalJustLetMeHandleEverything:** `chill, {PLAYER}, we got the dex. we have ten thousand people. we fill it in like a day. somebody is already fishing. do not ask who.`
- **RivalIllCompleteThePokedex:** `national dex? say less. ONE ISLAND first. Sevii speedrun. we go. do NOT check the ledge over there... we are gonna check the ledge over there.`
  _(HOOK preserved: "ONE ISLAND first" opens the Sevii Islands.)_

> DRAFT dialogue, not locked. Every beat is now a startable full line in Twitch's
> voice. Cut, reorder, or rewrite freely; the final voice is yours, same rule as
> buhrito.md.

---

## Lingo bank A - 2014 TPP era (curated best, 14 lines)

Curated to the MOST TELLING lines: each one carries lore, a name, or a behavior
that evokes the whole saga. The bare input-spam (`ababababab`, `UP UP UP`, `DOWN9`,
lone `ANARCHY` / `DEMOCRACY` chants, `NOT THE PC`, duplicate praises) was cut as
filler. Say the word to restore the full spam list for texture.

1. `PRAISE HELIX` - the chant that started a religion.
2. `CONSULT THE HELIX` - asking the fossil what to do, mid-battle.
3. `LORD HELIX HAS RISEN` - the day the fossil god finally evolved.
4. `THE DOME IS THE FALSE PROPHET` - the entire holy war in one line.
5. `PRAISE BIRD JESUS` - the Pidgey that became the team's messiah.
6. `ALL TERRAIN VENOMOTH` - a bug named like a monster truck. Beloved saint.
7. `PRAISE BATTERY JESUS` - Zapdos, the Master Ball legend.
8. `FLAREON THE ABOMINATION` - the traitor mon blamed for the massacre.
9. `NEVER FORGET BLOODY SUNDAY` - the day the mob released its own team.
10. `PRESS B TO PRAY` - do NOT confirm the release. Beg the RNG.
11. `START9` - anarchy loyalists sabotaging their own menu.
12. `DEMOCRACY IS THE DOME` - casting order itself as the enemy.
13. `CHECK THE LEDGE` - the ledge that trapped Red for hours.
14. `WE DID IT` - mock triumph after fumbling something trivial.

## Lingo bank B - modern Pokemon Twitch-chat, 2020s (28 lines)

Modern chat WATCHING POKEMON, not generic emote spam. Nuzlocke, randomizer,
competitive backseating, RNG rage. A few TPP callbacks bridge back to Bucket A.

Nuzlocke / permadeath:
1. `F IN CHAT` - a mon just fainted (permadeath).
2. `RIP` + the nickname - mourning a fallen teammate.
3. `THAT'S THE RUN` - the death that ends the nuzlocke.
4. `NOT THE ACE` - the carry mon is in danger.
5. `BOX IT` - bench it before it dies.
6. `NICKNAME IT` - name the catch so the death hurts more.
7. `FIRST ENCOUNTER ONLY` - the core nuzlocke rule.
8. `DUPES CLAUSE` - skip a species you already caught.
9. `THE GRAVEYARD` - the box full of dead mons.

RNG / hax:
10. `HAXED` - lost to pure luck.
11. `THAT CRIT` - a crit ruined the sweep.
12. `FULL PARA` - paralyzed every single turn.
13. `FROZEN SOLID` - frozen and never thawed.
14. `RNG GODS SAY NO` - blaming the dice.

Competitive / matchup / backseat:
15. `SWEEP` - one mon KOs the whole team.
16. `6-0` - a clean sweep score.
17. `OHKO` - one-hit KO.
18. `WALLED` - can't dent the opposing mon.
19. `SUPER EFFECTIVE` - chat calling the type matchup.
20. `IT'S 4X` - a double weakness, free KO.
21. `USE A POTION` - backseat heal advice.
22. `PLAY DIFFERENT` - backseat; the mob always knows better.

Catch / PC / retry:
23. `CATCH IT` - throw a ball at everything.
24. `RELEASE IT` - dump the mon (dark TPP callback).
25. `SEND IT` - throw the weak mon in anyway.
26. `GYM DIFF` - lost, blame the gym, not the play.
27. `RUN IT BACK` - lost, reset, try again.
28. `CLIP THAT CRIT` - save the highlight.

---

## Lingo bank C - hyperlocal Kaizo / nuzlocke streamer scene (heavily flavored)

The meaty, content-rich lines: full catchphrases and copypasta, not one-word spam.
Sourced from live 7TV/BTTV emote sets, Twitch bios, and real clip/VOD titles. This
bank feeds Twitch's MODERN-era voice: the crowd quoting the whole challenge-streamer
scene. HIGHEST release-swap risk (every line ties to a real, living creator). The
Shared Kaizo toolkit at the bottom is the release-safe subset (genre lingo, no owner).
Confidence: [doc] = documented catchphrase / bio / clip title; [built] = my phrasing
on a real emote or clip hook (the hook is real, the exact wording is yours to adjust).

DESIGN NOTE: "Buhrito" is also the OTHER rival's name (a real streamer whose lines the
existing buhrito.md draft already uses). Keep Buhrito's signature lines with the
Buhrito rival; Twitch can name-drop the scene (incl. Buhrito-as-streamer) meta-style,
but do not let the two rivals share a signature line, or they blur.

### pChal (Jan Krüger) - the analytical tryhard
- `PANTS STAY BROWN` [doc] - THE line. Stay composed, do not wipe. Origin: Emerald
  Kaizo attempt 151, in Steven's room, three mons left.
- `first encounter only. faint is death. cap at the ace. no items. that's the run.` [doc]
  - his codified hardcore ruleset, recited as a mantra.
- `best nuzlocker in the world. probably.` [doc] - self-description, hedge included.
- `151 attempts. I do not tilt, I iterate.` [doc/built] - the real Emerald Kaizo count.
- `I beat the game with ONE Rattata. do not tell me your team is bad.` [doc] - his real
  Rattata-only solo FireRed run.
- `this is not luck. it's a damage range, and I already did the math.` [built] -
  speedrunner-brained persona.

### MANNAT - father of the Drayano Gauntlet
- `Pokemon by trade, disaster by choice.` [doc] - his actual channel bio.
- `welcome back to day 100 of the Drayano Gauntlet, we are NOT free.` [doc] - his
  signature multi-romhack marathon.
- `it's a RANGE. it has ALWAYS been a range. you clicked it anyway.` [built] - Kaizo
  range despair.
- `he hears the crit and goes full mannatDonald, quacking at the screen.` [built on a
  real emote] - the duck-voice tilt.
- `stop YAPPING and click the move, we are on a timer.` [built on real emotes] -
  backseat-vs-streamer banter.

### JackieInternet - the Thinking Man's Nuzlocker
- `respect the art.` [doc] - his literal channel bio. Cold four-word flex.
- `safest gamer in the east. comes and goes like smoke, but always clears the pack.` [doc]
  - grandiose bio blurb, delivered deadpan.
- `the Thinking Man's Nuzlocker does not click that. he boxes it and moves on.` [built]
  - the cerebral-slow-and-safe persona.
- `DOESHEKNOW... he does not know.` [doc emote] - dramatic-irony ambush bit (chat sees
  it coming, the streamer does not).
- `that's not luck, that's a METAPHOR for the whole run.` [built on emote] - a chat that
  over-reads meaning into RNG.

### Buhrito - 1 death = reset (keep signature lines with the Buhrito RIVAL)
- `one death equals reset. that's the rule. always been the rule.` [doc] - his real
  challenge format.
- `INFINITE MENTAL, 8 hours plus, we NEVER back down.` [doc] - documented hype phrases.
- `SUMMONING GUYS... the guys are comin in.` [doc] - the "guys" summon/raid bit.
- `burrito.exe has crashed. please stand by.` [doc clip] - blue-screens under pressure.
- `LET HIM COOK. do not touch him. he is cooking.` [doc emote] - anti-backseat hype.
- `deal... or NO DEAL. box it or send it, chat decides.` [doc emotes] - crowd-sourced
  risky call.

### Ned (NedPT) - the salty Smash main who runs nuzlockes
- `Fearow again. it is ALWAYS Fearow.` [doc] - his documented arch-nemesis (Drill Peck
  plus high Speed is a real nuzlocke killer).
- `the restraining order clearly states Fearow stays 500 feet from my Machop.` [doc] -
  riff on his real "restraining order out against Fearows" bio joke.
- `brother I am a Sephiroth main, I do NOT get outranged.` [persona] - Smash arrogance
  bleeding into a Pokemon range check.
- `Ned can NOT just be happy for her, chat.` [doc clip] - competitive about someone
  else's good luck.
- `up-b angle was FINE, the game is wrong.` [doc clip] - deflect-blame energy.

### Moxi - the aspiring voice actor who fails the reading check
- `hold on, let me do the voice for this Gym Leader real quick.` [persona] - his
  documented aspiring-VA angle. The most original comedic hook of the group.
- `Moxi fails the reading check.` [doc clip] - misreads a move or a battle prompt.
- `he thought he had another turn.` [doc clip] - the classic misplayed-turn gut-punch.
- `Rachi flinch. that is the run, chat.` [doc clip] - Jirachi Serene Grace flinch loop,
  legendary nuzlocke pain.
- `average Ape player behavior.` [doc clip] - monkey-brain misplay self-own.

### Shared Kaizo toolkit (scene-wide, RELEASE-SAFE, not tied to one person)
- `sack it. we go again.` - sacrifice a mon to scout or tank a hit, reset momentum.
- `it's a range, chat.` / `that was a roll.` - damage is not fixed; the hit sat inside
  the possible spread.
- `set mode, no items, caps on. real ones only.` - the hardcore-nuzlocke difficulty stack.
- `dupes clause, so we fish the route again.` - re-search if the first encounter is a
  species you already own.
- `chat stop backseating, he SEES the Sturdy.` - backseating = viewers spamming
  unsolicited advice, a constant tension.
- `GG go next.` - post-wipe acceptance, restart the attempt.
- `it's not dead, it's just boxed. forever.` - permadeath gallows humor.

---

## Release-swap / dated flags

Bucket A (2014 TPP) is fan-community folklore with no single rights-holder. Safe to
keep. Deep-cut lines (Battery Jesus, RIP Digrat/Dux/Jay Leno) only land for people
who know the 2014 run; audience-recognition note, not a legal one.

Bucket B is now Pokemon-community slang (nuzlocke / competitive), NOT brand-owned
emote names, so brand risk is low and most lines are safe to keep. Watch only:
- `F IN CHAT` / `F` - generic enough, but the emote-culture origin is worth a glance.
- Everything else is descriptive Pokemon-community terminology (SWEEP, OHKO, nuzlocke
  rules) with no single rights-holder. Safe.

Bucket C is the HIGHEST swap priority: every named-streamer line ties to a real living
creator (pChal, Mannat, Jackie, Buhrito, Ned, Moxi) and their channel emotes / bios /
clips. Before any public release, swap the streamer names, emote strings, and signature
lines for original equivalents. The Shared Kaizo toolkit at the end of Bank C is the
one release-safe block (genre lingo, no single owner).

Sources: Helixpedia Gen 1 timeline, twitchplayswiki (Bird Jesus / Lord Helix / ATV /
Battery Jesus / Air Jordan / False Prophet pages), Know Your Meme (TPP; L + Ratio),
StreamScheme + Dexerto emote guides.

---

## Mechanical notes (scaffolding, not character direction)

- Battle text is STARTER-AGNOSTIC like Buhrito's: the same Twitch lines show
  regardless of which starter the player took; only the TEAM swaps. Heads-up on the
  Oak's Lab beat: the rival's starter counters the player's pick, so the "Abby the
  Charmander" flavor only literally holds when the player takes Bulbasaur. Flag as a
  soft flavor mismatch, same as Buhrito's Bulbasaur beat; not a blocker.
- Name cap: "Twitch" is 6 chars, fits PLAYER_NAME_LENGTH (7). Fine as-is.
- The per-beat DIALOGUE is still GAP. This doc gives era + team + a candidate pool;
  the user writes and locks the actual lines, then we wire branches on VAR_RIVAL_ID.
- Proposed team roster and random AI are DESIGN PROPOSALS. No trainers.party, AI
  flag, or script has been edited. Both need sign-off (team = balance + build; AI =
  the hard-but-fair difficulty exception).
- [FLAG: release-swap] the whole Twitch concept is a homage; genericize before any
  public release, same as Buhrito.
