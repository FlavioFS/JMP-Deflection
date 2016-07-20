#include <genesis.h>
#include "physics.h"

/** Moves the characters on input in the (x,y) plane (velocity has a constant absolute value)
 */
void directionalInput ( Vector2D * player, u16 JOY_NUMBER )
{
	// Player 1
	u16 value = JOY_readJoypad(JOY_NUMBER);

	// Resetting values (in case no button press occurs)
	player->x = FIX32(0);
	player->y = FIX32(0);

	// Diagonal motion
	if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	{
		if 		(value & BUTTON_LEFT)	player->x -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_RIGHT)	player->x += DEFAULT_SPEED_DIAG;

		if 		(value & BUTTON_UP)		player->y -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_DOWN)	player->y += DEFAULT_SPEED_DIAG;
	}

	// Single axis motion
	else
	{
		if 		(value & BUTTON_LEFT)	player->x -= DEFAULT_SPEED;
		else if (value & BUTTON_RIGHT)	player->x += DEFAULT_SPEED;

		else if (value & BUTTON_UP)		player->y -= DEFAULT_SPEED;
		else if (value & BUTTON_DOWN)	player->y += DEFAULT_SPEED;
	}

	// // ---------------------------------------------------------------------
	
	// // Player 2
	// value = JOY_readJoypad(JOY_2);

	// // Resetting values (in case no button press occurs)
	// p2->x = FIX32(0);
	// p2->y = FIX32(0);

	// // Diagonal motion
	// if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	// {
	// 	if 		(value & BUTTON_LEFT)	p2->x -= DEFAULT_SPEED_DIAG;
	// 	else if (value & BUTTON_RIGHT)	p2->x += DEFAULT_SPEED_DIAG;

	// 	if 		(value & BUTTON_UP)		p2->y -= DEFAULT_SPEED_DIAG;
	// 	else if (value & BUTTON_DOWN)	p2->y += DEFAULT_SPEED_DIAG;
	// }

	// // Single axis motion
	// else
	// {
	// 	if 		(value & BUTTON_LEFT)	p2->x -= DEFAULT_SPEED;
	// 	else if (value & BUTTON_RIGHT)	p2->x += DEFAULT_SPEED;

	// 	else if (value & BUTTON_UP)		p2->y -= DEFAULT_SPEED;
	// 	else if (value & BUTTON_DOWN)	p2->y += DEFAULT_SPEED;
	// }
}
