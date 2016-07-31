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
