#include "character_list.h"

/* Character data:
 * 1. KNIGHT
 * 2. WIZARD
 */
u8  base_hp      [CHARACTER_LIST_SIZE] = {5, 4};
u8  speed        [CHARACTER_LIST_SIZE] = {1, 1.1};
u16 cooldown     [CHARACTER_LIST_SIZE] = {300, 250};
u8  d_power      [CHARACTER_LIST_SIZE] = {1, 1.2};	// The ball becomes even faster after a successful hit
u16 atk_duration [CHARACTER_LIST_SIZE];
SpriteDefinition character_sprites [CHARACTER_LIST_SIZE];


/** Base HP          */ u8 CHL_hp   (u8 character_code) { return base_hp[character_code];  }
/** Move Speed       */ u8 CHL_spd  (u8 character_code) { return speed[character_code];    }
/** Attack Cooldown  */ u8 CHL_cd   (u8 character_code) { return cooldown[character_code]; }
/** Deflection Power */ u8 CHL_dPwr (u8 character_code) { return d_power[character_code];  }

/** Chosen Sprite    */
SpriteDefinition * CHL_chSprite (u8 character_code)
{
	return &character_sprites[character_code];
}

void CHL_initCharacterList()
{
	character_sprites[KNIGHT_CODE] = spr_knight_def;
	character_sprites[WIZARD_CODE] = spr_wizard_def;

	atk_duration[KNIGHT_CODE] = RESCOMP_TIME_TO_TICKS * spr_knight_def.animations[ANIM_ATK_R]->length;
	atk_duration[WIZARD_CODE] = RESCOMP_TIME_TO_TICKS * spr_wizard_def.animations[ANIM_ATK_R]->length;
}
