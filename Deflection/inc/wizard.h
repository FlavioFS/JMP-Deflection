#ifndef WIZARD_H
#define WIZARD_H

#include <genesis.h>
#include "sprites/wizard_res.h"

Sprite wizard_sprite;
int move_speed = 1;

void init_player_wizard(int, int);

void control_wizard();

#endif
