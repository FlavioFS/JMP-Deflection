// main file:
// @author: Lucas Falc�o @mail: <not@for.your.eyes> =P
// @author: Flavio Freitas @mail: <flaviofreitas.h@gmail.com>

#include <genesis.h>
#include "vector_utils.h"
#include "arena.h"
#include "controls.h"
 #include "character.h"
#include "knight.h"
#include "debug_tile.h"
#include "screens.h"
#include "gfx.h"

void joyNonDirectional ( u16 joy, u16 changed, u16 state );

Character * player_one, * player_two;
static u32 lastTick;

int main()
{
	VDP_setScreenWidth320();
	SPR_init(0);
	init_character_list();
	VDP_setPaletteColors(0, palette_black, 64);


	// playable characters
//	player_one = init_knight_character();
//	fix32 mspeed = 0.8;
//	player_one = init_debug_tile_character();
//	player_one = init_wizard_character();
//	player_two = init_knight_character();
//
//	set_character_position (player_one, P1_START_X, P1_START_Y);
//	set_character_position (player_two, P1_START_X + 50, P1_START_Y);
//
//	VDP_setPalette(PAL0, spr_debug_tile_def.palette->data);
//	VDP_setPalette(PAL1, spr_debug_tile_def.palette->data);
//	VDP_setPalette(PAL2, spr_debug_tile_def.palette->data);
//	VDP_setPalette(PAL3, spr_debug_tile_def.palette->data);

//	VDP_setPalette(PAL0, spr_knight_def.palette->data);
//	VDP_setPalette(PAL2, spr_wizard_def.palette->data);
//
//	set_character_palette(player_one, PAL2);
//	set_character_palette(player_two, PAL2);

//	lastTick = getTick();

	// Init joy handler
//	JOY_init();

	// Under construction
//	draw_arena();
	
//	JOY_setEventHandler(joyNonDirectional);

	// game loop
	while (1)
	{
		current_screen();
//		control_character (player_one, JOY_1);
//		control_character (player_two, JOY_2);
//		update_character_onscreen(player_one);
//		update_character_onscreen(player_two);
//
//		SPR_update(player_one->sprite, 1);
//		SPR_update(player_one->sprite, 1);

//		 wait for the screen to refresh
//		VDP_waitVSync();
	}

	SPR_end();

	return 0;
}


void joyNonDirectional ( u16 joy, u16 changed, u16 state )
{	
	if (joy == JOY_1)
	{
		// START button state changed
		if (changed & BUTTON_START)
		{
			// Pause game
		}

		if (changed & state)
		{
			if ( state & ( BUTTON_A | BUTTON_B | BUTTON_C ) )
			{
				// Already attacking
				if (getTick() - lastTick < player_one->atk_cooldown) return;
				lastTick = getTick();
				// if (player_one->sprite->animInd == 8 || player_one->sprite->animInd == 9 ) return;

				if (player_one->anim_idle_last_direction_id == player_one->anim_idle_up_id)
				{
					SPR_setAnim(player_one->sprite, player_one->anim_atk_left_id);
				}
				
				else if (player_one->anim_idle_last_direction_id == player_one->anim_idle_down_id)
				{
					SPR_setAnim(player_one->sprite, player_one->anim_atk_right_id);
				}

				else if (player_one->anim_idle_last_direction_id == player_one->anim_idle_left_id)
				{
					SPR_setAnim(player_one->sprite, player_one->anim_atk_left_id);
				}

				else if (player_one->anim_idle_last_direction_id == player_one->anim_idle_right_id)
				{
					SPR_setAnim(player_one->sprite, player_one->anim_atk_right_id);
				}
			}
		}
	}

	// else if (joy == JOY_2)
	// {
	// 	// START button state changed
	// 	if (changed & BUTTON_START)
	// 	{
	// 		// Pause game
	// 	}

	// 	if (changed & state)
	// 	{
	// 		if ( (state & BUTTON_A) )
	// 		{
	// 			if (player_two->anim_idle_last_direction_id == player_two->anim_atk_up_id)
	// 				SPR_setAnim(c, player_two->anim_atk_up_id);
				
	// 			else if (player_two->anim_idle_last_direction_id == player_two->anim_atk_down_id)
	// 				SPR_setAnim(c, player_two->anim_atk_down_id);

	// 			else if (player_two->anim_idle_last_direction_id == player_two->anim_atk_left_id)
	// 				SPR_setAnim(c, player_two->anim_atk_left_id);

	// 			else if (player_two->anim_idle_last_direction_id == player_two->anim_atk_right_id)
	// 				SPR_setAnim(c, player_two->anim_atk_right_id);
	// 		}
	// 	}
	// }
}
