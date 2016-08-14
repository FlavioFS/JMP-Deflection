#ifndef ARENA_H
#define ARENA_H

#define AR_MIN_X 130
#define AR_MIN_Y 145
#define AR_MAX_X 420
#define AR_MAX_Y 318

void load_tileset();
void draw_arena();
void draw_obstacle(unsigned int x,unsigned int y, unsigned int w, unsigned int h);

#endif
