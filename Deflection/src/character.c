#include "character.h"

/** Moves the characters on input in the (x,y) plane according to the velocity of the character
 *  << returns: animation code for the returning state
 */
s16 baseDirectionalInput ( Player * player, Character character, u16 JOYPAD )
{
	u16 value = JOY_readJoypad(JOYPAD);

	// Default: idle
	s16 rv = ANIM_IDLE;
	fix32 final_speed = 0;

	// Diagonal motion
	if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	{
		final_speed = character.diagonalSpeed;
		rv = ANIM_WALK;
	}

	// Single axis motion
	else if (value & (BUTTON_LEFT | BUTTON_RIGHT | BUTTON_UP | BUTTON_DOWN))
	{
		final_speed = character.straightSpeed;
		rv = ANIM_WALK;
	}

	// Horizontal
	if 		(value & BUTTON_LEFT)	player->pos.x -= final_speed;
	else if (value & BUTTON_RIGHT)	player->pos.x += final_speed;

	// Vertical
	if 		(value & BUTTON_UP)		player->pos.y -= final_speed;
	else if (value & BUTTON_DOWN)	player->pos.y += final_speed;

	return rv;
}


