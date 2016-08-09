#include "player.h"

PlayerData player [PLAYER_COUNT];

void pick_character (u8 pcode, u8 character_code)
{
	player[pcode].char_code = character_code;
	fill_hp(pcode);
}

void fill_hp (u8 pcode)
{
	player[pcode].hp = hp(player[pcode].char_code);
}
