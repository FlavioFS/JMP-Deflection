#include "controls.h"

// Character implementations
s16 knightDirectionalInput (Vector2D * player, u16 JOYPAD) { return directionalInput(player, SPD_KNIGHTY, JOYPAD); }
s16 wizardDirectionalInput (Vector2D * player, u16 JOYPAD) { return directionalInput(player,  SPD_WIZARD, JOYPAD); }


/** Moves the characters on input in the (x,y) plane according to the velocity of the character
 *  << returns: animation code for the returning state
 */
s16 directionalInput ( Vector2D * player, CharacterSpeeds speeds, u16 JOYPAD )
{
	s16 rv = ANIM_IDLE;

	// Player 1
	u16 value = JOY_readJoypad(JOYPAD);

	// Resetting values (in case no button press occurs)
	// player->x = FIX32(0);
	// player->y = FIX32(0);
	
	fix32 final_speed = 0;

	// Diagonal motion
	if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	{
		final_speed = speeds.diagonalSpeed;
		rv = TRUE;
	}

	// Single axis motion
	else
	{
		final_speed = speeds.straightSpeed;
		rv = TRUE;
	}

	// Horizontal
	if 		(value & BUTTON_LEFT)	player->x -= final_speed;
	else if (value & BUTTON_RIGHT)	player->x += final_speed;

	// Vertical
	if 		(value & BUTTON_UP)		player->y -= final_speed;
	else if (value & BUTTON_DOWN)	player->y += final_speed;

	return rv;
}
