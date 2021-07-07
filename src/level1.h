#define __BANK_PREFIX(A) __bank_##A
#define BANK(A) (UINT8) & (__BANK_PREFIX(A))
#define __SIZE_PREFIX(A) __size_##A
#define SIZE(A) (UWORD) & (__SIZE_PREFIX(A))
#define OFFSET(A) (void *)&(A)

#define MAX_ACTIVE_ACTORS 2

#include <gb/gb.h>
#include <gb/metasprites.h>

#include "../res/tiles/detective.h"
#include "../res/tiles/enemy_arrow.h"

typedef struct actor_t {
    UINT8 x;
    UINT8 y;
    UBYTE direction;
    UINT8 tile_count;
    const UINT8 *tile_data;
    const metasprite_t **actor_metasprites;
    UINT8 metasprite_frame_index;

} actor_t;
extern const struct actor_t level1[2];
extern const uint8_t level1_count;
// extern struct actor_t actor[2];
void load_scene_actors(actor_t *actor, uint8_t active_actors_count);
void render_actors();
