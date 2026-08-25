SaffronCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_OnTransition
	.byte 0

SaffronCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SAFFRON_CITY
	call_if_unset FLAG_RESCUED_MR_FUJI, SaffronCity_EventScript_MoveDoorGuardGrunt
	end

SaffronCity_EventScript_MoveDoorGuardGrunt::
	setobjectxyperm LOCALID_SAFFRON_DOOR_GUARD_GRUNT, 33, 31
	return

SaffronCity_EventScript_RocketGrunt1::
	msgbox SaffronCity_Text_WhatDoYouWantGetLost, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt2::
	msgbox SaffronCity_Text_BossTakeTownForTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt3::
	msgbox SaffronCity_Text_DontGetDefiantOrIllHurtYou, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt4::
	msgbox SaffronCity_Text_SaffronBelongsToTeamRocket, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt5::
	msgbox SaffronCity_Text_CriminalLifeMakesMeFeelAlive, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt6::
	msgbox SaffronCity_Text_WatchWhereYoureWalking, MSGBOX_NPC
	end

SaffronCity_EventScript_RocketGrunt7::
	msgbox SaffronCity_Text_WeCanExploitMonsAroundWorld, MSGBOX_NPC
	end

SaffronCity_EventScript_DoorGuardGrunt::
	lock
	goto_if_set FLAG_RESCUED_MR_FUJI, SaffronCity_EventScript_DoorGuardAsleep
	applymovement LOCALID_SAFFRON_DOOR_GUARD_GRUNT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SaffronCity_Text_ImASecurityGuard
	release
	end

SaffronCity_EventScript_DoorGuardAsleep::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox SaffronCity_Text_HesTakingASnooze
	release
	end

SaffronCity_EventScript_WorkerM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SABRINA, SaffronCity_EventScript_WorkerMAfter
	msgbox SaffronCity_Text_YouBeatTeamRocket
	release
	end

SaffronCity_EventScript_WorkerMAfter::
	msgbox SaffronCity_Text_WorkerMSabrinaFreed
	release
	end

SaffronCity_EventScript_Youngster::
	msgbox SaffronCity_Text_SafeToGoOutAgain, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SABRINA, SaffronCity_EventScript_LassAfter
	msgbox SaffronCity_Text_PeopleComingBackToSaffron
	release
	end

SaffronCity_EventScript_LassAfter::
	msgbox SaffronCity_Text_LassSabrinaFreed
	release
	end

SaffronCity_EventScript_Boy::
	msgbox SaffronCity_Text_FlewHereOnPidgeot, MSGBOX_NPC
	end

SaffronCity_EventScript_Pidgeot::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEOT, CRY_MODE_NORMAL
	msgbox SaffronCity_Text_Pidgeot
	waitmoncry
	release
	end

SaffronCity_EventScript_Man::
	msgbox SaffronCity_Text_SawRocketBossEscaping, MSGBOX_NPC
	end

SaffronCity_EventScript_CitySign::
	msgbox SaffronCity_Text_CitySign, MSGBOX_SIGN
	end

SaffronCity_EventScript_DojoSign::
	msgbox SaffronCity_Text_FightingDojo, MSGBOX_SIGN
	end

SaffronCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_SABRINA, 0
	msgbox SaffronCity_Text_GymSign
	releaseall
	end

SaffronCity_EventScript_TrainerTips1::
	msgbox SaffronCity_Text_FullHealCuresStatus, MSGBOX_SIGN
	end

SaffronCity_EventScript_TrainerTips2::
	msgbox SaffronCity_Text_GreatBallImprovedCatchRate, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphCoSign::
	msgbox SaffronCity_Text_SilphCoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MrPsychicsHouseSign::
	msgbox SaffronCity_Text_MrPsychicsHouse, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphProductSign::
	msgbox SaffronCity_Text_SilphsLatestProduct, MSGBOX_SIGN
	end

SaffronCity_EventScript_TrainerFanClubSign::
	msgbox SaffronCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

SaffronCity_Text_WhatDoYouWantGetLost::
	.string "This street's ours now.\n"
	.string "Turn around.\p"
	.string "You didn't see anything.\n"
	.string "Keep it that way.$"

SaffronCity_Text_BossTakeTownForTeamRocket::
	.string "The BOSS wants SAFFRON.\n"
	.string "So SAFFRON is his.\p"
	.string "That's how it works now.\n"
	.string "Get used to it.$"

SaffronCity_Text_DontGetDefiantOrIllHurtYou::
	.string "Eyes down. Keep walking.\p"
	.string "Folks who don't… we have\n"
	.string "a quiet word with them.\p"
	.string "You don't want the quiet\n"
	.string "word.$"

SaffronCity_Text_SaffronBelongsToTeamRocket::
	.string "Every door. Every gate.\n"
	.string "We hold the keys now.\p"
	.string "SAFFRON answers to\n"
	.string "TEAM ROCKET.$"

SaffronCity_Text_CriminalLifeMakesMeFeelAlive::
	.string "No badges. No rules.\n"
	.string "No one to answer to.\p"
	.string "You've no idea how good\n"
	.string "that feels.$"

SaffronCity_Text_WatchWhereYoureWalking::
	.string "Watch where you step.\p"
	.string "I'm not in the habit of\n"
	.string "asking twice.$"

