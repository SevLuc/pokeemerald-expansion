SaffronCity_CopycatsHouse_1F_Frlg_MapScripts::
	.byte 0

SaffronCity_CopycatsHouse_1F_EventScript_CopycatsMom::
	msgbox SaffronCity_CopycatsHouse_1F_Text_DaughterIsSelfCentered, MSGBOX_NPC
	end

SaffronCity_CopycatsHouse_1F_EventScript_CopycatsDad::
	msgbox SaffronCity_CopycatsHouse_1F_Text_DaughterLikesToMimicPeople, MSGBOX_NPC
	end

SaffronCity_CopycatsHouse_1F_EventScript_Chansey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHANSEY, CRY_MODE_NORMAL
	msgbox SaffronCity_CopycatsHouse_1F_Text_Chansey
	waitmoncry
	release
	end

SaffronCity_CopycatsHouse_1F_Text_DaughterIsSelfCentered::
	.string "My daughter has only a few friends.\p"
	.string "Lately she won't go out at all.\n"
	.string "Just sits at the mirror.\p"
	.string "Making face after face at herself.\n"
	.string "Like she's holding on to herself.\p"
	.string "…I don't understand it. But I don't\n"
	.string "stop her, either.$"

SaffronCity_CopycatsHouse_1F_Text_DaughterLikesToMimicPeople::
	.string "My daughter likes to mimic people.\n"
	.string "That's how she got the name COPYCAT.\p"
	.string "She can do anyone in SAFFRON.\n"
	.string "Voice, face, the walk. Anyone.\p"
	.string "There's just one person she won't\n"
	.string "even try.\p"
	.string "Goes quiet if you ask. …I've\n"
	.string "learned to stop asking.$"

SaffronCity_CopycatsHouse_1F_Text_Chansey::
	.string "CHANSEY: Chaan! Sii!$"

