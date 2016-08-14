// main file:
// @author: Lucas Falc�o @mail: <not@for.your.eyes> =P
// @author: Flavio Freitas @mail: <flaviofreitas.h@gmail.com>

#include <genesis.h>
#include "vector_utils.h"
//#include "arena.h"
//#include "controls.h"
#include "character.h"
//#include "knight.h"
#include "debug_tile.h"
#include "screens.h"
#include "gfx.h"


//Character * player_one, * player_two;

int main()
{
	VDP_setScreenWidth320();
	SPR_init(0);
	CHL_initCharacterList();
	VDP_setPaletteColors(0, palette_black, 64);


	// playable characters
//	player_one = init_knight_character();
//	fix32 mspeed = 0.8;
//	player_one = init_debug_tile_character();
//	player_one = init_wizard_character();
//	player_two = init_knight_character();
//
//	set_character_position (player_one, P1_START_X, P1_START_Y);
//	set_character_position (player_two, P1_START_X + 50, P1_START_Y);
//
//	VDP_setPalette(PAL0, spr_debug_tile_def.palette->data);
//	VDP_setPalette(PAL1, spr_debug_tile_def.palette->data);
//	VDP_setPalette(PAL2, spr_debug_tile_def.palette->data);
//	VDP_setPalette(PAL3, spr_debug_tile_def.palette->data);

//	VDP_setPalette(PAL0, spr_knight_def.palette->data);
//	VDP_setPalette(PAL2, spr_wizard_def.palette->data);
//
//	set_character_palette(player_one, PAL2);
//	set_character_palette(player_two, PAL2);

//	lastTick = getTick();

	// Init joy handler
//	JOY_init();

	// Under construction
//	draw_arena();
	
//	JOY_setEventHandler(joyNonDirectional);

	// game loop
	while (1)
	{
		current_screen();
//		control_character (player_one, JOY_1);
//		control_character (player_two, JOY_2);
//		update_character_onscreen(player_one);
//		update_character_onscreen(player_two);
//
//		SPR_update(player_one->sprite, 1);
//		SPR_update(player_one->sprite, 1);

//		 wait for the screen to refresh
//		VDP_waitVSync();
	}

	SPR_end();

	return 0;
}
