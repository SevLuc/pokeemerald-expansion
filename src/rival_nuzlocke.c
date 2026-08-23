#include "global.h"
#include "rival_nuzlocke.h"
#include "event_data.h" // VarGet / VarSet
#include "random.h"     // Random32
#include "constants/opponents.h"
#include "constants/vars.h"

static const u16 sLockeTrainerIds[] =
{
    TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE, TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR, TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER,
    TRAINER_RIVAL_CERULEAN_SQUIRTLE, TRAINER_RIVAL_CERULEAN_BULBASAUR, TRAINER_RIVAL_CERULEAN_CHARMANDER,
    TRAINER_RIVAL_SS_ANNE_SQUIRTLE, TRAINER_RIVAL_SS_ANNE_BULBASAUR, TRAINER_RIVAL_SS_ANNE_CHARMANDER,
    TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE, TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR, TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER,
    TRAINER_RIVAL_SILPH_SQUIRTLE, TRAINER_RIVAL_SILPH_BULBASAUR, TRAINER_RIVAL_SILPH_CHARMANDER,
    TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE, TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR, TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER,
    TRAINER_CHAMPION_FIRST_SQUIRTLE, TRAINER_CHAMPION_FIRST_BULBASAUR, TRAINER_CHAMPION_FIRST_CHARMANDER,
    TRAINER_CHAMPION_REMATCH_SQUIRTLE, TRAINER_CHAMPION_REMATCH_BULBASAUR, TRAINER_CHAMPION_REMATCH_CHARMANDER,
};

bool32 IsLockeRivalTrainer(u16 trainerNum)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sLockeTrainerIds); i++)
        if (sLockeTrainerIds[i] == trainerNum)
            return TRUE;
    return FALSE;
}

u8 BuildLockeParty(struct Pokemon *party, u16 trainerNum) { return 0; }

u32 GetLockeSeed(void)
{
    return ((u32)VarGet(VAR_LOCKE_SEED_HI) << 16) | (u32)VarGet(VAR_LOCKE_SEED_LO);
}

void InitLockeSeed(void)
{
    if (GetLockeSeed() != 0)
        return; // already seeded this save
    u32 seed = Random32();
    if (seed == 0)
        seed = 0x9E3779B9; // avoid the "unseeded" sentinel
    VarSet(VAR_LOCKE_SEED_LO, seed & 0xFFFF);
    VarSet(VAR_LOCKE_SEED_HI, (seed >> 16) & 0xFFFF);
}
