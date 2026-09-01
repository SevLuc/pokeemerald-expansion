# Rental Battle UI Polish Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Fix the accidental-retire control trap on the rental pick screen and give the pick screen and run-setup step a polished, consistent look matching the draft belt screen.

**Architecture:** Three C "screens" drive rental mode (all in `src/`): the draft belt (`rental_select_screen.c`, unchanged), the per-battle pick screen (`rental_preview_screen.c`, reworked), and a new setup screen (`rental_setup_screen.c`) that replaces two overworld multichoice menus. Screens are BG0 + text windows + mon-icon sprites; the new visuals use a tiny runtime-authored solid-color tileset (no PNG assets) so ROM impact is a handful of tiles. The lobby script (`data/maps/BattleFrontier_BattleTowerLobby/scripts.inc`) wires the setup screen via a new `special DoRentalSetup`.

**Tech Stack:** C (pokeemerald-expansion, FireRed target), devkitARM, poryscript `.inc` event scripts, `make firered`.

**Verification note:** These are GBA UI screens with no unit-test harness. Each task's verification is: (a) the ROM compiles clean with no new warnings (`-Werror` is on), and (b) a specific manual playtest check in mGBA. This matches the project rule that only new moves/abilities require battle tests.

**How to build:**
```bash
cd "/Users/lucsev/Documents/Projects/firered romhack"
export DEVKITARM=/opt/devkitpro/devkitARM
export PATH=$DEVKITARM/bin:$PATH
export PKG_CONFIG_PATH=/opt/homebrew/lib/pkgconfig:/usr/local/lib/pkgconfig
make firered -j$(sysctl -n hw.ncpu)
```
(Work happens in the worktree; the user builds from the main checkout. If building from the worktree, run `make firered` from the worktree root instead.)

---

## File map

- Modify `src/rental_preview_screen.c`: control rework (Task 1) + Direction A visuals (Task 2).
- Create `src/rental_setup_screen.c`: new themed setup screen (Task 3).
- Modify `include/rental_mode.h`: declare `DoRentalSetup` (Task 3).
- Modify `data/specials.inc`: register `DoRentalSetup` (Task 3).
- Modify `data/maps/BattleFrontier_BattleTowerLobby/scripts.inc`: wire setup screen, drop dead menus (Task 4).
- Modify `docs/overview/changelog.md`: record the change (Task 5).

---

## Task 1: Pick screen control rework (B = undo, SELECT = retire w/ confirm)

**Files:**
- Modify: `src/rental_preview_screen.c`

This task is pure input/logic, no visual changes. It removes the accidental-retire trap.

- [ ] **Step 1: Add confirm state to the struct**

In `struct RentalPreview` (around line 66-77), add two fields after `bool8 scoutOpen;`:

```c
    bool8 scoutOpen;
    bool8 retireConfirmOpen;   // SELECT opened the retire Yes/No box
    bool8 retireYes;           // confirm cursor: FALSE = NO (default), TRUE = YES
```

- [ ] **Step 2: Update the hint strings**

Replace the three hint string definitions (around lines 139-141):

```c
static const u8 sText_HintOpp[]    = _("Pad: Move   A: Scout   B: Leave");
static const u8 sText_HintPlr[]    = _("Pad: Move   A: Pick/Drop   B: Leave");
static const u8 sText_HintGo[]     = _("START: Begin once your team is set");
```

with:

```c
static const u8 sText_HintOpp[]    = _("Pad: Move  A: Scout  B: Undo  SEL: Retire");
static const u8 sText_HintPlr[]    = _("Pad: Move  A: Pick  B: Undo  SEL: Retire");
static const u8 sText_HintGo[]     = _("START: Begin once your team is set");
```

Then add the retire-confirm strings immediately after `sText_Gap` (around line 145):

```c
static const u8 sText_RetireQ[]    = _("Retire this run?");
static const u8 sText_Yes[]        = _("YES");
static const u8 sText_No[]         = _("NO");
static const u8 sText_ConfirmHint[]= _("A: Confirm   B: Cancel");
```

- [ ] **Step 3: Add the undo and retire-confirm helpers**

Add these two functions just above `static void Preview_Confirm(u8 taskId)` (around line 430):

