#include <genesis.h>
#include "physics.h"
#include "controls.h"

void control_character(Character * c, u16 joy_id)
{
	static const u16 mask_directionals = (BUTTON_UP   |
									  BUTTON_DOWN |
									  BUTTON_LEFT |
									  BUTTON_RIGHT);
	
	static const int ANIM_ATK_LENGTH = 3;

	u16 joy_state = JOY_readJoypad(joy_id);
	joy_state 	  = JOY_readJoypad(joy_id); // debounce

	u16 dir_input = joy_state & mask_directionals;

	if (c->sprite->animInd == c->anim_atk_left_id || c->sprite->animInd == c->anim_atk_right_id )
	{
		
		if (c->sprite->frameInd < ANIM_ATK_LENGTH) return;
	}

	if (dir_input == 0) {
		SPR_setAnim(c->sprite, c->anim_idle_last_direction_id);
	}

	// Diagonal
	else if ( (dir_input & (BUTTON_LEFT | BUTTON_RIGHT)) && (dir_input & (BUTTON_DOWN | BUTTON_UP)) )
	{
		if (dir_input & BUTTON_LEFT)
		{
			c->position.x = fix32Sub(c->position.x, c->diag_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_left_id);
			c->anim_idle_last_direction_id = c->anim_idle_left_id;
		}
		else if (dir_input & BUTTON_RIGHT)
		{
			c->position.x = fix32Add(c->diag_move_spd, c->position.x);
			SPR_setAnim(c->sprite, c->anim_move_right_id);
			c->anim_idle_last_direction_id = c->anim_idle_right_id;
		}

		if (dir_input & BUTTON_UP)
		{
			c->position.y = fix32Sub(c->position.y, c->diag_move_spd);
			// SPR_setAnim(c->sprite, c->anim_move_left_id);
			// c->anim_idle_last_direction_id = c->anim_idle_up_id;
		}
		else if (dir_input & BUTTON_DOWN)
		{
			c->position.y = fix32Add(c->position.y, c->diag_move_spd);
			// SPR_setAnim(c->sprite, c->anim_move_right_id);
			// c->anim_idle_last_direction_id = c->anim_idle_down_id;
		}
	}

	// Straight direction
	else
	{
		if (dir_input & BUTTON_LEFT)
		{
			c->position.x = fix32Sub(c->position.x, c->lin_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_left_id);
			c->anim_idle_last_direction_id = c->anim_idle_left_id;
		}
		else if (dir_input & BUTTON_RIGHT)
		{
			c->position.x = fix32Add(c->lin_move_spd, c->position.x);
			SPR_setAnim(c->sprite, c->anim_move_right_id);
			c->anim_idle_last_direction_id = c->anim_idle_right_id;
		}

		else if (dir_input & BUTTON_UP)
		{
			c->position.y = fix32Sub(c->position.y, c->lin_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_up_id);
			c->anim_idle_last_direction_id = c->anim_idle_up_id;
		}
		else if (dir_input & BUTTON_DOWN)
		{
			c->position.y = fix32Add(c->position.y, c->lin_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_down_id);
			c->anim_idle_last_direction_id = c->anim_idle_down_id;
		}
	}
}

void control_char ( Sprite * sprite, u8 player_code, u16 joy_id )
{
	static const u16 mask_directionals = (BUTTON_UP   |
									      BUTTON_DOWN |
									      BUTTON_LEFT |
									      BUTTON_RIGHT);

	u16 joy_state = JOY_readJoypad(joy_id);
	joy_state 	  = JOY_readJoypad(joy_id); // debounce

	u16 dir_input = joy_state & mask_directionals;
	PlayerData * player = PL_player(player_code);

	// Atk not finished, still locked, cannot reset animation or move
	if ( getTick() - player->last_attack < CHL_atkD(player->char_code) ) return;

	// Player is idling
	if (dir_input == 0) { SPR_setAnim(sprite, player->last_direction); }

	// Diagonal
	else if ((dir_input & (BUTTON_LEFT | BUTTON_RIGHT)) && (dir_input & (BUTTON_DOWN | BUTTON_UP)))
	{
		float diagonal_speed = CHL_dSpd(player->char_code);

		if ((dir_input & BUTTON_LEFT) && (sprite->x > AR_PL_MIN_X))
		{
			player->pos.x -= diagonal_speed;
			sprite->x = player->pos.x;
			SPR_setAnim(sprite, ANIM_WALK_L);
			player->last_direction = ANIM_IDLE_L;
		}
		else if ((dir_input & BUTTON_RIGHT) && (sprite->x < AR_PL_MAX_X))
		{
			player->pos.x += diagonal_speed;
			sprite->x = player->pos.x;
			SPR_setAnim(sprite, ANIM_WALK_R);
			player->last_direction = ANIM_IDLE_R;
		}

		if ((dir_input & BUTTON_UP) && (sprite->y > AR_PL_MIN_Y))
		{
			player->pos.y -= diagonal_speed;
			sprite->y = player->pos.y;
		}
		else if ((dir_input & BUTTON_DOWN) && (sprite->y < AR_PL_MAX_Y))
		{
			player->pos.y += diagonal_speed;
			sprite->y = player->pos.y;
		}
	}

	// Straight direction
	else
	{
		float linear_speed = CHL_spd(player->char_code);

		if ((dir_input & BUTTON_LEFT) && (sprite->x > AR_PL_MIN_X))
		{
			player->pos.x -= linear_speed;
			sprite->x = player->pos.x;
			SPR_setAnim(sprite, ANIM_WALK_L);
			player->last_direction = ANIM_IDLE_L;
		}
		else if ((dir_input & BUTTON_RIGHT) && (sprite->x < AR_PL_MAX_X))
		{
			player->pos.x += linear_speed;
			sprite->x = player->pos.x;
			SPR_setAnim(sprite, ANIM_WALK_R);
			player->last_direction = ANIM_IDLE_R;
		}

		else if ((dir_input & BUTTON_UP) && (sprite->y > AR_PL_MIN_Y))
		{
			player->pos.y -= linear_speed;
			sprite->y = player->pos.y;
			SPR_setAnim(sprite, ANIM_WALK_U);
			player->last_direction = ANIM_IDLE_U;
		}
		else if ((dir_input & BUTTON_DOWN) && (sprite->y < AR_PL_MAX_Y))
		{
			player->pos.y += linear_speed;
			sprite->y = player->pos.y;
			SPR_setAnim(sprite, ANIM_WALK_D);
			player->last_direction = ANIM_IDLE_D;
		}
	}
}
