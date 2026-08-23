#include "global.h"
#include "rival_nuzlocke.h"
#include "event_data.h" // VarGet / VarSet
#include "random.h"     // Random32
#include "pokemon.h"        // gSpeciesInfo, enum Type, NUMBER_OF_MON_TYPES
#include "wild_encounter.h" // gWildMonHeaders, struct WildPokemonInfo
#include "battle.h"         // GetTypeModifier (via battle_util.h), uq4_12 helpers
#include "constants/opponents.h"
#include "constants/vars.h"
#include "constants/maps.h" // MAP_GROUP(MAP_UNDEFINED) sentinel

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

// Splitmix32 — deterministic, well-distributed.
u32 Locke_Hash(u32 seed, u32 salt)
{
    u32 z = seed + salt * 0x9E3779B9u;
    z = (z ^ (z >> 16)) * 0x21F0AAADu;
    z = (z ^ (z >> 15)) * 0x735A2D97u;
    return z ^ (z >> 15);
}

u32 Locke_CountWeaknesses(enum Species species)
{
    enum Type d1 = gSpeciesInfo[species].types[0];
    enum Type d2 = gSpeciesInfo[species].types[1];
    u32 atk, count = 0;
    for (atk = 0; atk < NUMBER_OF_MON_TYPES; atk++)
    {
        uq4_12_t m = GetTypeModifier(atk, d1);
        if (d2 != d1)
            m = uq4_12_multiply(m, GetTypeModifier(atk, d2));
        if (m > UQ_4_12(1.0))
            count++;
    }
    return count;
}

// Finds the header for (group,num); returns NULL if the map or slot is absent.
static const struct WildPokemonInfo *Locke_SlotInfo(u8 mapGroup, u8 mapNum, u8 slotType)
{
    u32 i;
    for (i = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); i++)
    {
        const struct WildEncounterTypes *e;
        if (gWildMonHeaders[i].mapGroup != mapGroup || gWildMonHeaders[i].mapNum != mapNum)
            continue;
        e = &gWildMonHeaders[i].encounterTypes[0]; // time-of-day 0
        switch (slotType)
        {
        case LOCKE_SLOT_LAND:  return e->landMonsInfo;
        case LOCKE_SLOT_WATER: return e->waterMonsInfo;
        case LOCKE_SLOT_FISH:  return e->fishingMonsInfo;
        }
        return NULL;
    }
    return NULL;
}

// Returns the pick-th species in the slot table (wrapping by table length).
enum Species Locke_AreaSpeciesAt(u8 mapGroup, u8 mapNum, u8 slotType, u32 pick)
{
    const struct WildPokemonInfo *info = Locke_SlotInfo(mapGroup, mapNum, slotType);
    u32 len;
    if (info == NULL)
        return SPECIES_NONE;
    len = (slotType == LOCKE_SLOT_LAND) ? NUM_LAND_MONS_ENCOUNTER_SLOTS
        : (slotType == LOCKE_SLOT_WATER) ? NUM_WATER_MONS_ENCOUNTER_SLOTS
        : NUM_FISHING_MONS_ENCOUNTER_SLOTS;
    return info->wildPokemon[pick % len].species;
}

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
