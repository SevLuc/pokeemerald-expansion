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

TEST("Locke: every battle poolCount is within the area array and early fight is 3")
{
    EXPECT(Locke_AreaArrayLen() >= 3);
    EXPECT_EQ(Locke_BattlePoolCount(TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE), 3);
    EXPECT(Locke_BattlePoolCount(TRAINER_CHAMPION_FIRST_SQUIRTLE) <= Locke_AreaArrayLen());
    EXPECT(Locke_BattlePoolCount(TRAINER_CHAMPION_FIRST_SQUIRTLE) >= 5);
}
