#include "knighty.h"

void init_player_knighty(int posx, int posy)
{
	VDP_setPalette(PAL1, spr_knighty_def.palette->data);

	SPR_initSprite(&KNIGHTY_SPR, &spr_knighty_def, 
				   posx, posy,
				   TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}

void knighty_control(Vector2D * v, u16 JOY_NUMBER)
{
	directionalInput(v, JOY_NUMBER);
}
