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
#include "data.h"
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
// RENTAL BATTLE recruit board (UI proposal S4 / U5).
//
// After a win: pick one of the opponent's fielded mons to take, then one of your
// six to return in trade. Swaps that would break Species Clause, Item Clause, or
// the restricted cap are blocked (the pick refuses with a note). Sets the vars the
// script's RentalDoRecruit consumes and returns to the field:
//   gSpecialVar_0x8006 = opponent field index
//   gSpecialVar_0x8004 = release slot
//   gSpecialVar_Result = TRUE (recruit chosen) / FALSE (skip)
// Layout and setup mirror src/rental_preview_screen.c.
// ---------------------------------------------------------------------------

#define RECRUIT_TEAM_SIZE   6
#define ICON_BASE_X        20
#define ICON_STEP_X        36
#define ICON_TOP_Y         24   // opponent fielded row
#define ICON_BOT_Y         80   // your team row
#define CURSOR_RAISE        8

#define PHASE_PICK_OPP  0
#define PHASE_PICK_REL  1

enum {
    RWIN_TITLE,
    RWIN_MID,
    RWIN_TAGS,
    RWIN_MSG,
    RWIN_COUNT
};

struct RentalRecruit
{
    u8 phase;
    u8 oppCol;                              // chosen opponent (valid once phase >= PICK_REL)
    u8 cursor;                              // cursor within the active row
    u8 oppCount;
    u8 plrCount;
    u8 iconSpriteIds[2][RECRUIT_TEAM_SIZE]; // [0] opp, [1] player
};

static EWRAM_DATA struct RentalRecruit *sRecruit = NULL;
static EWRAM_DATA u8 *sRecruitBgTilemap = NULL;

static void CB2_InitRentalRecruit(void);
static void CB2_RentalRecruit(void);
static void VBlankCB_RentalRecruit(void);
static void Recruit_CreateIcons(void);
static void Recruit_UpdateCursorRaise(void);
static void Recruit_DrawTitleHud(void);
static void Recruit_DrawMid(void);
static void Recruit_DrawTags(void);
static void Recruit_DrawOppBuild(u8 oppCol);
static void Recruit_DrawHint(const u8 *hint);
static void Recruit_Task_Main(u8 taskId);
static void Recruit_Task_Exit(u8 taskId);

static const struct BgTemplate sRecruit_BgTemplates[] =
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

static const struct WindowTemplate sRecruit_WindowTemplates[] =
{
    [RWIN_TITLE] = { .bg = 0, .tilemapLeft = 0, .tilemapTop =  0, .width = 30, .height = 2, .paletteNum = 15, .baseBlock =   1 },
    [RWIN_MID]   = { .bg = 0, .tilemapLeft = 0, .tilemapTop =  7, .width = 30, .height = 2, .paletteNum = 15, .baseBlock =  61 },
    [RWIN_TAGS]  = { .bg = 0, .tilemapLeft = 0, .tilemapTop = 14, .width = 30, .height = 1, .paletteNum = 15, .baseBlock = 121 },
    [RWIN_MSG]   = { .bg = 0, .tilemapLeft = 0, .tilemapTop = 15, .width = 30, .height = 5, .paletteNum = 15, .baseBlock = 151 },
    DUMMY_WIN_TEMPLATE
};

static const u16 sRecruit_Pal[16] =
{
    RGB(4, 4, 10), RGB(31, 31, 31), RGB(9, 9, 14), RGB(30, 24, 10),
    RGB(20, 22, 28), RGB(31, 20, 18), RGB(18, 27, 20), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
};

static const u8 sTextColor[3]     = { 0, 1, 2 };
static const u8 sTextColorGold[3] = { 0, 3, 2 };