```c
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
    AddTextPrinterParameterized3(PWIN_MSG, FONT_SMALL, 140, 16, sTextColor, TEXT_SKIP_DRAW, sText_ConfirmHint);
    PutWindowTilemap(PWIN_MSG);
    CopyWindowToVram(PWIN_MSG, COPYWIN_FULL);
}
```

- [ ] **Step 4: Rewrite the main input handler**

Replace the entire `Preview_Task_Main` function (lines 459-528) with:

```c
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
```

- [ ] **Step 5: Build**

Run the build command from the header. Expected: compiles clean, no new warnings.

- [ ] **Step 6: Playtest verification (mGBA)**

Enter a rental run, reach the pick screen. Confirm:
- Pick to full; **B** removes the last-picked mon (badge count drops); B with none picked = failure beep, no exit.
- **SELECT** opens "Retire this run?" with cursor on **NO**; Left/Right toggles; **A on NO** or **B** returns to picking; **A on YES** ends the run to the hub "another run?" prompt.
- **B never exits the screen.** START still begins only when the team is full.

- [ ] **Step 7: Commit**

```bash
git add src/rental_preview_screen.c
git commit -m "fix(rental): B undoes last pick, SELECT retires with confirm on preview screen"
```

---

## Task 2: Pick screen Direction A visuals (framed bays + cursor highlight)

**Files:**
- Modify: `src/rental_preview_screen.c`

Adds a yellow-framed foe bay and cyan-framed player bay behind the icon rows, plus a highlighted cell under the cursor. Uses a runtime solid-color tileset (4 tiles), no new art assets.

- [ ] **Step 1: Extend the palette**

Replace the palette table (lines 119-125) with this (adds panel/frame/highlight colors at indices 4-7; index 4 was a color already present but unused by draw code, so redefining is safe):

```c
// Palette 15: 0 = navy backdrop, 1 = white text, 2 = shadow, 3 = gold accent,
// 4 = bay interior panel, 5 = foe frame (yellow), 6 = player frame (cyan),
// 7 = cursor cell highlight.
static const u16 sPreview_Pal[16] =
{
    RGB(4, 4, 10), RGB(31, 31, 31), RGB(9, 9, 14), RGB(30, 24, 10),
    RGB(6, 6, 14), RGB(30, 24, 8), RGB(13, 22, 26), RGB(12, 12, 26),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
    RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0), RGB(0, 0, 0),
};
```

- [ ] **Step 2: Add the solid-tile set and tile ids**

Add just below the palette (after line 125). Each tile is 32 bytes (8x8, 4bpp); a solid tile of palette index N has every byte equal to `(N<<4)|N` (both 4-bit pixels = N). The tiles are loaded at char index 500, above every window's glyph region in this charblock (windows here end near tile 300), so text rendering can't overwrite them. Tile 0 stays the blank navy backdrop.

```c
// Runtime solid-color tiles for the bays, loaded high to avoid the window glyph
// region. Values below are absolute char-tile indices used in the tilemap.
#define BAYTILE_BASE       500
enum {
    BAYTILE_PANEL     = BAYTILE_BASE, // pal 4 (bay interior)
    BAYTILE_FRAME_OPP,                // pal 5 (yellow)
    BAYTILE_FRAME_PLR,                // pal 6 (cyan)
    BAYTILE_HILITE,                   // pal 7
};
#define BAYTILE_NUM 4

#define SOLID_TILE(b) \
    (b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b), \
    (b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b),(b)
#define SOLID(idx) SOLID_TILE(((idx) << 4) | (idx))

static const u8 sPreview_BayTiles[BAYTILE_NUM * 32] =
{
    SOLID(4),  // BAYTILE_PANEL
    SOLID(5),  // BAYTILE_FRAME_OPP
    SOLID(6),  // BAYTILE_FRAME_PLR
    SOLID(7),  // BAYTILE_HILITE
};
```

- [ ] **Step 3: Declare the bay-draw helper**

Add to the forward declarations (near line 85-93):

```c
static void Preview_DrawBays(void);
```

- [ ] **Step 4: Implement the bay draw**

Add this function just above `Preview_DrawTitleHud` (around line 281). Coordinates are in 8px tiles; icons sit at y=24px (tiles 3-6) and y=80px (tiles 10-13).

