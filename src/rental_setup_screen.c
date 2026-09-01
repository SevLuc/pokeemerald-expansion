#include "global.h"
#include "main.h"
#include "bg.h"
#include "gpu_regs.h"
#include "palette.h"
#include "window.h"
#include "text.h"
#include "menu.h"
#include "task.h"
#include "malloc.h"
#include "sound.h"
#include "string_util.h"
#include "event_data.h"
#include "overworld.h"
#include "rental_mode.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// ---------------------------------------------------------------------------
// RENTAL BATTLE run-setup screen. Replaces the two overworld multichoice menus
// (format, restricted cap) with one themed screen matching the pick screen.
// Writes gSpecialVar_0x8004 (0 singles / 1 doubles), gSpecialVar_0x8005 (cap
// 0/1/2) and gSpecialVar_Result (1 = begin draft, 0 = leave), then returns to
// the lobby script which runs StartRentalDraft.
// ---------------------------------------------------------------------------

enum { SROW_FORMAT, SROW_CAP, SROW_COUNT };

enum {
    SWIN_HEADER,
    SWIN_ROWS,
    SWIN_HELP,
    SWIN_FOOT,
    SWIN_COUNT
};

struct RentalSetup
{
    u8 row;
    u8 format; // 0 singles, 1 doubles
    u8 cap;    // 0/1/2
};

static EWRAM_DATA struct RentalSetup *sSetup = NULL;
static EWRAM_DATA u8 *sSetupBgTilemap = NULL;

static void CB2_InitRentalSetup(void);
static void CB2_RentalSetup(void);
static void VBlankCB_RentalSetup(void);
static void Setup_DrawAll(void);
static void Setup_Task_Main(u8 taskId);
static void Setup_Task_Exit(u8 taskId);

static const struct BgTemplate sSetup_BgTemplates[] =
{
    { .bg = 0, .charBaseIndex = 0, .mapBaseIndex = 30, .screenSize = 0,
      .paletteMode = 0, .priority = 0, .baseTile = 0 },
};

static const struct WindowTemplate sSetup_WindowTemplates[] =
{
    [SWIN_HEADER] = { .bg = 0, .tilemapLeft = 0, .tilemapTop =  0, .width = 30, .height = 2, .paletteNum = 15, .baseBlock =   1 },
    [SWIN_ROWS]   = { .bg = 0, .tilemapLeft = 1, .tilemapTop =  4, .width = 28, .height = 8, .paletteNum = 15, .baseBlock =  61 },
    [SWIN_HELP]   = { .bg = 0, .tilemapLeft = 0, .tilemapTop = 13, .width = 30, .height = 2, .paletteNum = 15, .baseBlock = 301 },
    [SWIN_FOOT]   = { .bg = 0, .tilemapLeft = 0, .tilemapTop = 16, .width = 30, .height = 2, .paletteNum = 15, .baseBlock = 361 },
    DUMMY_WIN_TEMPLATE
};

// 0 navy, 1 white, 2 shadow, 3 gold, 4 panel, 5 frame(yellow), 6 cyan, 7 hilite.
static const u16 sSetup_Pal[16] =
{
    RGB(4, 4, 10), RGB(31, 31, 31), RGB(9, 9, 14), RGB(30, 24, 10),
    RGB(6, 6, 14), RGB(30, 24, 8), RGB(13, 22, 26), RGB(12, 12, 26),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
};

// Loaded high (tile 500+) to clear the window glyph region (windows end ~421).
#define STILE_BASE 500
enum { STILE_PANEL = STILE_BASE, STILE_FRAME, STILE_HILITE };
#define STILE_NUM 3

#define S_SOLID_TILE(b) \
    (b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b), \
    (b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b)
#define S_SOLID(idx) S_SOLID_TILE(((idx) << 4) | (idx))

static const u8 sSetup_Tiles[STILE_NUM * 32] =
{
    S_SOLID(4), S_SOLID(5), S_SOLID(7),
};

static const u8 sTextColor[3]     = { 0, 1, 2 }; // white on navy (header/help/foot)
static const u8 sTextColorGold[3] = { 0, 3, 2 }; // gold on navy
static const u8 sPanelText[3]     = { 4, 1, 2 }; // white on panel (rows window)
static const u8 sPanelGold[3]     = { 4, 3, 2 }; // gold on panel

