FuchsiaCity_Gym_Frlg_MapScripts::
	.byte 0

FuchsiaCity_Gym_EventScript_Koga::
	famechecker FAMECHECKER_KOGA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_KOGA, FuchsiaCity_Gym_Text_KogaIntro, FuchsiaCity_Gym_Text_KogaDefeat, FuchsiaCity_Gym_EventScript_DefeatedKoga, NO_MUSIC
	goto_if_unset FLAG_GOT_TM06_FROM_KOGA, FuchsiaCity_Gym_EventScript_GiveTM06
	msgbox FuchsiaCity_Gym_Text_KogaPostBattle
	release
	end

FuchsiaCity_Gym_EventScript_DefeatedKoga::
	famechecker FAMECHECKER_KOGA, 1
	clearflag FLAG_HIDE_FAME_CHECKER_KOGA_JOURNAL
	setflag FLAG_DEFEATED_KOGA
	setflag FLAG_BADGE05_GET
	set_gym_trainers_frlg 5
	goto FuchsiaCity_Gym_EventScript_GiveTM06
	end

FuchsiaCity_Gym_EventScript_GiveTM06::
	msgbox FuchsiaCity_Gym_Text_KogaExplainSoulBadge
	checkitemspace ITEM_TM06
	goto_if_eq VAR_RESULT, FALSE, FuchsiaCity_Gym_EventScript_NoRoomForTM06
	giveitem_msg FuchsiaCity_Gym_Text_ReceivedTM06FromKoga, ITEM_TM06
	setflag FLAG_GOT_TM06_FROM_KOGA
	msgbox FuchsiaCity_Gym_Text_KogaExplainTM06
	release
	end

FuchsiaCity_Gym_EventScript_NoRoomForTM06::
	msgbox FuchsiaCity_Gym_Text_MakeSpaceForThis
	release
	end

FuchsiaCity_Gym_EventScript_Phil::
	trainerbattle_single TRAINER_TAMER_PHIL, FuchsiaCity_Gym_Text_PhilIntro, FuchsiaCity_Gym_Text_PhilDefeat
	msgbox FuchsiaCity_Gym_Text_PhilPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Edgar::
	trainerbattle_single TRAINER_TAMER_EDGAR, FuchsiaCity_Gym_Text_EdgarIntro, FuchsiaCity_Gym_Text_EdgarDefeat
	msgbox FuchsiaCity_Gym_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Kirk::
	trainerbattle_single TRAINER_JUGGLER_KIRK, FuchsiaCity_Gym_Text_KirkIntro, FuchsiaCity_Gym_Text_KirkDefeat
	famechecker FAMECHECKER_KOGA, 2
	msgbox FuchsiaCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Shawn::
	trainerbattle_single TRAINER_JUGGLER_SHAWN, FuchsiaCity_Gym_Text_ShawnIntro, FuchsiaCity_Gym_Text_ShawnDefeat
	msgbox FuchsiaCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Kayden::
	trainerbattle_single TRAINER_JUGGLER_KAYDEN, FuchsiaCity_Gym_Text_KaydenIntro, FuchsiaCity_Gym_Text_KaydenDefeat
	msgbox FuchsiaCity_Gym_Text_KaydenPostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_JUGGLER_NATE, FuchsiaCity_Gym_Text_NateIntro, FuchsiaCity_Gym_Text_NateDefeat
	msgbox FuchsiaCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

FuchsiaCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_KOGA, FuchsiaCity_Gym_EventScript_GymGuyPostVictory
	msgbox FuchsiaCity_Gym_Text_GymGuyAdvice
	release
	end

FuchsiaCity_Gym_EventScript_GymGuyPostVictory::
	msgbox FuchsiaCity_Gym_Text_GymGuyPostVictory
	release
	end

FuchsiaCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, FuchsiaCity_Gym_EventScript_GymStatuePostVictory
	msgbox FuchsiaCity_Gym_Text_GymStatue
	releaseall
	end

FuchsiaCity_Gym_EventScript_GymStatuePostVictory::
	msgbox FuchsiaCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

FuchsiaCity_Gym_Text_KogaIntro::
	.string "KOGA: Fwahahaha!\p"
	.string "Another challenger. Do you know\n"
	.string "what this city runs on?\p"
	.string "Me. My works. My smoke.\n"
	.string "Every lamp in KANTO, lit by KOGA.\p"
	.string "I light your homes. I warm\n"
	.string "your winters. Essentially, a HERO.\p"
	.string "Still they send children to test\n"
	.string "me. …The ingratitude.\p"
	.string "Very well. My POISON built this\n"
	.string "empire, and it will bury you in it.\p"
	.string "Sleep. Suffer. Despair.\n"
	.string "Progress waits for no one!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

FuchsiaCity_Gym_Text_KogaDefeat::
	.string "Kh… you bested me. Rare.\p"
	.string "I respect two things, child.\n"
	.string "Results, and leverage.\p"
	.string "You have both. The SOULBADGE\n"
	.string "is yours.\p"
	.string "…And a talent like that,\n"
	.string "chasing little badges? Hm.\p"
	.string "We should talk. Properly.$"

FuchsiaCity_Gym_Text_KogaPostBattle::
	.string "When afflicted by TOXIC, a POKéMON\n"
	.string "suffers more and more.\p"
	.string "It suffers worsening damage as the\n"
	.string "battle wears on!\p"
	.string "It will surely terrorize foes!\p"
	.string "Hmph. You fight well.\n"
	.string "KOGA INDUSTRIES could use talent.\p"
	.string "Think on it. The lights of KANTO\n"
	.string "won't keep themselves lit.$"

