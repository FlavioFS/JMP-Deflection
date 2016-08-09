#ifndef _SCORE_H_
#define _SCORE_H_

#include <genesis.h>
#include "player.h"

extern u16 wins [PLAYER_COUNT];

/**
 * The scoreboard only resets when console shuts down
 */
u16 score (u8 player_code);
void win (u8 player_code);

#endif // _SCORE_H_
