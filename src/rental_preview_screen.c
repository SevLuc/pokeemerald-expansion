#include "global.h"
#include "main.h"
#include "bg.h"
#include "gpu_regs.h"
#include "palette.h"
#include "window.h"
#include "text.h"
#include "menu.h"
#include "sprite.h"
#include "task.h"
#include "malloc.h"
#include "sound.h"
#include "string_util.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "move.h"
#include "item.h"
#include "constants/moves.h"
#include "data.h"
#include "party_menu.h"
#include "event_data.h"
#include "overworld.h"
#include "battle.h"
#include "battle_tower_rental.h"
#include "rental_mode.h"
#include "constants/battle.h"
#include "constants/items.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// ---------------------------------------------------------------------------
// RENTAL BATTLE team-preview board (UI proposal S3 / U4).
//
// Replaces the old comma-list team-preview message plus the party-menu bring
// step with one screen: the opponent's roster and your drafted six shown as
// party icons, a scout panel (moves / item / ability) on any opponent, and a
// bring-N pick whose chosen order is the send / lead order (in doubles, the
// first two chosen lead).
//
// Reads:  gParties[B_TRAINER_PLAYER][0..5] (drafted, already materialized by the
//         draft screen), gRentalRun (opponent roster, bring count, streak, format,
//         cap) and gRentalMons (opponent builds for the scout panel).
// Writes: gSelectedOrderFromParty[] (1-based party indices, in send order,
//         0-terminated) and gSpecialVar_Result (TRUE = fight, FALSE = retire),
//         exactly what ReducePlayerPartyToSelectedMons and the battle path expect.
// ---------------------------------------------------------------------------

#define PREVIEW_TEAM_SIZE   6
#define ICON_BASE_X        20   // left edge of the first icon cell
#define ICON_STEP_X        36
#define ICON_OPP_Y         24
#define ICON_PLR_Y         80
#define CURSOR_RAISE        8

#define ROW_OPP  0
#define ROW_PLR  1

enum {
    PWIN_TITLE,
    PWIN_MID,
    PWIN_TAGS,
    PWIN_MSG,
    PWIN_COUNT
};

struct RentalPreview
{
    u8 row;                              // ROW_OPP / ROW_PLR
    u8 col;                              // 0..5
    u8 order[PREVIEW_TEAM_SIZE];         // player col -> send order (1..bring), 0 = not brought
    u8 broughtCount;
    u8 bringCount;                       // 3 (singles) / 4 (doubles)
    u8 oppCount;
    u8 plrCount;
    bool8 scoutOpen;
    bool8 retireConfirmOpen;   // SELECT opened the retire Yes/No box
    bool8 retireYes;           // confirm cursor: FALSE = NO (default), TRUE = YES
    u8 iconSpriteIds[2][PREVIEW_TEAM_SIZE];
};

static EWRAM_DATA struct RentalPreview *sPreview = NULL;
static EWRAM_DATA u8 *sPreviewBgTilemap = NULL;

static void CB2_InitRentalPreview(void);
static void CB2_RentalPreview(void);
static void VBlankCB_RentalPreview(void);
static void Preview_CreateIcons(void);
static void Preview_UpdateCursorRaise(void);
static void Preview_DrawTitleHud(void);
static void Preview_DrawMid(void);
static void Preview_DrawTags(void);
static void Preview_DrawInstructions(void);
static void Preview_DrawScout(u8 oppCol);
static void Preview_DrawRetireConfirm(void);
static void Preview_Task_Main(u8 taskId);
static void Preview_Task_Exit(u8 taskId);

