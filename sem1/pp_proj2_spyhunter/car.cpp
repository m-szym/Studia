#include "car.h"



CarStruct init_car(SDL_Renderer* renderer, const char* fpath, int x_pos, int y_pos, int x_vel, int y_vel)
{
	CarStruct new_car;

	new_car.tex_s = load_texture(fpath, renderer);

	new_car.x_vel = x_vel;
	new_car.y_vel = y_vel;

	new_car.x_pos = x_pos;
	new_car.y_pos = y_pos;

	new_car.coll_box.x = new_car.x_pos;
	new_car.coll_box.y = new_car.y_pos;
	new_car.coll_box.h = new_car.tex_s.height;
	new_car.coll_box.w = new_car.tex_s.width;

	return new_car;
}

CarStruct init_player_car(SDL_Renderer* renderer)
{
	return init_car(renderer, PLAYER_CAR_FPATH, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PLAYER_X_VEL, PLAYER_Y_VEL);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

NPC init_npc(SDL_Renderer* renderer, const char* fpath, int x_pos, int y_pos, int x_vel, int y_vel, int health)
{
	NPC new_npc;
	new_npc.car = init_car(renderer, fpath, x_pos, y_pos, x_vel, y_vel);

	new_npc.hp = health;

	new_npc.move_x.dir = 0;
	new_npc.move_x.frames = 0;

	new_npc.special_move = 0;

	return new_npc;
}

Player init_player(SDL_Renderer* renderer, int health)
{
	Player new_player;

	new_player.car = init_player_car(renderer);

	new_player.hp = health;
	new_player.lives = PLAYER_LIVES;

	new_player.points = 0;
	new_player.points_locked = 0;

	new_player.car.x_pos = SCREEN_WIDTH / 2;
	new_player.car.y_pos = LEVEL_HEIGHT - TILE_HEIGHT / 2 - 2 * TILE_HEIGHT;

	update_car_coll_box(new_player.car);

	new_player.weapon.type = PLAYER_NORMAL_WEAPON;
	new_player.weapon.ammo = 0;
	new_player.weapon.dmg = PLAYER_NORMAL_BULLET_DMG;

	return new_player;
}


void render_car(SDL_Renderer* renderer, CarStruct &car)	//old
{
	render_at_xy(renderer, car.tex_s, car.x_pos, car.y_pos);
}

void render_car_r(SDL_Renderer* renderer, CarStruct& car, SDL_Rect camera)
{
	render_at_xy_r(renderer, car.tex_s, car.x_pos - camera.x, car.y_pos - camera.y, NULL);
}


void move_car_to_xy(CarStruct &car, int x_pos, int y_pos)
{
	car.x_pos += x_pos;
	if (car.x_pos < 0 || car.x_pos + car.tex_s.width > SCREEN_WIDTH)
	{
		car.x_pos -= x_pos;
	}
	car.coll_box.x = car.x_pos;

	car.y_pos += y_pos;
	if (car.y_pos < 0 || car.y_pos + car.tex_s.height > SCREEN_HEIGHT)
	{
		car.y_pos -= y_pos;
	}
	car.coll_box.y = car.y_pos;
}

void move_car_by_vel(CarStruct &car, int x_dir, int y_dir, SDL_Rect wall)
{
	car.x_pos += x_dir * car.x_vel;
	if (car.x_pos < 0 || car.x_pos + car.tex_s.width > SCREEN_WIDTH)
	{
		car.x_pos -= x_dir * car.x_vel;		
	}
	car.coll_box.x = car.x_pos;

	car.y_pos += y_dir* car.y_vel;
	if (car.y_pos < 0 || car.y_pos + car.tex_s.height > SCREEN_HEIGHT)
	{
		car.y_pos -= y_dir * car.y_vel;
	}
	car.coll_box.y = car.y_pos;
}

void move_car_by_vel_r(CarStruct& car, int x_dir, int y_dir)
{
	car.x_pos += x_dir * car.x_vel;	
	if (car.x_pos < 100 || car.x_pos + car.tex_s.width > 500)
	{
		car.x_pos -= x_dir * car.x_vel;
	}
	car.coll_box.x = car.x_pos;

	car.y_pos += y_dir * car.y_vel;	
	if (car.y_pos < 0 || car.y_pos + car.tex_s.height > LEVEL_HEIGHT)
	{
		car.y_pos -= y_dir * car.y_vel;
	}
	car.coll_box.y = car.y_pos;
}

void move_car_vertically(CarStruct &car)
{
	car.y_pos += car.y_vel;
	if (car.y_pos < 0 || car.y_pos + car.tex_s.height > SCREEN_HEIGHT)
	{
		car.y_pos -= car.y_vel;	
	}
	car.coll_box.y = car.y_pos;
}

void move_car_horizontally(CarStruct &car)
{
	car.x_pos += car.x_vel;
	if (car.x_pos < 0 || car.x_pos + car.tex_s.width > SCREEN_WIDTH)
	{
		car.x_pos -= car.x_vel;
	}
	car.coll_box.x = car.x_pos;
}


void normal_move_car(CarStruct& car)
{
	car.x_pos += car.x_vel;
	if (car.x_pos < 0 || car.x_pos + car.tex_s.width > LEVEL_WIDTH)
	{
		car.x_pos -= car.x_vel;
	}
	car.coll_box.x = car.x_pos;

	car.y_pos +=  car.y_vel;
	if (car.y_pos < 0 || car.y_pos + car.tex_s.height > LEVEL_HEIGHT)
	{
		car.y_pos -= car.y_vel;
	}
	car.coll_box.y = car.y_pos;
}



void move_car_on_road(CarStruct& car, TileStruct* onscreeen[], SDL_Rect camera, int dir)
{
	int tile_cols = 0;
	SDL_Rect a;


	if (onscreeen[0] != NULL)
	{
		a = { car.x_pos + car.tex_s.width * dir, car.y_pos, car.tex_s.width, car.tex_s.height };
		if (collides_with_tile_road(*onscreeen[0], a) == TRUE)
		//if (car.x_pos + car.x_vel * dir >= onscreeen[0]->road_coll_box.x &&
		//	car.x_pos + car.tex_s.width + car.x_vel * dir <= onscreeen[0]->road_coll_box.x + onscreeen[0]->road_coll_box.w)
		{
			tile_cols++;
			/*car.x_pos += dir * car.x_vel;
			car.coll_box.x = car.x_pos;
			return;*/
		}
	}

	if (onscreeen[1] != NULL)
	{
		a = { car.x_pos + car.tex_s.width * dir, car.y_pos, car.tex_s.width, car.tex_s.height };
		if (collides_with_tile_road(*onscreeen[1], a) == TRUE)
		//if (car.x_pos + car.x_vel * dir >= onscreeen[1]->road_coll_box.x &&
		//	car.x_pos + car.tex_s.width + car.x_vel * dir <= onscreeen[1]->road_coll_box.x + onscreeen[1]->road_coll_box.w)
		{
			tile_cols++;
			//car.x_pos += dir * car.x_vel;
			//car.coll_box.x = car.x_pos;
			//return;
		}
	}


	if (tile_cols > 0)
	{
		car.x_pos += dir * car.x_vel;
		car.coll_box.x = car.x_pos;
	}
}
//lepiej dzia³a z check_collision() - powrót na drogê, ale pewnie bardziej obci¹¿a

void set_random_move(NPC& npc)
// 2 : 1 : 1 dla stop : lewo : prawo
{
	int r = rand() % 4;
	int frames = ((rand() % 5) + 1) * 7;
	int dir = 0;

	if (r == 0 || r == 1)
		dir = 0;
	else if (r == 2)
		dir = -1;
	else if (r == 3)
		dir = 1;

	update_move(npc, dir, frames);

}

MoveStruct set_move(int dir, int frames)
{
	MoveStruct new_move;
	new_move.dir = dir;
	new_move.frames = frames;
	return new_move;
}

void update_move(NPC& npc, int dir, int frames)
{
	npc.move_x.dir = dir;
	npc.move_x.frames = frames;
}




int cars_collide(CarStruct car1, CarStruct car2)
{
	return check_collision(car1.coll_box, car2.coll_box);
}



int push_car_x(CarStruct& moving_car, CarStruct& stationary_car, int moving_car_dir)
{
	if (check_collision(moving_car.coll_box, stationary_car.coll_box) == TRUE)
	{
		stationary_car.x_pos += moving_car_dir * moving_car.x_vel / 2;	//super twardy ruch
		stationary_car.coll_box.x = stationary_car.x_pos;
		return TRUE;
	}
	return FALSE;
}

void slow_push_car_x(CarStruct& moving_car, CarStruct& stationary_car, int moving_car_dir)
{
	if (push_car_x(moving_car, stationary_car, moving_car_dir) == TRUE)
	{
		moving_car.x_pos -= moving_car_dir * moving_car.x_vel / 2;
		moving_car.coll_box.x = moving_car.x_pos;
	}
}


//NPC
void wrap_spawn_npc(NPC npcs[], int player_y_pos, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s)
{
	for (int i = 0; i < MAX_CARS_ON_SCREEEN; i++)
	{
		if (npcs[i].hp <= 0)
		{
			spawn(npcs[i], player_y_pos, enemy_tex_s, neutral_tex_s);
			break;
		}

	}
}

void spawn(NPC& blank_npc, int player_y_pos, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s)
{
	int type = rand() % ENEMY_SPAWN_CHANCE;
	
	if (type == 0)
	{
		blank_npc.car.tex_s = enemy_tex_s;
		blank_npc.hp = ENEMY_NORMAL_HP;
		blank_npc.type = ENEMY_SYMBOL;
	}
	else
	{
		blank_npc.car.tex_s = neutral_tex_s;
		blank_npc.hp = NEUTRAL_HP;
		blank_npc.type = NEUTRAL_SYMBOL;
	}

	int x_dir = rand() % 2;
	if (x_dir == 0) x_dir = -1;
	else if (x_dir == 1) x_dir = 0;
	else if (x_dir == 2) x_dir = 1;

	if (x_dir == 0)
		blank_npc.car.y_pos = player_y_pos + -1 * (((rand() % 20) + 5) * 10);
	else
		blank_npc.car.y_pos = player_y_pos + -1 * (((rand() % 30) + 0) * 10);

	blank_npc.car.x_pos = LEVEL_WIDTH / 2 - blank_npc.car.tex_s.width / 2 + x_dir * (((rand() % 15) + 5) * 10);

	

	update_car_coll_box(blank_npc.car);
}

void kill_npc(NPC& npc, Player &player, int &npcs_num)
{
	npc.hp = 0;
	npc.car.x_pos = 2 * LEVEL_WIDTH;
	npc.car.y_pos = LEVEL_HEIGHT + LEVEL_WIDTH;
	update_car_coll_box(npc.car);

	if (npc.type == ENEMY_SYMBOL && player.points_locked <= 0)
		player.points += ENEMY_SCORE;
	else if (npc.type == NEUTRAL_SYMBOL)
		player.points_locked = NEUTRAL_KILL_LOCK_POINTS_TIME;//do zmiany
	npcs_num--;
}



int car_is_on_road(TileStruct* tiles_on_screen[], CarStruct car)
{
	if (tiles_on_screen[0] != NULL)
	{
		if (collides_with_tile(*tiles_on_screen[0], car.coll_box) == TRUE)
		{
			if (collides_with_tile_road(*tiles_on_screen[0], car.coll_box) == TRUE)
			{
				return TRUE;
			}
		}
	}

	if (tiles_on_screen[1] != NULL)
	{
		if (collides_with_tile(*tiles_on_screen[1], car.coll_box) == TRUE)
		{
			if (collides_with_tile_road(*tiles_on_screen[1], car.coll_box) == TRUE)
			{
				return TRUE;
			}
		}
	}

	return FALSE;

}

int car_is_in_killzone(TileStruct* tiles_on_screen[], CarStruct car)
{
	if (tiles_on_screen[0] != NULL)
	{
		if (collides_with_tile(*tiles_on_screen[0], car.coll_box) == TRUE)
		{
			if (car.x_pos < tiles_on_screen[0]->road_coll_box.x - POBOCZE  || 
				car.x_pos + car.tex_s.width > tiles_on_screen[0]->road_coll_box.x + tiles_on_screen[0]->road_coll_box.w + POBOCZE )
			{
				return TRUE;
			}
		}
	}

	if (tiles_on_screen[1] != NULL)
	{
		if (collides_with_tile(*tiles_on_screen[1], car.coll_box) == TRUE)
		{
			if (car.x_pos < tiles_on_screen[1]->road_coll_box.x - POBOCZE  ||
				car.x_pos + car.tex_s.width > tiles_on_screen[1]->road_coll_box.x + tiles_on_screen[1]->road_coll_box.w + POBOCZE )
			{
				return TRUE;
			}
		}
	}

	return FALSE;

}

//reset
void reset(Player& player, TileStruct tiles[], NPC npcs[], SDL_Rect& camera, RoadFragmentStruct road_fragments[], 
			double& worldTime, int& npcs_num, int& tile_n, int& tile_y_pos)
{
	player.car.x_pos = SCREEN_WIDTH / 2;
	player.car.y_pos = LEVEL_HEIGHT - 480 - 2 * 960;
	player.hp = PLAYER_HP;
	player.points_locked = 0;
	player.lives = PLAYER_LIVES;
	player.points = 0;
	player.weapon.type = PLAYER_NORMAL_WEAPON;
	player.weapon.dmg = PLAYER_NORMAL_BULLET_DMG;
	player.weapon.ammo = 0;
	update_car_coll_box(player.car);

	camera.y = ((player.car.y_pos + player.car.tex_s.height / 2) - SCREEN_HEIGHT / 2) - 100;

	for (int i = 0; i < MAX_CARS_ON_SCREEEN; i++)
	{
		npcs[i].hp = 0;
		npcs[i].move_x.dir = 0;
		npcs[i].move_x.frames = 0;
		npcs[i].special_move = 0;
	}

	for (int i = 0; i < TILES_N; i++)
	{
		tiles[i].y_pos = LEVEL_HEIGHT - ((TILE_HEIGHT / 2) + (i * TILE_HEIGHT));
		reload_tile(tiles[i], road_fragments[4 - i]);
		update_tile_coll_box(tiles[i]);
		update_tile_road_coll_box(tiles[i]);
	}


	worldTime = 0;
	npcs_num = 0;
	tile_n = 0;
	tile_y_pos = 0;
}


void update_car_coll_box(CarStruct& car)
{
	car.coll_box.x = car.x_pos;
	car.coll_box.y = car.y_pos;
}



//~AI
void ai_main(NPC& npc, TileStruct* tiles_on_screen[], Player &player, int &npcs_num)
{
	
	//1. jeœli poza drog¹ - powrót (nadpisuje aktualny ruch)
	if (car_is_on_road(tiles_on_screen, npc.car) == FALSE)
	{
		if ((abs(	(player.car.x_pos + (player.car.tex_s.width / 2)) - (npc.car.x_pos + (npc.car.tex_s.width / 2))	) 
					< 1.5 * ((player.car.tex_s.width + npc.car.tex_s.width) / 2) &&
			(check_collision_y(player.car.coll_box, npc.car.coll_box) == TRUE)))
		{
			kill_npc(npc, player, npcs_num);
			
		}
		else
		{
			if (npc.special_move == 0)
			{
				int temp = out_of_road_dir(tiles_on_screen, npc.car);
				int dir = 0;

				if (temp > 0) dir = -1;
				else if (temp < 0) dir = 1;
				else dir = 0;

				int frames = (abs(temp) / npc.car.x_vel) + 1;
				update_move(npc, dir, frames);
				npc.special_move = 1;

				return;
			}
		}
	}

	//2. jeœli obok gracza (mniej / wiêcej ta sama wysokoœæ) - szar¿a
	if (npc.type == ENEMY_SYMBOL)
	{
		if (npc.move_x.frames <= 0)
		{
			int r = rand() % 100;
			if (r == 0)
			{
				if ((npc.car.y_pos <= player.car.y_pos && npc.car.y_pos + npc.car.tex_s.height >= player.car.y_pos) ||
					(npc.car.y_pos >= player.car.y_pos && npc.car.y_pos <= player.car.y_pos + player.car.tex_s.height))
				{
					int dir = 0;
					int frames = (abs(npc.car.x_pos + npc.car.tex_s.width/2 - player.car.x_pos + player.car.tex_s.width/2) / npc.car.x_vel);

					if (npc.car.x_pos < player.car.x_pos) dir = 1;
					else if (npc.car.x_pos > player.car.x_pos) dir = -1;

					update_move(npc, dir, frames + 10);

					return;
				}
			}
		}
	}

	////m. wyjœcie lub nowy, losowy ruch
	if (npc.move_x.frames <= 0)
	{
		set_random_move(npc);
		return;
	}
}


Missile init_missile(SDL_Renderer* renderer, CarStruct origin_car, int x_dir, int y_dir, int dmg, char shooter, int type)
{
	Missile new_missile;

	if (shooter == PLAYER_SYMBOL)
	{
		if (type == PLAYER_NORMAL_WEAPON)
		{
				new_missile.bullet = init_car(renderer, PLAYER_NORMAL_BULLET_FPATH,
					origin_car.x_pos + (origin_car.tex_s.width / 2),
					origin_car.y_pos - PLAYER_NORMAL_BULLET_Y_VEL,
					PLAYER_NORMAL_BULLET_X_VEL, PLAYER_NORMAL_BULLET_Y_VEL);
		}
		else if (type == PLAYER_SPECIAL_WEAPON)
		{
			new_missile.bullet = init_car(renderer, PLAYER_SPECIAL_BULLET_FPATH,
				origin_car.x_pos + (origin_car.tex_s.width / 2),
				origin_car.y_pos - PLAYER_SPECIAL_BULLET_Y_VEL,
				PLAYER_SPECIAL_BULLET_X_VEL, PLAYER_SPECIAL_BULLET_Y_VEL);
		}
			
	}
	else if (shooter == ENEMY_SYMBOL)
	{
		if (type == 0)
		{
			if (y_dir == -1)
			{
				new_missile.bullet = init_car(renderer, ENEMY_NORMAL_BULLET_FPATH,
					origin_car.x_pos + (origin_car.tex_s.width / 2),
					origin_car.y_pos - ENEMY_NORMAL_BULLET_Y_VEL,
					ENEMY_NORMAL_BULLET_X_VEL, ENEMY_NORMAL_BULLET_Y_VEL);
			}
		}
	}

	new_missile.dmg = dmg;

	new_missile.shot_by = shooter;

	new_missile.x_dir = x_dir;
	new_missile.y_dir = y_dir;

	update_car_coll_box(new_missile.bullet);
	
	return new_missile;
}



// Inicjalizuje listê o g³owie "head".
void init_list(list_t* head) 
{
	head->next = NULL;
}


void add_new_missile_at_beginning(list_t* list_start, SDL_Renderer* renderer, CarStruct origin_car, int x_dir, int y_dir, 
									int dmg, char shooter, int type)
{
	list_t* new_el = (list_t*)malloc(sizeof(list_t));

	new_el->missile = init_missile(renderer, origin_car, x_dir, y_dir, dmg, shooter, type);
	new_el->next = list_start->next;
	list_start->next = new_el;
}

void shoot(list_t* list_start, SDL_Renderer* renderer, Player &player)
{
	if (player.weapon.type != PLAYER_NORMAL_WEAPON)
	{
		if (player.weapon.ammo > 0)
		{
			if (player.weapon.type == PLAYER_SPECIAL_WEAPON)
			{
				add_new_missile_at_beginning(list_start, renderer, player.car, -1, -1, player.weapon.dmg, PLAYER_SYMBOL, player.weapon.type);
				add_new_missile_at_beginning(list_start, renderer, player.car, 1, -1, player.weapon.dmg, PLAYER_SYMBOL, player.weapon.type);
			}
			player.weapon.ammo--;
		}
		else
		{
			load_normal_weapon(player);
		}
		return;
	}	

	//zwyk³y strza³ - w ostatecznoœci
	add_new_missile_at_beginning(list_start, renderer, player.car, 0, -1, player.weapon.dmg, PLAYER_SYMBOL, player.weapon.type);

}


// Usuwa element bêd¹cy nastêpnikiem elementu "l".
void remove_after(list_t* list_el)
{
	if (list_el->next != NULL) {
		void* el_to_remove = list_el->next;
		list_el->next = list_el->next->next;
		free(el_to_remove);
	}
};




void missiles_main(list_t* cursor, SDL_Rect camera, Player& player, NPC* npcs, int &npcs_num)
{
	//cursor = cursor->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.
	while (cursor != NULL && cursor->next != NULL)
	{
		cursor->next->missile.bullet.y_pos -= player.car.y_vel;
		update_car_coll_box(cursor->next->missile.bullet);
		
		move_car_by_vel_r(cursor->next->missile.bullet, cursor->next->missile.x_dir, cursor->next->missile.y_dir);

		if (check_collision(cursor->next->missile.bullet.coll_box, camera) == FALSE)
		{	
			SDL_DestroyTexture(cursor->next->missile.bullet.tex_s.texture);
			remove_after(cursor);//end
		}
		else
		{
			if (cursor->next->missile.shot_by == ENEMY_SYMBOL)
			{
				if (check_collision(cursor->next->missile.bullet.coll_box, player.car.coll_box) == TRUE)
				{
					player.hp -= cursor->next->missile.dmg;
					SDL_DestroyTexture(cursor->next->missile.bullet.tex_s.texture);
					remove_after(cursor);
				}
			}
			else if (cursor->next->missile.shot_by == PLAYER_SYMBOL)
			{
				for (int i = 0; i < MAX_CARS_ON_SCREEEN; i++)
				{
					if (npcs[i].hp > 0)
					{
						if (check_collision(cursor->next->missile.bullet.coll_box, npcs[i].car.coll_box) == TRUE)
						{
							npcs[i].hp -= cursor->next->missile.dmg;
							if (npcs[i].hp <= 0)
							{
								kill_npc(npcs[i], player, npcs_num);
							}
							SDL_DestroyTexture(cursor->next->missile.bullet.tex_s.texture);
							remove_after(cursor);
							i = MAX_CARS_ON_SCREEEN;	//¿eby zakoñczyæ fora - czy break nie wyszed³by z while ? (raczej nie)
						}
					}
				}
			}
		}


		cursor = cursor->next;
	}
}

void render_missiles(SDL_Renderer* renderer, list_t* list_start, SDL_Rect camera)
{
	list_start = list_start->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.
	while (list_start != NULL )
	{
		render_car_r(renderer, list_start->missile.bullet, camera);
		list_start = list_start->next;
	}
}

void load_normal_weapon(Player &player)
{
	player.weapon.type = PLAYER_NORMAL_WEAPON;
	player.weapon.ammo = 0;
	player.weapon.dmg = PLAYER_NORMAL_BULLET_DMG;
}

PowerUp init_powerup(SDL_Renderer* renderer)
{
	PowerUp new_powerup;

	new_powerup = init_car(renderer, POWERUP1_ICON_FPATH, SCREEN_WIDTH + 100, 0, 0, 0);

	return new_powerup;
}

void place_powerup(PowerUp &powerup, int player_y_pos)
{
	int x_dir = (rand() % 3) - 1;

	powerup.x_pos = SCREEN_WIDTH / 2 + x_dir * (((rand() % 5) + 5) * 10);
	powerup.y_pos = player_y_pos - (((rand() % 15) + 10) * 10);

	update_car_coll_box(powerup);
}

void remove_powerup(PowerUp& powerup)
{
	powerup.x_pos = SCREEN_WIDTH + 100;
	update_car_coll_box(powerup);
}

void give_powerup(PowerUp powerup, Player& player)
{
	player.weapon.type = PLAYER_SPECIAL_WEAPON;
	player.weapon.dmg = PLAYER_SPECIAL_BULLET_DMG;
	player.weapon.ammo = PLAYER_SPECIAL_AMMO;
}

void powerup_f(PowerUp &powerup, Player &player, SDL_Rect camera)
{
	if (powerup.x_pos > SCREEN_WIDTH)
	{
		int r = rand() % POWERUP_CHANCE;
		if (r == 0)
		{
			place_powerup(powerup, player.car.y_pos);
			//printf("\t++++\n");
			return;
		}
	}

	if (powerup.x_pos > SCREEN_WIDTH)
	{
		if (check_collision(powerup.coll_box, camera) == FALSE)
		{
			remove_powerup(powerup);
			//printf("\t-----\n");
			return;
		}
	}

	if (check_collision(powerup.coll_box, player.car.coll_box) == TRUE)
	{
		give_powerup(powerup, player);
		remove_powerup(powerup);
		//printf("\t=====\n");
		return;
	}
}


void render_powerup(SDL_Renderer* renderer, PowerUp powerup, SDL_Rect camera)
{
	render_car_r(renderer, powerup, camera);
}

int out_of_road_dir(TileStruct* tiles_on_screen[], CarStruct car)
{
	if (tiles_on_screen[0] != NULL)
	{
		if (collides_with_tile(*tiles_on_screen[0], car.coll_box) == TRUE)
		{
			if (car.x_pos < tiles_on_screen[0]->road_coll_box.x )
				return -1 * (tiles_on_screen[0]->road_coll_box.x - car.x_pos);
				//return -1;
			else if (car.x_pos + car.tex_s.width > tiles_on_screen[0]->road_coll_box.x + tiles_on_screen[0]->road_coll_box.w )
				//return 1;
				return 1 * ((car.x_pos + car.tex_s.width) - (tiles_on_screen[0]->road_coll_box.x + tiles_on_screen[0]->road_coll_box.w));
		}
	}

	if (tiles_on_screen[1] != NULL)
	{
		if (collides_with_tile(*tiles_on_screen[1], car.coll_box) == TRUE)
		{
			if (car.x_pos < tiles_on_screen[1]->road_coll_box.x )
				//return -1;
				return -1 * (tiles_on_screen[1]->road_coll_box.x  - car.x_pos);
			else if (car.x_pos + car.tex_s.width > tiles_on_screen[1]->road_coll_box.x + tiles_on_screen[1]->road_coll_box.w )
				//return 1;
				return 1 * ((car.x_pos + car.tex_s.width) - (tiles_on_screen[1]->road_coll_box.x + tiles_on_screen[1]->road_coll_box.w ));
		}
	}

	//na zapas, ale nie powinno nigdy siê wydarzyæ - funkcja wywo³ywana jest gdy auto na pewno jest poza drog¹, wiêc jeden z ifów bêdzie spe³niony
	return -5;
}



void init_npcs(SDL_Renderer* renderer, NPC npcs[])
{
	for (int i = 0; i < MAX_CARS_ON_SCREEEN; i++)
	{
		npcs[i] = init_npc(renderer, NEUTRAL_CAR_FPATH, 0, 0, NEUTRAL_X_VEL, NEUTRAL_Y_VEL, 0);
	}
}

void init_game(SDL_Renderer* renderer, NPC npcs[], Player &player, SDL_Rect &camera, TileStruct tiles[], RoadFragmentStruct road_fragments[])
{
	player = init_player(renderer, PLAYER_HP);

	init_npcs(renderer, npcs);

	camera.x = 0;
	camera.y = ((player.car.y_pos + player.car.tex_s.height / 2) - SCREEN_HEIGHT / 2) - 120;
	camera.h = SCREEN_HEIGHT;
	camera.w = SCREEN_WIDTH;

	//init_tiles(tiles, road_fragments);
}



void free_memory(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer, RoadFragmentStruct road_fragments[], TextureStruct &ui, NPC npcs[], Player &player, list_t* missiles)
{
	SDL_FreeSurface(screen);
	SDL_FreeSurface(charset);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	for (int i = 0; i < ROAD_FRAGMENTS_N; i++)
	{
		SDL_DestroyTexture(road_fragments->tex_s.texture);
	}
	SDL_DestroyTexture(ui.texture);
	for (int i = 0; i < MAX_CARS_ON_SCREEEN; i++)
	{
		SDL_DestroyTexture(npcs[i].car.tex_s.texture);
	}
	SDL_DestroyTexture(player.car.tex_s.texture);
	missiles = missiles->next; // Pomijamy wartoœæ nieokreœlon¹ w g³owie.
	if (missiles != NULL)
	{
		while (missiles->next != NULL)
		{
			SDL_DestroyTexture(missiles->next->missile.bullet.tex_s.texture);
			remove_after(missiles);
		}
	}
}

void player_f(Player &player, int move_attempt, TileStruct* onscreen[], double worldTime, int &quit, double &points_interval)
{
	move_car_by_vel_r(player.car, move_attempt, -1);
	if (player.hp <= 0)
	{
		if (worldTime > GRACE_PERIOD_S)
		{
			player.lives--;
			if (player.lives <= 0)
			{
				quit = 1;
				return;//?czy nie zepsuje czegoœ?
			}
			else
				player.hp = PLAYER_HP;
		}
		else
			player.hp = PLAYER_HP;
	}

	if (car_is_on_road(onscreen, player.car) == TRUE)
	{
		if (player.points_locked > 0)
			player.points_locked--;
		else
		{
			player.points += POINTS_PER_FRAME;
			points_interval += POINTS_PER_FRAME;
			
			if (points_interval >= LIVES_POINTS_INTERVAL)
			{
				player.lives++;
				points_interval = 0;
			}
		}
	}
	else
	{
		if (car_is_in_killzone(onscreen, player.car) == TRUE)
		{
			if (worldTime > GRACE_PERIOD_S)
			{
				player.lives--;
				if (player.lives <= 0)
				{
					quit = 1;
					return;//?czy nie zepsuje czegoœ?
				}
				else
				{
					player.car.x_pos = SCREEN_WIDTH / 2 - player.car.tex_s.width / 2;
					player.hp = PLAYER_HP;
				}
			}
			else
				player.hp = PLAYER_HP;
		}
	}
}

void npc_f(NPC npcs[], Player& player, TileStruct* onscreen[], int& npcs_num, int move_attempt, SDL_Rect camera, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s)
{
	int r = rand() % NPC_SPAWN_CHANCE;
	if ((r == 0) && (npcs_num < MAX_CARS_ON_SCREEEN))
	{
		wrap_spawn_npc(npcs, player.car.y_pos, enemy_tex_s, neutral_tex_s);
		npcs_num++;
	}

	for (int i = 0; i < MAX_CARS_ON_SCREEEN; i++)
	{
		

		if (npcs[i].hp > 0)
		{
			ai_main(npcs[i], onscreen, player, npcs_num);

			move_car_by_vel_r(npcs[i].car, 0, -1);	//standardowy ruch do góry

			slow_push_car_x(player.car, npcs[i].car, move_attempt);

			if (npcs[i].hp > 0)
			{

				if (npcs[i].move_x.frames > 0)
				{
					if (npcs[i].move_x.dir != 0)
					{
						if (npcs[i].special_move == 0)
							move_car_on_road(npcs[i].car, onscreen, camera, npcs[i].move_x.dir);
						else if (npcs[i].special_move == 1)
							move_car_by_vel_r(npcs[i].car, npcs[i].move_x.dir, 0);

						slow_push_car_x(npcs[i].car, player.car, npcs[i].move_x.dir);

					}
					npcs[i].move_x.frames--;
					if (npcs[i].special_move == 1)
					{
						if (npcs[i].move_x.frames <= 0)
						{
							npcs[i].special_move = 0;
						}
					}
				}
			}
		}
	}

};

void render_npcs(SDL_Renderer* renderer, SDL_Rect camera, NPC npcs[])
{
	for (int i = 0; i < MAX_CARS_ON_SCREEEN; i++)
	{
		if (npcs[i].hp > 0)
		{
			render_car_r(renderer, npcs[i].car, camera);
		}
	}
}


void render_screen(SDL_Renderer* renderer, SDL_Rect camera, NPC npcs[], Player player, TileStruct* onscreen[], SDL_Texture* scrtex, SDL_Surface* screen, list_t* missiles, TextureStruct ui, double worldTime, SDL_Surface* charset, int colors[], PowerUp powerup)
{
	char text[128];

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);

	DrawRectangle(screen, 500, 10, 100, 50, colors[BLACK], colors[BLACK]);
	sprintf(text, "Points: %.0lf", player.points);
	DrawString(screen, 500, 10, text, charset);
	sprintf(text, "Time: %.3lf", worldTime);
	DrawString(screen, 500, 18, text, charset);
	sprintf(text, "D:%dF:%dS:%d", npcs[0].move_x.dir, npcs[0].move_x.frames, npcs[0].special_move);
	DrawString(screen, 500, 28, text, charset);

	DrawRectangle(screen, 0, 10, 100, 50, colors[BLACK], colors[BLACK]);
	sprintf(text, "Lives:%d", player.lives);
	DrawString(screen, 0, 10, text, charset);
	sprintf(text, "X:%dY:%d", camera.x, camera.y);
	DrawString(screen, 0, 18, text, charset);

	render_road(onscreen, renderer, camera);

	render_npcs(renderer, camera, npcs);

	

	render_car_r(renderer, player.car, camera);

	render_missiles(renderer, missiles, camera);

	if (powerup.x_pos < SCREEN_WIDTH)
	{
		render_powerup(renderer, powerup, camera);
		//printf("R");
	}

	render_at_xy_r(renderer, ui, 0, 0, NULL);
	SDL_RenderPresent(renderer);

}