static const u8 sText_Recruit[]  = _("RECRUIT");
static const u8 sText_Streak[]   = _("STREAK ");
static const u8 sText_TakeOne[]  = _("Take into your keeping");
static const u8 sText_ReleaseOne[] = _("Return one of yours");
static const u8 sText_HintOpp[]  = _("Pad: Move   A: Take   B: Skip");
static const u8 sText_HintBreak[] = _("House rules forbid that trade.");
static const u8 sText_Star[]     = _("·");
static const u8 sText_At[]       = _(" · ");
static const u8 sText_Ability[]  = _("Ability: ");
static const u8 sText_Dash[]     = _("- ");
static const u8 sText_Gap[]      = _("   ");

void DoRentalRecruit(void)
{
    sRecruit = NULL;
    SetMainCallback2(CB2_InitRentalRecruit);
}

static u16 Recruit_OppSpecies(u8 i)
{
    return gRentalMons[gRentalRun.oppRoster[i]].species;
}

static u16 Recruit_PlayerSpecies(u8 i)
{
    return GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES_OR_EGG);
}

static s16 Recruit_IconCenterX(u8 col)
{
    return ICON_BASE_X + col * ICON_STEP_X + 16;
}

static u8 Recruit_ActiveCount(void)
{
    return (sRecruit->phase == PHASE_PICK_OPP) ? sRecruit->oppCount : sRecruit->plrCount;
}

static void CB2_InitRentalRecruit(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetHBlankCallback(NULL);
        CpuFill32(0, (void *)VRAM, VRAM_SIZE);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sRecruit_BgTemplates, ARRAY_COUNT(sRecruit_BgTemplates));
        sRecruitBgTilemap = AllocZeroed(BG_SCREEN_SIZE);
        SetBgTilemapBuffer(0, sRecruitBgTilemap);
        FillBgTilemapBufferRect(0, 0, 0, 0, 32, 32, 15);
        CopyBgTilemapBufferToVram(0);
        InitWindows(sRecruit_WindowTemplates);
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
        sRecruit = AllocZeroed(sizeof(*sRecruit));
        sRecruit->phase = PHASE_PICK_OPP;
        sRecruit->cursor = 0;
        sRecruit->oppCount = RentalGetFieldCount();
        if (sRecruit->oppCount > RECRUIT_TEAM_SIZE)
            sRecruit->oppCount = RECRUIT_TEAM_SIZE;
        CalculatePlayerPartyCount();
        sRecruit->plrCount = gPartiesCount[B_TRAINER_PLAYER];
        if (sRecruit->plrCount > RECRUIT_TEAM_SIZE)
            sRecruit->plrCount = RECRUIT_TEAM_SIZE;
        gMain.state++;
        break;
    case 3:
        LoadPalette(sRecruit_Pal, BG_PLTT_ID(15), sizeof(sRecruit_Pal));
        gPlttBufferUnfaded[0] = sRecruit_Pal[0];
        gPlttBufferFaded[0] = sRecruit_Pal[0];
        Recruit_CreateIcons();
        gMain.state++;
        break;
    case 4:
        Recruit_DrawTitleHud();
        Recruit_DrawMid();
        Recruit_DrawTags();
        Recruit_DrawHint(sText_HintOpp);
        Recruit_UpdateCursorRaise();
        CopyBgTilemapBufferToVram(0);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        ShowBg(0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_BG0_ON | DISPCNT_OBJ_1D_MAP);
        SetVBlankCallback(VBlankCB_RentalRecruit);
        CreateTask(Recruit_Task_Main, 0);
        SetMainCallback2(CB2_RentalRecruit);
        break;
    }
}

