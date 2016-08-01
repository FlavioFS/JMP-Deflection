// main file:
// @author: Lucas Falc�o @mail: <not@for.your.eyes> =P
// @author: Flavio Freitas @mail: <flaviofreitas.h@gmail.com>

#include <genesis.h>
#include "vector_utils.h"
#include "arena.h"
#include "controls.h"
#include "character.h"
#include "gfx.h"


int main()
{
	VDP_setScreenWidth320();
	SPR_init(0);

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
<<<<<<< HEAD

		control_character (player_one, JOY_1);

=======
		control_character (player_one, JOY_1);
		
>>>>>>> d9b78ad0b1acbeb715d5674aaa2bf15ab7f4c6a4
		update_character_onscreen(player_one);

		//SPR_update(player_one->sprite, 1);

		// wait for the screen to refresh
		VDP_waitVSync();
	}

	SPR_end();

	return 0;
}
