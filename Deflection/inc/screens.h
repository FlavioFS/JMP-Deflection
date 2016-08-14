#ifndef _SCREENS_H_
#define _SCREENS_H_

#include <genesis.h>
#include "character_list.h"
#include "score.h"
#include "player.h"
#include "animations.h"
#include "arena.h"

#define MAIN_SCREEN                0
#define CHARACTER_SELECTION_SCREEN 1
#define GAME_SCREEN                2
#define OPTIONS_SCREEN             3
#define CREDITS_SCREEN             4


#define MENU_COOLDOWN 50

extern u8 next_screen;

//// Methods
void set_next_screen (u8 screen_code);	// [1]
void current_screen();					// [2]
void menu_cooldown(u8 multiplier);      // [3]

// Screen list
void main_screen();						// [4]
void character_selection_screen();		// [5]
void game_screen();						// [6]
void options_screen();					// [7]
void credits_screen();					// [8]

// Joy Handlers (callbacks)
void joyNonDirectional ( u16 joy, u16 changed, u16 state );
void emptyJoyHandler ( u16 joy, u16 changed, u16 state );

// TODO remove faint?
void faint (PlayerData * p, u8 * match_over);

#endif // _SCREENS_H_
