#define __BANK_PREFIX(A) __bank_##A
#define BANK(A) (UINT8) & (__BANK_PREFIX(A))
#define __SIZE_PREFIX(A) __size_##A
#define SIZE(A) (UWORD) & (__SIZE_PREFIX(A))
#define OFFSET(A) (void *)&(A)

#include <gb/gb.h>
#include <gb/metasprites.h>

#include "../res/tiles/detective.h"
#include "../res/tiles/enemy_arrow.h"

typedef struct actor_t {
    UINT8 x;
    UINT8 y;
    UBYTE direction;
    UINT8 sprite_index;
    UINT8 tile_index;
    UINT8 tile_count;
    UINT8 *tile_data;
    metasprite_t *actor_metasprite;
    UINT8 metasprite_frame_index;

} actor_t;
extern const struct actor_t actor[2];
UINT8 load_scene_actors(actor_t *actor, UINT8 hiwater);
