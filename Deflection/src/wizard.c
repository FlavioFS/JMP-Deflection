#include "wizard.h"

void init_player_wizard(int posx, int posy)
{
	VDP_setPalette(PAL2, spr_knighty_def.palette->data);
	
	SPR_initSprite(&WIZARD_SPR, &spr_wizard_def, 
				   posx, posy,
				   TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
}

void wizard_control(Vector2D * v, u16 JOY_NUMBER)
{
	directionalInput(v, JOY_NUMBER);
}
