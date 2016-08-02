#include "hitbox.h"
#include <genesis.h>

Hitbox * hitbox_new (Vector2D pos, fix32 w, fix32 h)
{
    Hitbox * hb = (Hitbox*)MEM_alloc(sizeof(Hitbox));

    hb->position = pos;

    hb->w = w;
    hb->h = h;

    return hb;
}

u16 hitbox_detect_collision (Hitbox * a, Hitbox * b)
{
    if (a->position.x < b->position.x + b->w &&
        a->position.x + a->w > b->position.x &&
        a->position.y < b->position.y + b->h &&
        a->position.y + a->h > b->position.y)
    {
        return 1;
    }

    return 0;
}

void hitbox_set_position (Hitbox * hb, Vector2D new_pos)
{
    hb->position = new_pos;
}

void hitbox_translate (Hitbox * hb, fix32 x, fix32 y)
{
    hb->position.x = fix32Add(hb->position.x, x);
    hb->position.y = fix32Add(hb->position.y, y);
}
