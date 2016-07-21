#include <genesis.h>
#include "vector_utils.h"

/*////////////////////////////////////////////////////////////////////////////////////////////////////
	TODO: Replace "VDP_drawText" with "SPR_setPosition"
	SPR_setPosition(&sprites[0], fix32ToInt(posx), fix32ToInt(posy));
////////////////////////////////////////////////////////////////////////////////////////////////////*/
void bounceCharacter( Vector2D * speed, Vector2D * position )
{
	// 1) hack to clear old position
	VDP_setTileMapXY( VDP_PLAN_A, 0, fix32ToInt(position->x), fix32ToInt(position->y) );

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
		speed->x = -speed->x;
	}

	if ( position->y > 27 )
	{
		position->y = 27;
		speed->y = -speed->y;
	}

	if ( position->y < 0 )
	{
		position->y =  0;
		speed->y = -speed->y;
	}

	// 4) draws the Tile at the current position
	int xc = fix32ToInt(position->x);
	int yc = fix32ToInt(position->y);
	VDP_drawText( "O", xc, yc );
	VDP_setTileMapXY( VDP_PLAN_A, TILE_FONTINDEX + 'O' - 32, xc, yc );
}
