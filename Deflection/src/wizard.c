#include "wizard.h"

void init_player_wizard(int posx, int posy)
{
	VDP_setPalette(PAL2, wizard_res.palette->data);
	
	SPR_initSprite(&wizard_sprite, &wizard_res, 
				   posx, posy,
				   TILE_ATTR(PAL2, 1, 0, 0));
}

void control_wizard()
{
	//
}
