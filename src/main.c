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
UINT8 detective_platform_frame_start, detective_platform_frame_end;
UBYTE jumping, falling;
UINT8 fall_timer = 0;
INT8 gravity = -1;
UINT8 currentspeedY;
UINT8 floorYposition;

/******************************/
// 16BIT COORDINATES
/******************************/
UINT16 PosX, PosY;
INT16 SpdX, SpdY;
UINT8 PosF, Jump, Fall;

/******************************/
// Define your OBJ and BGP palettes, show SPRITES, turn on DISPLAY
/******************************/
void main() {
    BGP_REG = 0xE4;
    OBP0_REG = 0xE4;
    OBP1_REG = 0xE1;
    SPRITES_8x16;
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    hiwater = 0;
    floorYposition = 100;
    jumping = falling = 0;
    Jump = Fall = 0;

    Jump = SpdX = SpdY = 0;
    load_scene_actors(level1.actors, level1.actor_count);  //Loads level1.c actors

    while (TRUE) {
        PosF = 0;
        joy = joypad();

        /******************************/
        // JOYPAD INPUTS
        /******************************/
        // if (joy & J_UP) {
        //     SpdY -= 2;
        //     if (SpdY < -8) SpdY = -8;
        //     PosF |= ACC_Y;
        // }
        if (joy & J_LEFT) {
            active_actors[ACTOR_DETECTIVE].x--;
            active_actors[ACTOR_DETECTIVE].direction = FACE_LEFT;
            if (!(jumping)) {
                animate_detective();
            } else {
            }
        } else if (joy & J_RIGHT) {
            active_actors[ACTOR_DETECTIVE].x++;
            active_actors[ACTOR_DETECTIVE].direction = FACE_RIGHT;
            if (!(jumping)) {
                animate_detective();
            } else {
            }
        } else if (joy & J_DOWN) {
            animate_detective();
        }
        if (joy & J_A) {
            Jump = 10;
        }
        //DEBUG DETECTIVE Y COORDS
        if (joy & J_B) {
            printf("Y=%u\n", active_actors[ACTOR_DETECTIVE].y >> 4);
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
        //JUMPING
        if (Jump) {
            jumping = 1;
            active_actors[ACTOR_DETECTIVE].SpdY = -40;
            Jump--;
            if (Jump == 8) {
                Fall = 1;
            }
            if (Jump == 0) {
                jumping = 0;
            }
        }
        //FALLING
        if (Fall) {
            active_actors[ACTOR_DETECTIVE].SpdY += 4;
            if (active_actors[ACTOR_DETECTIVE].SpdY > 48) {
                active_actors[ACTOR_DETECTIVE].SpdY = 48;
            }
            if (active_actors[ACTOR_DETECTIVE].y >> 4 > floorYposition) {
                active_actors[ACTOR_DETECTIVE].SpdY = 0;
                Fall = 0;
            }
        }
        //GRAVITY (FRICTION)
        if (!(PosF & ACC_Y)) {
            if (active_actors[ACTOR_DETECTIVE].SpdY >= 0) {
                if (active_actors[ACTOR_DETECTIVE].SpdY) {
                    active_actors[ACTOR_DETECTIVE].SpdY--;
                }
            } else {
                active_actors[ACTOR_DETECTIVE].SpdY++;
            }
        }
        /******************************/
        // SEE SCENE.C FOR THESE FUNCTIONS
        /******************************/
        move_arrows();
        update_actors_xy();
        render_actors();

        // check_detective_y();
        // && !(Fall)

        wait_vbl_done();
    }
}

/******************************/
// DETECTIVE SPRITE ANIMATIONS
/******************************/
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
    if (jumping == 1) {
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index < 11) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 11;
            detective_platform_frame_start = 11;
            detective_platform_frame_end = 14;
        }
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index == 14) {
            detective_platform_frame_start = 14;
        }

    } else if ((joy & (J_LEFT | J_RIGHT) && jumping == 1)) {
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index < 11) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 11;
            detective_platform_frame_start = 11;
            detective_platform_frame_end = 14;
        }
    } else if ((joy & (J_LEFT | J_RIGHT) && (joy & J_DOWN) && jumping == 1)) {
        if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index < 11) {
            active_actors[ACTOR_DETECTIVE].metasprite_frame_index = 11;
            detective_platform_frame_start = 11;
            detective_platform_frame_end = 14;
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
    /******************************/
    // FRAME DELAYS
    /******************************/
    if (active_actors[ACTOR_DETECTIVE].frame_delay > 0) {
        active_actors[ACTOR_DETECTIVE].frame_delay--;

        if (active_actors[ACTOR_DETECTIVE].frame_delay == 0) {
            // Animate the body when detective is moving.
            if (active_actors[ACTOR_DETECTIVE].metasprite_frame_index == 5 || active_actors[ACTOR_DETECTIVE].metasprite_frame_index == 8) {
                active_actors[ACTOR_DETECTIVE].frame_delay = 10;
            }
            // else if (jumping == 1) {
            //     active_actors[ACTOR_DETECTIVE].frame_delay = 15;
            // }
            else {
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

// INT8 wouldhitsurface(UINT8 projectedYPosition) {
//     if (projectedYPosition >= floorYposition) {
//         return floorYposition;
//     }
//     return -1;
// }

// void jump() {
//     INT8 possiblesurfaceY;
//     actor_t *detective = &active_actors[ACTOR_DETECTIVE];

//     if (jumping == 0) {
//         jumping = 1;
//         currentspeedY = 2;
//     }
//     //gravity = -1
//     if (floorYposition - detective->y > 45) {
//         currentspeedY = currentspeedY + gravity;
//     }
//     detective->y = detective->y - currentspeedY;

//     possiblesurfaceY = wouldhitsurface(detective->y);

//     if (possiblesurfaceY > -1) {
//         jumping = 0;
//     }
// }

// active_actors[ACTOR_DETECTIVE].SpdY = -16;
// if (falling) {
//     fall_timer++;
//     if (fall_timer >= FALL_DELAY) {
//         Fall = 1;
//         fall_timer = 0;
//         falling = 0;
//     }
// }