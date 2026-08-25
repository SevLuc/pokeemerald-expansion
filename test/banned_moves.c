#include "global.h"
#include "pokemon.h"
#include "test/test.h"

// Player-only move bans (src/data/banned_moves.h + pokemon.c).
// Player and wild Pokemon must never carry banned moves; trainers are untouched.

static bool32 MonHasAnyBannedMove(struct Pokemon *mon)
{
    u32 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        enum Move move = GetMonData(mon, MON_DATA_MOVE1 + i);
        if (move != MOVE_NONE && IsMovePlayerBanned(move))
            return TRUE;
    }
    return FALSE;
}

static bool32 MonHasMove(struct Pokemon *mon, enum Move wanted)
{
    u32 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetMonData(mon, MON_DATA_MOVE1 + i) == wanted)
            return TRUE;
    }
    return FALSE;
}

TEST("IsMovePlayerBanned flags banned moves and clears legal ones")
{
    EXPECT(IsMovePlayerBanned(MOVE_TOXIC));
    EXPECT(IsMovePlayerBanned(MOVE_SWORDS_DANCE));
    EXPECT(IsMovePlayerBanned(MOVE_STEALTH_ROCK));
    EXPECT(IsMovePlayerBanned(MOVE_SUBSTITUTE));
    EXPECT(!IsMovePlayerBanned(MOVE_TACKLE));
    EXPECT(!IsMovePlayerBanned(MOVE_SURF));
}

TEST("GetBannedMoveReplacement returns the curated substitute")
{
    EXPECT_EQ(GetBannedMoveReplacement(SPECIES_BULBASAUR, MOVE_GROWTH), MOVE_SKULL_BASH);
    EXPECT_EQ(GetBannedMoveReplacement(SPECIES_BULBASAUR, MOVE_LEECH_SEED), MOVE_PETAL_DANCE);
    // No curated entry for this pair -> MOVE_NONE (backfill).
    EXPECT_EQ(GetBannedMoveReplacement(SPECIES_BULBASAUR, MOVE_TACKLE), MOVE_NONE);
}

TEST("ApplyPlayerMoveBans strips banned moves from a player mon")
{
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_BULBASAUR, 40, 0, OTID_STRUCT_PLAYER_ID);
    // Raw learnset gives Bulbasaur MOVE_GROWTH at this level (this is what trainers keep).
    EXPECT(MonHasMove(&mon, MOVE_GROWTH));

    ApplyPlayerMoveBans(&mon);
    EXPECT(!MonHasAnyBannedMove(&mon));
    EXPECT(!MonHasMove(&mon, MOVE_GROWTH));
    // Growth was swapped for its curated replacement.
    EXPECT(MonHasMove(&mon, MOVE_SKULL_BASH));
}

TEST("Player mon never learns a banned move on level up")
{
    struct Pokemon mon;
    u32 i;
    CreateMon(&mon, SPECIES_BULBASAUR, 5, 0, OTID_STRUCT_PLAYER_ID);
    ApplyPlayerMoveBans(&mon);

    for (i = 6; i <= 50; i++)
    {
        enum Move learned;
        SetMonData(&mon, MON_DATA_LEVEL, &i);
        learned = MonTryLearningNewMove(&mon, TRUE);
        while (learned != MOVE_NONE)
        {
            if (learned != MON_ALREADY_KNOWS_MOVE)
                EXPECT(!IsMovePlayerBanned(learned));
            learned = MonTryLearningNewMove(&mon, FALSE);
        }
    }
    EXPECT(!MonHasAnyBannedMove(&mon));
}
