#ifndef WIZARD_H
#define WIZARD_H

#include <genesis.h>
#include "gfx.h"
#include "controls.h"

Sprite WIZARD_SPR;

void init_player_wizard(int, int);
void wizard_control(Vector2D * v, u16 JOY_NUMBER);

#endif
