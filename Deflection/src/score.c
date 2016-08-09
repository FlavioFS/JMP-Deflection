#include "score.h"

u16 wins [PLAYER_COUNT] = { 0, 0 };

u16 score (u8 player_code)
{
    return wins [player_code];
}

void win (u8 player_code)
{
    wins[player_code]++;
}