static const u8 sText_Cursor[]   = _(">");
static const u8 sText_Title[]    = _("LOANER FLOOR");
static const u8 sText_SetRun[]   = _("SET YOUR RUN");
static const u8 sText_Format[]   = _("FORMAT");
static const u8 sText_Restr[]    = _("RESTRICTED");
static const u8 sText_Singles[]  = _("< SINGLES >");
static const u8 sText_Doubles[]  = _("< DOUBLES >");
static const u8 sText_Cap0[]     = _("<  0  >");
static const u8 sText_Cap1[]     = _("<  1  >");
static const u8 sText_Cap2[]     = _("<  2  >");
static const u8 sText_Bring3[]   = _("bring 3");
static const u8 sText_Bring4[]   = _("bring 4");
static const u8 sText_HelpFmt[]  = _("Singles: bring three of your six.");
static const u8 sText_HelpDbl[]  = _("Doubles: bring four; first two lead.");
static const u8 sText_HelpCap[]  = _("How many legendary-class allowed.");
static const u8 sText_Foot[]     = _("Pad: Move  <>: Change  START: Begin  B: Back");

void DoRentalSetup(void)
{
    sSetup = NULL;
    SetMainCallback2(CB2_InitRentalSetup);
}

static void CB2_InitRentalSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetHBlankCallback(NULL);
        CpuFill32(0, (void *)VRAM, VRAM_SIZE);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sSetup_BgTemplates, ARRAY_COUNT(sSetup_BgTemplates));
        sSetupBgTilemap = AllocZeroed(BG_SCREEN_SIZE);
        SetBgTilemapBuffer(0, sSetupBgTilemap);
        FillBgTilemapBufferRect(0, 0, 0, 0, 32, 32, 15);
        LoadBgTiles(0, sSetup_Tiles, sizeof(sSetup_Tiles), STILE_BASE);
        CopyBgTilemapBufferToVram(0);
        InitWindows(sSetup_WindowTemplates);
        DeactivateAllTextPrinters();
        gMain.state++;
        break;
    case 1:
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        FreeAllSpritePalettes();
        gMain.state++;
        break;
    case 2:
        sSetup = AllocZeroed(sizeof(*sSetup));
        sSetup->row = SROW_FORMAT;
        sSetup->format = 0;
        sSetup->cap = 0;
        gMain.state++;
        break;
    case 3:
        LoadPalette(sSetup_Pal, BG_PLTT_ID(15), sizeof(sSetup_Pal));
        gPlttBufferUnfaded[0] = sSetup_Pal[0];
        gPlttBufferFaded[0] = sSetup_Pal[0];
        gMain.state++;
        break;
    case 4:
        // Yellow frame box on the BG; the rows window (x1..28, y4..11) sits inside
        // it, so the frame shows as a border around the window and the panel color
        // comes from the window's own fill.
        FillBgTilemapBufferRect(0, STILE_FRAME, 0, 3, 30, 10, 15);
        Setup_DrawAll();
        CopyBgTilemapBufferToVram(0);
        gMain.state++;
        break;
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        ShowBg(0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_BG0_ON);
        SetVBlankCallback(VBlankCB_RentalSetup);
        CreateTask(Setup_Task_Main, 0);
        SetMainCallback2(CB2_RentalSetup);
        break;
    }
}

