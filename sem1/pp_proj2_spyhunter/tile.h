#pragma once


#include "tools.h"
#include "config.h"
#include <stdlib.h>

extern "C" 
{
	#include"./SDL2-2.0.10/include/SDL.h"
	#include"./SDL2-2.0.10/include/SDL_main.h"
}

struct TileStruct
{
	//int type;

	SDL_Rect tile_coll_box;

	TextureStruct* tex_s;

	int x_pos;
	int y_pos;

	SDL_Rect road_coll_box;
};


void render_tile(SDL_Renderer* renderer, TileStruct tile);	//old

void render_tile_r(SDL_Renderer* renderer, TileStruct tile, SDL_Rect camera);


int collides_with_tile(TileStruct tile, SDL_Rect obj);

int collides_with_tile_road(TileStruct tile, SDL_Rect obj);


void update_tile_coll_box(TileStruct& tile);

void update_tile_road_coll_box(TileStruct& tile);

void update_tile_colls(TileStruct& tile);	//obydwie nad t¹ w jednej


void reload_tile(TileStruct& tile, RoadFragmentStruct fragment);

void init_tiles(TileStruct tiles[], RoadFragmentStruct road_fragments[]);

void nullify(TileStruct** onscreen);

void environment(TileStruct tiles[], TileStruct* onscreen[], RoadFragmentStruct road_fragments[], SDL_Rect camera);

void render_road(TileStruct* onscreen[], SDL_Renderer* renderer, SDL_Rect camera);


