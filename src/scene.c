#include "scene.h"

#include <gb/gb.h>

// array of avaliable actors
actor_t active_actors[MAX_ACTIVE_ACTORS];  // active_actors[] is your working structures in WRAM
UINT8 active_actors_count;                 // amount of actors that are currently active

void load_scene_actors(const actor_t *actor, uint8_t actors_count) {
    actor_t *current_actor = active_actors;

    UINT8 hiwater = 0;
    for (UINT8 i = actors_count; i != 0; i--) {  //counter direction does not matter, because pointer is moved. only number of iterations matter.
        current_actor->tile_index = hiwater;
        set_sprite_data(hiwater, actor->tile_count, actor->tile_data);
        current_actor->x = actor->x;
        current_actor->y = actor->y;
        current_actor->direction = actor->direction;
        current_actor->frame_delay = actor->frame_delay;
        current_actor->actor_metasprites = actor->actor_metasprites;
        current_actor->metasprite_frame_index = actor->metasprite_frame_index;
        hiwater += actor->tile_count;
        current_actor++;
        actor++;
    }
    active_actors_count = actors_count;  //copies from ROM to RAM
}
//calls move_metasprite();, increases hiwater, and clears unnecessary Sprites in OAM after the hiwater's value
void render_actors() {
    actor_t *current_actor = active_actors;
    // draw each metasprite
    UINT8 hiwater = 0;
    for (UINT8 i = active_actors_count; i != 0; i--) {
        if (current_actor->direction == FACE_LEFT) {
            hiwater += move_metasprite(
                current_actor->actor_metasprites[current_actor->metasprite_frame_index],
                current_actor->tile_index,
                hiwater,
                current_actor->x, current_actor->y);
            current_actor++;
        } else if (current_actor->direction == FACE_RIGHT) {
            hiwater += move_metasprite_vflip(
                current_actor->actor_metasprites[current_actor->metasprite_frame_index],
                current_actor->tile_index,
                hiwater,
                current_actor->x, current_actor->y);
            current_actor++;
        }
    }
    // hide rest of the hardware sprites
    for (UINT8 i = hiwater; i < 40u; i++) shadow_OAM[i].y = 0;
}
