#ifndef HITBOX_H
#define HITBOX_H

#include "vector_utils.h"

typedef struct hitbox
{
    Vector2D position;
    fix32    w, h;
} Hitbox;

Hitbox * new_hitbox (Vector2D pos, fix32 w, fix32 h);

u16 detect_collision(Hitbox * a, Hitbox * b);

void set_hitbox_position(Hitbox * hb, Vector2D new_pos);

#endif
