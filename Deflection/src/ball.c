#include "ball.h"

// TODO separate model from sprites
Vector2Df bSpd = { 0, 0 };
Vector2Df bPos;

void BALL_init (Sprite ball)
{
	bPos.x = ball.x;
	bPos.y = ball.y;
}


void BALL_reset (Sprite * ball)
{
	static u8 round = 0;
	static const float starting_speedsX[PLAYER_COUNT] = { 0.2, -0.2 };
	static const float starting_speedY[PLAYER_COUNT] = {-0.1 , 0.1};

	V2D_set(&bPos, CENTER_X, CENTER_Y);
	V2D_set(&bSpd, starting_speedsX[round], starting_speedY[round]);

	ball->x = CENTER_X;
	ball->y = CENTER_Y;

	round++;
	if (round > PLAYER_COUNT) round = 0;
}


void BALL_move (Sprite * ball)
{
	Vector2Df new_pos = { bPos.x + bSpd.x, bPos.y + bSpd.y };

	if (new_pos.x < AR_BALL_MIN_X || new_pos.x > AR_BALL_MAX_X)
	{
		bSpd.x = -bSpd.x;
		new_pos.x = bPos.x + bSpd.x;
	}
	if (new_pos.y < AR_BALL_MIN_Y ||  new_pos.y > AR_BALL_MAX_Y)
	{
		bSpd.y = -bSpd.y;
		new_pos.y = bPos.y + bSpd.y;
	}

	bPos.x = new_pos.x;
	bPos.y = new_pos.y;

	ball->x = bPos.x;
	ball->y = bPos.y;
}

void BALL_deflect (u16 joy_direction, u8 player_code)
{
	Vector2Df normal;

	// Diagonal
	if      ( joy_direction & (BUTTON_UP & BUTTON_LEFT)    ) V2D_set(&normal, -SQRT2,  SQRT2);
	else if ( joy_direction & (BUTTON_UP & BUTTON_RIGHT)   ) V2D_set(&normal,  SQRT2,  SQRT2);
	else if ( joy_direction & (BUTTON_DOWN & BUTTON_LEFT)  ) V2D_set(&normal, -SQRT2, -SQRT2);
	else if ( joy_direction & (BUTTON_DOWN & BUTTON_RIGHT) ) V2D_set(&normal,  SQRT2, -SQRT2);

	// Straight
	else if ( joy_direction & (BUTTON_UP)    ) V2D_set(&normal,  0,  1);
	else if ( joy_direction & (BUTTON_DOWN)  ) V2D_set(&normal,  0, -1);
	else if ( joy_direction & (BUTTON_LEFT)  ) V2D_set(&normal, -1,  0);
	else if ( joy_direction & (BUTTON_RIGHT) ) V2D_set(&normal,  1,  0);

	else return;


	PlayerData * player = PL_player(player_code);

	// R = I - 2 . (I.n) . n
	Vector2Df part2 = V2D_prod( 2  * V2D_dot(bSpd, normal), normal );
	Vector2Df reflected = V2D_diff(bSpd, part2);

	// F = R + dp * (B - P)
	float dpower = CHL_dPwr(player->char_code);
	Vector2Df player2ball = V2D_diff(bPos, player->pos);
	Vector2Df final = V2D_sum(reflected, V2D_prod(dpower, player2ball));

	// Updates ball model
	V2D_setV(&bSpd, final);
}


u8 BALL_dangerZone (u8 player_code)
{
	PlayerData * player = PL_player(player_code);

	Vector2Df edge =
	{
			player->pos.x + ((PL_HITBOX_R - PL_HITBOX_L)/2),
			player->pos.y + ((PL_HITBOX_D - PL_HITBOX_U)/2)
	};
	Vector2Df diff = V2D_diff(bPos, edge);

	// Fast return when far away
	if (V2D_dot(diff, diff) < PL_HITBOX_MAX + 100) return TRUE;
	return FALSE;
}


u8 BALL_isHitting (u8 player_code)
{
	PlayerData * player = PL_player(player_code);


	Vector2Df edge =
	{
			player->pos.x + ((PL_HITBOX_R - PL_HITBOX_L)/2),
			player->pos.y + ((PL_HITBOX_D - PL_HITBOX_U)/2)
	};
	Vector2Df diff = V2D_diff(bPos, edge);

	// Fast return when far away
	if (V2D_dot(diff, diff) < PL_HITBOX_MIN) return TRUE;

	// Up, Down, Left and Right limits of the player sprite
	float U = player->pos.y + PL_HITBOX_U;
	float D = player->pos.y + PL_HITBOX_D;
	float L = player->pos.x + PL_HITBOX_L;
	float R = player->pos.x + PL_HITBOX_R;

	// Several cases
	// 1. Inner
	float BALL_DIAMETER = BALL_RADIUS + BALL_RADIUS;
	if ( (bPos.x > L - BALL_DIAMETER) && (bPos.x < R) && // Every frame, avoid product
         (bPos.y > U - BALL_DIAMETER) && (bPos.y < D) )  // <- inverted axis
		{ return TRUE; }

	// 2. Edges
	// Up Right
	V2D_set(&edge, R, U);
	float BRADIUS2 = BALL_RADIUS*BALL_RADIUS;
	if (V2D_dot(diff, diff) < BRADIUS2) return TRUE;

	// Up Left
	V2D_set(&edge, L, U);
	diff = V2D_diff(bPos, edge);
	if (V2D_dot(diff, diff) < BRADIUS2) return TRUE;

	// Down Left
	V2D_set(&edge, L, D);
	diff = V2D_diff(bPos, edge);
	if (V2D_dot(diff, diff) < BRADIUS2) return TRUE;

	// Down Right
	V2D_set(&edge, R, D);
	diff = V2D_diff(bPos, edge);
	if (V2D_dot(diff, diff) < BRADIUS2) return TRUE;

	return FALSE;
}










