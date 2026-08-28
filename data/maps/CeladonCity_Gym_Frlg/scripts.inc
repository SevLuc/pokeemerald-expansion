CeladonCity_Gym_Frlg_MapScripts::
	.byte 0

CeladonCity_Gym_EventScript_Erika::
	famechecker FAMECHECKER_ERIKA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_ERIKA, CeladonCity_Gym_Text_ErikaIntro, CeladonCity_Gym_Text_ErikaBadge, CeladonCity_Gym_EventScript_DefeatedErika, NO_MUSIC
	goto_if_unset FLAG_GOT_TM19_FROM_ERIKA, CeladonCity_Gym_EventScript_GiveTM19
	famechecker FAMECHECKER_ERIKA, 4
	msgbox CeladonCity_Gym_Text_ErikaPostBattle
	release
	end

CeladonCity_Gym_EventScript_DefeatedErika::
	famechecker FAMECHECKER_ERIKA, 1
	clearflag FLAG_HIDE_FAME_CHECKER_ERIKA_JOURNALS
	setflag FLAG_DEFEATED_ERIKA
	setflag FLAG_BADGE04_GET
	set_gym_trainers_frlg 4
	msgbox CeladonCity_Gym_Text_ErikaDefeatSpeech, MSGBOX_DEFAULT
	goto CeladonCity_Gym_EventScript_GiveTM19
	end

CeladonCity_Gym_EventScript_GiveTM19::
	msgbox CeladonCity_Gym_Text_ExplainRainbowBadgeTakeThis
	checkitemspace ITEM_TM19
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Gym_EventScript_NoRoomForTM19
	giveitem_msg CeladonCity_Gym_Text_ReceivedTM19FromErika, ITEM_TM19
	setflag FLAG_GOT_TM19_FROM_ERIKA
	msgbox CeladonCity_Gym_Text_ExplainTM19
	release
	end

CeladonCity_Gym_EventScript_NoRoomForTM19::
	msgbox CeladonCity_Gym_Text_ShouldMakeRoomForThis
	release
	end

CeladonCity_Gym_EventScript_Kay::
	trainerbattle_single TRAINER_LASS_KAY, CeladonCity_Gym_Text_KayIntro, CeladonCity_Gym_Text_KayDefeat
	msgbox CeladonCity_Gym_Text_KayPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Lisa::
	trainerbattle_single TRAINER_LASS_LISA, CeladonCity_Gym_Text_LisaIntro, CeladonCity_Gym_Text_LisaDefeat
	famechecker FAMECHECKER_ERIKA, 2
	msgbox CeladonCity_Gym_Text_LisaPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Tina::
	trainerbattle_single TRAINER_PICNICKER_TINA, CeladonCity_Gym_Text_TinaIntro, CeladonCity_Gym_Text_TinaDefeat
	msgbox CeladonCity_Gym_Text_TinaPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Bridget::
	trainerbattle_single TRAINER_BEAUTY_BRIDGET, CeladonCity_Gym_Text_BridgetIntro, CeladonCity_Gym_Text_BridgetDefeat
	msgbox CeladonCity_Gym_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Tamia::
	trainerbattle_single TRAINER_BEAUTY_TAMIA, CeladonCity_Gym_Text_TamiaIntro, CeladonCity_Gym_Text_TamiaDefeat
	famechecker FAMECHECKER_ERIKA, 3
	msgbox CeladonCity_Gym_Text_TamiaPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Lori::
	trainerbattle_single TRAINER_BEAUTY_LORI, CeladonCity_Gym_Text_LoriIntro, CeladonCity_Gym_Text_LoriDefeat
	msgbox CeladonCity_Gym_Text_LoriPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_Mary::
	trainerbattle_single TRAINER_COOLTRAINER_MARY, CeladonCity_Gym_Text_MaryIntro, CeladonCity_Gym_Text_MaryDefeat
	msgbox CeladonCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

CeladonCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, CeladonCity_Gym_EventScript_GymStatuePostVictory
	msgbox CeladonCity_Gym_Text_GymStatue
	releaseall
	end

CeladonCity_Gym_EventScript_GymStatuePostVictory::
	msgbox CeladonCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

CeladonCity_Gym_Text_ErikaIntro::
	.string "Oh… a visitor.\n"
	.string "Forgive me, I was tending the beds.\p"
	.string "Sit among the flowers a moment.\n"
	.string "…They rather like you.\p"
	.string "I am ERIKA. I've kept this garden\n"
	.string "since I was small.\p"
	.string "The scent makes callers drowsy.\n"
	.string "Few ever notice they've dozed.\p"
	.string "My POKéMON I raised from seed.\n"
	.string "…Lovely things. Mind the thorns.\p"
	.string "You truly wish to challenge me?\n"
	.string "A shame to spoil the quiet.{PLAY_BGM MUS_RG_ENCOUNTER_GYM_LEADER}$"

CeladonCity_Gym_Text_ErikaBadge::
	.string "The RAINBOWBADGE is yours.$"

CeladonCity_Gym_Text_ErikaDefeatSpeech::
	.string "Oh… you never once drifted off.\p"
	.string "Everyone drifts, here. The scent,\n"
	.string "the quiet. …But not you.\p"
	.string "How wide awake you must be inside.\n"
	.string "How tiring. …I do envy it.$"

