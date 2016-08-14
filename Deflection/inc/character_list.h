#ifndef _CHARACTER_LIST_H_
#define _CHARACTER_LIST_H_

#include <genesis.h>
#include "gfx.h"
#include "animations.h"

#define CHARACTER_LIST_SIZE 2

#define KNIGHT_CODE 0
#define WIZARD_CODE 1

// This definition must be the same value of TIME in RESCOMP for sprites of characters
#define RESCOMP_TIME_TO_TICKS 5
#define SQRT2DOT(x) (1.414 * x)

extern u8  base_hp      [CHARACTER_LIST_SIZE];
extern u8  d_power      [CHARACTER_LIST_SIZE];
extern u16 cooldown     [CHARACTER_LIST_SIZE];
extern u16 atk_duration [CHARACTER_LIST_SIZE];
extern s16 diag_speed   [CHARACTER_LIST_SIZE];
extern s16 speed        [CHARACTER_LIST_SIZE];
extern SpriteDefinition character_sprites [CHARACTER_LIST_SIZE];


u8  CHL_hp   (u8 character_code);
u8  CHL_dPwr (u8 character_code);
u16 CHL_cd   (u8 character_code);
u16 CHL_atkD (u8 character_code);
s16 CHL_dSpd (u8 character_code);
s16 CHL_spd  (u8 character_code);
SpriteDefinition * CHL_chSprite (u8 character_code);

void CHL_initCharacterList();

#endif // _CHARACTER_LIST_H_
