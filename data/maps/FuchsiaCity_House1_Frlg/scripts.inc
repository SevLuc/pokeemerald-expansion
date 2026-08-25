FuchsiaCity_House1_Frlg_MapScripts::
	.byte 0

FuchsiaCity_House1_EventScript_Woman::
	msgbox FuchsiaCity_House1_Text_WardenIsOldHasFalseTeeth, MSGBOX_NPC
	end

FuchsiaCity_House1_EventScript_OldMan::
	lock
	faceplayer
	famechecker FAMECHECKER_BILL, 2
	msgbox FuchsiaCity_House1_Text_BillIsMyGrandson
	release
	end

FuchsiaCity_House1_EventScript_LittleBoy::
	msgbox FuchsiaCity_House1_Text_BillFilesHisOwnMonData, MSGBOX_NPC
	end

FuchsiaCity_House1_Text_WardenIsOldHasFalseTeeth::
	.string "The SAFARI ZONE's WARDEN is old, \n"
	.string "but he's still very much active.\p"
	.string "All his teeth are false, though.\p"
	.string "He's fought KOGA's plants for\n"
	.string "years. Lost most of those fights.\p"
	.string "…We all did. We still flip KOGA's\n"
	.string "switches every morning.$"

FuchsiaCity_House1_Text_BillIsMyGrandson::
	.string "Hear that call out back?\n"
	.string "NIDORAN. The female one.\p"
	.string "Didn't need to look.$"

FuchsiaCity_House1_Text_BillFilesHisOwnMonData::
	.string "Grandpa names them by ear.\p"
	.string "I just point my POKéDEX.$"

