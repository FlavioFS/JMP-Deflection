#ifndef HITBOX_H
#define HITBOX_H

#include "vector_utils.h"

typedef struct hitbox
{
    Vector2D position;
    fix32    w, h;
} Hitbox;

Hitbox * hitbox_new (Vector2D pos, fix32 w, fix32 h);

u16 hitbox_detect_collision (Hitbox * a, Hitbox * b);

void hitbox_set_position (Hitbox * hb, Vector2D new_pos);

void hitbox_translate (Hitbox * hb, fix32 x, fix32 y);

void draw_hitbox(Hitbox * hb, u16 pal);

#endif
