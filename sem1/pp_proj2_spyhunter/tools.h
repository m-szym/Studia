#pragma once

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#include<stdio.h>

#include "config.h"

struct Toolbox
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
};

struct TextureStruct
{
	SDL_Texture* texture;
	int height;
	int width;
};

struct RoadFragmentStruct
{
	TextureStruct tex_s;
	SDL_Rect road_coll_box;
};



TextureStruct load_texture(const char* fpath, SDL_Renderer* renderer);

RoadFragmentStruct load_road_fragment(const char* fpath, SDL_Renderer* renderer, int road_x_offset);

void render_at_xy(SDL_Renderer* renderer, TextureStruct texture_struct, int x_pos, int y_pos);

void render_at_xy_r(SDL_Renderer* renderer, TextureStruct texture_struct, int x_pos, int y_pos, SDL_Rect* clip);

int check_collision(SDL_Rect obj1, SDL_Rect obj2);

int check_collision_x(SDL_Rect obj1, SDL_Rect obj2);

int check_collision_y(SDL_Rect obj1, SDL_Rect obj2);



void game_setup(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &scrtex, SDL_Surface* &screen);

void load_road_fragments(RoadFragmentStruct rf_list[], SDL_Renderer* renderer);

void load_graphics(SDL_Renderer* renderer, RoadFragmentStruct rf_list[], TextureStruct& ui, SDL_Surface*& charset, TextureStruct &enemy_tex_s, TextureStruct &neutral_tex_s);

void load_colors(int colors[], SDL_Surface* screen);

void update_clock(int& t1, int& t2, double& delta, double& worldTime);




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
// rysowanie pojedynczego pixela

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹dŸ poziomie (gdy dx = 1, dy = 0)

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
