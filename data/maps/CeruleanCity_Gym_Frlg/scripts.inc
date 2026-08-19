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
	@ Gym Guy (object 4) steps over and faces the player at the entrance.
	applymovement 4, CeruleanCity_Gym_Movement_GuideApproach
	waitmovement 0
	msgbox CeruleanCity_Gym_Text_NoBugsAllowed, MSGBOX_DEFAULT
	closemessage
	@ Shove the player back down toward the door, guide advancing after them.
	applymovement OBJ_EVENT_ID_PLAYER, CeruleanCity_Gym_Movement_PlayerShovedOut
	waitmovement 0
	applymovement 4, CeruleanCity_Gym_Movement_GuideAdvance
	waitmovement 0
	warp MAP_CERULEAN_CITY, 4
	waitstate
	releaseall
CeruleanCity_Gym_EventScript_BugCheckDone::
	end

CeruleanCity_Gym_Movement_GuideApproach::
	walk_down
	face_right
	step_end

CeruleanCity_Gym_Movement_PlayerShovedOut::
	walk_down
	step_end

CeruleanCity_Gym_Movement_GuideAdvance::
	walk_right
	face_down
	step_end

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
	.string "All WATER. No mercy.\p"
	.string "Prepare yourself. I'm sending out\n"
	.string "my strongest-\p"
	.string "{PLAY_SE SE_BALL_OPEN}*POP!*\p"
	.string "PSYDUCK?!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

CeruleanCity_Gym_Text_ExplainTM03::
	.string "TM03. WATER PULSE.\n"
	.string "My kind of move.\p"
	.string "Use it on something that swims.$"

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
	.string "…Huh. You didn't let me get away\n"
	.string "with anything.\p"
	.string "I only train what can't run.\p"
	.string "Turns out, today, neither could I.\p"
	.string "Here. The CASCADEBADGE.\n"
	.string "It's yours.$"

CeruleanCity_Gym_Text_DianaIntro::
	.string "What? You?\n"
	.string "I'm more than good enough for you!\p"
	.string "MISTY won't have to be bothered.$"

CeruleanCity_Gym_Text_DianaDefeat::
	.string "You overwhelmed me!\p"
	.string "…MISTY's still waiting. Good luck.$"

CeruleanCity_Gym_Text_DianaPostBattle::
	.string "Fine, you win.\n"
	.string "MISTY's next. Good luck.$"

CeruleanCity_Gym_Text_LuisIntro::
	.string "Splash!\p"
	.string "I'm first up!\n"
	.string "Let's do it!$"

CeruleanCity_Gym_Text_LuisDefeat::
	.string "That can't be!$"

CeruleanCity_Gym_Text_LuisPostBattle::
	.string "You beat me. Nice.\n"
	.string "MISTY won't be so easy.$"

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

