#ifndef _BALL_H_
#define _BALL_H_

#include <genesis.h>
#include "vector_utils.h"
#include "gfx.h"
#include "arena.h"
#include "player.h"
#include "character_list.h"
#include "vector_utils.h"

#define BALL_RADIUS 3
#define BALL_CENTER 3
#define CENTER_X 278
#define CENTER_Y 248

extern Vector2Df bSpd;
extern Vector2Df bPos;

void BALL_init (Sprite ball);
void BALL_move (Sprite * ball);
void BALL_reset (Sprite * ball);
void BALL_deflect (u16 joy_direction, u8 player_code);
u8   BALL_dangerZone (u8 player_code);
u8   BALL_isHitting (u8 player_code);

#endif // _BALL_H_
