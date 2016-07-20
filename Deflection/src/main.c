// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P
// @author: Flavio Freitas @mail: <flaviofreitas.h@gmail.com>

#include <genesis.h>
#include "vector_utils.h"
#include "arena.h"
#include "wizard.h"
#include "knighty.h"
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

Sprite spr_players [2];

int main()
{
	VDP_setScreenWidth320();

	Vector2D speed		= { FIX32(0.2), FIX32(0.2) };
	Vector2D position	= { FIX32(  1), FIX32(  1) };

	// Init joy handler
	JOY_init();
	JOY_setEventHandler( &joyAtkHandler );

	// Under construction
	// SPR_init( (4 * 8) + (3 * 3 * 9) );	// Knighty is 2x2 tiles and 8 frames, Wizard is 3x3 and 9 frames
	SPR_init( (4 * 8) + (3 * 3 * 9) );
	draw_arena();
	init_player_wizard(140, 128);
	init_player_knighty(128, 128);

	spr_players[1] = WIZARD_SPR;
	spr_players[0] = KNIGHTY_SPR;

	// game loop
	while (1)
	{
		// directionalInput( &p1, &p2 );
		wizard_control(&p1, JOY_1);
		knighty_control(&p2, JOY_2);

		bounceCharacter( &speed, &position );
		debugPlayers(p1, p2, p1_dir, p2_dir);

		// control_wizard(&p1);
		SPR_update(spr_players, 1);

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
	int xc = fix32ToInt(p1.x);
	int yc = fix32ToInt(p1.y);

	// Player 1
	if (joy == JOY_1)
	{
		if ( (state & BUTTON_A) || (state & BUTTON_B) || (state & BUTTON_C) )
		// if (state & BUTTON_B )
		{
			if (p1_dir.y != 0)
			{
				VDP_drawText( "XXX", xc - 1, fix32ToInt(p1.y - p1_dir.y) );
				VDP_drawText( "XXX", xc - 1, fix32ToInt(p1.y - 2*p1_dir.y) );
			}
			else if (p1_dir.x != 0)
			{
				VDP_drawText( "XX", fix32ToInt(p1.x + 2*p1_dir.x), yc - 1 );
				VDP_drawText( "XX", fix32ToInt(p1.x + 2*p1_dir.x), yc     );
				VDP_drawText( "XX", fix32ToInt(p1.x + 2*p1_dir.x), yc + 1 );
			}
		}
		
		VDP_setTileMapXY( VDP_PLAN_A, 0, xc, yc );
		VDP_setTileMapXY( VDP_PLAN_A, 0, fix32ToInt(p1.x + p1_dir.x), fix32ToInt(p1.y - p1_dir.y) );
	}
}

// Old
/*
void joyMoveHandler ( u16 joy, u16 joyChanged, u16 state ) {
	// Player 1
	if (joy == JOY_1)
	{
		if (state & BUTTON_START)		// Press
		{

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
	// }
}
*/
