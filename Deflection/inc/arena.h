#ifndef ARENA_H
#define ARENA_H

// Player dimensions 16x16
#define AR_PL_MIN_X 130
#define AR_PL_MIN_Y 145
#define AR_PL_MAX_X 420
#define AR_PL_MAX_Y 318

// Ball dimensions: 8x8
#define AR_BALL_MIN_X 137
#define AR_BALL_MIN_Y 161
#define AR_BALL_MAX_X 433
#define AR_BALL_MAX_Y 334

void load_tileset();
void draw_arena();
void draw_obstacle(unsigned int x,unsigned int y, unsigned int w, unsigned int h);

#endif
