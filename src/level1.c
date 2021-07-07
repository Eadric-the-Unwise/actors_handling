#define __BANK_PREFIX(A) __bank_##A
#define BANK(A) (UINT8) & (__BANK_PREFIX(A))
#define __SIZE_PREFIX(A) __size_##A
#define SIZE(A) (UWORD) & (__SIZE_PREFIX(A))
#define OFFSET(A) (void *)&(A)

#include "level1.h"

#include <gb/gb.h>

#include "../res/tiles/detective.h"
#include "../res/tiles/enemy_arrow.h"

// UINT8 hiwater;
UINT8 detective;
UINT8 enemy_arrow;
// array of avaliable actors
actor_t active_actors[MAX_ACTIVE_ACTORS];
UINT8 active_actors_count;  // amount of actors that are currently active
const uint8_t level1_count = 2;

const actor_t level1[2] =
    {
        {.x = 60,
         .y = 120,
         .tile_count = (sizeof(detective_data) >> 4),
         .tile_data = detective_data,
         .actor_metasprites = detective_metasprites,
         .metasprite_frame_index = 0},
        {.x = 40,
         .y = 60,
         .tile_count = (sizeof(enemy_arrow_data) >> 4),
         .tile_data = enemy_arrow_data,
         .actor_metasprites = enemy_arrow_metasprites,
         .metasprite_frame_index = 0}};

// UINT8 load_scene_actors(actor_t *actor, UINT8 hiwater) {
//     actor->tile_index = hiwater;
//     set_sprite_data(actor->tile_index, actor->tile_count, actor->tile_data);
//     hiwater += actor->tile_count;
//     return hiwater;
// }

void load_scene_actors(actor_t *actor, uint8_t active_actors_count) {
    actor_t *current_actor = active_actors;
    UINT8 hiwater = 0;
    for (UINT8 i = active_actors_count; i != 0; i++) {  //counter direction does not matter, because pointer is moved. only number of iterations matter.
        set_sprite_data(hiwater, actor->tile_count, actor->tile_data);
        hiwater += actor->tile_count;
        current_actor++;
        actor++;
    }
}

void render_actors() {
    actor_t *current_actor = active_actors;
    // draw each metasprite
    UINT8 sprite_hiwater = 0;
    UINT8 hiwater = 0;
    for (UINT8 i = active_actors_count; i != 0; i++) {
        sprite_hiwater += move_metasprite(
            current_actor->actor_metasprites[current_actor->metasprite_frame_index],
            hiwater,
            sprite_hiwater,
            current_actor->x, current_actor->y);
        hiwater += current_actor->tile_count;
        current_actor++;
    }
    // hide rest of the hardware sprites
    for (UINT8 i = hiwater; i < 40u; i++) shadow_OAM[i].y = 0;
}