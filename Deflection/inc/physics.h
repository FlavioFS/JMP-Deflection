#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector_utils.h"

#define DEFAULT_SPEED_DIAG	1
#define DEFAULT_SPEED 		1.41
// #define DEFAULT_SPEED 		FIX32(DEFAULT_SPEED_DIAG * 1.41)

void bounceCharacter ( Vector2D * speed, Vector2D * position );
void debugPlayers (Vector2D p1, Vector2D p2, Vector2D p1_dir, Vector2D p2_dir);

#endif
