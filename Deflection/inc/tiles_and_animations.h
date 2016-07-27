#ifndef SPRITE_DEFINITIONS_H
#define SPRITE_DEFINITIONS_H

#include <genesis.h>

// ANIMATIONS
#define ANIM_WALK 0
#define ANIM_IDLE 1

// TODO 4 walking cycles
//#define ANIM_IDLE       0
//#define ANIM_WALK_UP    1
//#define ANIM_WALK_DOWN  2
//#define ANIM_WALK_RIGHT 3
//#define ANIM_WALK_LEFT  4
//#define ANIM_WALK_ATK   5

#define TILE_NO_FLIP TILE_ATTR(PAL2, TRUE, FALSE, FALSE)
#define TILE_FLIP_V  TILE_ATTR(PAL2, TRUE,  TRUE, FALSE)
#define TILE_FLIP_H  TILE_ATTR(PAL2, TRUE, FALSE,  TRUE)
#define TILE_FLIP_VH TILE_ATTR(PAL2, TRUE,  TRUE,  TRUE)

//typedef struct
//{
//	s16 animation;
//	u16 tile;
//} ANIMATION_PACK;

#endif /* SPRITE_DEFINITIONS_H */
