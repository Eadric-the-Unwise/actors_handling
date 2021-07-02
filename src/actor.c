#define __BANK_PREFIX(A) __bank_##A
#define BANK(A) (UINT8) & (__BANK_PREFIX(A))
#define __SIZE_PREFIX(A) __size_##A
#define SIZE(A) (UWORD) & (__SIZE_PREFIX(A))
#define OFFSET(A) (void *)&(A)

#include "actor.h"

#include <gb/gb.h>

#include "../res/tiles/detective.h"
#include "../res/tiles/enemy_arrow.h"

// UINT8 hiwater;

actor_t actor[2] =
    {
        {.x = 60,
         .y = 120,
         .sprite_index = 0,
         .tile_index = 0,
         .tile_count = (sizeof(detective_data)),
         .tile_data = detective_data,
         .actor_metasprite = detective_metasprites[0]},

        {.x = 40,
         .y = 60,
         .sprite_index = 0,
         .tile_index = 0,
         .tile_count = (sizeof(enemy_arrow_data)),
         .tile_data = enemy_arrow_data,
         .actor_metasprite = enemy_arrow_metasprites[0]}};

UINT8 load_scene_actors(actor_t *actor) {
    set_sprite_data(actor->tile_index, actor->tile_count, actor->tile_data);
    move_metasprite(actor->actor_metasprite, actor->tile_index, actor->sprite_index, actor->x, actor->y);
}