static const struct BgTemplate sPreview_BgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sPreview_WindowTemplates[] =
{
    [PWIN_TITLE] = { .bg = 0, .tilemapLeft = 0, .tilemapTop =  0, .width = 30, .height = 2, .paletteNum = 15, .baseBlock =   1 },
    [PWIN_MID]   = { .bg = 0, .tilemapLeft = 0, .tilemapTop =  7, .width = 30, .height = 2, .paletteNum = 15, .baseBlock =  61 },
    [PWIN_TAGS]  = { .bg = 0, .tilemapLeft = 0, .tilemapTop = 14, .width = 30, .height = 1, .paletteNum = 15, .baseBlock = 121 },
    [PWIN_MSG]   = { .bg = 0, .tilemapLeft = 0, .tilemapTop = 15, .width = 30, .height = 5, .paletteNum = 15, .baseBlock = 151 },
    DUMMY_WIN_TEMPLATE
};

// Palette 15: 0 = backdrop (dark indigo, also the screen transparent color),
// 1 = white text, 2 = shadow, 3 = gold accent.
static const u16 sPreview_Pal[16] =
{
    RGB(4, 4, 10), RGB(31, 31, 31), RGB(9, 9, 14), RGB(30, 24, 10),
    RGB(20, 22, 28), RGB(31, 20, 18), RGB(18, 27, 20), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
};

static const u8 sTextColor[3]     = { 0, 1, 2 };
static const u8 sTextColorGold[3] = { 0, 3, 2 };

static const u8 sText_Challenger[] = _("CHALLENGER");
static const u8 sText_Streak[]     = _("STREAK ");
static const u8 sText_Space[]      = _(" ");
static const u8 sText_Singles[]    = _("SINGLES");
static const u8 sText_Doubles[]    = _("DOUBLES");
static const u8 sText_SpaceR[]     = _("  R");
static const u8 sText_YourTeam[]   = _("YOUR TEAM");
static const u8 sText_Bring[]      = _("BRING ");
static const u8 sText_Slash[]      = _("/");
static const u8 sText_HintOpp[]    = _("Pad: Move  A: Scout  B: Undo  SEL: Retire");
static const u8 sText_HintPlr[]    = _("Pad: Move  A: Pick  B: Undo  SEL: Retire");
static const u8 sText_HintGo[]     = _("START: Begin once your team is set");
static const u8 sText_At[]         = _(" · ");
static const u8 sText_Ability[]    = _("Ability: ");
static const u8 sText_Dash[]       = _("- ");
static const u8 sText_Gap[]        = _("   ");
static const u8 sText_RetireQ[]    = _("Retire this run?");
static const u8 sText_Yes[]        = _("YES");
static const u8 sText_No[]         = _("NO");
static const u8 sText_ConfirmHint[] = _("A: Confirm   B: Cancel");

void DoRentalTeamPreview(void)
{
    sPreview = NULL;
    SetMainCallback2(CB2_InitRentalPreview);
}

static u16 Preview_PlayerSpecies(u8 i)
{
    return GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES_OR_EGG);
}

static u16 Preview_OppSpecies(u8 i)
{
    return gRentalMons[gRentalRun.oppRoster[i]].species;
}

