#include "character_list.h"

/* Character data:
 * 1. KNIGHT
 * 2. WIZARD
 */
u8  base_hp  [CHARACTER_LIST_SIZE] = {5, 4};
u8  speed    [CHARACTER_LIST_SIZE] = {1, 1.1};
u16 cooldown [CHARACTER_LIST_SIZE] = {300, 250};
u8  d_power  [CHARACTER_LIST_SIZE] = {1, 1.2};	// The ball becomes even faster after a successful hit
SpriteDefinition character_sprites [CHARACTER_LIST_SIZE];


/** Base HP          */ u8 hp   (u8 character_code) { return base_hp[character_code];  }
/** Move Speed       */ u8 spd  (u8 character_code) { return speed[character_code];    }
/** Attack Cooldown  */ u8 cd   (u8 character_code) { return cooldown[character_code]; }
/** Deflection Power */ u8 dpwr (u8 character_code) { return d_power[character_code];  }

/** Chosen Sprite    */
SpriteDefinition * ch_sprite (u8 character_code)
{
	return &character_sprites[character_code];
}

void init_character_list()
{
	character_sprites[0] = spr_knight_def;
	character_sprites[1] = spr_wizard_def;
}
