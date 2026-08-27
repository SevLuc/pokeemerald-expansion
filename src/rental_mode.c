#include "global.h"
#include "random.h"
#include "string_util.h"
#include "pokemon.h"
#include "move.h"
#include "battle_tower_rental.h"

// Standalone rental battle mode.
//
// This file will grow into the mode's controller (draft, team preview, recruit).
// For the M2 skeleton it holds a single script special that proves the generated
// rental pool (gRentalMons, from tools/gen_rental_mons.py) is compiled into the
// ROM and indexable at run time.

// Script special: pick a random set from the rental pool and buffer its species
// name into gStringVar1 and its first move's name into gStringVar2, so a lobby
// script can display them. If the message shows a real species and move, the whole
// M0 data pipeline (JSON -> generated table -> in-game) is working end to end.
void BufferRandomRentalMon(void)
{
    u32 index = Random() % NUM_RENTAL_MONS;
    const struct TrainerMon *set = &gRentalMons[index];

    StringCopy(gStringVar1, GetSpeciesName(set->species));
    StringCopy(gStringVar2, GetMoveName(set->moves[0]));
}
