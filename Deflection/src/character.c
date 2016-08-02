#include "character.h"

Character * init_character (const SpriteDefinition * spr_def, fix32 mov_spd)
{
	Character * c = (Character*)MEM_alloc(sizeof(Character));

	c->sprite = (Sprite*)MEM_alloc(sizeof(Sprite));

	c->pal_index = PAL2;

	SPR_initSprite(c->sprite, spr_def, 0, 0,
				   TILE_ATTR(c->pal_index, 1, 0, 0));

	c->position.x = FIX32(0.0);
	c->position.y = FIX32(0.0);

	c->diag_move_spd = mov_spd;

	c->lin_move_spd  = fix32Mul(mov_spd, FIX32(1.41));

	return c;
}

void update_character_onscreen(Character * c)
{
	c->sprite->x = fix32ToInt(c->position.x);
	c->sprite->y = fix32ToInt(c->position.y);

	SPR_update(c->sprite, 1);
}

void set_character_position(Character * c, int x, int y)
{
	c->position.x = intToFix32(x);
	c->position.y = intToFix32(y);
}

void set_character_palette(Character * c, u16 pal)
{
	SPR_setAttribut(c->sprite,
				  TILE_ATTR(pal, 0, 0, 0));
}


void move_character (Character * c, u16 dir_input)
{
	VDP_drawText("RLDU", 20, 1);
	if (dir_input & BUTTON_UP)		VDP_drawText("1", 23, 2); else VDP_drawText("0", 23, 2);
	if (dir_input & BUTTON_DOWN)	VDP_drawText("1", 22, 2); else VDP_drawText("0", 22, 2);
	if (dir_input & BUTTON_LEFT)	VDP_drawText("1", 21, 2); else VDP_drawText("0", 21, 2);
	if (dir_input & BUTTON_RIGHT)	VDP_drawText("1", 20, 2); else VDP_drawText("0", 20, 2);

	if (dir_input & (BUTTON_UP | BUTTON_DOWN))		VDP_drawText("!", 25, 2); else VDP_drawText(" ", 25, 2);
	if (dir_input & (BUTTON_LEFT | BUTTON_RIGHT))	VDP_drawText("-", 26, 2); else VDP_drawText(" ", 26, 2);

	if (dir_input == 0)
		VDP_drawText("0", 28, 2);

	else if ((dir_input & (BUTTON_UP | BUTTON_DOWN)) && (dir_input & (BUTTON_LEFT | BUTTON_RIGHT)))
		VDP_drawText("X", 28, 2);

	else VDP_drawText("+", 28, 2);

	if (dir_input & (BUTTON_UP | BUTTON_DOWN))
	{
		if (dir_input & (BUTTON_LEFT | BUTTON_RIGHT)) VDP_drawText("A", 30, 2);
		else VDP_drawText("N", 30, 2);
	}
	else VDP_drawText("N", 30, 2);

	// ---------------------------------------------------------

	// Idle
	if (dir_input == 0)
	{
		SPR_setAnim(c->sprite, c->anim_idle_right_id);
		return;
	}

	// Diagonal movement
	/**
	 * Ok, since I had to write this to fix a bug, it deserves an explanation...
	 * Given the following values:
	 *  dir_input:    X Y Z W
	 *  BUTTON_UP:    0 0 0 1
	 *  BUTTON_DOWN:  0 0 1 0
	 *  BUTTON_LEFT:  0 1 0 0
	 *  BUTTON_RIGHT: 1 0 0 0
	 *  dir_input & (BUTTON_UP   | BUTTON_DOWN ) == X Y Z W & (0 0 1 1) == 0 0 Z W
	 *  dir_input & (BUTTON_LEFT | BUTTON_RIGHT) == X Y Z W & (1 1 0 0) == X Y 0 0
	 * So the "if" statement below is:
	 *  (X Y Z W) & (
	 */
	if ( (dir_input & (BUTTON_UP | BUTTON_DOWN)) && (dir_input & (BUTTON_LEFT | BUTTON_RIGHT)) )
	{
		if (dir_input & BUTTON_LEFT)
		{
			c->position.x = fix32Sub(c->position.x, c->diag_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_left_id);
		}
		else if (dir_input & BUTTON_RIGHT)
		{
			c->position.x = fix32Add(c->position.x, c->diag_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_right_id);
		}

		if (dir_input & BUTTON_UP)
		{
			c->position.y = fix32Sub(c->position.y, c->diag_move_spd);
		}
		else if (dir_input & BUTTON_DOWN)
		{
			c->position.y = fix32Add(c->position.y, c->diag_move_spd);
		}
	}

	// Straight movement
	else
	{
		if (dir_input & BUTTON_LEFT)
		{
			c->position.x = fix32Sub(c->position.x, c->lin_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_left_id);
		}
		else if (dir_input & BUTTON_RIGHT)
		{
			c->position.x = fix32Add(c->position.x, c->lin_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_right_id);
		}

		if (dir_input & BUTTON_UP)
		{
			c->position.y = fix32Sub(c->position.y, c->lin_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_up_id);
		}
		else if (dir_input & BUTTON_DOWN)
		{
			c->position.y = fix32Add(c->position.y, c->lin_move_spd);
			SPR_setAnim(c->sprite, c->anim_move_down_id);
		}
	}
}
