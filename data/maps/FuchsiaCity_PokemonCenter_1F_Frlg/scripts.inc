FuchsiaCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FuchsiaCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_FUCHSIA_CITY
	end

FuchsiaCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

FuchsiaCity_PokemonCenter_1F_EventScript_Man::
	msgbox FuchsiaCity_PokemonCenter_1F_Text_CantBecomeGoodTrainerWithOneMon, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_1F_EventScript_CooltrainerF::
	msgbox FuchsiaCity_PokemonCenter_1F_Text_PokemonLeagueWestOfViridian, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox FuchsiaCity_PokemonCenter_1F_Text_VisitSafariZoneForPokedex, MSGBOX_NPC
	end

FuchsiaCity_PokemonCenter_1F_Text_CantBecomeGoodTrainerWithOneMon::
	.string "You can't become a good TRAINER\n"
	.string "with just one strong POKéMON.\p"
	.string "But raising many POKéMON evenly\n"
	.string "is no easy task, either.\p"
	.string "Funny. A whole city can run off one\n"
	.string "POKéMON's breath, and does.\p"
	.string "You don't raise a fuss about it.\n"
	.string "You just… breathe it in.$"

FuchsiaCity_PokemonCenter_1F_Text_PokemonLeagueWestOfViridian::
	.string "The road to the LEAGUE starts\n"
	.string "far west, past VIRIDIAN.\p"
	.string "A long way from a quiet town\n"
	.string "like this one.\p"
	.string "…Best get walking, then.$"

FuchsiaCity_PokemonCenter_1F_Text_VisitSafariZoneForPokedex::
	.string "The SAFARI ZONE is full of\n"
	.string "POKéMON you see nowhere else.\p"
	.string "I spotted a KANGASKHAN once.\n"
	.string "Just once. Never again.$"

