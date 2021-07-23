#ifndef __SCENE_H__
//prevents the includes from being called twice
#define __SCENE_H__

#include <gb/gb.h>
#include <gb/metasprites.h>

#define MAX_ACTIVE_ACTORS 8
#define ACTOR_DETECTIVE 0
#define FACE_LEFT 1
#define FACE_RIGHT 0
#define JUMP_TIMER 15

typedef struct actor_t {
    UINT8 x;
    UINT16 y;
    INT16 SpdX;
    INT16 SpdY;
    UBYTE direction;
    UINT8 tile_count;
    UINT8 tile_index;
    UINT8 frame_delay;
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
void animate_detective();

#endif