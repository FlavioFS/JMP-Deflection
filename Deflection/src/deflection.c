// main file: 
// @author: Lucas Falcão @mail: <not@for.your.eyes> =P

#include <genesis.h>
#include "deflection.h"

// Global variables

// Players
Vector2D p1 = { FIX32(13), FIX32(14) };
Vector2D p2 = { FIX32(26), FIX32(14) };

// Vector2D v1 = { 0, 0 };
// Vector2D v2 = { 0, 0 };

Vector2D p1_dir = {  1, 0 };
Vector2D p2_dir = { -1, 0 };

// Bullet
Vector2D bulPos = { FIX32(19), FIX32(14) };
Vector2D bulVel = { FIX32( 0), FIX32( 0) };

int main()
{
	// print text on >> tile << h=1,v=0
	// VDP_drawText ( "X", 39,  27 );

	Vector2D speed		= { FIX32(0.2), FIX32(0.2) };
	Vector2D position	= { FIX32(  1), FIX32(  1) };

	// Init joy handler
	JOY_init();
	JOY_setEventHandler( &joyAtkHandler );

	// game loop
	while (1)
	{
		directionalInput();
		bounceCharacter( &speed, &position );
		renderPlayers(p1, p2);

		// wait for the screen to refresh
		VDP_waitVSync();
	}

	return 0;
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////
	TODO: Replace "VDP_drawText" with "SPR_setPosition"
	SPR_setPosition(&sprites[0], fix32ToInt(posx), fix32ToInt(posy));
////////////////////////////////////////////////////////////////////////////////////////////////////*/
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

void renderPlayers (Vector2D p1, Vector2D p2)
{
	VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "+", p1.x + p1_dir.x, p1.y - p1_dir.y );

	// if (p1_dir == V2D_NORTH)			{ VDP_drawText( "^",     p1.x, p1.y + 1 ); }
	// else if (p1_dir == V2D_SOUTH)	{ VDP_drawText( "v",     p1.x, p1.y - 1 ); }
	// else if (p1_dir == V2D_EAST)		{ VDP_drawText( ">", p1.x + 1,     p1.y ); }
	// else if (p1_dir == V2D_SOUTH)	{ VDP_drawText( "<", p1.x - 1,     p1.y ); }

	// VDP_drawText( "1", p1.x, p1.y );
	VDP_drawText( "2", p2.x, p2.y );

	// char * msg;
	// msg[0] = p1_dir.x;
	// msg[1] = p1_dir.y;
	// VDP_drawText( msg, 5, 25 );
	// VDP_drawText( "@", 7, 25 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

/** Moves the characters on input in the (x,y) plane (velocity has a constant absolute value)
 */
void directionalInput ()
{
	// Player 1
	u16 value = JOY_readJoypad(JOY_1);

	// Resetting values (in case no button press occurs)
	p1.x = FIX32(0);
	p1.y = FIX32(0);

	// Diagonal motion
	if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	{
		if 		(value & BUTTON_LEFT)	p1.x -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_RIGHT)	p1.x += DEFAULT_SPEED_DIAG;

		if 		(value & BUTTON_UP)		p1.y -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_DOWN)	p1.y += DEFAULT_SPEED_DIAG;
	}

	// Single axis motion
	else
	{
		if 		(value & BUTTON_LEFT)	p1.x -= DEFAULT_SPEED;
		else if (value & BUTTON_RIGHT)	p1.x += DEFAULT_SPEED;

		else if (value & BUTTON_UP)		p1.y -= DEFAULT_SPEED;
		else if (value & BUTTON_DOWN)	p1.y += DEFAULT_SPEED;
	}

	// ---------------------------------------------------------------------
	
	// Player 2
	value = JOY_readJoypad(JOY_2);

	// Resetting values (in case no button press occurs)
	p2.x = FIX32(0);
	p2.y = FIX32(0);

	// Diagonal motion
	if (value & (BUTTON_LEFT | BUTTON_RIGHT) & (BUTTON_UP | BUTTON_DOWN))
	{
		if 		(value & BUTTON_LEFT)	p2.x -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_RIGHT)	p2.x += DEFAULT_SPEED_DIAG;

		if 		(value & BUTTON_UP)		p2.y -= DEFAULT_SPEED_DIAG;
		else if (value & BUTTON_DOWN)	p2.y += DEFAULT_SPEED_DIAG;
	}

	// Single axis motion
	else
	{
		if 		(value & BUTTON_LEFT)	p2.x -= DEFAULT_SPEED;
		else if (value & BUTTON_RIGHT)	p2.x += DEFAULT_SPEED;

		else if (value & BUTTON_UP)		p2.y -= DEFAULT_SPEED;
		else if (value & BUTTON_DOWN)	p2.y += DEFAULT_SPEED;
	}
}

void joyAtkHandler ( u16 joy, u16 joyChanged, u16 state )
{
	// Player 1
	if (joy == JOY_1)
	{
		if ( (state & BUTTON_A) || (state & BUTTON_B) || (state & BUTTON_C) )
		// if (state & BUTTON_B )
		{
			if (p1_dir.y != 0)
			{
				VDP_drawText( "XXX", p1.x - 1, p1.y - p1_dir.y );
				VDP_drawText( "XXX", p1.x - 1, p1.y - 2*p1_dir.y );
			}
			else if (p1_dir.x != 0)
			{
				VDP_drawText( "XX", p1.x + 2*p1_dir.x, p1.y - 1 );
				VDP_drawText( "XX", p1.x + 2*p1_dir.x, p1.y     );
				VDP_drawText( "XX", p1.x + 2*p1_dir.x, p1.y + 1 );
			}
		}

		
		VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x, p1.y );
		VDP_setTileMapXY( VDP_PLAN_A, 0, p1.x + p1_dir.x, p1.y - p1_dir.y );
	}
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


/*////////////////////////////////////////////////////////////
	Vector2D Utils 
////////////////////////////////////////////////////////////*/

 /** Dot product
  */
s32 dot ( Vector2D v1, Vector2D v2 )
{
	return v1.x * v2.x + v1.y * v2.y;
}

/** Subtraction vector
 */
Vector2D diff ( Vector2D v1, Vector2D v2 )
{
	Vector2D rv = { v1.x - v2.x, v1.y - v2.y };
	return rv;
}

/** Squared distance
 */
s32 sqDist ( Vector2D v1, Vector2D v2 )
{
	Vector2D dif = diff(v1, v2);
	return dot(dif, dif);
}

/** Cross product
 */
s32 cross ( Vector2D v1, Vector2D v2 )
{
	return v1.x * v2.y - v2.x * v1.y;
}

/** Absolute value less than or equals then <value>
 */
u8 absLEQ ( Vector2D v, fix32 value )
{
	if (v.x * v.x + v.y * v.y <= FIX32(value * value)) return 1;
	return 0;
}