FuchsiaCity_Gym_Text_KogaExplainSoulBadge::
	.string "The SOULBADGE. A sound return\n"
	.string "on your investment.\p"
	.string "Your POKéMON's DEFENSE rises.\n"
	.string "Assets, properly protected.\p"
	.string "And you may SURF now, any water\n"
	.string "you please. Mine included.\p"
	.string "Take this as well. A signing bonus.$"

FuchsiaCity_Gym_Text_ReceivedTM06FromKoga::
	.string "{PLAYER} received TM06\n"
	.string "from KOGA.$"

FuchsiaCity_Gym_Text_KogaExplainTM06::
	.string "And this. TM06. TOXIC.\p"
	.string "Four centuries in the perfecting.\n"
	.string "Our founding product, you'd say.\p"
	.string "Poison built KOGA INDUSTRIES.\n"
	.string "…And KOGA INDUSTRIES built KANTO.$"

FuchsiaCity_Gym_Text_MakeSpaceForThis::
	.string "Make space, child.\n"
	.string "Opportunity knocks but once.$"

FuchsiaCity_Gym_Text_KaydenIntro::
	.string "Strength isn't the key for POKéMON.\n"
	.string "Do you understand this?\p"
	.string "POKéMON is about strategy!\p"
	.string "I'll show you how strategy can\n"
	.string "beat brute strength.$"

FuchsiaCity_Gym_Text_KaydenDefeat::
	.string "What?\n"
	.string "Extraordinary!$"

FuchsiaCity_Gym_Text_KaydenPostBattle::
	.string "So, you mix brawn with brains?\n"
	.string "Good strategy!\p"
	.string "That's remarkable for a child\n"
	.string "TRAINER.$"

FuchsiaCity_Gym_Text_KirkIntro::
	.string "I was a magician once upon a time.\p"
	.string "But I dreamt of becoming a ninja,\n"
	.string "so I joined this GYM.$"

FuchsiaCity_Gym_Text_KirkDefeat::
	.string "I'm done for!$"

FuchsiaCity_Gym_Text_KirkPostBattle::
	.string "Even though I've lost, I will keep\n"
	.string "training according to the teachings\l"
	.string "of KOGA, my ninja master.\p"
	.string "…Though he hired me for the old\n"
	.string "trade. Misdirection.\p"
	.string "The costume. The maze.\n"
	.string "Look here, so you don't look there.$"

FuchsiaCity_Gym_Text_NateIntro::
	.string "Let's see you beat my special\n"
	.string "techniques!$"

FuchsiaCity_Gym_Text_NateDefeat::
	.string "You had me fooled!$"

FuchsiaCity_Gym_Text_NatePostBattle::
	.string "I like poison and sleep techniques,\n"
	.string "as they linger after battle!$"

FuchsiaCity_Gym_Text_PhilIntro::
	.string "Stop right there!\p"
	.string "The famed invisible walls of\n"
	.string "FUCHSIA GYM have you frustrated?$"

FuchsiaCity_Gym_Text_PhilDefeat::
	.string "Whoa!\n"
	.string "You've got it!$"

FuchsiaCity_Gym_Text_PhilPostBattle::
	.string "You impressed me!\n"
	.string "Here's a hint!\p"
	.string "Look very closely for gaps in the\n"
	.string "invisible walls!$"

FuchsiaCity_Gym_Text_EdgarIntro::
	.string "I also study the way of the ninja\n"
	.string "with Master KOGA!\p"
	.string "Ninja have a long history of using\n"
	.string "animals!$"

FuchsiaCity_Gym_Text_EdgarDefeat::
	.string "Awoo!$"

FuchsiaCity_Gym_Text_EdgarPostBattle::
	.string "I still have much to learn.$"

FuchsiaCity_Gym_Text_ShawnIntro::
	.string "Master KOGA comes from a long line\n"
	.string "of ninjas.\p"
	.string "What did you descend from?$"

FuchsiaCity_Gym_Text_ShawnDefeat::
	.string "You're more skilled than I'd\n"
	.string "thought!$"

FuchsiaCity_Gym_Text_ShawnPostBattle::
	.string "Where there is light, there is\n"
	.string "shadow!\p"
	.string "Light and shadow!\n"
	.string "Which do you choose?\p"
	.string "Spectacle and smoke. The MASTER\n"
	.string "taught me both.\p"
	.string "One you watch. One you breathe.$"

FuchsiaCity_Gym_Text_GymGuyAdvice::
	.string "Yo!\n"
	.string "Champ in the making!\p"
	.string "FUCHSIA GYM is a tricked-up place.\n"
	.string "It's riddled with invisible walls!\p"
	.string "KOGA might appear close, but he's\n"
	.string "blocked off.\p"
	.string "You have to find gaps in the walls\n"
	.string "to reach him.$"

FuchsiaCity_Gym_Text_GymGuyPostVictory::
	.string "It's amazing how ninja can terrify,\n"
	.string "even now!\p"
	.string "You know who else gets lost in\n"
	.string "these walls?\p"
	.string "Folks who march in to shout at KOGA\n"
	.string "about the smog.\p"
	.string "They wander an hour and leave too\n"
	.string "hoarse to bother. …Clever, that.$"

FuchsiaCity_Gym_Text_GymStatue::
	.string "FUCHSIA POKéMON GYM\n"
	.string "LEADER: KOGA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}$"

FuchsiaCity_Gym_Text_GymStatuePlayerWon::
	.string "FUCHSIA POKéMON GYM\n"
	.string "LEADER: KOGA\p"
	.string "WINNING TRAINERS:\n"
	.string "{RIVAL}, {PLAYER}$"