static void CB2_RentalRecruit(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_RentalRecruit(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Recruit_CreateIcons(void)
{
    u8 i;
    for (i = 0; i < sRecruit->oppCount; i++)
        sRecruit->iconSpriteIds[0][i] = CreateMonIcon(Recruit_OppSpecies(i), SpriteCallbackDummy,
                Recruit_IconCenterX(i), ICON_TOP_Y, 0, 0);
    for (i = 0; i < sRecruit->plrCount; i++)
        sRecruit->iconSpriteIds[1][i] = CreateMonIcon(Recruit_PlayerSpecies(i), SpriteCallbackDummy,
                Recruit_IconCenterX(i), ICON_BOT_Y, 0,
                GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_PERSONALITY));
}

static void Recruit_UpdateCursorRaise(void)
{
    u8 i;
    for (i = 0; i < sRecruit->oppCount; i++)
        gSprites[sRecruit->iconSpriteIds[0][i]].y = ICON_TOP_Y;
    for (i = 0; i < sRecruit->plrCount; i++)
        gSprites[sRecruit->iconSpriteIds[1][i]].y = ICON_BOT_Y;

    if (sRecruit->phase == PHASE_PICK_OPP)
        gSprites[sRecruit->iconSpriteIds[0][sRecruit->cursor]].y = ICON_TOP_Y - CURSOR_RAISE;
    else
        gSprites[sRecruit->iconSpriteIds[1][sRecruit->cursor]].y = ICON_BOT_Y - CURSOR_RAISE;
}

static void Recruit_DrawTitleHud(void)
{
    u8 num[8];

    FillWindowPixelBuffer(RWIN_TITLE, PIXEL_FILL(0));
    AddTextPrinterParameterized3(RWIN_TITLE, FONT_SMALL, 2, 1, sTextColor, TEXT_SKIP_DRAW, sText_Recruit);

    StringCopy(gStringVar4, sText_Streak);
    ConvertIntToDecimalStringN(num, gRentalRun.winStreak, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringAppend(gStringVar4, num);
    AddTextPrinterParameterized3(RWIN_TITLE, FONT_SMALL,
            240 - 4 - GetStringWidth(FONT_SMALL, gStringVar4, 0), 1, sTextColorGold, TEXT_SKIP_DRAW, gStringVar4);

    PutWindowTilemap(RWIN_TITLE);
    CopyWindowToVram(RWIN_TITLE, COPYWIN_FULL);
}

static void Recruit_DrawMid(void)
{
    FillWindowPixelBuffer(RWIN_MID, PIXEL_FILL(0));
    AddTextPrinterParameterized3(RWIN_MID, FONT_SMALL, 2, 3, sTextColor, TEXT_SKIP_DRAW,
            (sRecruit->phase == PHASE_PICK_OPP) ? sText_TakeOne : sText_ReleaseOne);
    PutWindowTilemap(RWIN_MID);
    CopyWindowToVram(RWIN_MID, COPYWIN_FULL);
}

// Mark the chosen opponent with a star once we are picking the release slot.
static void Recruit_DrawTags(void)
{
    FillWindowPixelBuffer(RWIN_TAGS, PIXEL_FILL(0));
    if (sRecruit->phase == PHASE_PICK_REL)
        AddTextPrinterParameterized3(RWIN_TAGS, FONT_SMALL, ICON_BASE_X + sRecruit->oppCol * ICON_STEP_X + 12, 0,
                sTextColorGold, TEXT_SKIP_DRAW, sText_Star);
    PutWindowTilemap(RWIN_TAGS);
    CopyWindowToVram(RWIN_TAGS, COPYWIN_FULL);
}

static void Recruit_DrawHint(const u8 *hint)
{
    FillWindowPixelBuffer(RWIN_MSG, PIXEL_FILL(0));
    AddTextPrinterParameterized3(RWIN_MSG, FONT_SMALL, 2, 14, sTextColor, TEXT_SKIP_DRAW, hint);
    PutWindowTilemap(RWIN_MSG);
    CopyWindowToVram(RWIN_MSG, COPYWIN_FULL);
}

static void Recruit_DrawOppBuild(u8 oppCol)
{
    const struct TrainerMon *set = &gRentalMons[gRentalRun.oppRoster[oppCol]];
    u8 i, line;

    FillWindowPixelBuffer(RWIN_MSG, PIXEL_FILL(0));

    StringCopy(gStringVar4, GetSpeciesName(set->species));
    if (set->heldItem != ITEM_NONE)
    {
        StringAppend(gStringVar4, sText_At);
        StringAppend(gStringVar4, GetItemName(set->heldItem));
    }
    AddTextPrinterParameterized3(RWIN_MSG, FONT_SMALL, 2, 0, sTextColorGold, TEXT_SKIP_DRAW, gStringVar4);

    StringCopy(gStringVar4, sText_Ability);
    StringAppend(gStringVar4, gAbilitiesInfo[set->ability].name);
    AddTextPrinterParameterized3(RWIN_MSG, FONT_SMALL, 2, 10, sTextColor, TEXT_SKIP_DRAW, gStringVar4);

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
        AddTextPrinterParameterized3(RWIN_MSG, FONT_SMALL, 2, 20 + line * 10, sTextColor, TEXT_SKIP_DRAW, gStringVar4);
        line++;
    }

    PutWindowTilemap(RWIN_MSG);
    CopyWindowToVram(RWIN_MSG, COPYWIN_FULL);
}

static void Recruit_Finish(u8 taskId, bool8 doRecruit)
{
    if (doRecruit)
    {
        gSpecialVar_0x8006 = sRecruit->oppCol;
        gSpecialVar_0x8004 = sRecruit->cursor; // release slot
        gSpecialVar_Result = TRUE;
    }
    else
    {
        gSpecialVar_Result = FALSE;
    }
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Recruit_Task_Exit;
}

static void Recruit_Task_Main(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    if (JOY_NEW(DPAD_LEFT))
    {
        sRecruit->cursor = (sRecruit->cursor > 0) ? sRecruit->cursor - 1 : Recruit_ActiveCount() - 1;
        Recruit_UpdateCursorRaise();
        PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(DPAD_RIGHT))
    {
        sRecruit->cursor = (sRecruit->cursor < Recruit_ActiveCount() - 1) ? sRecruit->cursor + 1 : 0;
        Recruit_UpdateCursorRaise();
        PlaySE(SE_SELECT);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        if (sRecruit->phase == PHASE_PICK_OPP)
        {
            sRecruit->oppCol = sRecruit->cursor;
            sRecruit->phase = PHASE_PICK_REL;
            sRecruit->cursor = 0;
            PlaySE(SE_SELECT);
            Recruit_UpdateCursorRaise();
            Recruit_DrawMid();
            Recruit_DrawTags();
            Recruit_DrawOppBuild(sRecruit->oppCol);
        }
        else
        {
            if (RentalRecruitLegal(sRecruit->oppCol, sRecruit->cursor))
            {
                PlaySE(SE_SELECT);
                Recruit_Finish(taskId, TRUE);
            }
            else
            {
                PlaySE(SE_FAILURE);
                Recruit_DrawHint(sText_HintBreak);
            }
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        if (sRecruit->phase == PHASE_PICK_REL)
        {
            sRecruit->phase = PHASE_PICK_OPP;
            sRecruit->cursor = sRecruit->oppCol;
            PlaySE(SE_SELECT);
            Recruit_UpdateCursorRaise();
            Recruit_DrawMid();
            Recruit_DrawTags();
            Recruit_DrawHint(sText_HintOpp);
        }
        else
        {
            PlaySE(SE_SELECT);
            Recruit_Finish(taskId, FALSE);
        }
    }
}

static void Recruit_Task_Exit(u8 taskId)
{
    u8 i;
    if (gPaletteFade.active)
        return;

    for (i = 0; i < sRecruit->oppCount; i++)
        FreeAndDestroyMonIconSprite(&gSprites[sRecruit->iconSpriteIds[0][i]]);
    for (i = 0; i < sRecruit->plrCount; i++)
        FreeAndDestroyMonIconSprite(&gSprites[sRecruit->iconSpriteIds[1][i]]);
    FreeMonIconPalettes();

    FREE_AND_SET_NULL(sRecruit);
    FREE_AND_SET_NULL(sRecruitBgTilemap);
    FreeAllWindowBuffers();
    DestroyTask(taskId);
    SetMainCallback2(CB2_ReturnToFieldContinueScript);
}
