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
	.string "My neighbor down PALLET way\n"
	.string "tells an old story.\p"
	.string "They buried a box, generations\n"
	.string "back.\p"
	.string "To be opened only when one of\n"
	.string "theirs reaches the very top.\p"
	.string "Nobody living recalls what's\n"
	.string "inside. …A long wait, that.$"

ViridianCity_House_Text_MyDaddyLovesMonsToo::
	.string "My daddy loves POKéMON, too!\p"
	.string "He says someday he'll catch me\n"
	.string "a little one all my own.$"

ViridianCity_House_Text_Speary::
	.string "SPEARY: Tetweet!$"

ViridianCity_House_Text_SpearowNameSpeary::
	.string "SPEAROW\n"
	.string "Name: SPEARY$"

