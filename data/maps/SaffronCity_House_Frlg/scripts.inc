SaffronCity_House_Frlg_MapScripts::
	.byte 0

SaffronCity_House_EventScript_Lass::
	msgbox SaffronCity_House_Text_DontLookAtMyLetter, MSGBOX_NPC
	end

SaffronCity_House_EventScript_Youngster::
	msgbox SaffronCity_House_Text_GettingCopycatPokeDoll, MSGBOX_NPC
	end

SaffronCity_House_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox SaffronCity_House_Text_Pidgey
	waitmoncry
	release
	end

SaffronCity_House_EventScript_Letter::
	msgbox SaffronCity_House_Text_ExplainPPUp, MSGBOX_SIGN
	end

SaffronCity_House_Text_DontLookAtMyLetter::
	.string "…Thank you for writing.\n"
	.string "I hope to see you soon.\p"
	.string "…She stopped writing back, though.\n"
	.string "Right when folks started vanishing.\p"
	.string "So I keep writing anyway. And I\n"
	.string "keep a lamp lit in the window.\p"
	.string "…Hey! Don't read my letter!$"

SaffronCity_House_Text_Pidgey::
	.string "PIDGEY: Kurukkoo!$"

SaffronCity_House_Text_GettingCopycatPokeDoll::
	.string "The COPYCAT is cute!\n"
	.string "I'm getting her a POKé DOLL.\p"
	.string "The grown-ups get all weird about\n"
	.string "dolls lately. Won't say why.\p"
	.string "It's just a doll! …Right?$"

SaffronCity_House_Text_ExplainPPUp::
	.string "I was given a PP UP as a gift.\p"
	.string "It's used to increase the PP of\n"
	.string "a POKéMON's move.\p"
	.string "I should use it on a powerful move\n"
	.string "with only a few PP.$"

