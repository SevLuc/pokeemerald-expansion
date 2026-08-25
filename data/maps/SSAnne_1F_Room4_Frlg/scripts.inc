SSAnne_1F_Room4_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room4_EventScript_Woman::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SSAnne_1F_Room4_EventScript_WomanPlayerMale
	msgbox SSAnne_1F_Room4_Text_WaitressCherryPiePlease
	release
	end

SSAnne_1F_Room4_EventScript_WomanPlayerMale::
	msgbox SSAnne_1F_Room4_Text_WaiterCherryPiePlease
	release
	end

SSAnne_1F_Room4_Text_WaiterCherryPiePlease::
	.string "Waiter, I would like a cherry pie,\n"
	.string "please!$"

SSAnne_1F_Room4_Text_WaitressCherryPiePlease::
	.string "Waitress! A slice of cherry pie,\n"
	.string "and mind the crust.\p"
	.string "One does travel to be spoiled,\n"
	.string "after all.$"

