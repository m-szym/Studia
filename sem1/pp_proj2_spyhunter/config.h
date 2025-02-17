#pragma once

#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	480

#define LEVEL_WIDTH 600
#define LEVEL_HEIGHT 19200000


#define PLAYER_X_VEL 6
#define PLAYER_Y_VEL 5

#define NEUTRAL_X_VEL 6
#define NEUTRAL_Y_VEL 5

#define PLAYER_HP 10
#define PLAYER_LIVES 3
#define LIVES_POINTS_INTERVAL 250
#define NEUTRAL_HP 10
#define ENEMY_NORMAL_HP 10

#define TRUE 1
#define FALSE 0

#define POBOCZE 10

//œcie¿ki do plików
#define PLAYER_CAR_FPATH "graphics/car.bmp"
#define NEUTRAL_CAR_FPATH "graphics/neutral_car.bmp"
#define ENEMY_CAR_FPATH "graphics/enemy_car.bmp"
#define POWERUP1_ICON_FPATH "graphics/powerup1_icon.bmp"


#define START_SCREEN_FPATH "graphics/start_screen.bmp"

#define PLAYER_NORMAL_BULLET_FPATH "graphics/normal_bullet_player.bmp"
#define PLAYER_NORMAL_WEAPON 10
#define PLAYER_NORMAL_BULLET_DMG 5
#define PLAYER_NORMAL_BULLET_X_VEL 0
#define PLAYER_NORMAL_BULLET_Y_VEL 6

#define PLAYER_SPECIAL_BULLET_FPATH "graphics/special_bullet_player.bmp"
#define PLAYER_SPECIAL_WEAPON 11
#define PLAYER_SPECIAL_AMMO 20
#define PLAYER_SPECIAL_BULLET_DMG 10
#define PLAYER_SPECIAL_BULLET_X_VEL 2
#define PLAYER_SPECIAL_BULLET_Y_VEL 6

#define ENEMY_NORMAL_BULLET_FPATH "graphics/normal_bullet_enemy.bmp"
#define ENEMY_NORMAL_BULLET_DMG 1
#define ENEMY_NORMAL_BULLET_X_VEL 0
#define ENEMY_NORMAL_BULLET_Y_VEL 3

#define TILES_N 3	//do zamieniaj¹cych siê tileów
#define TILE_HEIGHT 960

#define MAX_CARS_ON_SCREEEN 5

#define POINTS_PER_FRAME 0.5

#define TILE_OFFSET 100

#define COLORS_N 4
#define BLACK 0
#define GREEN 1
#define RED 2
#define BLUE 3

#define ROAD_FRAGMENTS_N 5

#define ENEMY_SCORE 25

#define NPC_SPAWN_CHANCE 500
#define ENEMY_SPAWN_CHANCE 3

#define PLAYER_SYMBOL 'P'
#define ENEMY_SYMBOL 'E'
#define NEUTRAL_SYMBOL 'N'


#define GRACE_PERIOD_S 10
#define NEUTRAL_KILL_LOCK_POINTS_TIME 300

#define POWERUP_CHANCE 10000
