#include "knight.h"

// Knight's input handler
s16 knightDirectionalInput (Player * player, u16 JOYPAD)
{
	return baseDirectionalInput(player, KNIGHT, JOYPAD);
}
