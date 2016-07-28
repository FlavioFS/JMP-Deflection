#include "wizard.h"
#include "gfx.h"

Character * init_wizard_character()
{
	Character * c =	init_character(&spr_wizard_def, intToFix32(1));
	
	c->anim_iddle_id 	  = 0;
	c->anim_move_up_id 	  = 0;
	c->anim_move_down_id  = 0;
	c->anim_move_left_id  = 0;
	c->anim_move_right_id = 0;
	
	SPR_setAnim(c->sprite, c->anim_iddle_id);
	
	return c;
}
