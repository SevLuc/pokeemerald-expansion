LavenderTown_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

LavenderTown_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_LAVENDER_TOWN
	end

LavenderTown_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

LavenderTown_PokemonCenter_1F_EventScript_Gentleman::
	msgbox LavenderTown_PokemonCenter_1F_Text_RocketsDoAnythingForMoney, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_EventScript_Lass::
	msgbox LavenderTown_PokemonCenter_1F_Text_CubonesMotherKilledByRockets, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_EventScript_Youngster::
	msgbox LavenderTown_PokemonCenter_1F_Text_PeoplePayForCuboneSkulls, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_1F_Text_RocketsDoAnythingForMoney::
	.string "You know AGATHA of the ELITE\n"
	.string "FOUR? The GHOST trainer?\p"
	.string "She trained here as a girl, among\n"
	.string "the TOWER's spirits.\p"
	.string "Fierce even then. …Back when a\n"
	.string "friend of hers chose books over\l"
	.string "battle.$"

LavenderTown_PokemonCenter_1F_Text_CubonesMotherKilledByRockets::
	.string "I saw CUBONE's mother trying to\n"
	.string "escape from TEAM ROCKET.\p"
	.string "She was killed trying to get away…$"

LavenderTown_PokemonCenter_1F_Text_PeoplePayForCuboneSkulls::
	.string "You know how the CUBONE species\n"
	.string "wears skulls, right?\p"
	.string "People will pay a lot for one.$"

