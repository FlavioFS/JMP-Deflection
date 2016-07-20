#ifndef KNIGHTY_H
#define KNIGHTY_H

#define KNIGHTY_WALK 0
#define KNIGHTY_IDLE 1

#include <genesis.h>
#include "gfx.h"
#include "controls.h"
// #include "sprites/wizard_res.h"

Sprite KNIGHTY_SPR;
// int KNIGHTY_SPD = 1;

void init_player_knighty(int, int);
void knighty_control(Vector2D * v, u16 JOY_NUMBER, Sprite * target);

#endif
