#pragma once
#include "config.h"

const int DIRECTIONS_N = ADJACENT_SQUARES + (int) CAN_STAY_IN_PLACE;

const int DIR_NULL = 0;
const int DIR_UP = 1;
const int DIR_DOWN = 2;
const int DIR_LEFT = 3;
const int DIR_RIGHT = 4;

const int NULL_MARKER = 0;
const int DEAD_MARKER = -1;

#include <string>
//info messages
const std::string SPAWN_MESSAGE = "appears on map";
const std::string DEATH_MESSAGE = "dies";
const std::string MOVEMENT_MESSAGE = "moves to";
const std::string ATTACK_MESSAGE = "attacks ";
const std::string ATTACK_SUCCES_MESSAGE = "attacked succesfully";
const std::string ATTACK_FAILURE_MESSAGE = "defended itself";
const std::string MATING_MESSAGE = "mates with";
const std::string FLEE_MESSAGE = "flees from danger";
const std::string DANGERSENSE_MESSAGE = "senses danger";
const std::string LAZY_MESSAGE = "stays in place";
const std::string ATTACK_REFLECT_MESSAGE = "reflects attack";
const std::string PLANT_IDLE_MESSAGE = "grows";
const std::string SEEDING_MESSAGE = "seeds new ";

// Key codes for reading player input
const int KEY_Q = 0x71;				// "q" key code
const int KEY_N = 0x6e;				// "n" key code
const int KEY_L = 0x6c;				// "l" key code
const int KEY_S = 0x73;				// "s" key code
const int KEY_I = 0x69;				// "i" key code
const int KEY_ENTER = 0x0d;			// "enter" key code
const int KEY_ESC = 0x1b;			// "esc" key code
const int KEY_F = 0x66;				// "f" key code
const int KEY_R = 0x72;				// "r" key code
const int KEY_Y = 0x79;				// "y" key code
const int KEY_E = 0x65;				// "e" key code

const int KEY_0_UP = 0x48;			// "up arrow" key code
const int KEY_0_DOWN = 0x50;		// "down arrow" key code
const int KEY_0_LEFT = 0x4b;		// "left arrow" key code
const int KEY_0_RIGHT = 0x4d;		// "right arrow" key code

const int KEY_0 = 0x30;				// "0" key code
const int KEY_1 = 0x31;				// "1" key code
const int KEY_2 = 0x32;				// "2" key code
const int KEY_3 = 0x33;				// "3" key code
const int KEY_4 = 0x34;				// "4" key code
const int KEY_5 = 0x35;				// "5" key code
const int KEY_6 = 0x36;				// "6" key code
const int KEY_7 = 0x37;				// "7" key code
const int KEY_8 = 0x38;				// "8" key code
const int KEY_9 = 0x39;				// "9" key code


const int ORGANISM_TYPES = 10;


const int LOAD_ID_BUFFER = 9999999;
