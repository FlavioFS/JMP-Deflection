#ifndef CONTROLS_H
#define CONTROLS_H

#include <genesis.h>
#include "vector_utils.h"
#include "sprite_definitions.h"
#include "character_definitions.h"

// Character-specific behavior
s16 knightDirectionalInput (Vector2D * player, u16 JOYPAD);
s16 wizardDirectionalInput (Vector2D * player, u16 JOYPAD);

// General purpose input handler
s16 directionalInput ( Vector2D * player, CharacterSpeeds speeds, u16 JOYPAD );

#endif