void logic(NPC npcs[], Player& player, TileStruct* onscreen[], int& npcs_num, int move_attempt, SDL_Rect camera, list_t* missiles, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s, double worldTime, int& quit, double& points_interval, PowerUp& powerup)
{
	//power-up'y
	powerup_f(powerup, player, camera);
	//printf("X:%d Y:%d\n", powerup.x_pos, powerup.y_pos);

	//logika gracza
	player_f(player, move_attempt, onscreen, worldTime, quit, points_interval);

	//logika npc
	npc_f(npcs, player, onscreen, npcs_num, move_attempt, camera, enemy_tex_s, neutral_tex_s);

	//logika pocisków
	missiles_main(missiles, camera, player, npcs, npcs_num);
}



void kill_player(Player player, double worldTime, int &quit)
{
	quit = 1;
}

void render_endgame_screen(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[], double worldTime, Player player, int play_again)
{
	char text[128];

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);

	DrawRectangle(screen, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, colors[BLACK], colors[BLACK]);
	sprintf(text, "Game ended");
	DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 - 20, text, charset);
	sprintf(text, "Your points: %.0lf", player.points);
	DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 - 10, text, charset);
	sprintf(text, "Your time: %.3lf", worldTime);
	DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 , text, charset);
	if (play_again == TRUE)
		sprintf(text, "Press N to play again or ESC to close game");
	else 
		sprintf(text, "Press ESC to close game");
	DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 + 10, text, charset);
	


	SDL_RenderPresent(renderer);
}

