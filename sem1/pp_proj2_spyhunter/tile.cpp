#include "tile.h"

void render_tile(SDL_Renderer* renderer, TileStruct tile)	//old
{
	render_at_xy_r(renderer, *tile.tex_s, tile.x_pos, tile.y_pos, NULL);
}	 

void render_tile_r(SDL_Renderer* renderer, TileStruct tile, SDL_Rect camera)
{
	render_at_xy_r(renderer, *tile.tex_s, tile.x_pos - camera.x, tile.y_pos - camera.y, NULL);
}


int collides_with_tile(TileStruct tile, SDL_Rect obj)
{
	return check_collision(obj, tile.tile_coll_box);
}

int collides_with_tile_road(TileStruct tile, SDL_Rect obj)
{
	return check_collision(obj, tile.road_coll_box);
}


void update_tile_coll_box(TileStruct& tile)
{
	//tile.tile_coll_box.x = tile.x_pos;
	tile.tile_coll_box.y = tile.y_pos;
}

void update_tile_road_coll_box(TileStruct& tile)
{
	//tile.road_coll_box.x = tile.x_pos;
	tile.road_coll_box.y = tile.y_pos;
}

void update_tile_colls(TileStruct& tile)
{
	tile.tile_coll_box.y = tile.y_pos;
	tile.road_coll_box.y = tile.y_pos;
}


void reload_tile(TileStruct& tile, RoadFragmentStruct fragment)
{
	tile.tex_s = &(fragment.tex_s);
	tile.road_coll_box = fragment.road_coll_box;
}


void init_tiles(TileStruct tiles[], RoadFragmentStruct road_fragments[])
{
	for (int j = 0; j < TILES_N; j++)
	{
		tiles[j].x_pos = 100;
		tiles[j].tile_coll_box = { 100, 0, 400, 960 };
		tiles[j].y_pos = LEVEL_HEIGHT - ((TILE_HEIGHT / 2) + (j * TILE_HEIGHT));
		reload_tile(tiles[j], road_fragments[4 - j]);
		update_tile_coll_box(tiles[j]);
		update_tile_road_coll_box(tiles[j]);
	}
}

void nullify(TileStruct** onscreen)
{
	onscreen[0] = NULL;
	onscreen[1] = NULL;
}


void environment(TileStruct tiles[], TileStruct* onscreen[], RoadFragmentStruct road_fragments[], SDL_Rect camera)
{
	int r = -1;
	for (int i = 0; i < TILES_N; i++)
	{
		if (collides_with_tile(tiles[i], camera))
		{
			if (onscreen[0] == NULL)
				onscreen[0] = &(tiles[i]);
			else if (onscreen[1] == NULL)
				onscreen[1] = &(tiles[i]);

		}
		else if (tiles[i].y_pos >= camera.y)
		{
			tiles[i].y_pos -= TILES_N * TILE_HEIGHT;
			update_tile_coll_box(tiles[i]);

			r = rand() % 5;
			if (r == 0)
				reload_tile(tiles[i], road_fragments[0]);
			else if (r == 1)
				reload_tile(tiles[i], road_fragments[1]);
			else if (r == 2)
				reload_tile(tiles[i], road_fragments[2]);
			else if (r == 3)
				reload_tile(tiles[i], road_fragments[3]);
			else if (r == 4)
				reload_tile(tiles[i], road_fragments[4]);

			update_tile_road_coll_box(tiles[i]);
		}

	}
}

void render_road(TileStruct* onscreen[], SDL_Renderer* renderer, SDL_Rect camera)
{
	if (onscreen[0] != NULL)
	{
		render_tile_r(renderer, *onscreen[0], camera);
	}
	if (onscreen[1] != NULL)
	{
		render_tile_r(renderer, *onscreen[1], camera);
	}
}