static void CB2_InitRentalPreview(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetHBlankCallback(NULL);
        CpuFill32(0, (void *)VRAM, VRAM_SIZE);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sPreview_BgTemplates, ARRAY_COUNT(sPreview_BgTemplates));
        sPreviewBgTilemap = AllocZeroed(BG_SCREEN_SIZE);
        SetBgTilemapBuffer(0, sPreviewBgTilemap);
        FillBgTilemapBufferRect(0, 0, 0, 0, 32, 32, 15);
        CopyBgTilemapBufferToVram(0);
        InitWindows(sPreview_WindowTemplates);
        DeactivateAllTextPrinters();
        gMain.state++;
        break;
    case 1:
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        FreeAllSpritePalettes();
        LoadMonIconPalettes();
        gMain.state++;
        break;
    case 2:
        sPreview = AllocZeroed(sizeof(*sPreview));
        sPreview->row = ROW_PLR;
        sPreview->col = 0;
        sPreview->bringCount = gRentalRun.bringCount ? gRentalRun.bringCount : 3;
        CalculatePlayerPartyCount();
        sPreview->plrCount = gPartiesCount[B_TRAINER_PLAYER];
        if (sPreview->plrCount > PREVIEW_TEAM_SIZE)
            sPreview->plrCount = PREVIEW_TEAM_SIZE;
        sPreview->oppCount = gRentalRun.oppRosterCount;
        if (sPreview->oppCount > PREVIEW_TEAM_SIZE)
            sPreview->oppCount = PREVIEW_TEAM_SIZE;
        gMain.state++;
        break;
    case 3:
        LoadPalette(sPreview_Pal, BG_PLTT_ID(15), sizeof(sPreview_Pal));
        gPlttBufferUnfaded[0] = sPreview_Pal[0];
        gPlttBufferFaded[0] = sPreview_Pal[0];
        Preview_CreateIcons();
        gMain.state++;
        break;
    case 4:
        Preview_DrawTitleHud();
        Preview_DrawMid();
        Preview_DrawTags();
        Preview_DrawInstructions();
        Preview_UpdateCursorRaise();
        CopyBgTilemapBufferToVram(0);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        ShowBg(0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_BG0_ON | DISPCNT_OBJ_1D_MAP);
        SetVBlankCallback(VBlankCB_RentalPreview);
        CreateTask(Preview_Task_Main, 0);
        SetMainCallback2(CB2_RentalPreview);
        break;
    }
}

