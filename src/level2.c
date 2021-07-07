#include "level2.h"

#include <gb/gb.h>

#include "../res/tiles/detective.h"
#include "../res/tiles/enemy_arrow.h"
#include "scene.h"

const uint8_t level2_count = 4;

const actor_t level2_actors[4] =
    {
        {.x = 50,
         .y = 130,
         .tile_count = (sizeof(detective_data) >> 4),
         .tile_index = 0,
         .tile_data = detective_data,
         .actor_metasprites = detective_metasprites,
         .metasprite_frame_index = 0},
        {.x = 80,
         .y = 70,
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
         .y = 20,
         .tile_count = (sizeof(enemy_arrow_data) >> 4),
         .tile_index = 0,
         .tile_data = enemy_arrow_data,
         .actor_metasprites = enemy_arrow_metasprites,
         .metasprite_frame_index = 0}};
