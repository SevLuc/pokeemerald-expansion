CeruleanCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_OnTransition
	.byte 0

CeruleanCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CERULEAN_CITY
	call_if_unset FLAG_BADGE02_GET, CeruleanCity_EventScript_BlockRavagedHouse
	call_if_unset FLAG_GOT_SS_TICKET, CeruleanCity_EventScript_BlockExits
	end

@ The policeman stands below the robbed house door, sealing the shortcut
@ until the player earns the CASCADE BADGE from MISTY (was gated on the
@ S.S. TICKET, which comes later, leaving the house needlessly blocked).
CeruleanCity_EventScript_BlockRavagedHouse::
	setobjectxyperm LOCALID_CERULEAN_POLICEMAN, 30, 12
	return

CeruleanCity_EventScript_BlockExits::
	setobjectxyperm LOCALID_CERULEAN_SLOWBRO, 26, 31
	setobjectxyperm LOCALID_CERULEAN_LASS, 27, 31
	return

CeruleanCity_EventScript_RivalTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_RivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_CERULEAN_RIVAL, 23, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_RivalTriggerRight::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_CERULEAN_RIVAL, 24, 0
	goto CeruleanCity_EventScript_Rival
	end

CeruleanCity_EventScript_Rival::
	textcolor NPC_TEXT_COLOR_MALE
	setvar VAR_MAP_SCENE_ROUTE22, 2
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	addobject LOCALID_CERULEAN_RIVAL
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalEnter
	waitmovement 0
	goto_if_eq VAR_RIVAL_ID, RIVAL_ID_TWITCH, CeruleanCity_EventScript_RivalTwitch
	goto_if_eq VAR_RIVAL_ID, RIVAL_ID_LOCKE, CeruleanCity_EventScript_RivalLocke
	msgbox CeruleanCity_Text_RivalIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_RIVAL
	call_if_eq VAR_STARTER_MON, 2, CeruleanCity_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, CeruleanCity_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, CeruleanCity_EventScript_RivalCharmander
	famechecker FAMECHECKER_BILL, 0
	msgbox CeruleanCity_Text_RivalPostBattle
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 1, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 2, CeruleanCity_EventScript_RivalStartExitRight
	msgbox CeruleanCity_Text_OhRightLittlePresentAsFavor
	setvar VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 1
	setflag FLAG_GOT_FAME_CHECKER
	giveitem ITEM_FAME_CHECKER
	msgbox CeruleanCity_Text_ExplainFameCheckerSmellYa
	closemessage
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_CERULEAN_RIVAL
	releaseall
	end

CeruleanCity_EventScript_RivalTwitch::
	msgbox CeruleanCity_Text_TwitchRivalIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_RIVAL
	trainerbattle_no_intro TRAINER_RIVAL_TWITCH_CERULEAN, CeruleanCity_Text_TwitchRivalDefeat
	famechecker FAMECHECKER_BILL, 0
	msgbox CeruleanCity_Text_TwitchRivalPostBattle
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 1, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 2, CeruleanCity_EventScript_RivalStartExitRight
	msgbox CeruleanCity_Text_TwitchOhRightPresent
	setvar VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 1
	setflag FLAG_GOT_FAME_CHECKER
	giveitem ITEM_FAME_CHECKER
	msgbox CeruleanCity_Text_TwitchExplainFameChecker
	closemessage
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_CERULEAN_RIVAL
	releaseall
	end

