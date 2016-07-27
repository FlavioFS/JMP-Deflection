/**
 * This file defines the properties of PLAYERS (not to be confused with CHARACTERS). E.g:
 * 	> Position
 * 	> Facing direction (eye)
 * 	> HP (current)
 */

#ifndef PLAYERS_H
#define PLAYERS_H

#include "vector_utils.h"

typedef struct {
	Vector2D pos;
	Vector2D eye;
	unsigned short hp;
} Player;


#endif /* PLAYERS_H */
