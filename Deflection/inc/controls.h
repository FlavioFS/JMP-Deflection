#ifndef CONTROLS_H
#define CONTROLS_H

#include "vector_utils.h"
#include "character.h"

//void renderPlayers		( Vector2D p1_pos, Vector2D p2_pos	 );
//void joyAtkHandler		( u16 joy, u16 joyChanged, u16 state );
//void directionalInput	( Vector2D * p1, Vector2D * p2 );

void control_character(Character & playable_char, u16 joy_id);

#endif