```c
// Framed decorative bays behind each icon row, drawn straight into the BG tilemap.
static void Preview_DrawBays(void)
{
    // Foe bay: yellow frame, dark interior.
    FillBgTilemapBufferRect(0, BAYTILE_FRAME_OPP, 1, 2, 28, 6, 15);
    FillBgTilemapBufferRect(0, BAYTILE_PANEL,     2, 3, 26, 4, 15);
    // Player bay: cyan frame, dark interior.
    FillBgTilemapBufferRect(0, BAYTILE_FRAME_PLR, 1, 9, 28, 6, 15);
    FillBgTilemapBufferRect(0, BAYTILE_PANEL,     2, 10, 26, 4, 15);
}
```

- [ ] **Step 5: Add a cursor-cell highlight to the raise helper**

Replace `Preview_UpdateCursorRaise` (lines 267-279) with a version that also paints a highlight cell under the active icon. It redraws both bay interiors first (to clear the previous highlight), then highlights the current cell.

```c
static void Preview_UpdateCursorRaise(void)
{
    u8 i;
    s16 hx;

    for (i = 0; i < sPreview->oppCount; i++)
        gSprites[sPreview->iconSpriteIds[ROW_OPP][i]].y = ICON_OPP_Y;
    for (i = 0; i < sPreview->plrCount; i++)
        gSprites[sPreview->iconSpriteIds[ROW_PLR][i]].y = ICON_PLR_Y;

    // Repaint both interiors, then drop a highlight cell under the cursor.
    FillBgTilemapBufferRect(0, BAYTILE_PANEL, 2, 3, 26, 4, 15);
    FillBgTilemapBufferRect(0, BAYTILE_PANEL, 2, 10, 26, 4, 15);

    hx = 2 + sPreview->col * (ICON_STEP_X / 8); // 36px step -> ~4.5 tiles; approx to cell
    if (sPreview->row == ROW_OPP)
    {
        gSprites[sPreview->iconSpriteIds[ROW_OPP][sPreview->col]].y = ICON_OPP_Y - CURSOR_RAISE;
        FillBgTilemapBufferRect(0, BAYTILE_HILITE, hx, 3, 4, 4, 15);
    }
    else
    {
        gSprites[sPreview->iconSpriteIds[ROW_PLR][sPreview->col]].y = ICON_PLR_Y - CURSOR_RAISE;
        FillBgTilemapBufferRect(0, BAYTILE_HILITE, hx, 10, 4, 4, 15);
    }
    CopyBgTilemapBufferToVram(0);
}
```

- [ ] **Step 6: Load tiles and draw bays during init**

In `CB2_InitRentalPreview` case 0 (around line 175-176), after `FillBgTilemapBufferRect(0, 0, 0, 0, 32, 32, 15);`, add the tile load:

```c
        FillBgTilemapBufferRect(0, 0, 0, 0, 32, 32, 15);
        LoadBgTiles(0, sPreview_BayTiles, sizeof(sPreview_BayTiles), BAYTILE_BASE);
        CopyBgTilemapBufferToVram(0);
```

Then in case 4 (around line 210-217), add the bay draw before the HUD draws:

```c
    case 4:
        Preview_DrawBays();
        Preview_DrawTitleHud();
        Preview_DrawMid();
        Preview_DrawTags();
        Preview_DrawInstructions();
        Preview_UpdateCursorRaise();
        CopyBgTilemapBufferToVram(0);
        gMain.state++;
        break;
```

- [ ] **Step 7: Build**

Run the build. Expected: clean compile.

- [ ] **Step 8: Playtest verification (mGBA)**

On the pick screen confirm: foe row sits in a yellow-framed bay, your row in a cyan-framed bay; the cursor cell is visibly highlighted and follows Left/Right/Up/Down; order badges still show on picked mons; text (CHALLENGER / STREAK / BRING / hints) is still readable over the panels. If a bay row overlaps a text label awkwardly, nudge the `y` in `Preview_DrawBays` / `Preview_UpdateCursorRaise` and rebuild (interiors and highlight share the same rows, keep them in sync).

- [ ] **Step 9: Commit**

```bash
git add src/rental_preview_screen.c
git commit -m "feat(rental): Direction A framed bays and cursor highlight on preview screen"
```

---

## Task 3: New themed Setup screen (`DoRentalSetup`)

**Files:**
- Create: `src/rental_setup_screen.c`
- Modify: `include/rental_mode.h`
- Modify: `data/specials.inc`

