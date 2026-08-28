SSAnne_2F_Room2_Frlg_MapScripts::
	.byte 0

SSAnne_2F_Room2_EventScript_Brooks::
	trainerbattle_single TRAINER_GENTLEMAN_BROOKS, SSAnne_2F_Room2_Text_BrooksIntro, SSAnne_2F_Room2_Text_BrooksDefeat
	msgbox SSAnne_2F_Room2_Text_BrooksPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room2_Text_BrooksIntro::
	.string "Competing against the young keeps\n"
	.string "me youthful.$"

SSAnne_2F_Room2_Text_BrooksDefeat::
	.string "Good match!\n"
	.string "Ah, I feel young again!$"

SSAnne_2F_Room2_Text_BrooksPostBattle::
	.string "Fifteen years ago, I would\n"
	.string "have won!$"