CeladonCity_Gym_Text_ErikaPostBattle::
	.string "Mm. Still here?\p"
	.string "Stay as long as you like.\n"
	.string "The garden keeps no clocks.\p"
	.string "Tend a thing with enough care,\n"
	.string "and it will do anything for you.\p"
	.string "…Anything at all.$"

CeladonCity_Gym_Text_ExplainRainbowBadgeTakeThis::
	.string "The RAINBOWBADGE. It suits you.\p"
	.string "POKéMON up to Lv. 50 will heed you\n"
	.string "now, even far-off ones.\p"
	.string "And it stirs a sleeping STRENGTH\n"
	.string "in them, to move what won't move.\p"
	.string "…Take it. A gift from the garden.$"

CeladonCity_Gym_Text_ReceivedTM19FromErika::
	.string "{PLAYER} received TM19\n"
	.string "from ERIKA.$"

CeladonCity_Gym_Text_ExplainTM19::
	.string "And this. TM19. GIGA DRAIN.\p"
	.string "It takes a little life from them,\n"
	.string "soft as sleep, and gives it to you.\p"
	.string "Everything I grow does the same.\n"
	.string "…Takes. Gives. Takes.$"

CeladonCity_Gym_Text_ShouldMakeRoomForThis::
	.string "You've no room. …Make some, hm?\n"
	.string "Gentle things need a place to rest.$"

CeladonCity_Gym_Text_KayIntro::
	.string "I should tell you about this GYM.\p"
	.string "Only real ladies are allowed in\n"
	.string "here!\p"
	.string "ERIKA takes us all in.\n"
	.string "Never asks what we left behind.\p"
	.string "She never had a PEWTER number\n"
	.string "herself. Just keeps the door open.$"

CeladonCity_Gym_Text_KayDefeat::
	.string "You're too rough!$"

CeladonCity_Gym_Text_KayPostBattle::
	.string "Bleaah!\n"
	.string "I hope ERIKA wipes you out!$"

CeladonCity_Gym_Text_BridgetIntro::
	.string "Oh, welcome.\n"
	.string "I was getting bored.$"

CeladonCity_Gym_Text_BridgetDefeat::
	.string "My makeup!$"

CeladonCity_Gym_Text_BridgetPostBattle::
	.string "GRASS-type POKéMON are tough\n"
	.string "against the WATER type.\p"
	.string "They also have an edge on ROCK-\n"
	.string "and GROUND-type POKéMON.$"

CeladonCity_Gym_Text_TinaIntro::
	.string "…Weren't you peeking in here\n"
	.string "earlier?$"

CeladonCity_Gym_Text_TinaDefeat::
	.string "You're an eye-opener!$"

CeladonCity_Gym_Text_TinaPostBattle::
	.string "Oh, you were looking at ERIKA…\n"
	.string "You weren't looking at me…$"

CeladonCity_Gym_Text_TamiaIntro::
	.string "Look, look!\n"
	.string "See my POKéMON!\p"
	.string "I like the GRASS type.\n"
	.string "I like how they're easy to raise.$"

CeladonCity_Gym_Text_TamiaDefeat::
	.string "No!$"

CeladonCity_Gym_Text_TamiaPostBattle::
	.string "We only use GRASS-type POKéMON at\n"
	.string "our GYM.\p"
	.string "Why? We also use them for making\n"
	.string "flower arrangements!$"

CeladonCity_Gym_Text_LisaIntro::
	.string "Oh, hey!\p"
	.string "We don't like BUG- or FIRE-type\n"
	.string "POKéMON in here!$"

CeladonCity_Gym_Text_LisaDefeat::
	.string "Oh!\n"
	.string "You!$"

CeladonCity_Gym_Text_LisaPostBattle::
	.string "Our LEADER ERIKA might be quiet,\n"
	.string "but she's famous around here.\p"
	.string "The truth about her? Everyone\n"
	.string "wants it.\p"
	.string "Ask ten of us, you'll get ten\n"
	.string "ERIKAs. …She likes it that way.$"

CeladonCity_Gym_Text_LoriIntro::
	.string "Pleased to meet you.\n"
	.string "My hobby is POKéMON training.$"

CeladonCity_Gym_Text_LoriDefeat::
	.string "Oh!\n"
	.string "Splendid!$"

CeladonCity_Gym_Text_LoriPostBattle::
	.string "I have a blind date coming up.\n"
	.string "I have to learn to be polite,\l"
	.string "especially if I have to battle.\p"
	.string "The last one? …Generous.\n"
	.string "Every single month, even now.$"

CeladonCity_Gym_Text_MaryIntro::
	.string "Welcome to CELADON GYM!\p"
	.string "You'd better not underestimate\n"
	.string "the nice ladies here.$"

CeladonCity_Gym_Text_MaryDefeat::
	.string "Oh!\n"
	.string "Beaten!$"

CeladonCity_Gym_Text_MaryPostBattle::
	.string "I didn't bring my best POKéMON.\n"
	.string "Wait until next time!\p"
	.string "…My phone? Let it ring, dear.\n"
	.string "A man in PEWTER. He always calls.$"

CeladonCity_Gym_Text_GymStatue::
	.string "CELADON POKéMON GYM\n"
	.string "LEADER: ERIKA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}$"

CeladonCity_Gym_Text_GymStatuePlayerWon::
	.string "CELADON POKéMON GYM\n"
	.string "LEADER: ERIKA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"

