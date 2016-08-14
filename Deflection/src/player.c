#include "player.h"

PlayerData plyr [PLAYER_COUNT];

void PL_pickCharacter (u8 player_code, u8 character_code)
{
	plyr[player_code].char_code = character_code;
	plyr[player_code].last_direction = (player_code == P1_CODE) ? ANIM_IDLE_R : ANIM_IDLE_L;
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

void PL_setLastDir (u8 player_code, u8 direction)
{
	plyr[player_code].last_direction = direction;
}

// Getters
PlayerData * PL_player(u8 player_code)
{
	return &plyr[player_code];
}

u8 PL_hp (u8 char_code)
{
	return plyr[char_code].hp;
}

u8 PL_chCode (u8 player_code)
{
	return plyr[player_code].char_code;
}

u32 PL_lastAtk (u8 player_code)
{
	return plyr[player_code].last_attack;
}

u8 Pl_lastDir (u8 player_code)
{
	return plyr[player_code].last_direction;
}
