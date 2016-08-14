#ifndef _PLAYER_H
#define _PLAYER_H

#include <genesis.h>
#include "character_list.h"
#include "animations.h"

#define PLAYER_COUNT 2	// 2 Player PvP game
#define P1_CODE 0
#define P2_CODE 1

typedef struct
{
	u8 hp;             // Current HP, not character's base HP
	u8 char_code;      // Selected character's code
	u8 last_direction; // When the player stops, must look to last direction
	u32 last_attack;   // Cannot spam attack
} PlayerData;

extern PlayerData plyr [PLAYER_COUNT];

// Setters
void PL_pickCharacter (u8 player_code, u8 character_code);
void PL_fillHp (u8 player_code);
void PL_attack (u8 player_code);
void PL_setLastDir (u8 player_code, u8 direction);

// Getters
PlayerData * PL_player(u8 player_code);
u8 PL_hp (u8 char_code);
u8 PL_chCode(u8 player_code);
u32 PL_lastAtk (u8 player_code);
u8 last_dir (u8 player_code);

#endif /* _PLAYER_H */