SaffronCity_Text_WeCanExploitMonsAroundWorld::
	.string "Once SILPH bends to us,\n"
	.string "every POKéMON is stock.\p"
	.string "To buy. To sell. To break.\p"
	.string "And we'll be the ones who\n"
	.string "set the price.$"

SaffronCity_Text_YouBeatTeamRocket::
	.string "You beat TEAM ROCKET all alone?\n"
	.string "That's amazing!\p"
	.string "…But something worse walks SAFFRON\n"
	.string "now. My neighbor is just… gone.\p"
	.string "They say SABRINA keeps people.\n"
	.string "Inside dolls. I don't sleep much.$"

SaffronCity_Text_WorkerMSabrinaFreed::
	.string "My neighbor is home! Woke on his\n"
	.string "floor like from a nap.\p"
	.string "Whatever gripped this town let go\n"
	.string "all at once.\p"
	.string "That was you, wasn't it? Thank you.$"

SaffronCity_Text_SafeToGoOutAgain::
	.string "TEAM ROCKET's gone. Safe to go\n"
	.string "out again, they keep telling me.\p"
	.string "But it's so quiet now. Too quiet.\p"
	.string "Feels like the whole street is\n"
	.string "holding its breath.\p"
	.string "…I don't like it. I want it to\n"
	.string "stop.$"

SaffronCity_Text_PeopleComingBackToSaffron::
	.string "People fled from here in droves\n"
	.string "when those ROCKETS came.\p"
	.string "Now they trickle back… and some\n"
	.string "vanish again. No ROCKET to blame.\p"
	.string "They whisper it is HER. SABRINA.\n"
	.string "She was not always frightening.\p"
	.string "I knew her small. She laughed like\n"
	.string "a bell. …What became of that girl?$"

SaffronCity_Text_LassSabrinaFreed::
	.string "They are back! Everyone who\n"
	.string "vanished, home in their beds.\p"
	.string "None of them recall a thing.\p"
	.string "And SABRINA… I heard her LAUGH\n"
	.string "today. Like a bell. Like before.$"

SaffronCity_Text_FlewHereOnPidgeot::
	.string "I flew in on my PIDGEOT when I read\n"
	.string "about SILPH. Missed all the action.\p"
	.string "Odd town, though. Everyone walks\n"
	.string "like they're half asleep.\p"
	.string "Ask them why and they just… smile\n"
	.string "at you. Anyway! Nice weather.$"

SaffronCity_Text_Pidgeot::
	.string "PIDGEOT: Bi bibii!$"

SaffronCity_Text_SawRocketBossEscaping::
	.string "I saw the ROCKET BOSS escaping\n"
	.string "SILPH's building.\p"
	.string "Caught his face for just a second.\p"
	.string "That's what stuck with me, though.\n"
	.string "It was so… ordinary.\p"
	.string "A face you'd pass in any city and\n"
	.string "never think twice.$"

SaffronCity_Text_ImASecurityGuard::
	.string "I'm a security guard.\p"
	.string "Suspicious kids I don't allow in!$"

SaffronCity_Text_HesTakingASnooze::
	.string "…\n"
	.string "Snore…\p"
	.string "Hah! He's taking a snooze!$"

SaffronCity_Text_CitySign::
	.string "SAFFRON CITY\n"
	.string "Shining, Golden Land of Commerce$"

SaffronCity_Text_FightingDojo::
	.string "FIGHTING DOJO$"

SaffronCity_Text_GymSign::
	.string "SAFFRON CITY POKéMON GYM\n"
	.string "LEADER: SABRINA\l"
	.string "The Master of PSYCHIC POKéMON!$"

SaffronCity_Text_FullHealCuresStatus::
	.string "TRAINER TIPS\p"
	.string "FULL HEAL cures all ailments like\n"
	.string "burns, paralysis, poisoning,\l"
	.string "freezing, and sleep.\p"
	.string "It costs a bit more, but it's more\n"
	.string "convenient than buying other items.$"

SaffronCity_Text_GreatBallImprovedCatchRate::
	.string "TRAINER TIPS\p"
	.string "The new GREAT BALL offers improved\n"
	.string "catching rates.\p"
	.string "Try it on those hard-to-catch\n"
	.string "POKéMON.$"

SaffronCity_Text_SilphCoSign::
	.string "SILPH CO. OFFICE BUILDING$"

SaffronCity_Text_MrPsychicsHouse::
	.string "MR. PSYCHIC'S HOUSE$"

SaffronCity_Text_SilphsLatestProduct::
	.string "SILPH's latest product!\n"
	.string "Release to be determined…$"

SaffronCity_Text_TrainerFanClubSign::
	.string "POKéMON TRAINER FAN CLUB\p"
	.string "Many TRAINERS have scribbled their\n"
	.string "names on this sign.$"

SaffronCity_Text_HowCanClubNotRecognizeLance::
	.string "This FAN CLUB…\n"
	.string "No one here has a clue!\p"
	.string "LANCE showed me my GYARADOS is\n"
	.string "a SEA DRAGON.\p"
	.string "A SEA DRAGON! Now I can't UNSEE\n"
	.string "it!\p"
	.string "He sees the dragon in everything.\n"
	.string "He's the greatest, LANCE!$"

