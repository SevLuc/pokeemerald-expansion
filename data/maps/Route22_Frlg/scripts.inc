Route22_Frlg_MapScripts::
	.byte 0

Route22_EventScript_EarlyRivalTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRival::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_ROUTE22_RIVAL
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_EarlyRivalApproach
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_EarlyRivalApproach
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_EarlyRivalApproachBottom
	delay 6
	goto_if_eq VAR_RIVAL_ID, RIVAL_ID_TWITCH, Route22_EventScript_EarlyRivalTwitch
	msgbox Route22_Text_EarlyRivalIntro
	call_if_eq VAR_STARTER_MON, 2, Route22_EventScript_EarlyRivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, Route22_EventScript_EarlyRivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, Route22_EventScript_EarlyRivalCharmander
	msgbox Route22_Text_EarlyRivalPostBattle
Route22_EventScript_EarlyRivalDepart::
	closemessage
	delay 10
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_EarlyRivalExit
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_EarlyRivalExit
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_EarlyRivalExitBottom
	fadedefaultbgm
	removeobject LOCALID_ROUTE22_RIVAL
	setvar VAR_MAP_SCENE_ROUTE22, 2
	releaseall
	end

Route22_EventScript_EarlyRivalApproach::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproach
	waitmovement 0
	return

Route22_EventScript_EarlyRivalApproachBottom::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproachBottom
	applymovement LOCALID_PLAYER, Route22_Movement_PlayerFaceRival
	waitmovement 0
	return

Route22_EventScript_EarlyRivalSquirtle::
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalBulbasaur::
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalCharmander::
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalTwitch::
	msgbox Route22_Text_TwitchEarlyRivalIntro
	trainerbattle_earlyrival TRAINER_RIVAL_TWITCH_ROUTE22_EARLY, 0, Route22_Text_TwitchEarlyRivalDefeat, Text_RivalVictory
	msgbox Route22_Text_TwitchEarlyRivalPostBattle
	goto Route22_EventScript_EarlyRivalDepart

Route22_EventScript_EarlyRivalExit::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_EarlyRivalExit
	waitmovement 0
	return

Route22_EventScript_EarlyRivalExitBottom::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_EarlyRivalExitBottom
	waitmovement 0
	return

Route22_Movement_UnusedRivalExit:: @ 8
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_EarlyRivalExit::
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route22_Movement_EarlyRivalExitBottom::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route22_Movement_RivalApproach::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_RivalApproachBottom::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_down
	step_end

Route22_Movement_PlayerFaceRival::
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_up
	step_end

Route22_EventScript_LateRivalTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_ROUTE22_RIVAL, 25, 5
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRival::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_ROUTE22_RIVAL
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_LateRivalApproach
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_LateRivalApproach
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_LateRivalApproachBottom
	setvar VAR_LAST_TALKED, LOCALID_ROUTE22_RIVAL
	goto_if_eq VAR_RIVAL_ID, RIVAL_ID_TWITCH, Route22_EventScript_LateRivalTwitch
	msgbox Route22_Text_LateRivalIntro
	call_if_eq VAR_STARTER_MON, 2, Route22_EventScript_LateRivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, Route22_EventScript_LateRivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, Route22_EventScript_LateRivalCharmander
	msgbox Route22_Text_LateRivalPostBattle
Route22_EventScript_LateRivalDepart::
	closemessage
	delay 10
	playbgm MUS_RG_RIVAL_EXIT, 0
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_LateRivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_ROUTE22_RIVAL
	setvar VAR_MAP_SCENE_ROUTE22, 4
	releaseall
	end

Route22_EventScript_LateRivalApproach::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproach
	waitmovement 0
	return

Route22_EventScript_LateRivalApproachBottom::
	applymovement LOCALID_ROUTE22_RIVAL, Route22_Movement_RivalApproachBottom
	applymovement LOCALID_PLAYER, Route22_Movement_PlayerFaceRival
	waitmovement 0
	return

Route22_EventScript_LateRivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LateRivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LateRivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LateRivalTwitch::
	msgbox Route22_Text_TwitchLateRivalIntro
	trainerbattle_no_intro TRAINER_RIVAL_TWITCH_ROUTE22_LATE, Route22_Text_TwitchLateRivalDefeat
	msgbox Route22_Text_TwitchLateRivalPostBattle
	goto Route22_EventScript_LateRivalDepart

Route22_Movement_LateRivalExit::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route22_EventScript_LeagueGateSign::
	msgbox Route22_Text_LeagueGateSign, MSGBOX_SIGN
	end