@ Locke keeps the vanilla per-starter split. The Fame Checker handoff lines
@ (OhRightLittlePresentAsFavor / ExplainFameCheckerSmellYa) stay vanilla.
CeruleanCity_EventScript_RivalLocke::
	msgbox CeruleanCity_Text_LockeRivalIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_RIVAL
	call_if_eq VAR_STARTER_MON, 2, CeruleanCity_EventScript_RivalLockeSquirtle
	call_if_eq VAR_STARTER_MON, 1, CeruleanCity_EventScript_RivalLockeBulbasaur
	call_if_eq VAR_STARTER_MON, 0, CeruleanCity_EventScript_RivalLockeCharmander
	famechecker FAMECHECKER_BILL, 0
	msgbox CeruleanCity_Text_LockeRivalPostBattle
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 1, CeruleanCity_EventScript_RivalStartExit
	call_if_eq VAR_TEMP_1, 2, CeruleanCity_EventScript_RivalStartExitRight
	msgbox CeruleanCity_Text_OhRightLittlePresentAsFavor
	setvar VAR_MAP_SCENE_CERULEAN_CITY_RIVAL, 1
	setflag FLAG_GOT_FAME_CHECKER
	giveitem ITEM_FAME_CHECKER
	msgbox CeruleanCity_Text_ExplainFameCheckerSmellYa
	closemessage
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_CERULEAN_RIVAL
	releaseall
	end

CeruleanCity_EventScript_RivalLockeSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_SQUIRTLE, CeruleanCity_Text_LockeRivalDefeat
	return

CeruleanCity_EventScript_RivalLockeBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_BULBASAUR, CeruleanCity_Text_LockeRivalDefeat
	return

CeruleanCity_EventScript_RivalLockeCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_CHARMANDER, CeruleanCity_Text_LockeRivalDefeat
	return

CeruleanCity_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_SQUIRTLE, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_BULBASAUR, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_CERULEAN_CHARMANDER, CeruleanCity_Text_RivalDefeat
	return

CeruleanCity_EventScript_RivalStartExit::
	applymovement LOCALID_PLAYER, CeruleanCity_Movement_PlayerWatchRivalExit
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalStartExit
	waitmovement 0
	return

CeruleanCity_EventScript_RivalStartExitRight::
	applymovement LOCALID_PLAYER, CeruleanCity_Movement_PlayerWatchRivalExitRight
	applymovement LOCALID_CERULEAN_RIVAL, CeruleanCity_Movement_RivalStartExitRight
	waitmovement 0
	return

CeruleanCity_Movement_PlayerWatchRivalExit::
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_down
	step_end

CeruleanCity_Movement_PlayerWatchRivalExitRight::
	delay_16
	delay_8
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_down
	step_end

CeruleanCity_Movement_RivalEnter::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_Movement_RivalStartExit::
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_RivalStartExitRight::
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	delay_16
	delay_16
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

CeruleanCity_Movement_RivalExit::
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

CeruleanCity_EventScript_Grunt::
	lock
	faceplayer
	goto_if_defeated TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_EventScript_GruntDefeated
	message CeruleanCity_Text_GruntIntro
	waitmessage
	playbgm MUS_RG_ENCOUNTER_ROCKET, 0
	waitbuttonpress
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto CeruleanCity_EventScript_GruntDefeated
	end

CeruleanCity_EventScript_GruntDefeated::
	msgbox CeruleanCity_Text_OkayIllReturnStolenTM
	checkitemspace ITEM_TM28
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_EventScript_NoRoomForTM28
	giveitem_msg CeruleanCity_Text_RecoveredTM28FromGrunt, ITEM_TM28
	msgbox CeruleanCity_Text_BetterGetMovingBye
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_CERULEAN_GRUNT
	fadescreenswapbuffers FADE_FROM_BLACK
	setflag FLAG_GOT_TM28_FROM_ROCKET
	release
	end

CeruleanCity_EventScript_NoRoomForTM28::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CeruleanCity_Text_MakeRoomForThisCantRun
	release
	end

CeruleanCity_EventScript_GruntTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	applymovement LOCALID_CERULEAN_GRUNT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	goto CeruleanCity_EventScript_GruntTrigger
	end

CeruleanCity_EventScript_GruntTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 1
	applymovement LOCALID_CERULEAN_GRUNT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	goto CeruleanCity_EventScript_GruntTrigger
	end

