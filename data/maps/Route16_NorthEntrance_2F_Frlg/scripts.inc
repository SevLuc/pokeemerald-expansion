.equ REQUIRED_CAUGHT_MONS, 40

Route16_NorthEntrance_2F_Frlg_MapScripts::
	.byte 0

Route16_NorthEntrance_2F_EventScript_LittleBoy::
	msgbox Route16_NorthEntrance_2F_Text_OnBikeRideWithGirlfriend, MSGBOX_NPC
	end

Route16_NorthEntrance_2F_EventScript_LittleGirl::
	msgbox Route16_NorthEntrance_2F_Text_RidingTogetherOnNewBikes, MSGBOX_NPC
	end

Route16_NorthEntrance_2F_EventScript_LeftBinoculars::
	msgbox Route16_NorthEntrance_2F_Text_ItsCeladonDeptStore, MSGBOX_SIGN
	end

Route16_NorthEntrance_2F_EventScript_RightBinoculars::
	msgbox Route16_NorthEntrance_2F_Text_LongPathOverWater, MSGBOX_SIGN
	end

Route16_NorthEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_AMULET_COIN_FROM_OAKS_AIDE, Route16_NorthEntrance_2F_EventScript_AlreadyGotAmuletCoin
	msgbox Route16_NorthEntrance_2F_Text_GiveAmuletCoinIfCaught40, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_CAUGHT_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route16_NorthEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_AMULET_COIN
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route16_NorthEntrance_2F_Text_ReceivedAmuletCoinFromAide, ITEM_AMULET_COIN
	setflag FLAG_GOT_AMULET_COIN_FROM_OAKS_AIDE
	msgbox Route16_NorthEntrance_2F_Text_ExplainAmuletCoin
	release
	end

Route16_NorthEntrance_2F_EventScript_AlreadyGotAmuletCoin::
	msgbox Route16_NorthEntrance_2F_Text_ExplainAmuletCoin
	release
	end

Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_AMULET_COIN
	return

Route16_NorthEntrance_2F_Text_OnBikeRideWithGirlfriend::
	.string "Me and my girl are out for a\n"
	.string "lazy spin on our new bikes.$"

Route16_NorthEntrance_2F_Text_RidingTogetherOnNewBikes::
	.string "We saved up ages for these\n"
	.string "bikes.\p"
	.string "Today's our very first ride out\n"
	.string "together!$"

Route16_NorthEntrance_2F_Text_ItsCeladonDeptStore::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "It's the CELADON DEPT. STORE!$"

Route16_NorthEntrance_2F_Text_LongPathOverWater::
	.string "Let's see what the binoculars have\n"
	.string "to show…\p"
	.string "There's a long path over water far\n"
	.string "away.$"

Route16_NorthEntrance_2F_Text_GiveAmuletCoinIfCaught40::
	.string "Hello again! One of PROF. OAK's\n"
	.string "AIDES, remember?\p"
	.string "Forty species in the POKéDEX\n"
	.string "earns a reward, OAK says,\l"
	.string "and I'm the one holding it.\p"
	.string "An AMULET COIN, left in my care\n"
	.string "for you.\p"
	.string "So then, {PLAYER}.\p"
	.string "Have you gathered data on at\n"
	.string "least 40 kinds of POKéMON?$"

Route16_NorthEntrance_2F_Text_GreatHereYouGo::
	.string "Marvelous! {STR_VAR_3} kinds on\n"
	.string "record already!\p"
	.string "You've earned this. Take it!$"

Route16_NorthEntrance_2F_Text_ReceivedAmuletCoinFromAide::
	.string "{PLAYER} received the AMULET COIN\n"
	.string "from the AIDE.$"

Route16_NorthEntrance_2F_Text_ExplainAmuletCoin::
	.string "An AMULET COIN is a held item.\p"
	.string "Let its holder share in a win,\n"
	.string "and the prize money climbs.$"

