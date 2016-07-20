#include <genesis.h>
#include "physics.h"

/** Moves the characters on input in the (x,y) plane (velocity has a constant absolute value)
 */
void directionalInput ( Vector2D * p1, Vector2D * p2 )
{
	// Player 1
	u16 value = JOY_readJoypad(JOY_1);

	// Resetting values (in case no button press occurs)
	p1->x = FIX32(0);
	p1->y = FIX32(0);

	// Diagonal motion
	if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	{
		if 		(value & BUTTON_LEFT)	p1->x -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_RIGHT)	p1->x += DEFAULT_SPEED_DIAG;

		if 		(value & BUTTON_UP)		p1->y -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_DOWN)	p1->y += DEFAULT_SPEED_DIAG;
	}

	// Single axis motion
	else
	{
		if 		(value & BUTTON_LEFT)	p1->x -= DEFAULT_SPEED;
		else if (value & BUTTON_RIGHT)	p1->x += DEFAULT_SPEED;

		else if (value & BUTTON_UP)		p1->y -= DEFAULT_SPEED;
		else if (value & BUTTON_DOWN)	p1->y += DEFAULT_SPEED;
	}

	// ---------------------------------------------------------------------
	
	// Player 2
	value = JOY_readJoypad(JOY_2);

	// Resetting values (in case no button press occurs)
	p2->x = FIX32(0);
	p2->y = FIX32(0);

	// Diagonal motion
	if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	{
		if 		(value & BUTTON_LEFT)	p2->x -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_RIGHT)	p2->x += DEFAULT_SPEED_DIAG;

		if 		(value & BUTTON_UP)		p2->y -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_DOWN)	p2->y += DEFAULT_SPEED_DIAG;
	}

	// Single axis motion
	else
	{
		if 		(value & BUTTON_LEFT)	p2->x -= DEFAULT_SPEED;
		else if (value & BUTTON_RIGHT)	p2->x += DEFAULT_SPEED;

		else if (value & BUTTON_UP)		p2->y -= DEFAULT_SPEED;
		else if (value & BUTTON_DOWN)	p2->y += DEFAULT_SPEED;
	}
}
