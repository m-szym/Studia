#pragma once

#include "tools.h"
#include "config.h"
#include "tile.h"


#include <stdlib.h>
#include <string.h>

extern "C" 
{
	#include"./SDL2-2.0.10/include/SDL.h"
	#include"./SDL2-2.0.10/include/SDL_main.h"
}

struct CarStruct
{
	TextureStruct tex_s;

	int x_vel;
	int y_vel;

	int x_pos;
	int y_pos;

	SDL_Rect coll_box;
};



struct MoveStruct
{
	int dir;
	int frames;
};

struct NPC
{
	CarStruct car;

	int hp;

	MoveStruct move_x;

	int special_move;

	char type;
};


struct Weapon
{
	int type;
	int ammo;
	int dmg;
};

struct Player
{
	CarStruct car;

	int hp;
	double points;
	int points_locked;
	int lives;

	Weapon weapon;
};

typedef CarStruct BulletStruct;
typedef CarStruct PowerUp;

struct Missile
{
	BulletStruct bullet;
	char shot_by;
	int dmg;

	int x_dir;
	int y_dir;
};


CarStruct init_car(SDL_Renderer* renderer, const char* fpath, int x_pos, int y_pos, int x_vel, int y_vel);

CarStruct init_player_car(SDL_Renderer* renderer);


NPC init_npc(SDL_Renderer* renderer, const char* fpath, int x_pos, int y_pos, int x_vel, int y_vel, int health);

Player init_player(SDL_Renderer* renderer, int health);


void render_car(SDL_Renderer* renderer, CarStruct &car);	//old

void render_car_r(SDL_Renderer* renderer, CarStruct& car, SDL_Rect camera);


void move_car_to_xy(CarStruct &car, int x_pos, int y_pos);

void move_car_by_vel(CarStruct& car, int x_dir, int y_dir, SDL_Rect wall);

void move_car_by_vel_r(CarStruct& car, int x_dir, int y_dir);

void move_car_vertically(CarStruct &car);

void move_car_horizontally(CarStruct &car);


void normal_move_car(CarStruct& car);



void move_car_on_road(CarStruct& car, TileStruct* onscreeen[], SDL_Rect camera, int dx);

void set_random_move(NPC& npc);

MoveStruct set_move(int dir, int frames);

void update_move(NPC& npc, int dir, int frames);

int push_car_x(CarStruct& moving_car, CarStruct& stationary_car, int moving_car_dir);

void slow_push_car_x(CarStruct& moving_car, CarStruct& stationary_car, int moving_car_dir);

void wrap_spawn_npc(NPC npcs[], int player_y_pos, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s);

void spawn(NPC& blank_npc, int player_y_pos, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s);

void kill_npc(NPC& npc, Player &player, int &npcs_num);


int car_is_on_road(TileStruct* tiles_on_screen[], CarStruct car);

int car_is_in_killzone(TileStruct* tiles_on_screen[], CarStruct car);

void reset(Player& player, TileStruct tiles[], NPC npcs[], SDL_Rect& camera, RoadFragmentStruct road_fragments[], 
			double& worldTime, int& npcs_num, int& tile_n, int& tile_y_pos);

void update_car_coll_box(CarStruct& car);


// Typ struktury, opisuj¹cy listê jednokierunkow¹ liczb ca³kowitych.
// G³owa listy ma nieokreœlon¹ wartoœæ pola "value".
typedef struct list
{
	Missile missile;
	struct list* next;
} list_t;

void add_new_missile_at_beginning(list_t* list_start, SDL_Renderer* renderer, CarStruct origin_car, int x_dir, int y_dir, int dmg, char shooter, int type);

void shoot(list_t* list_start, SDL_Renderer* renderer, Player &player);

void remove_after(list_t* list_el);

void missiles_main(list_t* cursor, SDL_Rect camera, Player& player, NPC* npcs, int &npcs_num);

void render_missiles(SDL_Renderer* renderer, list_t* list_start, SDL_Rect camera);

void load_normal_weapon(Player& player);

PowerUp init_powerup(SDL_Renderer* renderer);

void place_powerup(PowerUp& powerup, int player_y_pos);

void remove_powerup(PowerUp& powerup);

void give_powerup(PowerUp powerup, Player& player);

void powerup_f(PowerUp& powerup, Player& player, SDL_Rect camera);

void render_powerup(SDL_Renderer* renderer, PowerUp powerup, SDL_Rect camera);

int out_of_road_dir(TileStruct* tiles_on_screen[], CarStruct car);

void init_game(SDL_Renderer* renderer, NPC npcs[], Player& player, SDL_Rect& camera, TileStruct tiles[], RoadFragmentStruct road_fragments[]);

void free_memory(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer, RoadFragmentStruct road_fragments[], TextureStruct &ui, NPC npcs[], Player &player, list_t* missiles);

void player_f(Player& player, int move_attempt, TileStruct* onscreen[], double worldTime, int& quit, double& points_interval);

void npc_f(NPC npcs[], Player& player, TileStruct* onscreen[], int& npcs_num, int move_attempt, SDL_Rect camera, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s);

void render_npcs(SDL_Renderer* renderer, SDL_Rect camera, NPC npcs[]);

void render_screen(SDL_Renderer* renderer, SDL_Rect camera, NPC npcs[], Player player, TileStruct* onscreen[], SDL_Texture* scrtex, SDL_Surface* screen, list_t* missiles, TextureStruct ui, double worldTime, SDL_Surface* charset, int colors[], PowerUp powerup);

void logic(NPC npcs[], Player& player, TileStruct* onscreen[], int& npcs_num, int move_attempt, SDL_Rect camera, list_t* missiles, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s, double worldTime, int& quit, double& points_interval, PowerUp& powerup);

void render_endgame_screen(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[], double worldTime, Player player, int play_again);

int game_end_restart(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[], double worldTime, Player player, SDL_Event event, int play_again);

void render_startgame_screen(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[]);

void start_game_v(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[], SDL_Event event);

void event_loop(NPC npcs[], Player& player, TileStruct* onscreen[], int& npcs_num, int& move_attempt, SDL_Rect& camera, list_t* missiles, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s, double& worldTime, int& quit, double& points_interval, PowerUp& powerup, SDL_Event& event, int& esc, TileStruct tiles[], RoadFragmentStruct road_fragments[], int& tile_n, int& tile_y_pos, int& stop, SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[]);





void ai_main(NPC& npc, TileStruct* tiles_on_screen[], Player& player, int& npcs_num);


Missile init_missile(SDL_Renderer* renderer, CarStruct origin_car, int x_dir, int y_dir, int dmg, char shooter, int type);

void init_list(list_t* head);
