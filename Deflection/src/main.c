// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P
// @author: Flavio Freitas @mail: <flaviofreitas.h@gmail.com>

#include <genesis.h>
#include "vector_utils.h"
#include "arena.h"
#include "controls.h"
#include "character.h"


int main()
{
	VDP_setScreenWidth320();
	SPR_init();

	// playable characters
	Character * player_one = init_wizard_character();
	
	set_character_position (player_one, P1_START_X, P2_START_Y);
	
	VDP_setPalette(PAL1, spr_wizard_def.palette->data);

	set_character_palette(player_one, PAL1);

	// Init joy handler
	JOY_init();
	

	// Under construction
	draw_arena();

	
	// game loop
	while (1)
	{
		control_character (player_one, JOY_1);
		
		update_character_onscreen(player_one);
		
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
