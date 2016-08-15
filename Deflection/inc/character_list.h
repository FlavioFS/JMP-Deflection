#ifndef _CHARACTER_LIST_H_
#define _CHARACTER_LIST_H_

#include <genesis.h>
#include "gfx.h"
#include "animations.h"

#define CHARACTER_LIST_SIZE 2

#define KNIGHT_CODE 0
#define WIZARD_CODE 1

// This definition must be the same value of TIME in RESCOMP for sprites of characters
#define SQRT2DOT(x) (1.414 * x)

extern u8    base_hp      [CHARACTER_LIST_SIZE];
extern float d_power      [CHARACTER_LIST_SIZE];
extern u32   cooldown     [CHARACTER_LIST_SIZE];
extern u32   atk_duration [CHARACTER_LIST_SIZE];
extern float diag_speed   [CHARACTER_LIST_SIZE];
extern float speed        [CHARACTER_LIST_SIZE];
extern SpriteDefinition character_sprites [CHARACTER_LIST_SIZE];

u16 status_preview [CHARACTER_LIST_SIZE][4];

u8    CHL_hp   (u8 character_code);
float CHL_dPwr (u8 character_code);
u32   CHL_cd   (u8 character_code);
u32   CHL_atkD (u8 character_code);
float CHL_dSpd (u8 character_code);
float CHL_spd  (u8 character_code);
SpriteDefinition * CHL_chSprite (u8 character_code);

u16 hp_preview     (u8 character_code);
u16 mspd_preview   (u8 character_code);
u16 dpower_preview (u8 character_code);
u16 delay_preview  (u8 character_code);

void CHL_initCharacterList();

#endif // _CHARACTER_LIST_H_
