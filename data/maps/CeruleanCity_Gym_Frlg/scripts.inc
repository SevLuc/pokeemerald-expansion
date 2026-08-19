CeruleanCity_Gym_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CeruleanCity_Gym_OnFrame
	.byte 0

CeruleanCity_Gym_OnFrame::
	map_script_2 VAR_TEMP_1, 0, CeruleanCity_Gym_EventScript_BugCheck
	.2byte 0

CeruleanCity_Gym_EventScript_BugCheck::
	setvar VAR_TEMP_1, 1
	specialvar VAR_RESULT, PartyHasBugType
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_Gym_EventScript_BugCheckDone
	lockall
	msgbox CeruleanCity_Gym_Text_NoBugsAllowed, MSGBOX_DEFAULT
	closemessage
	warp MAP_CERULEAN_CITY, 4
	waitstate
	releaseall
CeruleanCity_Gym_EventScript_BugCheckDone::
	end

CeruleanCity_Gym_EventScript_Misty::
	famechecker FAMECHECKER_MISTY, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_MISTY, CeruleanCity_Gym_Text_MistyIntro, CeruleanCity_Gym_Text_MistyDefeat, CeruleanCity_Gym_EventScript_MistyDefeated, NO_MUSIC
	goto_if_unset FLAG_GOT_TM03_FROM_MISTY, CeruleanCity_Gym_EventScript_GiveTM03
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_MistyDefeated::
	famechecker FAMECHECKER_MISTY, 1
	setflag FLAG_DEFEATED_MISTY
	setflag FLAG_BADGE02_GET
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	set_gym_trainers_frlg 2
	goto CeruleanCity_Gym_EventScript_GiveTM03
	end

CeruleanCity_Gym_EventScript_GiveTM03::
	msgbox CeruleanCity_Gym_Text_ExplainCascadeBadge
	checkitemspace ITEM_TM03
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_Gym_EventScript_NoRoomForTM03
	giveitem_msg CeruleanCity_Gym_Text_ReceivedTM03FromMisty, ITEM_TM03
	setflag FLAG_GOT_TM03_FROM_MISTY
	msgbox CeruleanCity_Gym_Text_ExplainTM03
	release
	end

CeruleanCity_Gym_EventScript_NoRoomForTM03::
	msgbox CeruleanCity_Gym_Text_BetterMakeRoomForThis
	release
	end

CeruleanCity_Gym_EventScript_Diana::
	trainerbattle_single TRAINER_PICNICKER_DIANA, CeruleanCity_Gym_Text_DianaIntro, CeruleanCity_Gym_Text_DianaDefeat
	msgbox CeruleanCity_Gym_Text_DianaPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_Luis::
	trainerbattle_single TRAINER_SWIMMER_MALE_LUIS, CeruleanCity_Gym_Text_LuisIntro, CeruleanCity_Gym_Text_LuisDefeat
	famechecker FAMECHECKER_MISTY, 2
	msgbox CeruleanCity_Gym_Text_LuisPostBattle, MSGBOX_AUTOCLOSE
	end

CeruleanCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MISTY, CeruleanCity_Gym_EventScript_GymGuyPostVictory
	msgbox CeruleanCity_Gym_Text_GymGuyAdvice
	release
	end

CeruleanCity_Gym_EventScript_GymGuyPostVictory::
	msgbox CeruleanCity_Gym_Text_WeMakePrettyGoodTeam
	release
	end

CeruleanCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE02_GET, CeruleanCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeruleanCity_Gym_Text_GymStatue
	releaseall
	end

CeruleanCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeruleanCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeruleanCity_Gym_Text_NoBugsAllowed::
	.string "Whoa there! Is that a BUG POKéMON?\p"
	.string "…Yeah, no. Not in MISTY's gym.\p"
	.string "One BUG in here and she's up on a\n"
	.string "chair for the afternoon.\p"
	.string "Leave it outside. Then we'll talk.$"

CeruleanCity_Gym_Text_MistyIntro::
	.string "So you're my next challenger.\p"
	.string "I'm MISTY. Youngest of the\n"
	.string "Sensational Sisters.\p"
	.string "They do the dance shows.\n"
	.string "I do the actual battling.\p"
	.string "My policy? All-out offensive.\n"
	.string "All WATER, no holding back-\p"
	.string "…PSYDUCK. I did NOT let you out.\p"
	.string "Ugh. Whatever. Stay if you want.\n"
	.string "Just don't get in my way.\p"
	.string "Let's go!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

CeruleanCity_Gym_Text_ExplainTM03::
	.string "TM03 teaches WATER PULSE.\p"
	.string "Use it on an aquatic POKéMON!$"

CeruleanCity_Gym_Text_ExplainCascadeBadge::
	.string "The CASCADEBADGE makes all\n"
	.string "POKéMON up to Lv. 30 obey.\p"
	.string "That includes even outsiders you\n"
	.string "got in trades.\p"
	.string "There's more. You can now use CUT\n"
	.string "anytime, even out of battle.\p"
	.string "You can CUT down small trees to\n"
	.string "open new pathways.\p"
	.string "You can also have my favorite TM.$"

CeruleanCity_Gym_Text_ReceivedTM03FromMisty::
	.string "{PLAYER} received TM03\n"
	.string "from MISTY.$"

CeruleanCity_Gym_Text_BetterMakeRoomForThis::
	.string "You better make room for this!$"

CeruleanCity_Gym_Text_MistyDefeat::
	.string "Ugh! Fine. You got me.\p"
	.string "You're strong. I'll admit that.\n"
	.string "…Don't let it go to your head.\p"
	.string "Here. The CASCADEBADGE. Earned.\p"
	.string "…Even PSYDUCK looks impressed.\n"
	.string "And PSYDUCK is NEVER impressed.$"

CeruleanCity_Gym_Text_DianaIntro::
	.string "What? You?\n"
	.string "I'm more than good enough for you!\p"
	.string "MISTY won't have to be bothered.$"

CeruleanCity_Gym_Text_DianaDefeat::
	.string "You overwhelmed me!$"

CeruleanCity_Gym_Text_DianaPostBattle::
	.string "You've heard about the duck.\n"
	.string "Everyone has. …Don't bring it up.$"

CeruleanCity_Gym_Text_LuisIntro::
	.string "Splash!\p"
	.string "I'm first up!\n"
	.string "Let's do it!$"

CeruleanCity_Gym_Text_LuisDefeat::
	.string "That can't be!$"

CeruleanCity_Gym_Text_LuisPostBattle::
	.string "You got this far, so you know\n"
	.string "the rule about bugs by now. …Good.$"

CeruleanCity_Gym_Text_GymGuyAdvice::
	.string "Yo!\n"
	.string "Champ in the making!\p"
	.string "Let me give you some advice!\p"
	.string "The LEADER, MISTY, is a pro who\n"
	.string "uses WATER-type POKéMON.\p"
	.string "You can drain all their water with\n"
	.string "GRASS-type POKéMON.\p"
	.string "Or, you might use ELECTRIC-type\n"
	.string "POKéMON and zap them!$"

CeruleanCity_Gym_Text_WeMakePrettyGoodTeam::
	.string "You beat MISTY!\n"
	.string "See, what'd I tell ya?\p"
	.string "You and me, kid, we make a pretty\n"
	.string "darn-good team!$"

CeruleanCity_Gym_Text_GymStatue::
	.string "CERULEAN POKéMON GYM\n"
	.string "LEADER: MISTY\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}$"

CeruleanCity_Gym_Text_GymStatuePlayerWon::
	.string "CERULEAN POKéMON GYM\n"
	.string "LEADER: MISTY\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"