CeruleanCity_EventScript_GruntTrigger::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox CeruleanCity_Text_GruntIntro
	setvar VAR_LAST_TALKED, LOCALID_CERULEAN_GRUNT
	trainerbattle_no_intro TRAINER_TEAM_ROCKET_GRUNT_5, CeruleanCity_Text_GruntDefeat
	setvar VAR_MAP_SCENE_CERULEAN_CITY_ROCKET, 1
	goto CeruleanCity_EventScript_GruntDefeated
	end

CeruleanCity_EventScript_Policeman::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE02_GET, CeruleanCity_EventScript_PolicemanBlocking
	msgbox CeruleanCity_Text_PeopleHereWereRobbed
	closemessage
	applymovement LOCALID_CERULEAN_POLICEMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

@ While the robbed-house shortcut is sealed (pre-CASCADE BADGE), the policeman
@ turns the player back with a PSYDUCK hint they piece together themselves.
CeruleanCity_EventScript_PolicemanBlocking::
	msgbox CeruleanCity_Text_PolicemanPsyduckHint
	closemessage
	applymovement LOCALID_CERULEAN_POLICEMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeruleanCity_EventScript_LittleBoy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SS_TICKET, CeruleanCity_EventScript_LittleBoySlowbroMoved
	msgbox CeruleanCity_Text_IfSlowbroWasntThereCouldCutTree
	release
	end

CeruleanCity_EventScript_LittleBoySlowbroMoved::
	msgbox CeruleanCity_Text_YouCanCutDownSmallTrees
	release
	end

CeruleanCity_EventScript_BaldingMan::
	lock
	faceplayer
	goto_if_set FLAG_BADGE02_GET, CeruleanCity_EventScript_BaldingManPostBadge
	msgbox CeruleanCity_Text_PokemonEncyclopediaAmusing
	release
	end

CeruleanCity_EventScript_BaldingManPostBadge::
	msgbox CeruleanCity_Text_MistyPsyduckHeart
	release
	end

CeruleanCity_EventScript_Youngster::
	msgbox CeruleanCity_Text_TrainerLifeIsToughIsntIt, MSGBOX_NPC
	end

CeruleanCity_EventScript_CeruleanCaveGuard::
	msgbox CeruleanCity_Text_ThisIsCeruleanCave, MSGBOX_NPC
	end

CeruleanCity_EventScript_Woman::
	lock
	faceplayer
	msgbox CeruleanCity_Text_WantBrightRedBicycle
	closemessage
	applymovement LOCALID_CERULEAN_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeruleanCity_EventScript_Lass::
	lock
	random 3
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroCommand1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroCommand2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroCommand3
	waitmessage
	delay 40
	playse SE_PIN
	applymovement LOCALID_CERULEAN_SLOWBRO, Common_Movement_QuestionMark
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroFailed1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroFailed2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroFailed3
	release
	end

CeruleanCity_EventScript_SlowbroCommand1::
	message CeruleanCity_Text_SlowbroUseSonicboom
	return

CeruleanCity_EventScript_SlowbroCommand2::
	message CeruleanCity_Text_SlowbroPunch
	return

CeruleanCity_EventScript_SlowbroCommand3::
	message CeruleanCity_Text_SlowbroWithdraw
	return

CeruleanCity_EventScript_SlowbroFailed1::
	msgbox CeruleanCity_Text_SlowbroPayAttention
	return

CeruleanCity_EventScript_SlowbroFailed2::
	msgbox CeruleanCity_Text_NoYouBlewItAgain
	return

CeruleanCity_EventScript_SlowbroFailed3::
	msgbox CeruleanCity_Text_HardToControlMonsObedience
	return

CeruleanCity_EventScript_Slowbro::
	lock
	random 4
	copyvar VAR_0x8008, VAR_RESULT
	call_if_eq VAR_0x8008, 0, CeruleanCity_EventScript_SlowbroText1
	call_if_eq VAR_0x8008, 1, CeruleanCity_EventScript_SlowbroText2
	call_if_eq VAR_0x8008, 2, CeruleanCity_EventScript_SlowbroText3
	call_if_eq VAR_0x8008, 3, CeruleanCity_EventScript_SlowbroText4
	release
	end