Route22_Text_EarlyRivalIntro::
	.string "Yo what's up {PLAYER},\n"
	.string "oh this is a battle?\p"
	.string "what is the level cap\n"
	.string "right now? …\p"
	.string "And how this pre status\n"
	.string "thing works.\p"
	.string "bro why am I playing this\n"
	.string "game blind?$"

Route22_Text_EarlyRivalDefeat::
	.string "wait I preslept an insomnia\n"
	.string "guy!? whats going on man??$"

Route22_Text_EarlyRivalPostBattle::
	.string "Huh!?? bro what is the\n"
	.string "point of pre status,\p"
	.string "why is this in my game?\p"
	.string "what is the point of being\n"
	.string "preslept…\p"
	.string "if your just sleeping?\p"
	.string "Alright I botted out, its\n"
	.string "all good though.\p"
	.string "Time to start over!\n"
	.string "Peaceeee!$"

Route22_Text_TwitchEarlyRivalIntro::
	.string "YO {PLAYER}. our bird evolved.\n"
	.string "it is BIRD JESUS now.\p"
	.string "it is technically still a\n"
	.string "Pidgey. same thing.\p"
	.string "same energy. PRAISE BIRD JESUS.\p"
	.string "is this a battle?\n"
	.string "it is now.$"

Route22_Text_TwitchEarlyRivalDefeat::
	.string "we got democracy'd. somebody\n"
	.string "voted to lose and that was\l"
	.string "the vote.\p"
	.string "input lag.\n"
	.string "we did that ON PURPOSE.$"

Route22_Text_TwitchEarlyRivalPostBattle::
	.string "free heal, thank you. blacking\n"
	.string "out warps us to the center,\l"
	.string "so that is not a loss.\p"
	.string "that is TECH. START9.\n"
	.string "we go next. CHECK THE LEDGE.$"

@ Translated in RB as "{RIVAL}: What? Why do I have 2 POKéMON? You should catch some more too!"
Route22_Text_RivalShouldCatchSomeMons::
	.string "{RIVAL}“なんだ？\n"
	.string "ポケモン　2ひきも\l"
	.string "もってるの　なぜか　だって？\p"
	.string "おまえも\n"
	.string "つかまえれば　いい　じゃん！$"

Route22_Text_LateRivalIntro::
	.string "Yo {PLAYER}?? no wayyy you\n"
	.string "actually made it to\l"
	.string "the endgame.\p"
	.string "you got all 8 too?\n"
	.string "ok ok.\p"
	.string "aight run me one real\n"
	.string "quick, im just warming up\p"
	.string "before I go deathless\n"
	.string "E4 baby.\p"
	.string "lets gooo!$"

Route22_Text_LateRivalDefeat::
	.string "bro that was literally a\n"
	.string "warmup match, doesnt count.\p"
	.string "I dont even have any\n"
	.string "pokeballs.$"

Route22_Text_LateRivalPostBattle::
	.string "bro I dont even know what\n"
	.string "the e4 is but there must\l"
	.string "be some.\p"
	.string "But Im running it back\n"
	.string "right now.\p"
	.string "Infinite mental.\p"
	.string "I N F I N I T E   S U P A G U Y S$"

Route22_Text_TwitchLateRivalIntro::
	.string "no way. you made it to the\n"
	.string "endgame? you got all 8?\p"
	.string "okay, big news first.\n"
	.string "LORD HELIX HAS RISEN.\p"
	.string "our fossil is a GOD now. bow.\p"
	.string "second news: we are running\n"
	.string "the E4 deathless.\p"
	.string "best nuzlocker in the world.\n"
	.string "probably. warm up with us.$"

Route22_Text_TwitchLateRivalDefeat::
	.string "warmup match, does not count.\p"
	.string "we do not even run items.\n"
	.string "no items, that is the run.\p"
	.string "remember? we said that.\n"
	.string "it is a rule now.$"

Route22_Text_TwitchLateRivalPostBattle::
	.string "we do not tilt. we iterate.\p"
	.string "ten thousand of us, ten\n"
	.string "thousand attempts. run it back.\p"
	.string "see you at the top, {PLAYER}.\n"
	.string "GG go next.$"

@ Translated in RB as "{RIVAL}: Hahaha! {PLAYER}! That's your best? You're nowhere near as good as me, pal! Go train some more! You loser!"
Route22_Text_LateRivalVictory::
	.string "{RIVAL}“ひゃははッ　{PLAYER}ー！\n"
	.string "それで　がんばってるのかよ！\l"
	.string "おれの　さいのうに　くらべりゃ\l"
	.string "{PLAYER}は　まだまだ　だな！\p"
	.string "もっと　れんしゅう　こいよ！\n"
	.string "あははーッ！$"

Route22_Text_LeagueGateSign::
	.string "POKéMON LEAGUE\n"
	.string "Front Gate$"

