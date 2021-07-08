#include "level2.h"

#include <gb/gb.h>

#include "../res/tiles/detective.h"
#include "../res/tiles/enemy_arrow.h"
#include "scene.h"

const actor_t level2_actors[4] =
    {
        {.x = 140,
         .y = 36,
         .tile_count = (sizeof(detective_data) >> 4),
         .tile_index = 0,
         .tile_data = detective_data,
         .actor_metasprites = detective_metasprites,
         .metasprite_frame_index = 0},
        {.x = 160,
         .y = 140,
         .tile_count = (sizeof(enemy_arrow_data) >> 4),
         .tile_index = 0,
         .tile_data = enemy_arrow_data,
         .actor_metasprites = enemy_arrow_metasprites,
         .metasprite_frame_index = 0},
        {.x = 120,
         .y = 50,
         .tile_count = (sizeof(enemy_arrow_data) >> 4),
         .tile_index = 0,
         .tile_data = enemy_arrow_data,
         .actor_metasprites = enemy_arrow_metasprites,
         .metasprite_frame_index = 0},
        {.x = 140,
         .y = 80,
         .tile_count = (sizeof(enemy_arrow_data) >> 4),
         .tile_index = 0,
         .tile_data = enemy_arrow_data,
         .actor_metasprites = enemy_arrow_metasprites,
         .metasprite_frame_index = 0}};
const level_t level2 = {.actors = level2_actors,
                        .actor_count = 4};