#include "level1.h"

#include <gb/gb.h>

#include "../res/tiles/detective.h"
#include "../res/tiles/detective_large.h"
#include "../res/tiles/detective_large_walk.h"
#include "../res/tiles/detective_platform_stand.h"
#include "../res/tiles/enemy_arrow.h"
#include "scene.h"

const actor_t level1_actors[2] =
    {
        {.x = 88,
         .y = 120,
         .tile_count = (sizeof(detective_large_data) >> 4),
         .tile_index = 0,
         .tile_data = detective_large_data,
         .actor_metasprites = detective_large_metasprites,
         .metasprite_frame_index = 0},
        {.x = 160,
         .y = 60,
         .tile_count = (sizeof(enemy_arrow_data) >> 4),
         .tile_index = 0,
         .tile_data = enemy_arrow_data,
         .actor_metasprites = enemy_arrow_metasprites,
         .metasprite_frame_index = 0}};

const level_t level1 = {.actors = level1_actors,
                        .actor_count = 2};