static void CB2_RentalPreview(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_RentalPreview(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static s16 Preview_IconCenterX(u8 col)
{
    return ICON_BASE_X + col * ICON_STEP_X + 16; // CreateMonIcon x is the sprite center
}

static void Preview_CreateIcons(void)
{
    u8 i;
    for (i = 0; i < sPreview->oppCount; i++)
    {
        sPreview->iconSpriteIds[ROW_OPP][i] = CreateMonIcon(Preview_OppSpecies(i), SpriteCallbackDummy,
                Preview_IconCenterX(i), ICON_OPP_Y, 0, 0);
    }
    for (i = 0; i < sPreview->plrCount; i++)
    {
        sPreview->iconSpriteIds[ROW_PLR][i] = CreateMonIcon(Preview_PlayerSpecies(i), SpriteCallbackDummy,
                Preview_IconCenterX(i), ICON_PLR_Y, 0,
                GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_PERSONALITY));
    }
}

// The cursor is the single raised icon; every other icon sits at its base y.
static void Preview_UpdateCursorRaise(void)
{
    u8 i;
    for (i = 0; i < sPreview->oppCount; i++)
        gSprites[sPreview->iconSpriteIds[ROW_OPP][i]].y = ICON_OPP_Y;
    for (i = 0; i < sPreview->plrCount; i++)
        gSprites[sPreview->iconSpriteIds[ROW_PLR][i]].y = ICON_PLR_Y;

    if (sPreview->row == ROW_OPP)
        gSprites[sPreview->iconSpriteIds[ROW_OPP][sPreview->col]].y = ICON_OPP_Y - CURSOR_RAISE;
    else
        gSprites[sPreview->iconSpriteIds[ROW_PLR][sPreview->col]].y = ICON_PLR_Y - CURSOR_RAISE;
}

static void Preview_DrawTitleHud(void)
{
    u8 num[8];

    FillWindowPixelBuffer(PWIN_TITLE, PIXEL_FILL(0));
    AddTextPrinterParameterized3(PWIN_TITLE, FONT_SMALL, 2, 1, sTextColor, TEXT_SKIP_DRAW, sText_Challenger);

    StringCopy(gStringVar4, sText_Streak);
    ConvertIntToDecimalStringN(num, gRentalRun.winStreak, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringAppend(gStringVar4, num);
    StringAppend(gStringVar4, sText_Space);
    StringAppend(gStringVar4, (gRentalRun.format == RENTAL_FORMAT_DOUBLES) ? sText_Doubles : sText_Singles);
    StringAppend(gStringVar4, sText_SpaceR);
    ConvertIntToDecimalStringN(num, gRentalRun.restrictedCap, STR_CONV_MODE_LEFT_ALIGN, 1);
    StringAppend(gStringVar4, num);
    AddTextPrinterParameterized3(PWIN_TITLE, FONT_SMALL,
            240 - 4 - GetStringWidth(FONT_SMALL, gStringVar4, 0), 1, sTextColorGold, TEXT_SKIP_DRAW, gStringVar4);

    PutWindowTilemap(PWIN_TITLE);
    CopyWindowToVram(PWIN_TITLE, COPYWIN_FULL);
}

static void Preview_DrawMid(void)
{
    u8 num[8];

    FillWindowPixelBuffer(PWIN_MID, PIXEL_FILL(0));
    AddTextPrinterParameterized3(PWIN_MID, FONT_SMALL, 2, 3, sTextColor, TEXT_SKIP_DRAW, sText_YourTeam);

    StringCopy(gStringVar4, sText_Bring);
    ConvertIntToDecimalStringN(num, sPreview->broughtCount, STR_CONV_MODE_LEFT_ALIGN, 1);
    StringAppend(gStringVar4, num);
    StringAppend(gStringVar4, sText_Slash);
    ConvertIntToDecimalStringN(num, sPreview->bringCount, STR_CONV_MODE_LEFT_ALIGN, 1);
    StringAppend(gStringVar4, num);
    AddTextPrinterParameterized3(PWIN_MID, FONT_SMALL,
            240 - 4 - GetStringWidth(FONT_SMALL, gStringVar4, 0), 3, sTextColorGold, TEXT_SKIP_DRAW, gStringVar4);

    PutWindowTilemap(PWIN_MID);
    CopyWindowToVram(PWIN_MID, COPYWIN_FULL);
}

// Draw each brought player mon's send-order number under its icon.
static void Preview_DrawTags(void)
{
    u8 i;
    u8 str[2];

    FillWindowPixelBuffer(PWIN_TAGS, PIXEL_FILL(0));
    for (i = 0; i < sPreview->plrCount; i++)
    {
        if (sPreview->order[i] == 0)
            continue;
        str[0] = CHAR_0 + sPreview->order[i];
        str[1] = EOS;
        AddTextPrinterParameterized3(PWIN_TAGS, FONT_SMALL, ICON_BASE_X + i * ICON_STEP_X + 12, 0,
                sTextColorGold, TEXT_SKIP_DRAW, str);
    }
    PutWindowTilemap(PWIN_TAGS);
    CopyWindowToVram(PWIN_TAGS, COPYWIN_FULL);
}

static void Preview_DrawInstructions(void)
{
    FillWindowPixelBuffer(PWIN_MSG, PIXEL_FILL(0));
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 2, 6, sTextColor, TEXT_SKIP_DRAW,
            (sPreview->row == ROW_OPP) ? sText_HintOpp : sText_HintPlr);
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 2, 24, sTextColor, TEXT_SKIP_DRAW, sText_HintGo);
    PutWindowTilemap(PWIN_MSG);
    CopyWindowToVram(PWIN_MSG, COPYWIN_FULL);
}

