#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <genesis.h>

typedef struct
{
	fix32 x;
	fix32 y;
} Vector2D;

void bounceCharacter	( Vector2D * speed, Vector2D * position	);
void renderPlayers		( Vector2D p1_pos, Vector2D p2_pos		);
void joyAtkHandler		( u16 joy, u16 joyChanged, u16 state	);

// Vector2D utils
fix32 dot 		( Vector2D v1, Vector2D v2 );
Vector2D diff	( Vector2D v1, Vector2D v2 );
fix32 sqDist	( Vector2D v1, Vector2D v2 );
u8 absLEQ		( Vector2D  v, fix32 value );

const static Vector2D V2D_NORTH = {  0,  1 };
const static Vector2D V2D_SOUTH = {  0, -1 };
const static Vector2D  V2D_EAST = {  1,  0 };
const static Vector2D  V2D_WEST = { -1,  0 };

#endif
