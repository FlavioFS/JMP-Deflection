// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P
// @author: Flavio Freitas @mail: <flaviofreitas.h@gmail.com>

#include <genesis.h>
#include "vector_utils.h"
#include "arena.h"
#include "wizard.h"
#include "controls.h"
#include "physics.h"

// Handlers must be in main file
void joyAtkHandler ( u16 joy, u16 joyChanged, u16 state );

//// Global variables
// Players
Vector2D p1 = { FIX32(13), FIX32(14) };
Vector2D p2 = { FIX32(26), FIX32(14) };

// Vector2D v1 = { 0, 0 };
// Vector2D v2 = { 0, 0 };

Vector2D p1_dir = {  1, 0 };
Vector2D p2_dir = { -1, 0 };

// Bullet
Vector2D bulPos = { FIX32(19), FIX32(14) };
Vector2D bulVel = { FIX32( 0), FIX32( 0) };

int main()
{
	// print text on >> tile << h=1,v=0
	// VDP_drawText ( "X", 39,  27 );

	Vector2D speed		= { FIX32(0.2), FIX32(0.2) };
	Vector2D position	= { FIX32(  1), FIX32(  1) };

	// Init joy handler
	JOY_init();
	JOY_setEventHandler( &joyAtkHandler );

	// Under construction
	SPR_init(0);
	draw_arena();
	init_player_wizard(128, 128);


	// game loop
	while (1)
	{
		directionalInput( &p1, &p2 );
		bounceCharacter( &speed, &position );
		debugPlayers(p1, p2, p1_dir, p2_dir);

		control_wizard();
		SPR_update(&wizard_sprite, 1);

		// wait for the screen to refresh
		VDP_waitVSync();
	}
	
	SPR_end();

	return 0;
}

// We need to discuss this later!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/* Handlers... WHY?!
 * GOTTA FIND A MODULAR SOLUTION!!
 */
 void joyAtkHandler ( u16 joy, u16 joyChanged, u16 state )
{
	// Player 1
	if (joy == JOY_1)
	{
		if ( (state & BUTTON_A) || (state & BUTTON_B) || (state & BUTTON_C) )
		// if (state & BUTTON_B )
		{
			if (p1_dir.y != 0)
			{
				VDP_drawText( "XXX", p1.x - 1, p1.y - p1_dir.y );
				VDP_drawText( "XXX", p1.x - 1, p1.y - 2*p1_dir.y );
			}
			else if (p1_dir.x != 0)
			{
				VDP_drawText( "XX", p1.x + 2*p1_dir.x, p1.y - 1 );
				VDP_drawText( "XX", p1.x + 2*p1_dir.x, p1.y     );
				VDP_drawText( "XX", p1.x + 2*p1_dir.x, p1.y + 1 );
			}
		}

		
		VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
		VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x + p1_dir.x, p1.y - p1_dir.y );
	}
}

void joyMoveHandler ( u16 joy, u16 joyChanged, u16 state ) {
	// Player 1
	if (joy == JOY_1)
	{
		if (state & BUTTON_START)		// Press
		{
			/* code */
		}
		else if (joyChanged & BUTTON_START)	// Release
		{

		}


		if (state & BUTTON_UP)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.y >= 1) p1.y -= 1;
		}
		else if (state & BUTTON_DOWN)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.y < 27) p1.y += 1;
		}


		if (state & BUTTON_LEFT)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.x >= 1) p1.x -= 1;
		}
		else if (state & BUTTON_RIGHT)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.x < 39) p1.x += 1;
		}

		else if (state & BUTTON_START)	// Press start
		{

		}
		else if (state & BUTTON_START)	// Release start
		{

		}

		// int dbg_pos[] = { 10, 20 };
		// VDP_drawText( state, dbg_pos[0], dbg_pos[1] );
	}

	// Player 2
	// else if (joy == JOY_1B)
	// {
		/* code */
	// }
}
