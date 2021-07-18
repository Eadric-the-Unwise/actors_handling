#include <gb/console.h>
#include <gb/drawing.h>
#include <gb/font.h>
#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdint.h>
#include <stdio.h>
/******************************/
// Include your scene and map header files
/******************************/
#include "level1.h"
#include "level2.h"
#include "scene.h"

UINT8 joy;
UINT8 hiwater;
/******************************/
// Load enemies sequencially up to MAX_ACTIVE_ACTORS
/******************************/
void move_enemies() {
    actor_t *current_actor = &active_actors[1];  //The Detective is currently active_actors[0], so active_actors[1] and above are enemies

    for (UINT8 i = 1; i < active_actors_count; i++) {
        current_actor->x--;
        current_actor++;
    }
}
/******************************/
// Define your OBJ and BGP palettes, show SPRITES, turn on DISPLAY
/******************************/
void main() {
    BGP_REG = 0x00;
    OBP0_REG = 0xE4;
    OBP1_REG = 0xE1;
    SPRITES_8x16;
    DISPLAY_ON;
    // SHOW_BKG;
    SHOW_SPRITES;
    hiwater = 0;

    load_scene_actors(level1.actors, level1.actor_count);  //Loads level1.c actors
    while (TRUE) {
        joy = joypad();
        /******************************/
        // Basic AI movement for Enemies ONLY
        /******************************/
        if (joy & J_LEFT) {
            active_actors[ACTOR_DETECTIVE].x--;
            active_actors[ACTOR_DETECTIVE].direction = FACE_LEFT;
            animate_detective();
        } else if (joy & J_RIGHT) {
            active_actors[ACTOR_DETECTIVE].x++;
            active_actors[ACTOR_DETECTIVE].direction = FACE_RIGHT;
            animate_detective();
        } else if (joy & J_DOWN) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 1;
        }
        /******************************/
        // Load stages on button press
        /******************************/
        if (joy & J_A) {
            load_scene_actors(level2.actors, level2.actor_count);
        } else if (joy & J_B) {
            load_scene_actors(level1.actors, level1.actor_count);
        }

        /******************************/
        // NOT PRESSING DIRECTION
        /******************************/
        if (!(joy & (J_LEFT | J_RIGHT | J_UP | J_DOWN))) {
            if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index != 0) {
                active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 0;
            }
        }

        move_enemies();
        render_actors();  //see scene.c
        wait_vbl_done();
    }
}

/******************************/
// Disregard code below this line. For reference only
/******************************/
// set_sprite_data(0, (sizeof(detective_data) >> 4), detective_data);
// set_sprite_data(0x0C, (sizeof(enemy_arrow_data) >> 4), enemy_arrow_data);

// move_metasprite(detective_metasprites[0], 0, 0, 60, 120);
// move_metasprite(enemy_arrow_metasprites[0], 0x0C, 2, 40, 40);

// load_scene_actors(&actor[0]);  //"&actors[0]" is just "actors"