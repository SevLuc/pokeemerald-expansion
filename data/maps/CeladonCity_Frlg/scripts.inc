CeladonCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_OnTransition
	.byte 0

CeladonCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CELADON_CITY
	end

CeladonCity_EventScript_LittleGirl::
	msgbox CeladonCity_Text_GotMyKoffingInCinnabar, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan1::
	lock
	faceplayer
	goto_if_set FLAG_BADGE04_GET, CeladonCity_EventScript_OldMan1PostBadge
	msgbox CeladonCity_Text_GymIsGreatFullOfWomen
	release
	end

CeladonCity_EventScript_OldMan1PostBadge::
	msgbox CeladonCity_Text_OldMan1ErikaWink
	release
	end

CeladonCity_EventScript_Woman::
	msgbox CeladonCity_Text_GameCornerIsBadForCitysImage, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan2::
	msgbox CeladonCity_Text_BlewItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_EventScript_SoftboiledTutor::
	goto EventScript_SoftboiledTutor
	end

CeladonCity_EventScript_FatMan::
	lock
	faceplayer
	msgbox CeladonCity_Text_MyTrustedPalPoliwrath
	closemessage
	applymovement LOCALID_CELADON_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_Poliwrath::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
	msgbox CeladonCity_Text_Poliwrath
	closemessage
	waitmoncry
	applymovement LOCALID_CELADON_POLIWRATH, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_RocketGrunt1::
	msgbox CeladonCity_Text_KeepOutOfTeamRocketsWay, MSGBOX_NPC
	end

CeladonCity_EventScript_RocketGrunt2::
	msgbox CeladonCity_Text_GetLostOrIllPunchYou, MSGBOX_NPC
	end

CeladonCity_EventScript_Boy::
	msgbox CeladonCity_Text_ScaldedTongueOnTea, MSGBOX_NPC
	end

CeladonCity_EventScript_SilphCoScientist::
	msgbox CeladonCity_Text_SomeoneStoleSilphScope, MSGBOX_NPC
	end

CeladonCity_EventScript_TrainerTips1::
	msgbox CeladonCity_Text_ExplainXAccuracyDireHit, MSGBOX_SIGN
	end

CeladonCity_EventScript_CitySign::
	msgbox CeladonCity_Text_CitySign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_ERIKA, 0
	msgbox CeladonCity_Text_GymSign
	releaseall
	end

CeladonCity_EventScript_MansionSign::
	msgbox CeladonCity_Text_MansionSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_DeptStoreSign::
	msgbox CeladonCity_Text_DeptStoreSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_TrainerTips2::
	msgbox CeladonCity_Text_GuardSpecProtectsFromStatus, MSGBOX_SIGN
	end

CeladonCity_EventScript_PrizeExchangeSign::
	msgbox CeladonCity_Text_PrizeExchangeSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GameCornerSign::
	msgbox CeladonCity_Text_GameCornerSign, MSGBOX_SIGN
	end

CeladonCity_Text_GotMyKoffingInCinnabar::
	.string "I got my KOFFING in CINNABAR.\p"
	.string "It's usually nice, but it breathes\n"
	.string "poison when it's angry.\p"
	.string "…ERIKA grows flowers like that.\p"
	.string "Pretty ones. But mom says never\n"
	.string "sniff one twice. …I forget why.$"

CeladonCity_Text_GymIsGreatFullOfWomen::
	.string "Heheh! This GYM is great!\n"
	.string "It's full of women!\p"
	.string "…Though I hear she teaches them\n"
	.string "more than flowers in there.\p"
	.string "Wouldn't know. Never once got\n"
	.string "past the door.$"

CeladonCity_Text_OldMan1ErikaWink::
	.string "So you beat ERIKA?\p"
	.string "And you still can't tell me one\n"
	.string "true thing about her.\p"
	.string "Heh. …That's ERIKA.$"

CeladonCity_Text_GameCornerIsBadForCitysImage::
	.string "CELADON takes pride in its efforts\n"
	.string "to keep the city beautiful.\p"
	.string "That's why the new GAME CORNER is\n"
	.string "bad for our city's image.\p"
	.string "Mind, some say it's no accident\n"
	.string "we stay so lovely.\p"
	.string "ERIKA's perfumes, on the wind.\n"
	.string "…I don't ask. I just breathe.$"

