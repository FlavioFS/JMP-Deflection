#include <genesis.h>
#include "vector_utils.h"

/*////////////////////////////////////////////////////////////////////////////////////////////////////
	TODO: Replace "VDP_drawText" with "SPR_setPosition"
	SPR_setPosition(&sprites[0], fix32ToInt(posx), fix32ToInt(posy));
////////////////////////////////////////////////////////////////////////////////////////////////////*/
void bounceCharacter( Vector2D * speed, Vector2D * position )
{
	int xc = fix32ToInt(position->x);
	int yc = fix32ToInt(position->y);

	// 1) hack to clear old position
	VDP_setTileMapXY( VDP_PLAN_A, 0, xc, yc );

	// 2) animation step: just a guess to be adjusted later
	xc += speed->x;
	yc += speed->y;

	// 3) coordinate clamping and speed adjustment
	if ( xc > 39 )
	{
		xc = 39;
		speed->x = -speed->x;
	}

	if ( xc < 0 )
	{
		xc =  0;
		speed->x   *= -1;
	}

	if ( yc > 27 )
	{
		yc = 27;
		speed->y   *= -1;
	}

	if ( yc < 0 )
	{
		yc =  0;
		speed->y   *= -1;
	}

	// 4) draws the Tile at the current position
	VDP_drawText( "O", xc, yc );
	VDP_setTileMapXY( VDP_PLAN_A, TILE_FONTINDEX + 'O' - 32, xc, yc );
}

void debugPlayers (Vector2D p1, Vector2D p2, Vector2D p1_dir, Vector2D p2_dir)
{
	VDP_drawText( "1", fix32ToInt(p1.x), fix32ToInt(p1.y) );
	VDP_drawText( "+", fix32ToInt(p1.x + p1_dir.x), fix32ToInt(p1.y - p1_dir.y) );

	// VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "2", fix32ToInt(p2.x), fix32ToInt(p2.y) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
