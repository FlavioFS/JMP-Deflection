#include "character_list.h"

/* Character data:
 * 1. KNIGHT
 * 2. WIZARD
 */
u8  base_hp      [CHARACTER_LIST_SIZE] = {5, 4};
u8  d_power      [CHARACTER_LIST_SIZE] = {1, 1.2};	// The ball becomes even faster after a successful hit
u32 cooldown     [CHARACTER_LIST_SIZE] = {300, 250};
u32 atk_duration [CHARACTER_LIST_SIZE] = {100, 100 };
s16 diag_speed   [CHARACTER_LIST_SIZE] = {1, 1.1};
s16 speed        [CHARACTER_LIST_SIZE] = {SQRT2DOT(1), SQRT2DOT(1.1)};
SpriteDefinition character_sprites [CHARACTER_LIST_SIZE];


/** Base HP          */  u8 CHL_hp   (u8 character_code) { return base_hp[character_code];      }
/** Deflection Power */  u8 CHL_dPwr (u8 character_code) { return d_power[character_code];      }
/** Attack Cooldown  */ u32 CHL_cd   (u8 character_code) { return cooldown[character_code];     }
/** Atk Duration     */ u32 CHL_atkD (u8 character_code) { return atk_duration[character_code]; }
/** Diagonal Mov Spd */ s16 CHL_dSpd (u8 character_code) { return diag_speed[character_code];   }
/** Linear Mov Spd   */ s16 CHL_spd  (u8 character_code) { return speed[character_code];        }

/** Chosen Sprite    */
SpriteDefinition * CHL_chSprite (u8 character_code)
{
	return &character_sprites[character_code];
}

void CHL_initCharacterList()
{
	character_sprites[KNIGHT_CODE] = spr_knight_def;
	character_sprites[WIZARD_CODE] = spr_wizard_def;
}
