#include "hitbox.h"
#include <genesis.h>

Hitbox * new_hitbox (Vector2D pos, fix32 w, fix32 h)
{
    Hitbox * hb  = (Hitbox*)MEM_alloc(sizeof(Hitbox));
    hb->position = pos;
    hb->w        = w;
    hb->h        = h;

    return hb;
}

u16 detect_collision(Hitbox * a, Hitbox * b)
{
    //
}

void set_hitbox_position(Hitbox * hb, Vector2D new_pos)
{
    //
}
