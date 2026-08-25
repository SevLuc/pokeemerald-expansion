SSAnne_B1F_Room5_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room5_EventScript_Boy::
	msgbox SSAnne_B1F_Room5_Text_MachokeHasStrengthToMoveRocks, MSGBOX_NPC
	end

SSAnne_B1F_Room5_EventScript_Machoke::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOKE, CRY_MODE_NORMAL
	msgbox SSAnne_B1F_Room5_Text_Machoke
	waitmoncry
	release
	end

SSAnne_B1F_Room5_Text_MachokeHasStrengthToMoveRocks::
	.string "My MACHOKE's the strongest\n"
	.string "pal aboard!\p"
	.string "Shoves crates the sailors\n"
	.string "can't budge…$"

SSAnne_B1F_Room5_Text_Machoke::
	.string "MACHOKE: Gwoh! Goggoh!$"

