SilphCo_6F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_6F_OnLoad
	.byte 0

SilphCo_6F_OnLoad::
	call_if_unset FLAG_SILPH_6F_DOOR, EventScript_Close6FDoor
	end

SilphCo_6F_EventScript_WorkerM2::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM2RocketsGone
	msgbox SilphCo_6F_Text_TargetedSilphForOurMonProducts
	release
	end

SilphCo_6F_EventScript_WorkerM2RocketsGone::
	msgbox SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder
	release
	end

SilphCo_6F_EventScript_WorkerM3::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM3RocketsGone
	msgbox SilphCo_6F_Text_RocketsTookOverBuilding
	release
	end

SilphCo_6F_EventScript_WorkerM3RocketsGone::
	msgbox SilphCo_6F_Text_BetterGetBackToWork
	release
	end

SilphCo_6F_EventScript_WorkerM1::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM1RocketsGone
	msgbox SilphCo_6F_Text_HelpMePlease
	release
	end

SilphCo_6F_EventScript_WorkerM1RocketsGone::
	msgbox SilphCo_6F_Text_WeGotEngaged
	release
	end

SilphCo_6F_EventScript_WorkerF1::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerF1RocketsGone
	msgbox SilphCo_6F_Text_ThatManIsSuchACoward
	release
	end

SilphCo_6F_EventScript_WorkerF1RocketsGone::
	msgbox SilphCo_6F_Text_NeedsMeToLookAfterHim
	release
	end

SilphCo_6F_EventScript_WorkerF2::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerF2RocketsGone
	msgbox SilphCo_6F_Text_RocketsTryingToConquerWorld
	release
	end

SilphCo_6F_EventScript_WorkerF2RocketsGone::
	msgbox SilphCo_6F_Text_RocketsRanAwayBecauseOfYou
	release
	end

SilphCo_6F_EventScript_FloorSign::
	msgbox SilphCo_6F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_6F_EventScript_Taylor::
	trainerbattle_single TRAINER_SCIENTIST_TAYLOR, SilphCo_6F_Text_TaylorIntro, SilphCo_6F_Text_TaylorDefeat
	msgbox SilphCo_6F_Text_TaylorPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_30, SilphCo_6F_Text_Grunt1Intro, SilphCo_6F_Text_Grunt1Defeat
	msgbox SilphCo_6F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_31, SilphCo_6F_Text_Grunt2Intro, SilphCo_6F_Text_Grunt2Defeat
	msgbox SilphCo_6F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_Text_RocketsTookOverBuilding::
	.string "One morning they simply\n"
	.string "walked in.\p"
	.string "Keycards, guards, the lot.\n"
	.string "By noon the tower was theirs.\p"
	.string "We never stood a chance.$"

SilphCo_6F_Text_BetterGetBackToWork::
	.string "Well, better get back to work.$"

SilphCo_6F_Text_HelpMePlease::
	.string "Oh dear, oh dear…\p"
	.string "I didn't sign on for this.\n"
	.string "I wanted a steady desk job.\p"
	.string "Help me. Please.$"

SilphCo_6F_Text_WeGotEngaged::
	.string "We got engaged.\n"
	.string "Heheh!$"

SilphCo_6F_Text_ThatManIsSuchACoward::
	.string "That man beside me?\p"
	.string "Weeping into the carpet\n"
	.string "since the ROCKETS arrived.\p"
	.string "One of us has to keep our\n"
	.string "head. So it's me.$"

SilphCo_6F_Text_NeedsMeToLookAfterHim::
	.string "He's so helpless, he needed\n"
	.string "someone like me to look after him.$"

SilphCo_6F_Text_RocketsTryingToConquerWorld::
	.string "You understand what's at\n"
	.string "stake here?\p"
	.string "They don't just want SILPH.\n"
	.string "They want every POKéMON in it.\p"
	.string "And then the wild ones\n"
	.string "beyond these walls.$"

SilphCo_6F_Text_RocketsRanAwayBecauseOfYou::
	.string "TEAM ROCKET ran away, and it's all\n"
	.string "because of you!$"

SilphCo_6F_Text_TargetedSilphForOurMonProducts::
	.string "They came for what SILPH\n"
	.string "makes. The POKé BALLS.\p"
	.string "My grandfather carved his\n"
	.string "by hand, one at a time.\p"
	.string "Our line stamps out a\n"
	.string "thousand an hour.\p"
	.string "We ended his craft. Now\n"
	.string "someone's come to end ours.$"

SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder::
	.string "Come work for SILPH when you\n"
	.string "get older.$"

SilphCo_6F_Text_Grunt1Intro::
	.string "I am one of the four ROCKET\n"
	.string "BROTHERS!$"

SilphCo_6F_Text_Grunt1Defeat::
	.string "Flame out!$"

SilphCo_6F_Text_Grunt1PostBattle::
	.string "No matter!\n"
	.string "My brothers will avenge me!$"

SilphCo_6F_Text_TaylorIntro::
	.string "That rotten PRESIDENT!\p"
	.string "Serves him right for shipping me\n"
	.string "off to the TIKSI BRANCH!\p"
	.string "That's why TEAM ROCKET came after\n"
	.string "us, I'm sure of it!$"

SilphCo_6F_Text_TaylorDefeat::
	.string "Shoot!$"

SilphCo_6F_Text_TaylorPostBattle::
	.string "TIKSI BRANCH?\n"
	.string "It's in Russian no-man's-land!$"

SilphCo_6F_Text_Grunt2Intro::
	.string "You dare betray TEAM ROCKET?$"

SilphCo_6F_Text_Grunt2Defeat::
	.string "You traitor!$"

SilphCo_6F_Text_Grunt2PostBattle::
	.string "If you stand for justice, you\n"
	.string "betray us bad guys!$"

SilphCo_6F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "6F$"