CeruleanCity_EventScript_SlowbroText1::
	msgbox CeruleanCity_Text_SlowbroTookSnooze
	return

CeruleanCity_EventScript_SlowbroText2::
	msgbox CeruleanCity_Text_SlowbroLoafingAround
	return

CeruleanCity_EventScript_SlowbroText3::
	msgbox CeruleanCity_Text_SlowbroTurnedAway
	return

CeruleanCity_EventScript_SlowbroText4::
	msgbox CeruleanCity_Text_SlowbroIgnoredOrders
	return

CeruleanCity_EventScript_CitySign::
	msgbox CeruleanCity_Text_CitySign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_TrainerTips::
	msgbox CeruleanCity_Text_TrainerTipsHeldItems, MSGBOX_SIGN
	end

CeruleanCity_EventScript_BikeShopSign::
	msgbox CeruleanCity_Text_BikeShopSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_MISTY, 0
	msgbox CeruleanCity_Text_GymSign
	releaseall
	end

CeruleanCity_Text_RivalIntro::
	.string "Yo {PLAYER} whats poppin?\p"
	.string "you talked to the old guy\n"
	.string "in the house next to the\l"
	.string "pokecenter?\p"
	.string "proposing a trade RALTS\n"
	.string "for Lickytung?\p"
	.string "this guy is trying to hit\n"
	.string "a lick on me\p"
	.string "Oh… I forgot this was a\n"
	.string "fight…\p"
	.string "we good though!$"

CeruleanCity_Text_RivalDefeat::
	.string "Wait wait wait wait wait\n"
	.string "I misclicked.$"

CeruleanCity_Text_RivalPostBattle::
	.string "Oh yo, real quick,\n"
	.string "go find the Bill guy up\l"
	.string "north.\p"
	.string "He just shows you his rare\n"
	.string "mons for free,\l"
	.string "absolute cinema.\p"
	.string "Watch out though, even\n"
	.string "with my goated movement\p"
	.string "I ran into some demon\n"
	.string "optionals.\p"
	.string "Aight, Peaceeee!$"

CeruleanCity_Text_LockeRivalIntro::
	.string "Back, and the roster's\n"
	.string "stacked, chat.\p"
	.string "Honestly? So is yours.\n"
	.string "Numbers are up.\p"
	.string "…You're the numbers.\n"
	.string "You're why I do this.\p"
	.string "…right?$"

CeruleanCity_Text_LockeRivalDefeat::
	.string "Two for two on camera,\n"
	.string "and I'm HERE for it.\p"
	.string "Clean beat, {PLAYER}.\p"
	.string "Thank you for being\n"
	.string "here. All of you.\p"
	.string "That's what matters.\n"
	.string "…That's what matters.$"

CeruleanCity_Text_LockeRivalPostBattle::
	.string "Go north, chat sent me.\p"
	.string "The Bill guy shows off\n"
	.string "his rare mons for free.\p"
	.string "Great content. Go say\n"
	.string "hi.\p"
	.string "…And we're clear.$"

CeruleanCity_Text_TwitchRivalIntro::
	.string "yo, you beat the bridge?\n"
	.string "the whole bridge? okay, okay.\p"
	.string "do NOT touch the PC.\n"
	.string "we do not trust the PC.\p"
	.string "NEVER FORGET BLOODY SUNDAY.\p"
	.string "also DEMOCRACY IS THE DOME.\n"
	.string "anyway. fight?$"

CeruleanCity_Text_TwitchRivalDefeat::
	.string "PRESS B. PRESS B TO PRAY…\p"
	.string "we pressed A.\n"
	.string "we ALWAYS press A.\p"
	.string "it is our curse.$"

