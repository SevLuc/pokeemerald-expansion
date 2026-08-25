SSAnne_2F_Room1_Frlg_MapScripts::
	.byte 0

SSAnne_2F_Room1_EventScript_Gentleman::
	lock
	faceplayer
	message SSAnne_2F_Room1_Text_SleepingMonLookedLikeThis
	waitmessage
	setvar VAR_0x8004, SPECIES_SNORLAX
	special SetSeenMon
	showmonpic SPECIES_SNORLAX, 10, 3
	waitbuttonpress
	hidemonpic
	release
	end

SSAnne_2F_Room1_Text_SleepingMonLookedLikeThis::
	.string "I've sailed to the ends of KANTO\n"
	.string "and back again.\p"
	.string "Never once have I seen a POKéMON\l"
	.string "sleep the way that one did.\p"
	.string "Flat on its back, snoring like the\n"
	.string "engine room. Like so!$"

