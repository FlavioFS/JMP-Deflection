// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P

#include <genesis.h>
#include "vector_utils.h"
#include "arena.h"
#include "red_wizard.h"

int main()
{	
	SPR_init(0);
	
	draw_arena();
	
	init_player_wizard(128, 128);
				   
	// game loop
	while (1)
	{
		control_wizard();
		
		SPR_update(&wizard_sprite, 1);
		
		// wait for the screen to refresh
		VDP_waitVSync();
	}
	
	SPR_end();

	return 0;
}
