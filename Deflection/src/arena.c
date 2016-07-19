#include <genesis.h>
#include "arena.h"
#include "tilesets/arena1_tileset.h"

void draw_obstacle(unsigned int x,unsigned int y, unsigned int w, unsigned int h);

void load_tileset()
{
	// load the tiles
	VDP_loadBMPTileData(tileset_arena_one.image,// the image itself
						TILE_USERINDEX,   		// initial index for loaded tiles
						tileset_arena_one.w/8,	// width of the tileset img
						tileset_arena_one.h/8,	// height of tileset
						tileset_arena_one.w/8);	// width in tiles it can differ (?)
	
	// load the tileset palette
	VDP_setPalette (PAL3 ,tileset_arena_one.palette->data);
}

void draw_arena()
{
	load_tileset();
	
	// lets draw !
	// ground 
	VDP_fillTileMapRect(VDP_PLAN_B,
						TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX+5),
						0, 0,
						40, 28);
						
	// the screen 'forehead'
	VDP_fillTileMapRect(VDP_PLAN_B,
						TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX),
						0, 0,
						40, 3);

	// top wall
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX+2),
					192, 40);
	// bottom wall
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,1,0,TILE_USERINDEX+2),
					1728, 40);
					
	// side walls
	short int i;
	for ( i=3; i<28; i++ )
	{
		// left
		VDP_fillTileMap(VDP_PLAN_B,
						TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX+3),
						i*64, 1);
		// right
		VDP_fillTileMap(VDP_PLAN_B,
						TILE_ATTR_FULL(PAL3,0,0,1,TILE_USERINDEX+3),
						i*64+39, 1);
	}
						
	// corners
	// top-left
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX+1),
					192, 1);
	// top-right
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,1,TILE_USERINDEX+1),
					231, 1);
	// bottom-left
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,1,0,TILE_USERINDEX+1),
					1728, 1);
	// bottom-right
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,1,1,TILE_USERINDEX+1),
					1767, 1);
					
	// draw some obstacles
	draw_obstacle ( 5, 5, 3, 3 );
	draw_obstacle ( 30, 15, 3, 3 );
}

// draw a rectangle
// x and y are relative to top-left corner of the arena
void draw_obstacle(unsigned int x,unsigned int y, unsigned int w, unsigned int h)
{
	if ( w < 2 || h < 2 )
		return;
	
	unsigned int real_x = x+1;
	unsigned int real_y = y+4;
	
	VDP_fillTileMapRect(VDP_PLAN_B,
						TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX),
						real_x, real_y,
						w, h);
						
	// top wall
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,1,0,TILE_USERINDEX+2),
					64*real_y + real_x, w);
	// bottom wall
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX+2),
					64*(real_y + h-1) + real_x, w);
					
	unsigned short int i;
	for (i=0; i<h; i++)
	{
		// left wall
		VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,1,TILE_USERINDEX+3),
					64*(real_y + i) + real_x, 1);
					
		// right wall
		VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX+3),
					64*(real_y + i) + real_x + w-1, 1);
	}
	
	// corners	
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,0,TILE_USERINDEX+4),
					64*real_y + real_x, 1);
	
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,0,1,TILE_USERINDEX+4),
					64*real_y + real_x + w-1, 1);
					
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,1,0,TILE_USERINDEX+4),
					64*(real_y + h-1) + real_x, 1);
					
	VDP_fillTileMap(VDP_PLAN_B,
					TILE_ATTR_FULL(PAL3,0,1,1,TILE_USERINDEX+4),
					64*(real_y + h-1) + real_x + w-1, 1);
}
