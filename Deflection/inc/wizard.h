#ifndef WIZARD_H
#define WIZARD_H

#include <genesis.h>
#include "gfx.h"
#include "controls.h"
// #include "sprites/wizard_res.h"

Sprite WIZARD_SPR;
// int WIZARD_SPD = 1;

void init_player_wizard(int, int);
void wizard_control(Vector2D * v, u16 JOY_NUMBER);

#endif
