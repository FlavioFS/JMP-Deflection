#ifndef CHARACTER_H
#define CHARACTER_H

#include <genesis.h>
#include "vector_utils.h"

typedef struct struct_character
{
	Sprite * sprite;

	Vector2D position;

	fix32 lin_move_spd;
	fix32 diag_move_spd;

	u16 pal_index;

	u16 anim_idle_up_id;
	u16 anim_idle_down_id;
	u16 anim_idle_left_id;
	u16 anim_idle_right_id;

	u16 anim_move_up_id;
	u16 anim_move_down_id;
	u16 anim_move_left_id;
	u16 anim_move_right_id;

	u16 anim_atk_up_id;
	u16 anim_atk_down_id;
	u16 anim_atk_left_id;
	u16 anim_atk_right_id;

	u16 anim_faint_up_id;
	u16 anim_faint_down_id;
	u16 anim_faint_left_id;
	u16 anim_faint_right_id;

} Character;

Character * init_character (const SpriteDefinition * spr_def, fix32 mov_spd);

void update_character_onscreen(Character * c);

void set_character_position(Character * c, int x, int y);

void set_character_palette(Character * c, u16 pal);

void move_character (Character * c, u16 dir_input);

#endif
