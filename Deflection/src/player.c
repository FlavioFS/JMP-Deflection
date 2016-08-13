#include "player.h"

PlayerData plyr [PLAYER_COUNT];

void pick_character (u8 pcode, u8 character_code)
{
	plyr[pcode].char_code = character_code;
	fill_hp(pcode);
}

void fill_hp (u8 pcode)
{
	plyr[pcode].hp = hp(plyr[pcode].char_code);
}

PlayerData player(u8 player_code)
{
	return plyr [player_code];
}

u8 ch_code (u8 player_code)
{
	return player(player_code).char_code;
}
