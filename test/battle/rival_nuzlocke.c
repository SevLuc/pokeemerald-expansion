#include "global.h"
#include "test/battle.h"
#include "rival_nuzlocke.h"
#include "event_data.h"
#include "constants/vars.h"
#include "constants/maps.h"

TEST("Locke: predicate matches all rival fights except Oak's Lab and Twitch")
{
    EXPECT(IsLockeRivalTrainer(TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE));
    EXPECT(IsLockeRivalTrainer(TRAINER_RIVAL_CERULEAN_CHARMANDER));
    EXPECT(IsLockeRivalTrainer(TRAINER_CHAMPION_FIRST_BULBASAUR));
    EXPECT(IsLockeRivalTrainer(TRAINER_CHAMPION_REMATCH_SQUIRTLE));
    EXPECT(!IsLockeRivalTrainer(TRAINER_RIVAL_OAKS_LAB_SQUIRTLE));
    EXPECT(!IsLockeRivalTrainer(TRAINER_RIVAL_TWITCH_CERULEAN));
    EXPECT(!IsLockeRivalTrainer(TRAINER_BUG_CATCHER_ANTHONY)); // any non-rival
}

TEST("Locke: seed is stable once set and nonzero after init")
{
    VarSet(VAR_LOCKE_SEED_LO, 0);
    VarSet(VAR_LOCKE_SEED_HI, 0);
    InitLockeSeed();
    u32 first = GetLockeSeed();
    EXPECT(first != 0);
    EXPECT_EQ(GetLockeSeed(), first); // stable across calls
    InitLockeSeed();                  // idempotent: does not overwrite an existing seed
    EXPECT_EQ(GetLockeSeed(), first);
}

TEST("Locke: weakness count matches known typings")
{
    // Geodude (Rock/Ground): weak to Water, Grass, Ice, Fighting, Ground, Steel = 6
    EXPECT_EQ(Locke_CountWeaknesses(SPECIES_GEODUDE), 6);
    // Pidgey (Normal/Flying): weak to Electric, Ice, Rock = 3
    EXPECT_EQ(Locke_CountWeaknesses(SPECIES_PIDGEY), 3);
}

TEST("Locke: hashed RNG is deterministic and varies by salt")
{
    u32 a = Locke_Hash(12345u, 1u);
    EXPECT_EQ(a, Locke_Hash(12345u, 1u));
    EXPECT(a != Locke_Hash(12345u, 2u));
}

TEST("Locke: land species lookup returns a valid species from Route 1")
{
    enum Species s = Locke_AreaSpeciesAt(MAP_GROUP(MAP_ROUTE1), MAP_NUM(MAP_ROUTE1), LOCKE_SLOT_LAND, 0);
    EXPECT(s != SPECIES_NONE);
}

TEST("Locke: early Route 22 party has 4 mons, no dupes, starter present and not lead")
{
    struct Pokemon party[PARTY_SIZE];
    VarSet(VAR_LOCKE_SEED_LO, 0x1234);
    VarSet(VAR_LOCKE_SEED_HI, 0x5678);
    u8 n = BuildLockeParty(party, TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER); // rival took Charmander
    EXPECT_EQ(n, 4);

    u32 i, j;
    bool32 hasStarter = FALSE;
    for (i = 0; i < n; i++)
    {
        enum Species si = GetMonData(&party[i], MON_DATA_SPECIES);
        EXPECT(si != SPECIES_NONE);
        if (si == SPECIES_CHARMANDER || si == SPECIES_CHARMELEON || si == SPECIES_CHARIZARD)
            hasStarter = TRUE;
        for (j = i + 1; j < n; j++)
            EXPECT(si != GetMonData(&party[j], MON_DATA_SPECIES));
    }
    EXPECT(hasStarter);

    enum Species lead = GetMonData(&party[0], MON_DATA_SPECIES);
    EXPECT(lead != SPECIES_CHARMANDER && lead != SPECIES_CHARMELEON && lead != SPECIES_CHARIZARD);
}

TEST("Locke: same seed reproduces the same team")
{
    struct Pokemon a[PARTY_SIZE], b[PARTY_SIZE];
    VarSet(VAR_LOCKE_SEED_LO, 0xABCD); VarSet(VAR_LOCKE_SEED_HI, 0x0001);
    u8 na = BuildLockeParty(a, TRAINER_RIVAL_CERULEAN_SQUIRTLE);
    u8 nb = BuildLockeParty(b, TRAINER_RIVAL_CERULEAN_SQUIRTLE);
    EXPECT_EQ(na, nb);
    for (u32 i = 0; i < na; i++)
        EXPECT_EQ(GetMonData(&a[i], MON_DATA_SPECIES), GetMonData(&b[i], MON_DATA_SPECIES));
}

TEST("Locke: lead has the minimum weakness count among non-ace members")
{
    struct Pokemon party[PARTY_SIZE];
    VarSet(VAR_LOCKE_SEED_LO, 0x0F0F); VarSet(VAR_LOCKE_SEED_HI, 0x00A0);
    u8 n = BuildLockeParty(party, TRAINER_RIVAL_CERULEAN_BULBASAUR);
    u32 leadW = Locke_CountWeaknesses(GetMonData(&party[0], MON_DATA_SPECIES));
    for (u32 i = 1; i < n; i++)
    {
        enum Species si = GetMonData(&party[i], MON_DATA_SPECIES);
        if (si == SPECIES_BULBASAUR || si == SPECIES_IVYSAUR || si == SPECIES_VENUSAUR)
            continue; // ace excluded from the lead comparison
        EXPECT(leadW <= Locke_CountWeaknesses(si));
    }
}

TEST("Locke: every battle poolCount is within the area array and early fight is 3")
{
    EXPECT(Locke_AreaArrayLen() >= 3);
    EXPECT_EQ(Locke_BattlePoolCount(TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE), 3);
    EXPECT(Locke_BattlePoolCount(TRAINER_CHAMPION_FIRST_SQUIRTLE) <= Locke_AreaArrayLen());
    EXPECT(Locke_BattlePoolCount(TRAINER_CHAMPION_FIRST_SQUIRTLE) >= 5);
}
