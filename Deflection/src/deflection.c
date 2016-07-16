// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P

#include <genesis.h>
#include "vector_utils.h"
#include "deflection.h"
#include "arena.h"
#include "players.h"

// Global variables
Vector2D p1 = { 13, 14 };
Vector2D p2 = { 26, 14 };

Vector2D p1_facing = {  1, 0 };
Vector2D p2_facing = { -1, 0 };

int main()
{
	// print text on >> tile << h=1,v=0
	// VDP_drawText ( "X", 39,  27 );

	Vector2D speed		= { 0.2, 0.2 };
	Vector2D position	= { 1, 1 };

	// Init joy handler
	JOY_init();
	JOY_setEventHandler( &joyAtkHandler );

	// lets try rendering the arena !
	draw_arena();
	
	// lets try loadind player sprites 
	load_players_sprite_data();
	
	// game loop
	while (1)
	{
		bounceCharacter( &speed, &position );
		renderPlayers(p1, p2);

		// wait for the screen to refresh
		VDP_waitVSync();
	}

	return 0;
}
