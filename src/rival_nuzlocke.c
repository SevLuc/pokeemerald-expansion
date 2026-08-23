#include "global.h"
#include "rival_nuzlocke.h"
#include "event_data.h" // VarGet / VarSet
#include "random.h"     // Random32
#include "pokemon.h"        // gSpeciesInfo, enum Type, NUMBER_OF_MON_TYPES
#include "wild_encounter.h" // gWildMonHeaders, struct WildPokemonInfo
#include "battle.h"         // GetTypeModifier (via battle_util.h), uq4_12 helpers
#include "constants/opponents.h"
#include "constants/vars.h"
#include "constants/maps.h"    // MAP_GROUP(MAP_UNDEFINED) sentinel
#include "constants/species.h" // SPECIES_* names

#include "data/rival_nuzlocke_battles.h"

static const struct LockeBattle *Locke_FindBattle(u16 trainerNum)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sLockeBattles); i++)
        if (sLockeBattles[i].trainerId == trainerNum)
            return &sLockeBattles[i];
    return NULL;
}

bool32 IsLockeRivalTrainer(u16 trainerNum)
{
    return Locke_FindBattle(trainerNum) != NULL;
}

bool32 ShouldGenerateLockeParty(u16 trainerNum)
{
    return IsLockeRivalTrainer(trainerNum) && VarGet(VAR_RIVAL_ID) == RIVAL_ID_LOCKE;
}

u32 Locke_AreaArrayLen(void)
{
    return ARRAY_COUNT(sLockeAreas);
}

u32 Locke_BattlePoolCount(u16 trainerNum)
{
    const struct LockeBattle *b = Locke_FindBattle(trainerNum);
    return b ? b->poolCount : 0;
}

// Vanilla rival per-fight ACE level (the starter's level in trainers_frlg.party).
static u8 Locke_LevelForBattle(const struct LockeBattle *b)
{
    switch (b->trainerId)
    {
    case TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE:
    case TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR:
    case TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER: return 12;
    case TRAINER_RIVAL_CERULEAN_SQUIRTLE:
    case TRAINER_RIVAL_CERULEAN_BULBASAUR:
    case TRAINER_RIVAL_CERULEAN_CHARMANDER:      return 18;
    case TRAINER_RIVAL_SS_ANNE_SQUIRTLE:
    case TRAINER_RIVAL_SS_ANNE_BULBASAUR:
    case TRAINER_RIVAL_SS_ANNE_CHARMANDER:       return 20;
    case TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE:
    case TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR:
    case TRAINER_RIVAL_POKEMON_TOWER_CHARMANDER: return 25;
    case TRAINER_RIVAL_SILPH_SQUIRTLE:
    case TRAINER_RIVAL_SILPH_BULBASAUR:
    case TRAINER_RIVAL_SILPH_CHARMANDER:         return 40;
    case TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE:
    case TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR:
    case TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER:  return 53;
    case TRAINER_CHAMPION_FIRST_SQUIRTLE:
    case TRAINER_CHAMPION_FIRST_BULBASAUR:
    case TRAINER_CHAMPION_FIRST_CHARMANDER:      return 63;
    default:                                     return 75; // rematch
    }
}

static enum Species Locke_StarterOf(u16 trainerId)
{
    switch (trainerId)
    {
    case TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE: case TRAINER_RIVAL_CERULEAN_SQUIRTLE:
    case TRAINER_RIVAL_SS_ANNE_SQUIRTLE: case TRAINER_RIVAL_POKEMON_TOWER_SQUIRTLE:
    case TRAINER_RIVAL_SILPH_SQUIRTLE: case TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE:
    case TRAINER_CHAMPION_FIRST_SQUIRTLE: case TRAINER_CHAMPION_REMATCH_SQUIRTLE:
        return SPECIES_SQUIRTLE;
    case TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR: case TRAINER_RIVAL_CERULEAN_BULBASAUR:
    case TRAINER_RIVAL_SS_ANNE_BULBASAUR: case TRAINER_RIVAL_POKEMON_TOWER_BULBASAUR:
    case TRAINER_RIVAL_SILPH_BULBASAUR: case TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR:
    case TRAINER_CHAMPION_FIRST_BULBASAUR: case TRAINER_CHAMPION_REMATCH_BULBASAUR:
        return SPECIES_BULBASAUR;
    default:
        return SPECIES_CHARMANDER;
    }
}

// Evolve a freshly created mon up to whatever its level allows (chained).
static void Locke_EvolveToLevel(struct Pokemon *mon)
{
    bool32 canStop;
    u32 guard;
    for (guard = 0; guard < 3; guard++)
    {
        enum Species target = GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, 0, NULL, &canStop, CHECK_EVO);
        if (target == SPECIES_NONE)
            return;
        SetMonData(mon, MON_DATA_SPECIES, &target);
        CalculateMonStats(mon);
    }
}

static bool32 Locke_Contains(const enum Species *arr, u32 count, enum Species s)
{
    u32 i;
    for (i = 0; i < count; i++)
        if (arr[i] == s)
            return TRUE;
    return FALSE;
}

