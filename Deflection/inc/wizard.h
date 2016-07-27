/**
 * Character implementation: Knighty
 */

#ifndef WIZARD_H
#define WIZARD_H

#include "character.h"

#define WIZARD (Character)	\
{							\
	FIX32(1.2),				\
	DIAG(1.2)				\
}

// Wizard's input handler
s16 wizardDirectionalInput (Player * player, u16 JOYPAD);

#endif /* WIZARD_H */