CeladonCity_Text_BlewItAllAtSlots::
	.string "Moan…\n"
	.string "I blew it all at the slots!\p"
	.string "I knew I should have cashed in my\n"
	.string "COINS for prizes!$"

CeladonCity_Text_MyTrustedPalPoliwrath::
	.string "This is my trusted pal, POLIWRATH.\p"
	.string "It evolved from a POLIWHIRL when\n"
	.string "I used a WATER STONE.\p"
	.string "Strong as he is, I'd not face\n"
	.string "ERIKA with him.\p"
	.string "I saw her battle once, years back.\n"
	.string "…I've slept poorly ever since.$"

CeladonCity_Text_Poliwrath::
	.string "POLIWRATH: Ribi ribit!$"

CeladonCity_Text_GetLostOrIllPunchYou::
	.string "What are you staring at?\n"
	.string "Get lost, or I'll punch you.$"

CeladonCity_Text_KeepOutOfTeamRocketsWay::
	.string "Keep out of TEAM ROCKET's way!\p"
	.string "…But you keep clear of that GYM,\n"
	.string "too. Boss's orders.\p"
	.string "Something about her garden.\n"
	.string "I don't ask twice.$"

CeladonCity_Text_ExplainXAccuracyDireHit::
	.string "TRAINER TIPS\p"
	.string "X ACCURACY boosts the accuracy of\n"
	.string "techniques.\p"
	.string "DIRE HIT jacks up the likelihood\n"
	.string "of critical hits.\p"
	.string "Get your items at the CELADON\n"
	.string "DEPT. STORE!$"

CeladonCity_Text_CitySign::
	.string "CELADON CITY\n"
	.string "The City of Rainbow Dreams$"

CeladonCity_Text_GymSign::
	.string "CELADON CITY POKéMON GYM\n"
	.string "LEADER: ERIKA\l"
	.string "The Nature-Loving Princess!$"

CeladonCity_Text_MansionSign::
	.string "CELADON MANSION$"

CeladonCity_Text_DeptStoreSign::
	.string "Find what you need at the\n"
	.string "CELADON DEPT. STORE!$"

CeladonCity_Text_GuardSpecProtectsFromStatus::
	.string "TRAINER TIPS\p"
	.string "GUARD SPEC. protects POKéMON\n"
	.string "from status-reduction moves during\l"
	.string "battle.\p"
	.string "Get your items at the\n"
	.string "CELADON DEPT. STORE!$"

CeladonCity_Text_PrizeExchangeSign::
	.string "COINS exchanged for prizes!\n"
	.string "PRIZE EXCHANGE$"

CeladonCity_Text_GameCornerSign::
	.string "ROCKET GAME CORNER\n"
	.string "The playground for grown-ups!$"

CeladonCity_Text_ScaldedTongueOnTea::
	.string "Aaaagh, ow…\n"
	.string "I scalded my tongue!\p"
	.string "This nice old lady in the MANSION\n"
	.string "gave me some TEA.\p"
	.string "But it was boiling hot!\n"
	.string "Gotta cool it to drink it.\p"
	.string "…They say her tea leaves come\n"
	.string "from ERIKA's garden.\p"
	.string "Maybe that's why I saw colors\n"
	.string "that don't have names.$"

Text_SoftboiledTeach::
	.string "Hello, there!\p"
	.string "I've seen you about, but I never\n"
	.string "had a chance to chat.\p"
	.string "It must be good luck that brought\n"
	.string "us together finally.\p"
	.string "I'd like to celebrate by teaching\n"
	.string "you the move SOFTBOILED.$"

Text_SoftboiledDeclined::
	.string "I'll always be keeping an eye out\n"
	.string "for you.\p"
	.string "I hope we can chat again.$"

Text_SoftboiledWhichMon::
	.string "So, who's the POKéMON that gets\n"
	.string "the chance to learn SOFTBOILED?$"

Text_SoftboiledTaught::
	.string "I wish you the best of luck!$"

CeladonCity_Text_SomeoneStoleSilphScope::
	.string "Oh, what am I to do…\p"
	.string "Someone stole our SILPH SCOPE.\p"
	.string "The thief came running this way,\n"
	.string "I'm sure of it.\p"
	.string "But I lost sight of him!\n"
	.string "Where'd he go?$"

