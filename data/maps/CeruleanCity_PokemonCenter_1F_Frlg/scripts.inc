CeruleanCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

CeruleanCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	end

CeruleanCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

CeruleanCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox CeruleanCity_PokemonCenter_1F_Text_EveryoneCallsBillPokemaniac, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_1F_EventScript_Rocker::
	msgbox CeruleanCity_PokemonCenter_1F_Text_BillDoesWhateverForRareMons, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_1F_EventScript_Youngster::
	lock
	faceplayer
	famechecker FAMECHECKER_BILL, 1
	msgbox CeruleanCity_PokemonCenter_1F_Text_BillCollectsRareMons
	release
	end

CeruleanCity_PokemonCenter_1F_EventScript_Lass::
	msgbox CeruleanCity_PokemonCenter_1F_Text_TryTradingUpstairs, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_1F_Text_BillDoesWhateverForRareMons::
	.string "Rare POKéMON? Head south to\n"
	.string "VERMILION sometime.\p"
	.string "Loud fella runs the GYM there.\n"
	.string "Electric types, and plenty.\p"
	.string "That city wasn't always so free,\n"
	.string "they say. …No one will tell you why.$"

CeruleanCity_PokemonCenter_1F_Text_EveryoneCallsBillPokemaniac::
	.string "You won't find MISTY in town\n"
	.string "half the time, you know.\p"
	.string "Off chasing that PSYDUCK again.\n"
	.string "The thing never stays put.\p"
	.string "Slips its BALL and wanders off…\n"
	.string "she always goes and fetches it.$"

CeruleanCity_PokemonCenter_1F_Text_BillCollectsRareMons::
	.string "BILL has lots of POKéMON!\n"
	.string "He collects all the rare ones!\p"
	.string "MISTY only ever keeps WATER\n"
	.string "types, though. …I wonder why.$"

CeruleanCity_PokemonCenter_1F_Text_TryTradingUpstairs::
	.string "Head upstairs and trade POKéMON\n"
	.string "with a friend sometime.\p"
	.string "You'll turn up all sorts you'd\n"
	.string "never catch yourself.\p"
	.string "And a traded POKéMON grows\n"
	.string "a touch faster, too.\p"
	.string "Our LEADER never trades a thing,\n"
	.string "mind. Keeps to her own pool.$"

