PewterCity_Gym_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PewterCity_Gym_OnFrame
	.byte 0

PewterCity_Gym_OnFrame::
	map_script_2 VAR_TEMP_1, 0, PewterCity_Gym_EventScript_PhonesRinging
	.2byte 0

PewterCity_Gym_EventScript_PhonesRinging::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_BADGE01_GET, PewterCity_Gym_EventScript_PhonesRingingEnd
	lockall
	playse SE_POKENAV_CALL
	delay 25
	playse SE_POKENAV_CALL
	delay 25
	playse SE_POKENAV_CALL
	msgbox PewterCity_Gym_Text_PhonesRinging, MSGBOX_DEFAULT
	releaseall
PewterCity_Gym_EventScript_PhonesRingingEnd::
	end

PewterCity_Gym_EventScript_Brock::
	famechecker FAMECHECKER_BROCK, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_BROCK, PewterCity_Gym_Text_BrockIntro, PewterCity_Gym_Text_BrockDefeat, PewterCity_Gym_EventScript_DefeatedBrock, NO_MUSIC
	goto_if_unset FLAG_GOT_TM39_FROM_BROCK, PewterCity_Gym_EventScript_GiveTM39
	msgbox PewterCity_Gym_Text_BrockPostBattle
	release
	end

PewterCity_Gym_EventScript_DefeatedBrock::
	famechecker FAMECHECKER_BROCK, 1
	setflag FLAG_DEFEATED_BROCK
	setflag FLAG_BADGE01_GET
	setvar VAR_MAP_SCENE_PEWTER_CITY, 1
	setflag FLAG_HIDE_PEWTER_CITY_GYM_GUIDE
	clearflag FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY
	set_gym_trainers_frlg 1
	goto PewterCity_Gym_EventScript_GiveTM39
	end

PewterCity_Gym_EventScript_GiveTM39::
	msgbox PewterCity_Gym_Text_TakeThisWithYou
	checkitemspace ITEM_TM39
	goto_if_eq VAR_RESULT, FALSE, PewterCity_Gym_EventScript_NoRoomForTM39
	giveitem_msg PewterCity_Gym_Text_ReceivedTM39FromBrock, ITEM_TM39
	setflag FLAG_GOT_TM39_FROM_BROCK
	msgbox PewterCity_Gym_Text_ExplainTM39
	release
	end

PewterCity_Gym_EventScript_NoRoomForTM39::
	msgbox PewterCity_Gym_Text_DontHaveRoomForThis
	release
	end

PewterCity_Gym_EventScript_Liam::
	trainerbattle_single TRAINER_CAMPER_LIAM, PewterCity_Gym_Text_LiamIntro, PewterCity_Gym_Text_LiamDefeat
	msgbox PewterCity_Gym_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
	end

PewterCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_BROCK, PewterCity_Gym_EventScript_GymGuyPostVictory
	msgbox PewterCity_Gym_Text_LetMeTakeYouToTheTop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_Gym_EventScript_GymGuyTakeMeToTop
	goto_if_eq VAR_RESULT, NO, PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop
	end

PewterCity_Gym_EventScript_GymGuyPostVictory::
	msgbox PewterCity_Gym_Text_YoureChampMaterial
	release
	end

PewterCity_Gym_EventScript_GymGuyTakeMeToTop::
	msgbox PewterCity_Gym_Text_LetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyDontTakeMeToTop::
	msgbox PewterCity_Gym_Text_ItsFreeLetsGetHappening
	goto PewterCity_Gym_EventScript_GymGuyAdvice
	end

PewterCity_Gym_EventScript_GymGuyAdvice::
	msgbox PewterCity_Gym_Text_TryDifferentPartyOrders
	release
	end

PewterCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, PewterCity_Gym_EventScript_GymStatuePostVictory
	msgbox PewterCity_Gym_Text_GymStatue
	releaseall
	end

PewterCity_Gym_EventScript_GymStatuePostVictory::
	msgbox PewterCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

PewterCity_Gym_Text_PhonesRinging::
	.string "The phones along the walls ring\n"
	.string "and ring… Nobody answers.$"

PewterCity_Gym_Text_BrockIntro::
	.string "A challenger! Wonderful.\p"
	.string "Oh, the phones…? Let's just say\n"
	.string "I'm a very reachable man.\p"
	.string "ROCK taught me patience, kid.\n"
	.string "So did a marriage or two.\p"
	.string "Word of advice, kid. Always read\n"
	.string "the whole contract before you say\l"
	.string "'I do'…\p"
	.string "RING! RING! RING! RING! RING!\p"
	.string "…Ignore that. Let's battle.{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

