CeladonCity_Condominiums_3F_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_3F_EventScript_Programmer::
	msgbox CeladonCity_Condominiums_3F_Text_ImTheProgrammer, MSGBOX_NPC
	end

CeladonCity_Condominiums_3F_EventScript_GraphicArtist::
	msgbox CeladonCity_Condominiums_3F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

CeladonCity_Condominiums_3F_EventScript_Writer::
	msgbox CeladonCity_Condominiums_3F_Text_IWroteTheStory, MSGBOX_NPC
	end

CeladonCity_Condominiums_3F_EventScript_Designer::
	lock
	faceplayer
	specialvar VAR_RESULT, HasAllKantoMons
	goto_if_eq VAR_RESULT, TRUE, CeladonCity_Condominiums_3F_EventScript_CompletedPokedex
	msgbox CeladonCity_Condominiums_3F_Text_ImGameDesignerShowMeFinishedPokedex
	release
	end

CeladonCity_Condominiums_3F_EventScript_CompletedPokedex::
	goto CeladonCity_Condominiums_3F_EventScript_ShowDiploma
	end

CeladonCity_Condominiums_3F_EventScript_ShowDiploma::
	message CeladonCity_Condominiums_3F_Text_CompletedPokedexCongratulations
	waitmessage
	delay 60
	special Special_ShowDiploma
	release
	end

CeladonCity_Condominiums_3F_EventScript_DevelopmentRoomSign::
	msgbox CeladonCity_Condominiums_3F_Text_GameFreakDevelopmentRoom, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_EventScript_Computer1::
	msgbox CeladonCity_Condominiums_3F_Text_ItsTheGameProgram, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_EventScript_Computer2::
	msgbox CeladonCity_Condominiums_3F_Text_SomeonesPlayingGame, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_EventScript_Computer3::
	msgbox CeladonCity_Condominiums_3F_Text_ItsScriptBetterNotLookAtEnding, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_Text_ImTheProgrammer::
	.string "Me? I just play guitar.\p"
	.string "Can't sleep for that GAME\n"
	.string "CORNER jingle downtown.\p"
	.string "…Gets in your head like\n"
	.string "a slot reel, and it stays.$"

CeladonCity_Condominiums_3F_Text_ImTheGraphicArtist::
	.string "I sketch the routes for fun.\n"
	.string "Signs, bridges, all of it.\p"
	.string "Those little chalk arrows\n"
	.string "under the road signs, though?\p"
	.string "Don't look at me.\n"
	.string "I never drew a one of them.$"

CeladonCity_Condominiums_3F_Text_IWroteTheStory::
	.string "I've been writing a book\n"
	.string "about our GYM LEADER.\p"
	.string "Ten years now. Every draft,\n"
	.string "she comes out a different woman.\p"
	.string "…I've given up on finishing\n"
	.string "it. She won't hold still.$"

CeladonCity_Condominiums_3F_Text_ImGameDesignerShowMeFinishedPokedex::
	.string "The DEPT. STORE stocks\n"
	.string "near everything, they say.\p"
	.string "Near. The one thing I've\n"
	.string "wanted isn't on any floor.\p"
	.string "Been hunting it for years.\n"
	.string "…Half the fun's the hunt.$"

CeladonCity_Condominiums_3F_Text_CompletedPokedexCongratulations::
	.string "Wow! Excellent!\n"
	.string "You completed your POKéDEX!\l"
	.string "Congratulations!\l"
	.string "…$"

CeladonCity_Condominiums_3F_Text_ItsTheGameProgram::
	.string "It's the game program! Messing with\n"
	.string "it could bug out the game!$"

CeladonCity_Condominiums_3F_Text_SomeonesPlayingGame::
	.string "Someone's playing a game instead of\n"
	.string "working!$"

CeladonCity_Condominiums_3F_Text_ItsScriptBetterNotLookAtEnding::
	.string "It's the script!\n"
	.string "Better not look at the ending!$"

CeladonCity_Condominiums_3F_Text_GameFreakDevelopmentRoom::
	.string "GAME FREAK Development Room$"