// Does `mon` resist attacking type `atk`? (defensive multiplier < 1)
static bool32 Locke_ResistsType(enum Species species, enum Type atk)
{
    enum Type d1 = gSpeciesInfo[species].types[0];
    enum Type d2 = gSpeciesInfo[species].types[1];
    uq4_12_t m = GetTypeModifier(atk, d1);
    if (d2 != d1)
        m = uq4_12_multiply(m, GetTypeModifier(atk, d2));
    return m < UQ_4_12(1.0);
}

u8 BuildLockeParty(struct Pokemon *party, u16 trainerNum)
{
    const struct LockeBattle *b = Locke_FindBattle(trainerNum);
    u32 seed = GetLockeSeed();
    enum Species starter = Locke_StarterOf(trainerNum);
    u8 level;
    enum Species pool[64];
    u32 poolN = 0;
    enum Species chosen[PARTY_SIZE];
    u32 chosenN = 0;
    bool32 used[64];
    u32 a, i;
    u32 aceIndex = 0; // starter is chosen[0]

    // Zero the whole party buffer first: the battle engine derives enemy team
    // size by scanning for the first SPECIES_NONE, so trailing slots left over
    // from a prior battle would appear as phantom enemy mons for short teams.
    ZeroPartyMons(party);

    if (b == NULL)
        return 0;
    level = Locke_LevelForBattle(b);

    // 1) One distinct species per area (dupes clause).
    for (a = 0; a < b->poolCount; a++)
    {
        const struct LockeArea *area = &sLockeAreas[a];
        u32 attempt;
        for (attempt = 0; attempt < 8; attempt++)
        {
            u32 pick = Locke_Hash(seed, (a << 4) + attempt);
            enum Species s = Locke_AreaSpeciesAt(area->mapGroup, area->mapNum, area->slotType, pick);
            if (s != SPECIES_NONE && !Locke_Contains(pool, poolN, s))
            {
                pool[poolN++] = s;
                break;
            }
        }
    }

    // 2) Coverage selection. Starter always kept (recorded as chosen[0], the ace).
    chosen[chosenN++] = starter;
    for (i = 0; i < 64; i++)
        used[i] = FALSE;

    while (chosenN < b->teamSize && (chosenN - 1) < poolN)
    {
        u32 bestIdx = 0xFFFFFFFF, bestScore = 0xFFFFFFFF;
        u32 p, atk;
        for (p = 0; p < poolN; p++)
        {
            u32 score;
            if (used[p])
                continue;
            score = Locke_CountWeaknesses(pool[p]) * 4;
            // bonus: resists a type the starter is weak to
            for (atk = 0; atk < NUMBER_OF_MON_TYPES; atk++)
            {
                enum Type sa = gSpeciesInfo[starter].types[0], sb = gSpeciesInfo[starter].types[1];
                uq4_12_t sm = GetTypeModifier(atk, sa);
                if (sb != sa) sm = uq4_12_multiply(sm, GetTypeModifier(atk, sb));
                if (sm > UQ_4_12(1.0) && Locke_ResistsType(pool[p], atk) && score >= 1)
                    score -= 1;
            }
            if (score < bestScore) { bestScore = score; bestIdx = p; }
        }
        if (bestIdx == 0xFFFFFFFF)
            break;
        used[bestIdx] = TRUE;
        chosen[chosenN++] = pool[bestIdx];
    }

    // 3) Create + evolve.
    for (i = 0; i < chosenN; i++)
    {
        CreateMon(&party[i], chosen[i], level, USE_RANDOM_IVS, OTID_STRUCT_RANDOM_NO_SHINY);
        Locke_EvolveToLevel(&party[i]);
    }

    // 4) Ordering: least-weak NON-ACE member leads; ace never slot 0.
    {
        u32 leadIdx = 0xFFFFFFFF, leadW = 0xFFFFFFFF;
        for (i = 0; i < chosenN; i++)
        {
            u32 w;
            if (i == aceIndex)
                continue;
            w = Locke_CountWeaknesses(GetMonData(&party[i], MON_DATA_SPECIES));
            if (w < leadW) { leadW = w; leadIdx = i; }
        }
        if (leadIdx != 0xFFFFFFFF && leadIdx != 0)
        {
            struct Pokemon tmp = party[0];
            party[0] = party[leadIdx];
            party[leadIdx] = tmp;
            if (aceIndex == 0) aceIndex = leadIdx;      // ace moved to leadIdx
            else if (aceIndex == leadIdx) aceIndex = 0; // (won't happen: ace skipped)
        }
        // If the ace still sits at slot 0 (e.g. only 1 non-ace member forced it), push it to slot 1.
        if (aceIndex == 0 && chosenN > 1)
        {
            struct Pokemon tmp = party[0];
            party[0] = party[1];
            party[1] = tmp;
            aceIndex = 1;
        }
    }

    return chosenN;
}

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
