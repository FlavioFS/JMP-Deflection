#include "knighty.h"

void init_player_knighty(int posx, int posy)
{
	VDP_setPaletteColors(0, spr_knighty_def.palette->data, 64);


	SPR_initSprite(&KNIGHTY_SPR, &spr_knighty_def, 
				   posx, posy,
				   TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
}

void knighty_control(Vector2D * v, u16 JOY_NUMBER)
{
	directionalInput(v, JOY_NUMBER);
}
