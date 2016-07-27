// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P
// @author: Flavio Freitas @mail: <flaviofreitas.h@gmail.com>

#include <genesis.h>

#include "../inc/player.h"
//#include "player_definitions.h"
#include "vector_utils.h"
#include "tiles_and_animations.h"
#include "arena.h"
#include "physics.h"
#include "gfx.h"

// Available Characters
#include "knight.h"
#include "wizard.h"

Player players[2];
Sprite sprites [2];

// Prototypes
void joyAtkHandler ( u16 joy, u16 joyChanged, u16 state );	// Handlers must be in main file
void debugPlayers ();
void init_palettes_and_sprites ();

int main()
{
	VDP_setScreenWidth320();

	// Vector2D speed		= { FIX32(0.2), FIX32(0.2) };
	Player speed		= { FIX32(  1), FIX32(  1) };
	Player position	= { FIX32(  1), FIX32(  1) };

	// Init joy handler
	JOY_init();
	JOY_setEventHandler( &joyAtkHandler );

	// Under construction
	// SPR_init( (4 * 8) + (3 * 3 * 9) );	// Knighty is 2x2 tiles and 8 frames, Wizard is 3x3 and 9 frames
	SPR_init(0);
	draw_arena();

	// Test
//	 init_player_knighty(&sprites[0], fix32ToInt(p1.x), fix32ToInt(p1.x));
//	 init_player_wizard(&sprites[1], fix32ToInt(p2.x), fix32ToInt(p2.y));
	
	// playerSpriteList[0] = KNIGHTY_SPR;
	// playerSpriteList[1] = WIZARD_SPR;

//	init_palettes_and_sprites();

	// game loop
	while (1)
	{
//		 directionalInput( &p1, &p2 );
//		wizard_control(&p1, JOY_1, &sprites[1]);
//		knighty_control(&p1, JOY_1, &sprites[0]);

		bounceCharacter( &speed, &position );
		debugPlayers();

		// control_wizard(&p1);

		// "directionalInput" returns the animation for the state after input
		SPR_setAnim(&sprites[0], knightDirectionalInput(&players[0], JOY_1));
		SPR_setAnim(&sprites[1], wizardDirectionalInput(&players[1], JOY_2));

//		SPR_setAnim(&sprites[0], ANIM_IDLE);
		SPR_update(sprites, 2);

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
	int xc = fix32ToInt(players[0].pos.x);
	int yc = fix32ToInt(players[0].pos.y);

	// Player 1
	if (joy == JOY_1)
	{
		if ( (state & BUTTON_A) || (state & BUTTON_B) || (state & BUTTON_C) )
		// if (state & BUTTON_B )
		{
			if (players[0].pos.y != 0)
			{
				VDP_drawText( "XXX", xc - 1, fix32ToInt(players[0].pos.y - players[0].pos.y) );
				VDP_drawText( "XXX", xc - 1, fix32ToInt(players[0].pos.y - 2*players[0].pos.y) );
			}
			else if (players[0].pos.x != 0)
			{
				VDP_drawText( "XX", fix32ToInt(players[0].pos.x + 2*players[0].pos.x), yc - 1 );
				VDP_drawText( "XX", fix32ToInt(players[0].pos.x + 2*players[0].pos.x), yc     );
				VDP_drawText( "XX", fix32ToInt(players[0].pos.x + 2*players[0].pos.x), yc + 1 );
			}
		}
		
		VDP_setTileMapXY( VDP_PLAN_A, 0, xc, yc );
		VDP_setTileMapXY( VDP_PLAN_A, 0, fix32ToInt(players[0].pos.x + players[0].pos.x), fix32ToInt(players[0].pos.y - players[0].pos.y) );
	}
}

void debugPlayers ()
{
	VDP_drawText( "1", fix32ToInt(players[0].pos.x), fix32ToInt(players[0].pos.y) );
	VDP_drawText( "+", fix32ToInt(players[0].pos.x + players[0].pos.x), fix32ToInt(players[0].pos.y - players[0].pos.y) );

	// VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "2", fix32ToInt(players[1].pos.x), fix32ToInt(players[1].pos.y) );
}


void init_palettes_and_sprites ()
{
	VDP_setPalette( 0, spr_knighty_def.palette->data);
	VDP_setPalette(16, spr_wizard_def.palette->data);

	SPR_initSprite(&sprites[0], &spr_knighty_def, 128, 128, TILE_NO_FLIP);
	SPR_initSprite(&sprites[1], &spr_knighty_def, 150, 128, TILE_NO_FLIP);

	SPR_setAnim(&sprites[0], ANIM_IDLE);
	SPR_setAnim(&sprites[1], ANIM_IDLE);
	SPR_update(sprites, 2);
}
