#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

typedef struct Vector2D
{
	double x;
	double y;
} Vector2D;

typedef struct Rect
{
	Vector2D downleft;
	Vector2D upright;
} Rect;

// Vector2D Utils
double dot ( Vector2D v1, Vector2D v2 );

Vector2D diff ( Vector2D v1, Vector2D v2 );

double sqDist ( Vector2D v1, Vector2D v2 );

#endif