PewterCity_Gym_Text_BrockDefeat::
	.string "Lost again. Same as my love life.\p"
	.string "At least you didn't take half\n"
	.string "the GYM.\p"
	.string "Here, you earned it.\n"
	.string "The official LEAGUE BOULDERBADGE.\p"
	.string "{FONT_NORMAL}{PLAYER} received the BOULDERBADGE\n"
	.string "from BROCK!{PAUSE_MUSIC}{PLAY_BGM}{MUS_OBTAIN_BADGE}{PAUSE 0xFE}{PAUSE 0x56}{RESUME_MUSIC}\p"
	.string "{FONT_MALE}It toughens up your POKéMON, and\n"
	.string "lets them use FLASH out of battle.\p"
	.string "Unlike a marriage, a BADGE is\n"
	.string "yours to keep. Cherish it.\p"
	.string "RING! RING! RING! RING!\p"
	.string "…Ah, the phone.\n"
	.string "…I have to take this. Good luck.$"

PewterCity_Gym_Text_TakeThisWithYou::
	.string "Hold on, kid. A parting gift.\p"
	.string "Ex-wives get the house.\n"
	.string "You get the TM.$"

PewterCity_Gym_Text_ReceivedTM39FromBrock::
	.string "{PLAYER} received TM39\n"
	.string "from BROCK.$"

PewterCity_Gym_Text_ExplainTM39::
	.string "A TM, Technical Machine, contains a\n"
	.string "technique for POKéMON.\p"
	.string "Using a TM teaches the move it\n"
	.string "contains to a POKéMON.\p"
	.string "A TM is good for only one use.\p"
	.string "So, when you use one, pick the\n"
	.string "POKéMON carefully.\p"
	.string "Anyways…\n"
	.string "TM39 contains ROCK TOMB.\p"
	.string "It hurls boulders at the foe and\n"
	.string "lowers its SPEED.$"

PewterCity_Gym_Text_BrockPostBattle::
	.string "You again!\p"
	.string "My lawyer says I can't afford\n"
	.string "a rematch.$"

PewterCity_Gym_Text_DontHaveRoomForThis::
	.string "You don't have room for this.$"

PewterCity_Gym_Text_LiamIntro::
	.string "Not so fast, challenger!\p"
	.string "Hear all these phones? Each one\n"
	.string "rings different.\p"
	.string "That's not decoration.\n"
	.string "That's a filing system.$"

PewterCity_Gym_Text_LiamDefeat::
	.string "Okay, okay. You win.\p"
	.string "Six phones out there. Six… let's\n"
	.string "call 'em 'previous sponsors.'$"

PewterCity_Gym_Text_LiamPostBattle::
	.string "Soft heart, that BROCK.\n"
	.string "Rock-hard everywhere else.$"

PewterCity_Gym_Text_LetMeTakeYouToTheTop::
	.string "Hey! Welcome to PEWTER GYM.\p"
	.string "Don't mind the phones.\n"
	.string "BROCK says let 'em ring.\p"
	.string "I'm no TRAINER, but I can give you\n"
	.string "a tip. Want to hear it?$"

PewterCity_Gym_Text_LetsGetHappening::
	.string "All right!\n"
	.string "Let's get happening!$"

PewterCity_Gym_Text_TryDifferentPartyOrders::
	.string "The first POKéMON out in a match is\n"
	.string "at the left of the POKéMON LIST.\p"
	.string "By changing the order of POKéMON,\n"
	.string "you may gain an advantage.\p"
	.string "Try different orders to suit your\n"
	.string "opponent's party.$"

PewterCity_Gym_Text_ItsFreeLetsGetHappening::
	.string "It's a free service!\n"
	.string "Let's get happening!$"

PewterCity_Gym_Text_YoureChampMaterial::
	.string "Just as I thought!\n"
	.string "You're POKéMON champ material!$"

PewterCity_Gym_Text_GymStatue::
	.string "PEWTER POKéMON GYM\n"
	.string "LEADER: BROCK\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}$"

PewterCity_Gym_Text_GymStatuePlayerWon::
	.string "PEWTER POKéMON GYM\n"
	.string "LEADER: BROCK\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"

