/**
 * Base class for Characters.
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <genesis.h>

#include "player.h"
#include "tiles_and_animations.h"

// Some utils for diagonal speed
#define SQRT_2	FIX32(1.41)
#define DIAG(x) FIX32(x / SQRT_2)

// Attributes
typedef struct
{
//	unsigned short base_hp;
//	unsigned short atk_duration;	// in frames
//	unsigned short atk_cooldown;	// in frames
	fix32 straightSpeed;
	fix32 diagonalSpeed;
} Character;

// Methods
s16 baseDirectionalInput ( Player * player, Character ch, u16 JOYPAD );	// Reads input, returns animation and tile

#endif /* CHARACTER_H */
