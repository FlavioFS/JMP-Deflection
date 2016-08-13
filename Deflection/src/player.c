#include "player.h"

PlayerData plyr [PLAYER_COUNT];

void PL_pickCharacter (u8 player_code, u8 character_code)
{
	plyr[player_code].char_code = character_code;
	PL_fillHp(player_code);
	PL_attack(character_code);
}

void PL_fillHp (u8 player_code)
{
	plyr[player_code].hp = CHL_hp(plyr[player_code].char_code);
}

void PL_attack (u8 player_code)
{
	plyr[player_code].last_attack = getTick();
}

// Getters
PlayerData PL_player(u8 player_code)
{
	return plyr [player_code];
}

u8 PL_chCode (u8 player_code)
{
	return PL_player(player_code).char_code;
}

u32 PL_lastAtk (u8 player_code)
{
	return plyr[player_code].last_attack;
}