CeruleanCity_Text_TwitchRivalPostBattle::
	.string "go north, {PLAYER}. the Bill guy\n"
	.string "shows you his rare mons for FREE.\p"
	.string "absolute cinema.\n"
	.string "tell him the Helix sent you.\p"
	.string "PRAISE HELIX.$"

CeruleanCity_Text_TwitchOhRightPresent::
	.string "oh wait. take this.\n"
	.string "no reason. the Helix provides.\p"
	.string "do not try to sell it.\n"
	.string "we tried. you cannot.$"

CeruleanCity_Text_TwitchExplainFameChecker::
	.string "it is basically the wiki.\n"
	.string "intel on all the big trainers.\p"
	.string "we memorized every word back\n"
	.string "in 2014… wait.\p"
	.string "why does chat look different?\n"
	.string "the emotes changed.\l"
	.string "the words changed.\p"
	.string "we… we EVOLVED.\n"
	.string "new meta dropped.\p"
	.string "GG. we go next.$"

CeruleanCity_Text_OhRightLittlePresentAsFavor::
	.string "Oh wait, hold up.\p"
	.string "Ngl I kinda feel bad,\n"
	.string "you're playing this thing\l"
	.string "totally blind.\p"
	.string "Here, take this, on me.$"

CeruleanCity_Text_ExplainFameCheckerSmellYa::
	.string "It's basically the wiki,\n"
	.string "pulls up intel on all the\l"
	.string "big-name trainers.\p"
	.string "I don't need it, I got the\n"
	.string "whole meta memorized\l"
	.string "already.\p"
	.string "You a bum though…\p"
	.string "Aight, for real this time.\n"
	.string "Peaceeee!$"

CeruleanCity_Text_GruntIntro::
	.string "Hey! Stay out!\n"
	.string "It's not your yard!\p"
	.string "…Huh?\n"
	.string "Me?\p"
	.string "I'm an innocent bystander!\n"
	.string "Don't you believe me?{PLAY_BGM}{MUS_RG_ENCOUNTER_ROCKET}$"

CeruleanCity_Text_GruntDefeat::
	.string "GRUNT: Stop! I give up!\n"
	.string "I'll leave quietly!$"

CeruleanCity_Text_OkayIllReturnStolenTM::
	.string "…Okay.\n"
	.string "I'll return the TM I stole.$"

CeruleanCity_Text_RecoveredTM28FromGrunt::
	.string "{PLAYER} recovered TM28 from\n"
	.string "the TEAM ROCKET GRUNT.$"

CeruleanCity_Text_BetterGetMovingBye::
	.string "I better get moving!\n"
	.string "Bye!$"

CeruleanCity_Text_MakeRoomForThisCantRun::
	.string "Make room for this!\n"
	.string "I can't run until I give it to you!$"

CeruleanCity_Text_TrainerLifeIsToughIsntIt::
	.string "MISTY runs that gym alone.\n"
	.string "Has for years.\p"
	.string "Say what you want about her.$"

CeruleanCity_Text_YouCanCutDownSmallTrees::
	.string "Did you know that you can CUT down\n"
	.string "small trees?\p"
	.string "Even that small tree in front of\n"
	.string "the shop can be CUT down.\p"
	.string "I think there's a way around it,\n"
	.string "though.$"

CeruleanCity_Text_IfSlowbroWasntThereCouldCutTree::
	.string "If that SLOWBRO wasn't there, you\n"
	.string "could CUT down the small tree.\p"
	.string "That way, you'd reach the other\n"
	.string "side. There's a way around, though.\p"
	.string "That SLOWBRO's near as stubborn\n"
	.string "as MISTY's PSYDUCK!$"

CeruleanCity_Text_PokemonEncyclopediaAmusing::
	.string "That PSYDUCK answers to no one.\n"
	.string "…Not even her.$"

CeruleanCity_Text_MistyPsyduckHeart::
	.string "Everyone thinks that PSYDUCK is\n"
	.string "the joke.\p"
	.string "…I think it's the one thing she'd\n"
	.string "never replace.$"

