/*////////////////////////////////////////////////////////////
	Vector2D Utils 
////////////////////////////////////////////////////////////*/

#include "vector_utils.h"

/**
 * Set coordinates
 */
void V2D_set ( Vector2Df * v, float x, float y )
{
	v->x = x;
	v->y = y;
}
void V2D_setV ( Vector2Df * v, Vector2Df v2 )
{
	V2D_set(v, v2.x, v2.y);
}

/**
 * Product by scalar
 */
Vector2Df V2D_prod ( float alpha, Vector2Df v   )
{
	Vector2Df rv = { alpha * v.x, alpha * v.y };
	return rv;
}

 /** Dot product
  */
float V2D_dot ( Vector2Df v1, Vector2Df v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}

/** Sum vector
 */
Vector2Df V2D_sum ( Vector2Df v1, Vector2Df v2 )
{
	Vector2Df rv = { v1.x + v2.x, v1.y + v2.y };
	return rv;
}

/** Subtraction vector
 */
Vector2Df V2D_diff ( Vector2Df v1, Vector2Df v2 )
{
	Vector2Df rv = { v1.x - v2.x, v1.y - v2.y };
	return rv;
}

/** Squared distance
 */
float V2D_sqDist ( Vector2Df v1, Vector2Df v2 )
{
	Vector2Df dif = V2D_diff(v1, v2);
	return V2D_dot(dif, dif);
}

/** Cross product
 */
float V2D_cross ( Vector2Df v1, Vector2Df v2 )
{
	return v1.x * v2.y - v2.x * v1.y;
}

/** Absolute value less than or equals then <value>
 */
u8 V2D_absLEQ ( Vector2Df v, float value )
{
	if (v.x * v.x + v.y * v.y <= value * value) return TRUE;
	return FALSE;
}
