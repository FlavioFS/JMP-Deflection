#ifndef CONTROLS_H
#define CONTROLS_H

#include "vector_utils.h"

void renderPlayers	( Vector2D p1_pos, Vector2D p2_pos	 );
void joyAtkHandler	( u16 joy, u16 joyChanged, u16 state );
u8 directionalInput	( Vector2D * p1, Vector2D * p2 );

#endif
