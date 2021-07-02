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
    UINT8 tile_data;
    UINT8 actor_metasprite;

} actor_t;
UINT8 load_scene_actors(actor_t *actor);
void set_sprite_data(uint8_t first_tile, uint8_t nb_tiles, const uint8_t *data);
uint8_t move_metasprite(const metasprite_t *metasprite, uint8_t base_tile, uint8_t base_sprite, uint8_t x, uint8_t y);
extern struct actor_t actor[2];
