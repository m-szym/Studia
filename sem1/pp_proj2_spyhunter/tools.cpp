#include "tools.h"


// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text,SDL_Surface* charset) 
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) 
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) 
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) 
{
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostokπta o d≥ugoúci bokÛw l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,Uint32 outlineColor, Uint32 fillColor) 
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

TextureStruct load_texture(const char* fpath, SDL_Renderer* renderer)
{
	TextureStruct new_texture_struct;
	new_texture_struct.texture = NULL;
	new_texture_struct.height = 0;
	new_texture_struct.width = 0;

	SDL_Surface* loaded_surface = SDL_LoadBMP(fpath);

	new_texture_struct.texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	new_texture_struct.height = loaded_surface->h;
	new_texture_struct.width = loaded_surface->w;

	SDL_FreeSurface(loaded_surface);

	return new_texture_struct;
}

RoadFragmentStruct load_road_fragment(const char* fpath, SDL_Renderer* renderer, int road_width)
{
	RoadFragmentStruct new_road_fragment;
	new_road_fragment.tex_s = load_texture(fpath, renderer);

	new_road_fragment.road_coll_box.x = (LEVEL_WIDTH - road_width) / 2;
	new_road_fragment.road_coll_box.y = 0;

	new_road_fragment.road_coll_box.w = road_width;
	new_road_fragment.road_coll_box.h = new_road_fragment.tex_s.height;

	return new_road_fragment;
}

void render_at_xy(SDL_Renderer* renderer, TextureStruct texture_struct, int x_pos, int y_pos)
{
	SDL_Rect target;
	target.x = x_pos;
	target.y = y_pos;
	target.h = texture_struct.height;
	target.w = texture_struct.width;
	SDL_RenderCopy(renderer, texture_struct.texture, NULL, &target);
}

void render_at_xy_r(SDL_Renderer* renderer, TextureStruct texture_struct, int x_pos, int y_pos, SDL_Rect* clip)
{
	SDL_Rect a = { x_pos, y_pos, texture_struct.width, texture_struct.height };

	if (clip != NULL)
	{
		a.w = clip->w;
		a.h = clip->h;
	}

	SDL_RenderCopy(renderer, texture_struct.texture, clip, &a);
}




int check_collision(SDL_Rect obj1, SDL_Rect obj2)
{
	if (obj1.x >= obj2.x + obj2.w)
		return FALSE;
	if (obj1.x + obj1.w <= obj2.x)
		return FALSE;
	if (obj1.y >= obj2.y + obj2.h)
		return FALSE;
	if (obj1.y + obj1.h <= obj2.y)
		return FALSE;
	return TRUE;
}

int check_collision_x(SDL_Rect obj1, SDL_Rect obj2)
{
	if (obj1.x >= obj2.x + obj2.w)
		return FALSE;
	if (obj1.x + obj1.w <= obj2.x)
		return FALSE;
	return TRUE;
}

int check_collision_y(SDL_Rect obj1, SDL_Rect obj2)
{
	if (obj1.y >= obj2.y + obj2.h)
		return FALSE;
	if (obj1.y + obj1.h <= obj2.y)
		return FALSE;
	return TRUE;
}




void game_setup(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& scrtex, SDL_Surface*& screen)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("PP2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Marek SzymaÒski 193229");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	// wy≥πczenie widocznoúci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);
}






void load_road_fragments(RoadFragmentStruct rf_list[], SDL_Renderer* renderer)
{
	rf_list[0] = load_road_fragment("graphics/tile-100.bmp", renderer, 100);
	rf_list[1] = load_road_fragment("graphics/tile-150.bmp", renderer, 150);
	rf_list[2] = load_road_fragment("graphics/tile-200.bmp", renderer, 200);
	rf_list[3] = load_road_fragment("graphics/tile-250.bmp", renderer, 250);
	rf_list[4] = load_road_fragment("graphics/tile-300.bmp", renderer, 300);
}

void load_graphics(SDL_Renderer* renderer, RoadFragmentStruct rf_list[], TextureStruct& ui, SDL_Surface*&charset, TextureStruct &enemy_tex_s, TextureStruct &neutral_tex_s)
{
	ui = load_texture("graphics/ui2.bmp", renderer);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("graphics/cs8x8.bmp");
	SDL_SetColorKey(charset, true, 0x000000);

	load_road_fragments(rf_list, renderer);

	neutral_tex_s = load_texture("graphics/neutral_car.bmp", renderer);
	enemy_tex_s = load_texture("graphics/enemy_car.bmp", renderer);
}

void load_colors(int colors[], SDL_Surface* screen)
{
	colors[0] = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	colors[1] = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	colors[2] = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	colors[3] = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
}

void update_clock(int& t1, int& t2, double& delta, double& worldTime)
{
	t2 = SDL_GetTicks();
	delta = (t2 - t1) * 0.001;
	t1 = t2;
	worldTime += delta;
}

