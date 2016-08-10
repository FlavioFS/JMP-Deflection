#include "wizard.h"
#include "gfx.h"

Character * init_wizard_character()
{
	Character * c =	init_character(&spr_wizard_def, intToFix32(1));
	
		c->anim_idle_up_id    = 0;
		c->anim_idle_down_id  = 1;
		c->anim_idle_left_id  = 2;
		c->anim_idle_right_id = 3;

		c->anim_move_up_id     = 4;
		c->anim_move_down_id   = 5;
		c->anim_move_left_id   = 6;
		c->anim_move_right_id  = 7;

		c->anim_atk_up_id      = 0;
		c->anim_atk_down_id    = 0;
		c->anim_atk_left_id    = 8;
		c->anim_atk_right_id   = 9;

		c->anim_faint_up_id    = 0;
		c->anim_faint_down_id  = 0;
		c->anim_faint_left_id  = 0;
		c->anim_faint_right_id = 0;


		c->anim_idle_last_direction_id = c->anim_idle_right_id;
		SPR_setAnim(c->sprite, c->anim_idle_right_id);
	
	return c;
}
