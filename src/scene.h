#ifndef __SCENE_H__
//prevents the includes from being called twice
#define __SCENE_H__

#include <gb/gb.h>
#include <gb/metasprites.h>

#define MAX_ACTIVE_ACTORS 4
#define ACTOR_DETECTIVE 0

typedef struct actor_t {
    UINT8 x;
    UINT8 y;
    UBYTE direction;
    UINT8 tile_count;
    UINT8 tile_index;
    const UINT8 *tile_data;
    const metasprite_t **actor_metasprites;
    UINT8 metasprite_frame_index;

} actor_t;

typedef struct level_t {
    const actor_t *actors;
    UINT8 actor_count;
} level_t;

extern actor_t active_actors[MAX_ACTIVE_ACTORS];

extern UINT8 active_actors_count;

void load_scene_actors(const actor_t *actor, uint8_t actors_count);
void render_actors();

#endif