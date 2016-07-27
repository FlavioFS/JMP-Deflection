/*////////////////////////////////////////////////////////////
	Vector2D Utils 
////////////////////////////////////////////////////////////*/

#include "vector_utils.h"

 /** Dot product
  */
s32 dot ( Player v1, Player v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}

/** Subtraction vector
 */
Player diff ( Player v1, Player v2 )
{
	Player rv = { v1.x - v2.x, v1.y - v2.y };
	return rv;
}

/** Squared distance
 */
s32 sqDist ( Player v1, Player v2 )
{
	Player dif = diff(v1, v2);
	return dot(dif, dif);
}

/** Cross product
 */
s32 cross ( Player v1, Player v2 )
{
	return v1.x * v2.y - v2.x * v1.y;
}

/** Absolute value less than or equals then <value>
 */
u8 absLEQ ( Player v, fix32 value )
{
	if (v.x * v.x + v.y * v.y <= FIX32(value * value)) return 1;
	return 0;
}