#include "wizard.h"

// Wizard's input handler
s16 wizardDirectionalInput (Player * player, u16 JOYPAD)
{
	return baseDirectionalInput(player, WIZARD, JOYPAD);
}
