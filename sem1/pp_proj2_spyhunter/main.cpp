#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include "config.h"
#include "car.h"
#include "tools.h"
#include "tile.h"


#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char* argv[])
{
	int t1 = 0, t2 = 0, quit = 0, i = 0, r = 0, tile_n = 0, tile_y_pos = 0, move_attempt = 0, npcs_num = 0, stop = 0, esc = 0;
	int colors[COLORS_N];
	double delta = 0, worldTime = 0, points_interval = 0;
	SDL_Event event;
	SDL_Surface* screen = NULL, * charset = NULL;
	SDL_Texture* scrtex = NULL;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	RoadFragmentStruct road_fragments[ROAD_FRAGMENTS_N];
	TextureStruct ui, enemy_tex_s, neutral_tex_s;
	SDL_Rect camera;
	NPC npcs[MAX_CARS_ON_SCREEEN];
	Player player;
	TileStruct tiles[TILES_N];
	TileStruct* onscreen[2];
	list_t missiles;
	PowerUp power_up;
	srand(time(0));
	game_setup(window, renderer, scrtex, screen);
	load_graphics(renderer, road_fragments, ui, charset, enemy_tex_s, neutral_tex_s);
	power_up = init_powerup(renderer);
	init_game(renderer, npcs, player, camera, tiles, road_fragments);
	init_tiles(tiles, road_fragments);
	nullify(onscreen);
	init_list(&missiles);
	load_colors(colors, screen);
	t1 = SDL_GetTicks();
	SDL_PollEvent(&event);
	start_game_v(renderer, charset, screen, scrtex, colors, event);
	while (!quit) 
	{
		if (!stop)
		{
			update_clock(t1, t2, delta, worldTime);
			for (i = 0; i < TILES_N; i++)
			{
				if (collides_with_tile(tiles[i], camera))
				{
					if (onscreen[0] == NULL) onscreen[0] = &(tiles[i]);
					else if (onscreen[1] == NULL) onscreen[1] = &(tiles[i]);
				}
				else if (tiles[i].y_pos >= camera.y)
				{
					tiles[i].y_pos -= TILES_N * TILE_HEIGHT;
					update_tile_coll_box(tiles[i]);
					r = rand() % 5;
					if (r == 0)			reload_tile(tiles[i], road_fragments[0]);
					else if (r == 1)	reload_tile(tiles[i], road_fragments[1]);
					else if (r == 2)	reload_tile(tiles[i], road_fragments[2]);
					else if (r == 3)	reload_tile(tiles[i], road_fragments[3]);
					else if (r == 4)	reload_tile(tiles[i], road_fragments[4]);
					update_tile_road_coll_box(tiles[i]);
				}
			}
			logic(npcs, player, onscreen, npcs_num, move_attempt, camera, &missiles, enemy_tex_s, neutral_tex_s, worldTime, quit, points_interval, power_up);
		}

		render_screen(renderer, camera, npcs, player, onscreen, scrtex, screen, &missiles, ui, worldTime, charset, colors, power_up);

		event_loop(npcs, player, onscreen, npcs_num, move_attempt, camera, &missiles, enemy_tex_s, neutral_tex_s, worldTime, quit, points_interval, power_up, event, esc, tiles, road_fragments, tile_n, tile_y_pos, stop, renderer, charset, screen, scrtex, colors);
	};
	free_memory(screen, charset, scrtex, window, renderer, road_fragments, ui, npcs, player, &missiles);
	SDL_Quit();
	return 0;
}
