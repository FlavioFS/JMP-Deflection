#ifndef CONTROLS_H
#define CONTROLS_H

#include "vector_utils.h"
#include "character.h"
#include "player.h"

//void renderPlayers		( Vector2D p1_pos, Vector2D p2_pos	 );
// void joyAtkHandler     ( u16 joy, u16 joy_changed, u16 state );
//void directionalInput	( Vector2D * p1, Vector2D * p2 );

void control_character ( Character * c, u16 joy_id );
void control_char ( Sprite * sprite, u8 player_code, u16 joy_id );

#endif
