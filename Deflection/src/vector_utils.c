#include "vector_utils.h"

// Vector2D Utils
double dot ( Vector2D v1, Vector2D v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2D diff ( Vector2D v1, Vector2D v2 )
{
	Vector2D rv = { v1.x - v2.x, v1.y - v2.y };
	return rv;
}

double sqDist ( Vector2D v1, Vector2D v2 )
{
	Vector2D dif = diff(v1, v2);
	return dot(dif, dif);
}
