/**
 * This file defines properties of each CHARACHTER in the game. E.g.:
 * 	> Movement Speed
 * 	> Base HP (lives)
 * 	> Attack duration
 * 	> Dash invincibility time
 * 	> Attack cooldown
 */

#ifndef CHARACTER_DEFINITIONS_H
#define CHARACTER_DEFINITIONS_H

#include "player_definitions.h"

#define SQRT_2	FIX32(1.41)
#define DIAG(x) FIX32(x / SQRT_2)

typedef struct CharacterSpeeds {
	fix32 straightSpeed;
	fix32 diagonalSpeed;
} CharacterSpeeds;

// Knighty
#define SPD_KNIGHTY (CharacterSpeeds) { FIX32(1.2), DIAG(1.2) }
/*
	Base HP (chances)
	Attack duration
	Dash invincibility duration
	Attack cooldown
*/


// Wizard
#define SPD_WIZARD  (CharacterSpeeds) { FIX32(1.2), DIAG(1.2) }
/*
	Base HP (chances)
	Attack duration
	Dash invencibility duration
	Attack cooldown
*/



// Golem?
// #define SPD_GOLEM   (CharacterSpeeds) { FIX32(1.0), DIAG(1;0) }

// Satyr?
// #define SPD_SATYR   (CharacterSpeeds) { FIX32(1.8), DIAG(1.8) }

// Elf?
// #define SPD_ELF     (CharacterSpeeds) { FIX32(1.6), DIAG(1.6) }

// Samurai?
// #define SPD_SAMURAI (CharacterSpeeds) { FIX32(2.0), DIAG(2.0) }


#endif /* CHARACTER_DEFINITIONS_H */
