SaffronCity_Gym_Frlg_MapScripts::
	.byte 0

SaffronCity_Gym_EventScript_Sabrina::
	famechecker FAMECHECKER_SABRINA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_SABRINA, SaffronCity_Gym_Text_SabrinaIntro, SaffronCity_Gym_Text_SabrinaDefeat, SaffronCity_Gym_EventScript_DefeatedSabrina, NO_MUSIC
	goto_if_unset FLAG_GOT_TM04_FROM_SABRINA, SaffronCity_Gym_EventScript_GiveTM04
	msgbox SaffronCity_Gym_Text_ExplainTM04
	release
	end

SaffronCity_Gym_EventScript_DefeatedSabrina::
	famechecker FAMECHECKER_SABRINA, 2
	famechecker FAMECHECKER_SABRINA, 3
	clearflag FLAG_HIDE_SAFFRON_CITY_POKECENTER_SABRINA_JOURNALS
	setflag FLAG_DEFEATED_SABRINA
	setflag FLAG_BADGE06_GET
	set_gym_trainers_frlg 6
	goto SaffronCity_Gym_EventScript_GiveTM04
	end

SaffronCity_Gym_EventScript_GiveTM04::
	msgbox SaffronCity_Gym_Text_ExplainMarshBadgeTakeThis
	checkitemspace ITEM_TM04
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_Gym_EventScript_NoRoomForTM04
	giveitem_msg SaffronCity_Gym_Text_ReceivedTM04FromSabrina, ITEM_TM04
	setflag FLAG_GOT_TM04_FROM_SABRINA
	msgbox SaffronCity_Gym_Text_SabrinaPostBattle
	release
	end

SaffronCity_Gym_EventScript_NoRoomForTM04::
	msgbox SaffronCity_Gym_Text_BagFullOfOtherItems
	release
	end

SaffronCity_Gym_EventScript_Johan::
	trainerbattle_single TRAINER_PSYCHIC_JOHAN, SaffronCity_Gym_Text_JohanIntro, SaffronCity_Gym_Text_JohanDefeat
	msgbox SaffronCity_Gym_Text_JohanPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Tyron::
	trainerbattle_single TRAINER_PSYCHIC_TYRON, SaffronCity_Gym_Text_TyronIntro, SaffronCity_Gym_Text_TyronDefeat
	famechecker FAMECHECKER_SABRINA, 5
	msgbox SaffronCity_Gym_Text_TyronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Cameron::
	trainerbattle_single TRAINER_PSYCHIC_CAMERON, SaffronCity_Gym_Text_CameronIntro, SaffronCity_Gym_Text_CameronDefeat
	msgbox SaffronCity_Gym_Text_CameronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PSYCHIC_PRESTON, SaffronCity_Gym_Text_PrestonIntro, SaffronCity_Gym_Text_PrestonDefeat
	msgbox SaffronCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Amanda::
	trainerbattle_single TRAINER_CHANNELER_AMANDA, SaffronCity_Gym_Text_AmandaIntro, SaffronCity_Gym_Text_AmandaDefeat
	msgbox SaffronCity_Gym_Text_AmandaPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Stacy::
	trainerbattle_single TRAINER_CHANNELER_STACY, SaffronCity_Gym_Text_StacyIntro, SaffronCity_Gym_Text_StacyDefeat
	msgbox SaffronCity_Gym_Text_StacyPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Tasha::
	trainerbattle_single TRAINER_CHANNELER_TASHA, SaffronCity_Gym_Text_TashaIntro, SaffronCity_Gym_Text_TashaDefeat
	msgbox SaffronCity_Gym_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SABRINA, SaffronCity_Gym_EventScript_GymGuyPostVictory
	msgbox SaffronCity_Gym_Text_GymGuyAdvice
	release
	end

SaffronCity_Gym_EventScript_GymGuyPostVictory::
	msgbox SaffronCity_Gym_Text_GymGuyPostVictory
	release
	end

SaffronCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, SaffronCity_Gym_EventScript_GymStatuePostVictory
	msgbox SaffronCity_Gym_Text_GymStatue
	releaseall
	end

SaffronCity_Gym_EventScript_GymStatuePostVictory::
	msgbox SaffronCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

SaffronCity_Gym_Text_SabrinaIntro::
	.string "You climbed where the others\n"
	.string "could not. I hid the way.\p"
	.string "I hid it inside their own minds.\p"
	.string "Can you feel them? All of SAFFRON,\n"
	.string "folded quiet within me.\p"
	.string "Sleeping. Orderly. Mine.\p"
	.string "There is a small, still place for\n"
	.string "you as well. Let me show you.{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

SaffronCity_Gym_Text_SabrinaDefeat::
	.string "…\p"
	.string "…Ha.\p"
	.string "…Hah. Haha. HAHAHA!\p"
	.string "I am laughing. I am LAUGHING.\n"
	.string "When did I last…?\p"
	.string "…Absolute cinema!!\p"
	.string "Oh. Oh, I can FEEL again.\n"
	.string "That warmth… it is feeling itself.\p"
	.string "I had forgotten it had a shape.\p"
	.string "And surprise. True surprise.\n"
	.string "I saw none of this coming.\p"
	.string "The cold is letting go of me,\n"
	.string "and it does not hurt at all.\p"
	.string "I feel them waking. All of them.\n"
	.string "Coming home, blinking, unharmed.\p"
	.string "…Thank you. Truly.\p"
	.string "Take the MARSHBADGE.\n"
	.string "You broke the spell.$"

