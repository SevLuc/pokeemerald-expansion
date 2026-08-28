SSAnne_B1F_Room1_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room1_EventScript_Barny::
	trainerbattle_single TRAINER_FISHERMAN_BARNY, SSAnne_B1F_Room1_Text_BarnyIntro, SSAnne_B1F_Room1_Text_BarnyDefeat
	msgbox SSAnne_B1F_Room1_Text_BarnyPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room1_Text_BarnyIntro::
	.string "Hello, stranger!\p"
	.string "I can't tell if you're from the seas\n"
	.string "or mountains, but stop and chat.\p"
	.string "All my POKéMON are from the sea.$"

SSAnne_B1F_Room1_Text_BarnyDefeat::
	.string "Darn!\n"
	.string "I let that one get away!$"

SSAnne_B1F_Room1_Text_BarnyPostBattle::
	.string "I was going to make you my\n"
	.string "assistant, too!$"

