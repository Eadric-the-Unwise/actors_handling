#include <gb/console.h>
#include <gb/drawing.h>
#include <gb/font.h>
#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdint.h>
#include <stdio.h>

#include "actor.h"

UINT8 joy;
UINT8 hiwater;

void main() {
    BGP_REG = 0x1B;
    OBP0_REG = 0xE4;
    OBP1_REG = 0xE1;
    SPRITES_8x16;
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    load_scene_actors(&actor[0], hiwater);

    // set_sprite_data(0, (sizeof(detective_data) >> 4), detective_data);
    // set_sprite_data(0x0C, (sizeof(enemy_arrow_data) >> 4), enemy_arrow_data);

    // move_metasprite(detective_metasprites[0], 0, 0, 60, 120);
    // move_metasprite(enemy_arrow_metasprites[0], 0x0C, 2, 40, 40);
}