// Scout: the opponent's build, from the library entry (moves / item / ability).
static void Preview_DrawScout(u8 oppCol)
{
    const struct TrainerMon *set = &gRentalMons[gRentalRun.oppRoster[oppCol]];
    u8 i, line;

    FillWindowPixelBuffer(PWIN_MSG, PIXEL_FILL(0));

    StringCopy(gStringVar4, GetSpeciesName(set->species));
    if (set->heldItem != ITEM_NONE)
    {
        StringAppend(gStringVar4, sText_At);
        StringAppend(gStringVar4, GetItemName(set->heldItem));
    }
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 2, 0, sTextColorGold, TEXT_SKIP_DRAW, gStringVar4);

    StringCopy(gStringVar4, sText_Ability);
    StringAppend(gStringVar4, gAbilitiesInfo[set->ability].name);
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 2, 10, sTextColor, TEXT_SKIP_DRAW, gStringVar4);

    // Two moves per line: "- move   - move".
    line = 0;
    for (i = 0; i < MAX_MON_MOVES; i += 2)
    {
        gStringVar4[0] = EOS;
        if (set->moves[i] != MOVE_NONE)
        {
            StringCopy(gStringVar4, sText_Dash);
            StringAppend(gStringVar4, GetMoveName(set->moves[i]));
        }
        if (i + 1 < MAX_MON_MOVES && set->moves[i + 1] != MOVE_NONE)
        {
            StringAppend(gStringVar4, sText_Gap);
            StringAppend(gStringVar4, sText_Dash);
            StringAppend(gStringVar4, GetMoveName(set->moves[i + 1]));
        }
        AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 2, 20 + line * 10, sTextColor, TEXT_SKIP_DRAW, gStringVar4);
        line++;
    }

    PutWindowTilemap(PWIN_MSG);
    CopyWindowToVram(PWIN_MSG, COPYWIN_FULL);
}

static void Preview_ToggleBring(void)
{
    u8 col = sPreview->col;
    u8 i;

    if (sPreview->order[col] != 0)
    {
        // Deselect: drop this one and shuffle every later order down by one.
        u8 removed = sPreview->order[col];
        sPreview->order[col] = 0;
        for (i = 0; i < sPreview->plrCount; i++)
        {
            if (sPreview->order[i] > removed)
                sPreview->order[i]--;
        }
        sPreview->broughtCount--;
        PlaySE(SE_SELECT);
    }
    else if (sPreview->broughtCount < sPreview->bringCount)
    {
        sPreview->broughtCount++;
        sPreview->order[col] = sPreview->broughtCount;
        PlaySE(SE_SELECT);
    }
    else
    {
        PlaySE(SE_FAILURE);
        return;
    }
    Preview_DrawMid();
    Preview_DrawTags();
}

// B on the player row: pop the most recently picked mon (its order == broughtCount).
static void Preview_Undo(void)
{
    u8 i;
    if (sPreview->broughtCount == 0)
    {
        PlaySE(SE_FAILURE);
        return;
    }
    for (i = 0; i < sPreview->plrCount; i++)
    {
        if (sPreview->order[i] == sPreview->broughtCount)
        {
            sPreview->order[i] = 0;
            break;
        }
    }
    sPreview->broughtCount--;
    PlaySE(SE_SELECT);
    Preview_DrawMid();
    Preview_DrawTags();
}

// The retire confirm box, drawn into the message window. Default cursor sits on NO.
static void Preview_DrawRetireConfirm(void)
{
    FillWindowPixelBuffer(PWIN_MSG, PIXEL_FILL(0));
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 2, 2, sTextColorGold, TEXT_SKIP_DRAW, sText_RetireQ);
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 30, 16,
            sPreview->retireYes ? sTextColorGold : sTextColor, TEXT_SKIP_DRAW, sText_Yes);
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 80, 16,
            sPreview->retireYes ? sTextColor : sTextColorGold, TEXT_SKIP_DRAW, sText_No);
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 2, 28, sTextColor, TEXT_SKIP_DRAW, sText_ConfirmHint);
    PutWindowTilemap(PWIN_MSG);
    CopyWindowToVram(PWIN_MSG, COPYWIN_FULL);
}

static void Preview_Confirm(u8 taskId)
{
    u8 i, o;
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        gSelectedOrderFromParty[i] = 0;
    for (i = 0; i < sPreview->plrCount; i++)
    {
        o = sPreview->order[i];
        if (o != 0 && o <= MAX_FRONTIER_PARTY_SIZE)
            gSelectedOrderFromParty[o - 1] = i + 1; // 1-based party index, in send order
    }
    gSpecialVar_Result = TRUE;
    gTasks[taskId].func = Preview_Task_Exit;
}

