// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P

#include <genesis.h>
#include "deflection.h"

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

void bounceCharacter( Vector2D * speed, Vector2D * position )
{
	// 1) hack to clear old position
	VDP_setTileMapXY( VDP_PLAN_A, 0, position->x, position->y );

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
		speed->x   *= -1;
	}

	if ( position->y > 27 )
	{
		position->y = 27;
		speed->y   *= -1;
	}

	if ( position->y < 0 )
	{
		position->y =  0;
		speed->y   *= -1;
	}

	// 4) draws the Tile at the current position
	VDP_drawText( "O", position->x, position->y );
	VDP_setTileMapXY( VDP_PLAN_A, TILE_FONTINDEX + 'O' - 32, position->x, position->y );
}

void renderPlayers (Vector2D p1, Vector2D p2) {
	VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "+", p1.x + p1_facing.x, p1.y - p1_facing.y );

	// if (p1_facing == V2D_NORTH)			{ VDP_drawText( "^",     p1.x, p1.y + 1 ); }
	// else if (p1_facing == V2D_SOUTH)	{ VDP_drawText( "v",     p1.x, p1.y - 1 ); }
	// else if (p1_facing == V2D_EAST)		{ VDP_drawText( ">", p1.x + 1,     p1.y ); }
	// else if (p1_facing == V2D_SOUTH)	{ VDP_drawText( "<", p1.x - 1,     p1.y ); }

	// VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "2", p2.x, p2.y );

	// char * msg;
	// msg[0] = p1_facing.x;
	// msg[1] = p1_facing.y;
	// VDP_drawText( msg, 5, 25 );
	// VDP_drawText( "@", 7, 25 );
}

void joyAtkHandler ( u16 joy, u16 joyChanged, u16 state ) {
	// Player 1
	if (joy == JOY_1)
	{
		if ( (state & BUTTON_A) || (state & BUTTON_B) || (state & BUTTON_C) )
		// if (state & BUTTON_B )
		{
			if (p1_facing.y != 0)
			{
				VDP_drawText( "XXX", p1.x - 1, p1.y - p1_facing.y );
				VDP_drawText( "XXX", p1.x - 1, p1.y - 2*p1_facing.y );
			}
			else if (p1_facing.x != 0)
			{
				VDP_drawText( "XX", p1.x + 2*p1_facing.x, p1.y - 1 );
				VDP_drawText( "XX", p1.x + 2*p1_facing.x, p1.y     );
				VDP_drawText( "XX", p1.x + 2*p1_facing.x, p1.y + 1 );
			}
			// if (p1_facing == V2D_NORTH)
			// {
			// 	VDP_drawText( "XXX", p1.x - 1, p1.y - 1 );
			// 	VDP_drawText( "XXX", p1.x - 1, p1.y - 2 );
			// }
			// else if (p1_facing == V2D_SOUTH)
			// {
			// 	VDP_drawText( "XXX", p1.x - 1, p1.y + 1 );
			// 	VDP_drawText( "XXX", p1.x - 1, p1.y + 2 );
			// }
			// else if (p1_facing == V2D_EAST)
			// {
			// 	VDP_drawText( "XX", p1.x + 1, p1.y - 1 );
			// 	VDP_drawText( "XX", p1.x + 1, p1.y     );
			// 	VDP_drawText( "XX", p1.x + 1, p1.y + 1 );
			// }
			// else if (p1_facing == V2D_SOUTH)
			// {
			// 	VDP_drawText( "XX", p1.x - 1, p1.y - 1 );
			// 	VDP_drawText( "XX", p1.x - 1, p1.y     );
			// 	VDP_drawText( "XX", p1.x - 1, p1.y + 1 );
			// }
		}

		// else
		// {
			// Clears previous position
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x + p1_facing.x, p1.y - p1_facing.y );

		if (state & BUTTON_UP)
		{
			if (p1.y >= 1) p1.y -= 1;
			p1_facing.x = 0;
			p1_facing.y = 1;
		}
		else if (state & BUTTON_DOWN)
		{
			if (p1.y < 27) p1.y += 1;
			p1_facing.x = 0;
			p1_facing.y = -1;
		}

		else if (state & BUTTON_RIGHT)
		{
			if (p1.x < 39) p1.x += 1;
			p1_facing.x = 1;
			p1_facing.y = 0;
		}
		else if (state & BUTTON_LEFT)
		{
			if (p1.x >= 1) p1.x -= 1;
			p1_facing.x = -1;
			p1_facing.y = 0;
		}
		// }
	}

	// Player 2
	// else if (joy == JOY_1B)
	// {
	// 	if (state & ( BUTTON_A | BUTTON_B | BUTTON_C ) )
	// 	{
	// 		VDP_drawText( " ", p1.x, p1.y );
	// 		if (p1.y >= 1) p1.y -= 1;
	// 	}
	// }
}

void joyMoveHandler ( u16 joy, u16 joyChanged, u16 state ) {
	// Player 1
	if (joy == JOY_1)
	{
		if (state & BUTTON_START)		// Press
		{
			/* code */
		}
		else if (joyChanged & BUTTON_START)	// Release
		{

		}


		if (state & BUTTON_UP)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.y >= 1) p1.y -= 1;
		}
		else if (state & BUTTON_DOWN)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.y < 27) p1.y += 1;
		}


		if (state & BUTTON_LEFT)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.x >= 1) p1.x -= 1;
		}
		else if (state & BUTTON_RIGHT)
		{
			VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
			if (p1.x < 39) p1.x += 1;
		}

		else if (state & BUTTON_START)	// Press start
		{

		}
		else if (state & BUTTON_START)	// Release start
		{

		}

		// int dbg_pos[] = { 10, 20 };
		// VDP_drawText( state, dbg_pos[0], dbg_pos[1] );
	}

	// Player 2
	// else if (joy == JOY_1B)
	// {
		/* code */
	// }
}

// Vector2D Utils
double dot ( Vector2D v1, Vector2D v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2D diff ( Vector2D v1, Vector2D v2 )
{
	Vector2D rv = { v1.x - v2.x, v1.y - v2.y };
	return rv;
}

double sqDist ( Vector2D v1, Vector2D v2 )
{
	Vector2D dif = diff(v1, v2);
	return dot(dif, dif);
}