One screen replaces the two overworld multichoice menus. It sets `gSpecialVar_0x8004` (format 0/1), `gSpecialVar_0x8005` (cap 0/1/2), and `gSpecialVar_Result` (1 begin / 0 exit), then returns to the script, which calls the existing `StartRentalDraft`.

- [ ] **Step 1: Create the setup screen file**

Create `src/rental_setup_screen.c` with exactly this content:

```c
#include "global.h"
#include "main.h"
#include "bg.h"
#include "gpu_regs.h"
#include "palette.h"
#include "window.h"
#include "text.h"
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
```

- [ ] **Step 2: Declare the special in the header**

In `include/rental_mode.h`, add near the other screen declarations (after the `void DoRentalTeamPreview(void);` line, ~line 102):

```c
void DoRentalSetup(void); // themed run-setup screen (format + restricted cap)
```

- [ ] **Step 3: Register the special**

In `data/specials.inc`, add a line in the rental block (after `def_special StartRentalDraft`, line 22):

```
	def_special DoRentalSetup
```

- [ ] **Step 4: Build**

Run the build. Expected: the new file compiles and links; `DoRentalSetup` resolves. (The screen isn't wired into the script yet, that happens in Task 4, so it won't run in game, but it must compile.)

- [ ] **Step 5: Commit**

```bash
git add src/rental_setup_screen.c include/rental_mode.h data/specials.inc
git commit -m "feat(rental): themed run-setup screen (format + restricted cap)"
```

---

## Task 4: Wire the setup screen into the lobby script

**Files:**
- Modify: `data/maps/BattleFrontier_BattleTowerLobby/scripts.inc`

Replace the two multichoice blocks with a single call to `DoRentalSetup`, and delete the now-dead menu labels and their strings.

- [ ] **Step 1: Replace the setup script blocks**

