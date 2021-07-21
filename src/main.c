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
UINT8 detective_platform_frame_start;
UINT8 detective_platform_frame_end;

/******************************/
// Load enemies sequencially up to MAX_ACTIVE_ACTORS
/******************************/
void move_arrows() {
    actor_t *current_actor = &active_actors[1];  //The Detective is currently active_actors[0], so active_actors[1] and above are enemies

    for (UINT8 i = 1; i < active_actors_count; i++) {
        if (current_actor->direction == FACE_LEFT) {
            current_actor->x--;
        } else if (current_actor->direction == FACE_RIGHT) {
            current_actor->x++;
        }
        if (current_actor->x == 16) {
            current_actor->direction = FACE_RIGHT;
        } else if (current_actor->x == 160) {
            current_actor->direction = FACE_LEFT;
        }
        current_actor++;
    }
}
// if (current_actor->direction == FACE_RIGHT) {
//     for (UINT8 i = 1; i < active_actors_count; i++) {
//         current_actor->x++;
//         current_actor++;
//     }
// }
// }
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
            animate_detective();
        } else if (joy & J_A) {
            animate_detective();
        }
        /******************************/
        // Load stages on button press
        /******************************/
        if (joy & J_START) {
            load_scene_actors(level2.actors, level2.actor_count);
        } else if (joy & J_SELECT) {
            load_scene_actors(level1.actors, level1.actor_count);
        }

        /******************************/
        // NOT PRESSING DIRECTION
        /******************************/
        if (!(joy & (J_LEFT | J_RIGHT | J_UP | J_DOWN | J_A))) {
            if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index != 0) {
                active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 0;
            }
        }

        move_arrows();
        render_actors();  //see scene.c
        wait_vbl_done();
    }
}

void animate_detective() {
    if ((joy & (J_LEFT | J_RIGHT) && !(joy & (J_DOWN | J_A)))) {
        detective_platform_frame_start = 5;
        detective_platform_frame_end = 10;
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index < detective_platform_frame_start || active_actors[ACTOR_DETECTIVE].metasprite_frame_index > detective_platform_frame_end) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 5;
        }
    } else if ((joy & (J_LEFT | J_RIGHT) && (joy & J_DOWN) && !(joy & J_A))) {
        detective_platform_frame_start = 1;
        detective_platform_frame_end = 4;
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index > detective_platform_frame_end) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 1;
        }
    }
    if (joy & J_A) {
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index < 11) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 11;
            detective_platform_frame_start = 11;
            detective_platform_frame_end = 16;
        }
    } else if ((joy & (J_LEFT | J_RIGHT) && (joy & J_A))) {
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index < 11) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 11;
            detective_platform_frame_start = 11;
            detective_platform_frame_end = 16;
        }
    } else if ((joy & (J_LEFT | J_RIGHT) && (joy & J_DOWN) && (joy & J_A))) {
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index < 11) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 11;
            detective_platform_frame_start = 11;
            detective_platform_frame_end = 16;
        }
    } else if ((joy & J_DOWN) && !(joy & (J_LEFT | J_RIGHT | J_A))) {
        active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 1;
        detective_platform_frame_start = 1;
        detective_platform_frame_end = 1;
    }
    // The amount of delay between frame animation. Decrement animation delays
    if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index == 0) {
        active_actors[ACTOR_DETECTIVE].metasprite_frame_index = detective_platform_frame_start;
    }
    if (active_actors[ACTOR_DETECTIVE].frame_delay > 0) {
        active_actors[ACTOR_DETECTIVE].frame_delay--;

        if (active_actors[ACTOR_DETECTIVE].frame_delay == 0) {
            // Animate the body when detective is moving.
            if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index == 5 || active_actors[ACTOR_DETECTIVE].metasprite_frame_index == 8) {
                active_actors[ACTOR_DETECTIVE].frame_delay = 10;
            } else {
                active_actors[ACTOR_DETECTIVE].frame_delay = 6;
            }
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index++;

            // if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index > 10) {
            //     active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 5;
            // }
            if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index > detective_platform_frame_end) {
                active_actors[ACTOR_DETECTIVE].metasprite_frame_index = detective_platform_frame_start;
            }
        }
        // detective->body_frame_delay = detective->body_frame_index % 2 ? FRAME_DELAY * 2 : FRAME_DELAY;
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