SaffronCity_Gym_Text_SabrinaPostBattle::
	.string "Look. I am crying, and I do not\n"
	.string "mind at all.\p"
	.string "Everyone I gathered is home again.\n"
	.string "No harm done.\p"
	.string "No one recalls the dark. …That is\n"
	.string "my last gift to them.\p"
	.string "Come back anytime, friend. The\n"
	.string "lights are on in SAFFRON again.$"

SaffronCity_Gym_Text_ExplainMarshBadgeTakeThis::
	.string "The MARSHBADGE. It keeps POKéMON\n"
	.string "up to Lv. 70 loyal to you.\p"
	.string "Raise one past that, and it turns\n"
	.string "wild, deaf to your voice.\p"
	.string "Power without a warm hand goes\n"
	.string "cold. …No one knows that better.\p"
	.string "Take this as well. With my thanks.$"

SaffronCity_Gym_Text_ReceivedTM04FromSabrina::
	.string "{PLAYER} received TM04 from\n"
	.string "SABRINA.$"

SaffronCity_Gym_Text_ExplainTM04::
	.string "TM04. CALM MIND.\p"
	.string "A gentle stillness. It lifts SP.\n"
	.string "ATK and SP. DEF alike.\p"
	.string "I lived years in the colder kind\n"
	.string "of still.\p"
	.string "…This one is kinder. Take it.$"

SaffronCity_Gym_Text_BagFullOfOtherItems::
	.string "Your bag is full, friend.\n"
	.string "…I did not need to foresee that.$"

SaffronCity_Gym_Text_AmandaIntro::
	.string "This mouth is not mine.\n"
	.string "It says: NORTH panels find her.\p"
	.string "…I cannot stop it.$"

SaffronCity_Gym_Text_AmandaDefeat::
	.string "…Oh. I'm awake. Briefly.\p"
	.string "Believe nothing we tell you.$"

SaffronCity_Gym_Text_AmandaPostBattle::
	.string "…North. The north panels.\n"
	.string "…North…$"

SaffronCity_Gym_Text_JohanIntro::
	.string "SHE speaks through me.\n"
	.string "Go SOUTH. Only south reaches her.$"

SaffronCity_Gym_Text_JohanDefeat::
	.string "Gah! Myself, for a moment.\p"
	.string "Every hint here is a lie.$"

SaffronCity_Gym_Text_JohanPostBattle::
	.string "…South. Go south.\n"
	.string "…South…$"

SaffronCity_Gym_Text_StacyIntro::
	.string "My hands move on their own.\n"
	.string "Left, she says. Always bear left.$"

SaffronCity_Gym_Text_StacyDefeat::
	.string "…That was not me fighting.\p"
	.string "None of this is us.$"

SaffronCity_Gym_Text_StacyPostBattle::
	.string "…Left. Only left.\n"
	.string "…Left…$"

SaffronCity_Gym_Text_TyronIntro::
	.string "You will bear RIGHT. Never left.\n"
	.string "…I cannot stop saying it.$"

SaffronCity_Gym_Text_TyronDefeat::
	.string "Free… one breath. Listen:\p"
	.string "we would never help her willingly.$"

SaffronCity_Gym_Text_TyronPostBattle::
	.string "…Right. Never left.\n"
	.string "…Right…$"

SaffronCity_Gym_Text_TashaIntro::
	.string "Stand still, she whispers.\n"
	.string "Stand still, and she will come.$"

SaffronCity_Gym_Text_TashaDefeat::
	.string "…Move. Please, move.\p"
	.string "Standing still is how she takes you.$"

SaffronCity_Gym_Text_TashaPostBattle::
	.string "…Stand still.\n"
	.string "…Stand still…$"

SaffronCity_Gym_Text_CameronIntro::
	.string "The center panel. Step there.\n"
	.string "She promises it leads to her.$"

SaffronCity_Gym_Text_CameronDefeat::
	.string "…My own thoughts, a moment.\p"
	.string "Her promises are not ours to keep.$"

SaffronCity_Gym_Text_CameronPostBattle::
	.string "…The center panel.\n"
	.string "…The center…$"

SaffronCity_Gym_Text_PrestonIntro::
	.string "Turn back. There is no way through.\n"
	.string "Turn back. Turn back.$"

SaffronCity_Gym_Text_PrestonDefeat::
	.string "…I'd have warned you if I could.\p"
	.string "Keep going. Reach her. Please.$"

SaffronCity_Gym_Text_PrestonPostBattle::
	.string "…No way through.\n"
	.string "…Turn back…$"

SaffronCity_Gym_Text_GymGuyAdvice::
	.string "…Champ in the making. …No.\n"
	.string "That is not my voice.\p"
	.string "Hear me under it, kid.\n"
	.string "Trust NO ONE in this gym.\p"
	.string "Not the panels. Not the hints.\n"
	.string "…Not even me.\p"
	.string "One truth slips past her:\n"
	.string "FIGHTING folds fast to PSYCHIC.\p"
	.string "…Go. Before she notices\n"
	.string "I said that.$"

SaffronCity_Gym_Text_GymGuyPostVictory::
	.string "Whew! My head is my own again!\p"
	.string "You hear that? Laughter. From the\n"
	.string "GYM.\p"
	.string "…When did SABRINA last laugh?\n"
	.string "The whole town just breathed out.$"

SaffronCity_Gym_Text_GymStatue::
	.string "SAFFRON POKéMON GYM\n"
	.string "LEADER: SABRINA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}$"

SaffronCity_Gym_Text_GymStatuePlayerWon::
	.string "SAFFRON POKéMON GYM\n"
	.string "LEADER: SABRINA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"

