#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

typedef struct Vector2D
{
	int x;
	int y;
};

typedef struct Rect
{
	Vector2D pos;
	int widht, height;
};

double vector_dot 		( Vector2D v1, Vector2D v2 );
Vector2D vector_diff	( Vector2D v1, Vector2D v2 );
double vector_sqDist	( Vector2D v1, Vector2D v2 );

const Vector2D V2D_NORTH = {  0,  1 };
const Vector2D V2D_SOUTH = {  0, -1 };
const Vector2D  V2D_EAST = {  1,  0 };
const Vector2D  V2D_WEST = { -1,  0 };

#endif
