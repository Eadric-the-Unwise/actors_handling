#include <gb/console.h>
#include <gb/drawing.h>
#include <gb/font.h>
#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdint.h>
#include <stdio.h>

#include "level1.h"
#include "level2.h"
#include "scene.h"

UINT8 joy;
UINT8 hiwater;

void move_enemies() {
    actor_t *current_actor = &active_actors[1];

    for (UINT8 i = 1; i < active_actors_count; i++) {
        current_actor->x--;
        current_actor++;
    }
}

void main() {
    BGP_REG = 0x1B;
    OBP0_REG = 0xE4;
    OBP1_REG = 0xE1;
    SPRITES_8x16;
    DISPLAY_ON;
    // SHOW_BKG;
    SHOW_SPRITES;
    hiwater = 0;

    // set_sprite_data(0, (sizeof(detective_data) >> 4), detective_data);
    // set_sprite_data(0x0C, (sizeof(enemy_arrow_data) >> 4), enemy_arrow_data);

    // move_metasprite(detective_metasprites[0], 0, 0, 60, 120);
    // move_metasprite(enemy_arrow_metasprites[0], 0x0C, 2, 40, 40);
    // return;
    load_scene_actors(level1.actors, level1.actor_count);
    while (TRUE) {
        joy = joypad();
        if (joy & J_LEFT) {
            active_actors[ACTOR_DETECTIVE].x--;
        } else if (joy & J_RIGHT) {
            active_actors[ACTOR_DETECTIVE].x++;
        }
        if (joy & J_A) {
            load_scene_actors(level2.actors, level2.actor_count);
        } else if (joy & J_B) {
            load_scene_actors(level1.actors, level1.actor_count);
        }
        move_enemies();
        render_actors();
        wait_vbl_done();
        // load_scene_actors(&actor[0]);  //"&actors[0]" is just "actors"
    }
}