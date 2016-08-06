#include <genesis.h>
#include "physics.h"
#include "controls.h"

void control_character(Character * c, u16 joy_id)
{
	static const mask_directionals = (BUTTON_UP   |
									  BUTTON_DOWN |
									  BUTTON_LEFT |
									  BUTTON_RIGHT);
	
	static const ANIM_ATK_LENGTH = 3;

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

	else if (dir_input & (BUTTON_LEFT | BUTTON_RIGHT) && dir_input & (BUTTON_DOWN | BUTTON_UP))
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
			SPR_setAnim(c->sprite, c->anim_move_left_id);
			c->anim_idle_last_direction_id = c->anim_idle_up_id;
		}
		else if (dir_input & BUTTON_DOWN)
		{
			c->position.y = fix32Add(c->position.y, c->diag_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_right_id);
			c->anim_idle_last_direction_id = c->anim_idle_down_id;
		}
	}
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
