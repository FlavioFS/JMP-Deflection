#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector_utils.h"

#define DEFAULT_SPEED_DIAG	1
#define DEFAULT_SPEED 		1.41
// #define DEFAULT_SPEED 		FIX32(DEFAULT_SPEED_DIAG * 1.41)

// Bullet
Vector2D bulPos = { FIX32(19), FIX32(14) };
Vector2D bulVel = { FIX32( 0), FIX32( 0) };

void bounceCharacter ( Vector2D * speed, Vector2D * position );

#endif
