SSAnne_1F_Room3_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room3_EventScript_LittleGirl::
	msgbox SSAnne_1F_Room3_Text_AlwaysTravelWithWigglytuff, MSGBOX_NPC
	end

SSAnne_1F_Room3_EventScript_BaldingMan::
	msgbox SSAnne_1F_Room3_Text_CruiseIsElegantAndCozy, MSGBOX_NPC
	end

SSAnne_1F_Room3_EventScript_Wigglytuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WIGGLYTUFF, CRY_MODE_NORMAL
	msgbox SSAnne_1F_Room3_Text_Wigglytuff
	waitmoncry
	release
	end

SSAnne_1F_Room3_Text_CruiseIsElegantAndCozy::
	.string "No proper way to meet the\n"
	.string "sea but a cruise.\p"
	.string "And CINNABAR is its true\n"
	.string "door…$"

SSAnne_1F_Room3_Text_AlwaysTravelWithWigglytuff::
	.string "WIGGLYTUFF goes where\n"
	.string "I go.\p"
	.string "When the waves get loud,\n"
	.string "it hums to me…$"

SSAnne_1F_Room3_Text_Wigglytuff::
	.string "WIGGLYTUFF: Puup pupuu!$"

