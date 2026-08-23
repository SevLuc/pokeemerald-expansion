#include "global.h"
#include "test/battle.h"
#include "rival_nuzlocke.h"
#include "event_data.h"
#include "constants/vars.h"

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
