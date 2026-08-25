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
	.string "A cruise like this is the only\n"
	.string "proper way to meet the sea.\p"
	.string "And CINNABAR is the sea's true\n"
	.string "door. Say what you like.$"

SSAnne_1F_Room3_Text_AlwaysTravelWithWigglytuff::
	.string "WIGGLYTUFF comes everywhere I go.\p"
	.string "It sings me to sleep when the waves\n"
	.string "get too loud at night.$"

SSAnne_1F_Room3_Text_Wigglytuff::
	.string "WIGGLYTUFF: Puup pupuu!$"

