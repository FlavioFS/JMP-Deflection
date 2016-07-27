/**
 * Character implementation: Knighty
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

#define KNIGHT (Character) \
{							\
	FIX32(1.2),				\
	DIAG(1.2)				\
}

// Knighty's input handler
s16 knightDirectionalInput (Player * player, u16 JOYPAD);

#endif /* KNIGHTY_ */
