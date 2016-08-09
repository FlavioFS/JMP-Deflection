#ifndef _SCREENS_H_
#define _SCREENS_H_

#include <genesis.h>
#include "character_list.h"
#include "score.h"
#include "player.h"

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

// Screen list
void main_screen();						// [3]
void character_selection_screen();		// [4]
void game_screen();						// [5]
void options_screen();					// [6]
void credits_screen();					// [7]

// TODO remove faint?
void faint (PlayerData * p, u8 * match_over);

#endif // _SCREENS_H_
