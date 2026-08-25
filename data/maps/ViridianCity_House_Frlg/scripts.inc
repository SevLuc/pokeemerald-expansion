ViridianCity_House_Frlg_MapScripts::
	.byte 0

ViridianCity_House_EventScript_BaldingMan::
	msgbox ViridianCity_House_Text_NicknamingIsFun, MSGBOX_NPC
	end

ViridianCity_House_EventScript_LittleGirl::
	msgbox ViridianCity_House_Text_MyDaddyLovesMonsToo, MSGBOX_NPC
	end

ViridianCity_House_EventScript_Speary::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SPEAROW, CRY_MODE_NORMAL
	msgbox ViridianCity_House_Text_Speary
	waitmoncry
	release
	end

ViridianCity_House_EventScript_NicknameSign::
	msgbox ViridianCity_House_Text_SpearowNameSpeary, MSGBOX_SIGN
	end

ViridianCity_House_Text_NicknamingIsFun::
	.string "PALLET buried a box, long ago.\p"
	.string "To be opened only when one of\n"
	.string "ours reaches the very top…$"

ViridianCity_House_Text_MyDaddyLovesMonsToo::
	.string "My daddy loves POKéMON, too!\p"
	.string "He says he'll catch me a little\n"
	.string "one someday.$"

ViridianCity_House_Text_Speary::
	.string "SPEARY: Tetweet!$"

ViridianCity_House_Text_SpearowNameSpeary::
	.string "SPEAROW\n"
	.string "Name: SPEARY$"

