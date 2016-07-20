#include "vector_utils.h"
#include <genesis.h>

/*////////////////////////////////////////////////////////////////////////////////////////////////////
	TODO: Replace "VDP_drawText" with "SPR_setPosition"
	SPR_setPosition(&sprites[0], fix32ToInt(posx), fix32ToInt(posy));
////////////////////////////////////////////////////////////////////////////////////////////////////*/
void bounceCharacter( Vector2D * speed, Vector2D * position )
{
	// 1) hack to clear old position
	VDP_setTileMapXY( VDP_PLAN_A, 0, position->x, position->y );

	// 2) animation step: just a guess to be adjusted later
	position->x += speed->x;
	position->y += speed->y;

	// 3) coordinate clamping and speed adjustment
	if ( position->x > 39 )
	{
		position->x = 39;
		speed->x = -speed->x;
	}

	if ( position->x < 0 )
	{
		position->x =  0;
		speed->x   *= -1;
	}

	if ( position->y > 27 )
	{
		position->y = 27;
		speed->y   *= -1;
	}

	if ( position->y < 0 )
	{
		position->y =  0;
		speed->y   *= -1;
	}

	// 4) draws the Tile at the current position
	VDP_drawText( "O", position->x, position->y );
	VDP_setTileMapXY( VDP_PLAN_A, TILE_FONTINDEX + 'O' - 32, position->x, position->y );
}

void debugPlayers (Vector2D p1, Vector2D p2, Vector2D p1_dir, Vector2D p2_dir)
{
	VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "+", p1.x + p1_dir.x, p1.y - p1_dir.y );

	// if (p1_dir == V2D_NORTH)			{ VDP_drawText( "^",     p1.x, p1.y + 1 ); }
	// else if (p1_dir == V2D_SOUTH)	{ VDP_drawText( "v",     p1.x, p1.y - 1 ); }
	// else if (p1_dir == V2D_EAST)		{ VDP_drawText( ">", p1.x + 1,     p1.y ); }
	// else if (p1_dir == V2D_SOUTH)	{ VDP_drawText( "<", p1.x - 1,     p1.y ); }

	// VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "2", p2.x, p2.y );

	// char * msg;
	// msg[0] = p1_dir.x;
	// msg[1] = p1_dir.y;
	// VDP_drawText( msg, 5, 25 );
	// VDP_drawText( "@", 7, 25 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
