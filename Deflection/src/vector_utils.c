/*////////////////////////////////////////////////////////////
	Vector2D Utils 
////////////////////////////////////////////////////////////*/

#include "vector_utils.h"

 /** Dot product
  */
s32 dot ( Vector2D v1, Vector2D v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}

/** Subtraction vector
 */
Vector2D diff ( Vector2D v1, Vector2D v2 )
{
	Vector2D rv = { v1.x - v2.x, v1.y - v2.y };
	return rv;
}

/** Squared distance
 */
s32 sqDist ( Vector2D v1, Vector2D v2 )
{
	Vector2D dif = diff(v1, v2);
	return dot(dif, dif);
}

/** Cross product
 */
s32 cross ( Vector2D v1, Vector2D v2 )
{
	return v1.x * v2.y - v2.x * v1.y;
}

/** Absolute value less than or equals then <value>
 */
u8 absLEQ ( Vector2D v, fix32 value )
{
	if (v.x * v.x + v.y * v.y <= FIX32(value * value)) return 1;
	return 0;
}