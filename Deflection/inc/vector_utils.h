#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#include <genesis.h>

#define SQRT2 1.414

typedef struct Vector2D
{
	fix32 x;
	fix32 y;
} Vector2D;

typedef struct
{
	float x;
	float y;
} Vector2Df;

typedef struct
{
	u16 x;
	u16 y;
} VectorU16;


// Vector2D utils
void      V2D_set    ( Vector2Df * v, float x, float y );
void      V2D_setV   ( Vector2Df * v, Vector2Df v2 );
Vector2Df V2D_prod	 (   float alpha, Vector2Df  v );
float     V2D_dot 	 ( Vector2Df  v1, Vector2Df v2 );
Vector2Df V2D_sum 	 ( Vector2Df  v1, Vector2Df v2 );
Vector2Df V2D_diff	 ( Vector2Df  v1, Vector2Df v2 );
float     V2D_sqDist ( Vector2Df  v1, Vector2Df v2 );
u8        V2D_absLEQ ( Vector2Df   v, float value );

// TODO remove this?
const static Vector2D V2D_NORTH = {  0,  1 };
const static Vector2D V2D_SOUTH = {  0, -1 };
const static Vector2D  V2D_EAST = {  1,  0 };
const static Vector2D  V2D_WEST = { -1,  0 };

#endif