int game_end_restart(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[], double worldTime, Player player, SDL_Event event, int play_again)
{
	int quit = 0;
	int cont = FALSE;
	while (!quit)
	{
		render_endgame_screen(renderer, charset, screen, scrtex, colors, worldTime, player, play_again);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = 1;
					cont = FALSE;
				}
				else if (event.key.keysym.sym == SDLK_n)
				{
					if (play_again == TRUE)
					{
						quit = 1;
						cont = TRUE;
					}
				}
				break;
			case SDL_KEYUP:
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
	}
	return cont;
}


void render_startgame_screen(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[])
{
	char text[128];

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);

	TextureStruct start_screen = load_texture(START_SCREEN_FPATH, renderer);
	render_at_xy_r(renderer, start_screen, 0, 0, NULL);
	SDL_DestroyTexture(start_screen.texture);

	SDL_RenderPresent(renderer);
}
void start_game_v(SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[], SDL_Event event)
{
	int quit = 0;
	while (!quit)
	{
		render_startgame_screen(renderer, charset, screen, scrtex, colors);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_RETURN)
					quit = 1;
				break;
			case SDL_KEYUP:
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
	}
}

void event_loop(NPC npcs[], Player& player, TileStruct* onscreen[], int& npcs_num, int &move_attempt, SDL_Rect &camera, list_t* missiles, TextureStruct enemy_tex_s, TextureStruct neutral_tex_s, double &worldTime, int& quit, double& points_interval, PowerUp& powerup, SDL_Event &event, int &esc, TileStruct tiles[], RoadFragmentStruct road_fragments[], int &tile_n, int &tile_y_pos, int &stop, SDL_Renderer* renderer, SDL_Surface* charset, SDL_Surface* screen, SDL_Texture* scrtex, int colors[])
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = 1;
				esc = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
				move_attempt = 1;
			else if (event.key.keysym.sym == SDLK_LEFT)
				move_attempt = -1;
			else if (event.key.keysym.sym == SDLK_n)
				reset(player, tiles, npcs, camera, road_fragments, worldTime, npcs_num, tile_n, tile_y_pos);
			else if (event.key.keysym.sym == SDLK_p)
			{
				if (stop == 0) stop = 1;
				else stop = 0;
			}
			if (event.key.keysym.sym == SDLK_SPACE)
				shoot(missiles, renderer, player);
			break;
		case SDL_KEYUP:
			move_attempt = 0;
			break;
		case SDL_QUIT:
			quit = 1;
			break;
		};
	};

	if (!stop)
	{
		if (camera.y > 0) camera.y -= player.car.y_vel;
		tile_y_pos += player.car.y_vel;
		if (tile_y_pos >= TILE_HEIGHT)
		{
			tile_y_pos = 0;
			tile_n++;
		}
		nullify(onscreen);
	};

	if (quit)
	{
		if (!esc)
		{
			if (game_end_restart(renderer, charset, screen, scrtex, colors, worldTime, player, event, TRUE) == TRUE)
			{
				reset(player, tiles, npcs, camera, road_fragments, worldTime, npcs_num, tile_n, tile_y_pos);
				quit = 0;
			}
		}
		else
			game_end_restart(renderer, charset, screen, scrtex, colors, worldTime, player, event, FALSE);
	};
}
