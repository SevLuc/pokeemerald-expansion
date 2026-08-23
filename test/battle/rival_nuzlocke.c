#include "global.h"
#include "test/battle.h"
#include "rival_nuzlocke.h"

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
