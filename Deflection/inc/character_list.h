#ifndef _CHARACTER_LIST_H_
#define _CHARACTER_LIST_H_

#include <genesis.h>
#include "gfx.h"

#define CHARACTER_LIST_SIZE 2

#define KNIGHT_CODE 0
#define WIZARD_CODE 1

extern u8  base_hp  [CHARACTER_LIST_SIZE];
extern u8  speed    [CHARACTER_LIST_SIZE];
extern u16 cooldown [CHARACTER_LIST_SIZE];
extern u8  d_power  [CHARACTER_LIST_SIZE];
extern SpriteDefinition character_sprites [CHARACTER_LIST_SIZE];


u8 hp   (u8 character_code);
u8 spd  (u8 character_code);
u8 cd   (u8 character_code);
u8 dpwr (u8 character_code);
SpriteDefinition * ch_sprite (u8 character_code);

void init_character_list();

#endif // _CHARACTER_LIST_H_