static void CB2_RentalSetup(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB_RentalSetup(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Setup_DrawAll(void)
{
    bool8 fmtActive = (sSetup->row == SROW_FORMAT);

    // Header (white/gold on navy).
    FillWindowPixelBuffer(SWIN_HEADER, PIXEL_FILL(0));
    AddTextPrinterParameterized3(SWIN_HEADER, FONT_SMALL, 4, 3, sTextColor, TEXT_SKIP_DRAW, sText_Title);
    AddTextPrinterParameterized3(SWIN_HEADER, FONT_SMALL,
            240 - 4 - GetStringWidth(FONT_SMALL, sText_SetRun, 0), 3, sTextColorGold, TEXT_SKIP_DRAW, sText_SetRun);
    PutWindowTilemap(SWIN_HEADER);
    CopyWindowToVram(SWIN_HEADER, COPYWIN_FULL);

    // Rows window: filled with the panel color; active row is gold with a '>' cursor.
    FillWindowPixelBuffer(SWIN_ROWS, PIXEL_FILL(4));
    AddTextPrinterParameterized3(SWIN_ROWS, FONT_SMALL, 2, fmtActive ? 6 : 30, sPanelGold, TEXT_SKIP_DRAW, sText_Cursor);
    AddTextPrinterParameterized3(SWIN_ROWS, FONT_SMALL, 14, 6, fmtActive ? sPanelGold : sPanelText, TEXT_SKIP_DRAW, sText_Format);
    AddTextPrinterParameterized3(SWIN_ROWS, FONT_SMALL, 96, 6, sPanelGold, TEXT_SKIP_DRAW,
            sSetup->format ? sText_Doubles : sText_Singles);
    AddTextPrinterParameterized3(SWIN_ROWS, FONT_SMALL, 182, 6, sPanelText, TEXT_SKIP_DRAW,
            sSetup->format ? sText_Bring4 : sText_Bring3);
    AddTextPrinterParameterized3(SWIN_ROWS, FONT_SMALL, 14, 30, fmtActive ? sPanelText : sPanelGold, TEXT_SKIP_DRAW, sText_Restr);
    AddTextPrinterParameterized3(SWIN_ROWS, FONT_SMALL, 96, 30, sPanelGold, TEXT_SKIP_DRAW,
            sSetup->cap == 2 ? sText_Cap2 : (sSetup->cap == 1 ? sText_Cap1 : sText_Cap0));
    PutWindowTilemap(SWIN_ROWS);
    CopyWindowToVram(SWIN_ROWS, COPYWIN_FULL);

    // Help line (depends on active row): carries the descriptive notes.
    FillWindowPixelBuffer(SWIN_HELP, PIXEL_FILL(0));
    AddTextPrinterParameterized3(SWIN_HELP, FONT_SMALL, 4, 4, sTextColor, TEXT_SKIP_DRAW,
            (sSetup->row == SROW_CAP) ? sText_HelpCap : (sSetup->format ? sText_HelpDbl : sText_HelpFmt));
    PutWindowTilemap(SWIN_HELP);
    CopyWindowToVram(SWIN_HELP, COPYWIN_FULL);

    // Footer.
    FillWindowPixelBuffer(SWIN_FOOT, PIXEL_FILL(0));
    AddTextPrinterParameterized3(SWIN_FOOT, FONT_SMALL, 4, 4, sTextColor, TEXT_SKIP_DRAW, sText_Foot);
    PutWindowTilemap(SWIN_FOOT);
    CopyWindowToVram(SWIN_FOOT, COPYWIN_FULL);
}

static void Setup_Commit(u8 taskId, bool8 begin)
{
    if (begin)
    {
        gSpecialVar_0x8004 = sSetup->format;
        gSpecialVar_0x8005 = sSetup->cap;
        gSpecialVar_Result = 1;
    }
    else
    {
        gSpecialVar_Result = 0;
    }
    gTasks[taskId].func = Setup_Task_Exit;
}

static void Setup_Task_Main(u8 taskId)
{
    if (gPaletteFade.active)
        return;

    if (JOY_NEW(DPAD_UP | DPAD_DOWN))
    {
        sSetup->row ^= 1;
        PlaySE(SE_SELECT);
        Setup_DrawAll();
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT | A_BUTTON))
    {
        if (sSetup->row == SROW_FORMAT)
            sSetup->format ^= 1;
        else
            sSetup->cap = (sSetup->cap + 1) % 3;
        PlaySE(SE_SELECT);
        Setup_DrawAll();
    }
    else if (JOY_NEW(START_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        Setup_Commit(taskId, TRUE);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        Setup_Commit(taskId, FALSE);
    }
}

static void Setup_Task_Exit(u8 taskId)
{
    if (gPaletteFade.active)
        return;
    FREE_AND_SET_NULL(sSetup);
    FREE_AND_SET_NULL(sSetupBgTilemap);
    FreeAllWindowBuffers();
    DestroyTask(taskId);
    SetMainCallback2(CB2_ReturnToFieldContinueScript);
}
