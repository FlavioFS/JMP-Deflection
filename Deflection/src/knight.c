#include "knight.h"
#include "gfx.h"

Character * init_knight_character()
{
	Character * c =	init_character(&spr_knight_def, FIX32(0.8));

	c->anim_idle_up_id    = 0;
	c->anim_idle_down_id  = 0;
	c->anim_idle_left_id  = 0;
	c->anim_idle_right_id = 1;

	c->anim_move_up_id     = 0;
	c->anim_move_down_id   = 0;
	c->anim_move_left_id   = 2;
	c->anim_move_right_id  = 3;

	c->anim_atk_up_id      = 0;
	c->anim_atk_down_id    = 0;
	c->anim_atk_left_id    = 4;
	c->anim_atk_right_id   = 5;
	
	c->anim_faint_up_id    = 0;
	c->anim_faint_down_id  = 0;
	c->anim_faint_left_id  = 0;
	c->anim_faint_right_id = 0;


	SPR_setAnim(c->sprite, c->anim_idle_right_id);

	return c;
}
