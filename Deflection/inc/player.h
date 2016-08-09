#ifndef _PLAYER_H
#define _PLAYER_H

#include <genesis.h>
#include "character_list.h"

#define PLAYER_COUNT 2	// 2 Player PvP game
#define P1_CODE 0
#define P2_CODE 1

typedef struct
{
	u8 hp;        // Current HP, not character's base HP
	u8 char_code; // Selected character's code
} PlayerData;

extern PlayerData player [PLAYER_COUNT];

// Methods
void pick_character (u8 pcode, u8 character_code);
void fill_hp (u8 pcode);

#endif /* _PLAYER_H */
