/**
 * This file defines the properties of PLAYERS (not to be confused with CHARACTERS). E.g:
 * 	> Position
 * 	> HP (current)
 */

#ifndef PLAYER_DEFINITIONS_H
#define PLAYER_DEFINITIONS_H

#include "vector_utils.h"

//// Global variables
// Players
Vector2D p1 = { FIX32(128), FIX32(128) };
Vector2D p2 = { FIX32(150), FIX32(128) };

// Vector2D v1 = { 0, 0 };
// Vector2D v2 = { 0, 0 };

Vector2D p1_dir = {  1, 0 };
Vector2D p2_dir = { -1, 0 };

#endif /* PLAYER_DEFINITIONS_H */