CeruleanCity_Text_PeopleHereWereRobbed::
	.string "The people here were robbed.\p"
	.string "TEAM ROCKET is behind it, sure as\n"
	.string "anything. Our FORCE can't cope.\p"
	.string "And the one giving the orders?\n"
	.string "No one's ever seen his face.\p"
	.string "A clean-handed man, somewhere.\n"
	.string "…The kind you never think to watch.$"

CeruleanCity_Text_PolicemanPsyduckHint::
	.string "This door won't budge for now.\p"
	.string "Stubborn as a certain PSYDUCK.$"

CeruleanCity_Text_SlowbroUseSonicboom::
	.string "Okay! SLOWBRO!\n"
	.string "Use SONICBOOM!$"

CeruleanCity_Text_SlowbroPayAttention::
	.string "Come on, SLOWBRO, pay attention!$"

CeruleanCity_Text_SlowbroPunch::
	.string "SLOWBRO, punch!$"

CeruleanCity_Text_NoYouBlewItAgain::
	.string "No!\n"
	.string "You blew it again!$"

CeruleanCity_Text_SlowbroWithdraw::
	.string "SLOWBRO, WITHDRAW!$"

CeruleanCity_Text_HardToControlMonsObedience::
	.string "No! That's wrong!\n"
	.string "It's so hard to control POKéMON!\p"
	.string "Your POKéMON's obedience depends\n"
	.string "on your abilities as a TRAINER.\p"
	.string "Even MISTY can't make her silly\n"
	.string "one mind. Mine only loafs, though.$"

CeruleanCity_Text_SlowbroTookSnooze::
	.string "SLOWBRO took a snooze…$"

CeruleanCity_Text_SlowbroLoafingAround::
	.string "SLOWBRO is loafing around…$"

CeruleanCity_Text_SlowbroTurnedAway::
	.string "SLOWBRO turned away…$"

CeruleanCity_Text_SlowbroIgnoredOrders::
	.string "SLOWBRO ignored orders…$"

CeruleanCity_Text_WantBrightRedBicycle::
	.string "The SENSATIONAL SISTERS keep it\n"
	.string "all spotless for their shows.\p"
	.string "Not MISTY. That girl's forever\n"
	.string "soaked. Lives in the pool, near.$"

CeruleanCity_Text_ThisIsCeruleanCave::
	.string "This is CERULEAN CAVE.\p"
	.string "Horribly strong POKéMON live inside\n"
	.string "there.\p"
	.string "It takes a very special TRAINER to\n"
	.string "be allowed inside there.\p"
	.string "You'd have to be strong enough to\n"
	.string "become the POKéMON LEAGUE\l"
	.string "CHAMPION for starters.\p"
	.string "And, you would have to have\n"
	.string "made a great achievement.\p"
	.string "Between you and me…\p"
	.string "The old-timers say the strongest\n"
	.string "thing in there isn't native.\p"
	.string "Came up from the south long ago,\n"
	.string "they whisper. From over the sea.\p"
	.string "Something that didn't want to be\n"
	.string "found. …I'd leave it be.$"

CeruleanCity_Text_CitySign::
	.string "CERULEAN CITY\n"
	.string "A Mysterious, Blue Aura Surrounds\l"
	.string "It$"

CeruleanCity_Text_TrainerTipsHeldItems::
	.string "TRAINER TIPS\p"
	.string "A POKéMON can be made to hold\n"
	.string "an item.\p"
	.string "Some items can even be used by\n"
	.string "the holding POKéMON in battle.$"

CeruleanCity_Text_BikeShopSign::
	.string "Grass and caves handled easily!\n"
	.string "BIKE SHOP$"

CeruleanCity_Text_GymSign::
	.string "CERULEAN CITY POKéMON GYM\n"
	.string "LEADER: MISTY\l"
	.string "The Tomboyish Mermaid!$"