Replace lines 1415-1450 (from `BattleFrontier_BattleTowerLobby_EventScript_RentalAskFormat::` through the end of `..._EventScript_RentalStartDraft::`'s body, i.e. up to and including the `closemessage`/`special StartRentalDraft`/`waitstate` of the old StartDraft label). The exact old block is:

```
BattleFrontier_BattleTowerLobby_EventScript_RentalAskFormat::
	message BattleFrontier_BattleTowerLobby_Text_RentalFormatPrompt
	waitmessage
	dynmultipush BattleFrontier_BattleTowerLobby_Text_RentalOptSingles, 0
	dynmultipush BattleFrontier_BattleTowerLobby_Text_RentalOptDoubles, 1
	dynmultistack 1, 1, FALSE, 2, 0, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_RentalFmtSingles
	case 1, BattleFrontier_BattleTowerLobby_EventScript_RentalFmtDoubles
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_RentalExitMode
BattleFrontier_BattleTowerLobby_EventScript_RentalFmtSingles::
	setvar VAR_0x8004, 0
	goto BattleFrontier_BattleTowerLobby_EventScript_RentalAskCap
BattleFrontier_BattleTowerLobby_EventScript_RentalFmtDoubles::
	setvar VAR_0x8004, 1
BattleFrontier_BattleTowerLobby_EventScript_RentalAskCap::
	message BattleFrontier_BattleTowerLobby_Text_RentalCapPrompt
	waitmessage
	dynmultipush BattleFrontier_BattleTowerLobby_Text_RentalOptCapNone, 0
	dynmultipush BattleFrontier_BattleTowerLobby_Text_RentalOptCapOne, 1
	dynmultipush BattleFrontier_BattleTowerLobby_Text_RentalOptCapTwo, 2
	dynmultistack 1, 1, FALSE, 3, 0, 0, DYN_MULTICHOICE_CB_NONE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleTowerLobby_EventScript_RentalCap0
	case 1, BattleFrontier_BattleTowerLobby_EventScript_RentalCap1
	case 2, BattleFrontier_BattleTowerLobby_EventScript_RentalCap2
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerLobby_EventScript_RentalAskFormat
BattleFrontier_BattleTowerLobby_EventScript_RentalCap0::
	setvar VAR_0x8005, 0
	goto BattleFrontier_BattleTowerLobby_EventScript_RentalStartDraft
BattleFrontier_BattleTowerLobby_EventScript_RentalCap1::
	setvar VAR_0x8005, 1
	goto BattleFrontier_BattleTowerLobby_EventScript_RentalStartDraft
BattleFrontier_BattleTowerLobby_EventScript_RentalCap2::
	setvar VAR_0x8005, 2
BattleFrontier_BattleTowerLobby_EventScript_RentalStartDraft::
	closemessage
	special StartRentalDraft
	waitstate
```

Replace all of it with:

```
BattleFrontier_BattleTowerLobby_EventScript_RentalAskFormat::
	closemessage
	special DoRentalSetup
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerLobby_EventScript_RentalExitMode
BattleFrontier_BattleTowerLobby_EventScript_RentalStartDraft::
	special StartRentalDraft
	waitstate
```

Note: the label `..._EventScript_RentalStartDraft::` is kept (nothing else jumps to it today, but keeping it is harmless and preserves the anchor). The `..._EventScript_RentalBattleLoop::` label immediately follows in the file and is untouched.

- [ ] **Step 2: Delete the dead setup strings**

Delete these now-unreferenced string definitions (lines 1521-1541): `..._Text_RentalFormatPrompt`, `..._Text_RentalOptSingles`, `..._Text_RentalOptDoubles`, `..._Text_RentalCapPrompt`, `..._Text_RentalOptCapNone`, `..._Text_RentalOptCapOne`, `..._Text_RentalOptCapTwo`. Leave `..._Text_RentalDraftIntro` (still used) and everything from `..._Text_RentalPreview` onward.

- [ ] **Step 3: Build**

Run the build. Expected: script assembles, no "undefined symbol" for the deleted labels/strings, links clean.

- [ ] **Step 4: Playtest verification (mGBA)**

Start rental mode from the loaner floor: keeper's line shows, then the **Setup screen** appears. Toggle FORMAT (note flips bring 3 / bring 4), cycle RESTRICTED 0/1/2, help line updates per row. **START** begins the draft with the chosen values (verify in the following draft/battle that doubles brings 4, cap allows the right number of restricted mons). **B** on the setup screen leaves rental mode (soft reset to title).

- [ ] **Step 5: Commit**

```bash
git add data/maps/BattleFrontier_BattleTowerLobby/scripts.inc
git commit -m "feat(rental): use themed setup screen; drop old format/cap multichoice menus"
```

---

## Task 5: Docs + full-flow verification

**Files:**
- Modify: `docs/overview/changelog.md`

- [ ] **Step 1: Add a changelog entry**

Append under the most recent dated section (or add a new `## 2026-09-01` heading if none for today) in `docs/overview/changelog.md`:

```markdown
- Rental battle: new themed run-setup screen (format + restricted cap) replacing the
  two overworld menus; pick screen redesigned with framed foe/team bays and a cursor
  highlight; pick-screen controls reworked so B undoes the last pick and SELECT
  retires behind a Yes/No confirm (B can no longer end a run by accident).
```

If `docs/overview/changelog.md` does not exist, create it with a top-level `# Changelog` heading followed by a `## 2026-09-01` section containing the bullet above.

- [ ] **Step 2: Full-run playtest (mGBA)**

Play one complete rental interaction end to end: loaner line, setup screen, draft 6 of 12, pick screen (scout, pick, undo, retire-confirm cancel), a battle, win, another pick, then SELECT-retire (confirm YES) to the "another run?" prompt. Confirm nothing regressed and every new control behaves per the spec.

- [ ] **Step 3: Commit**

```bash
git add docs/overview/changelog.md
git commit -m "docs(overview): changelog for rental UI polish"
```

---

## Self-review notes

- **Spec coverage:** Setup screen (Task 3-4), pick-screen Direction A visuals (Task 2), B=undo/SELECT=retire controls (Task 1), draft/recruit screens untouched (out of scope, honored), keeper text preserved (Task 4 keeps `RentalDraftIntro`). All spec sections mapped.
- **Var contract:** setup writes `gSpecialVar_0x8004`/`0x8005`/`Result`; `StartRentalDraft` already reads `0x8004`/`0x8005` (confirmed in `src/rental_mode.c:348`). Consistent.
- **Control names:** `retireConfirmOpen`/`retireYes` used consistently in Task 1. `Preview_Undo`, `Preview_DrawRetireConfirm`, `Preview_DrawBays` declared and defined.
- **Risk / tuning:** the bay/highlight tile coordinates in Task 2 and the panel/text positions in Task 3 are pixel-tuned by eye in mGBA; steps say to nudge and rebuild. This is expected for GBA UI and does not change the logic.
```