static void Preview_Retire(u8 taskId)
{
    u8 i;
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        gSelectedOrderFromParty[i] = 0;
    gSpecialVar_Result = FALSE;
    gTasks[taskId].func = Preview_Task_Exit;
}

static u8 Preview_ColCount(void)
{
    return (sPreview->row == ROW_OPP) ? sPreview->oppCount : sPreview->plrCount;
}

static void Preview_Task_Main(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    // Retire confirm takes priority over everything else.
    if (sPreview->retireConfirmOpen)
    {
        if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
        {
            sPreview->retireYes = !sPreview->retireYes;
            PlaySE(SE_SELECT);
            Preview_DrawRetireConfirm();
        }
        else if (JOY_NEW(A_BUTTON))
        {
            if (sPreview->retireYes)
            {
                sPreview->retireConfirmOpen = FALSE;
                PlaySE(SE_SELECT);
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                Preview_Retire(taskId);
            }
            else
            {
                sPreview->retireConfirmOpen = FALSE;
                PlaySE(SE_SELECT);
                Preview_DrawInstructions();
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            sPreview->retireConfirmOpen = FALSE;
            PlaySE(SE_SELECT);
            Preview_DrawInstructions();
        }
        return;
    }

    if (sPreview->scoutOpen)
    {
        if (JOY_NEW(A_BUTTON | B_BUTTON))
        {
            sPreview->scoutOpen = FALSE;
            PlaySE(SE_SELECT);
            Preview_DrawInstructions();
        }
        return;
    }

    if (JOY_NEW(DPAD_LEFT))
    {
        sPreview->col = (sPreview->col > 0) ? sPreview->col - 1 : Preview_ColCount() - 1;
        Preview_UpdateCursorRaise();
        PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        sPreview->col = (sPreview->col < Preview_ColCount() - 1) ? sPreview->col + 1 : 0;
        Preview_UpdateCursorRaise();
        PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(DPAD_UP | DPAD_DOWN))
    {
        sPreview->row = (sPreview->row == ROW_OPP) ? ROW_PLR : ROW_OPP;
        if (sPreview->col >= Preview_ColCount())
            sPreview->col = Preview_ColCount() - 1;
        Preview_UpdateCursorRaise();
        Preview_DrawInstructions();
        PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        if (sPreview->row == ROW_OPP)
        {
            sPreview->scoutOpen = TRUE;
            PlaySE(SE_SELECT);
            Preview_DrawScout(sPreview->col);
        }
        else
        {
            Preview_ToggleBring();
        }
    }
    else if (JOY_NEW(START_BUTTON))
    {
        if (sPreview->broughtCount == sPreview->bringCount)
        {
            PlaySE(SE_SELECT);
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
            Preview_Confirm(taskId);
        }
        else
        {
            PlaySE(SE_FAILURE);
        }
    }
    else if (JOY_NEW(SELECT_BUTTON))
    {
        sPreview->retireConfirmOpen = TRUE;
        sPreview->retireYes = FALSE;   // default to NO
        PlaySE(SE_SELECT);
        Preview_DrawRetireConfirm();
    }
    else if (JOY_NEW(B_BUTTON))
    {
        Preview_Undo();
    }
}

static void Preview_Task_Exit(u8 taskId)
{
    u8 i;
    if (gPaletteFade.active)
        return;

    for (i = 0; i < sPreview->oppCount; i++)
        FreeAndDestroyMonIconSprite(&gSprites[sPreview->iconSpriteIds[ROW_OPP][i]]);
    for (i = 0; i < sPreview->plrCount; i++)
        FreeAndDestroyMonIconSprite(&gSprites[sPreview->iconSpriteIds[ROW_PLR][i]]);
    FreeMonIconPalettes();

    FREE_AND_SET_NULL(sPreview);
    FREE_AND_SET_NULL(sPreviewBgTilemap);
    FreeAllWindowBuffers();
    DestroyTask(taskId);
    SetMainCallback2(CB2_ReturnToFieldContinueScript);
}
