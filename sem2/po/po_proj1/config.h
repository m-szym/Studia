#pragma once

const int ADJACENT_SQUARES = 4;
const bool CAN_STAY_IN_PLACE = false;

//-------Controls------
const int HUMAN_SKILL_KEY = 0x0d;
const int EXIT_KEY = 0x71;
const int SAVE_WORLD_KEY = 0x73;


//-------Animals------

//base animal
const int BASE_ANIMAL_STRENGTH = 0;
const int BASE_ANIMAL_INITIATIVE = 10;
const int BASE_ANIMAL_SPEED = 1;

//Sheep
const int SHEEP_STRENGTH = 4;
const int SHEEP_INITIATIVE = 4;
const int SHEEP_SPEED = BASE_ANIMAL_SPEED;
const char SHEEP_SYMBOL = 'S';

//Wolf
const int WOLF_STRENGTH = 9;
const int WOLF_INITIATIVE = 5;
const int WOLF_SPEED = BASE_ANIMAL_SPEED;
const char WOLF_SYMBOL = 'W';

//Fox
const int FOX_STRENGTH = 3;
const int FOX_INITIATIVE = 7;
const int FOX_SPEED = BASE_ANIMAL_SPEED;
const char FOX_SYMBOL = 'F';

//Antelope
const int ANTELOPE_STRENGTH = 4;
const int ANTELOPE_INITIATIVE = 4;
const int ANTELOPE_SPEED = 2;
const char ANTELOPE_SYMBOL = 'A';
const int ANTELOPE_ESCAPE_CHANCE_BASE = 10;
const int ANTELOPE_ESCAPE_THRESHOLD = 0;

//Turtle
const int TURTLE_STRENGTH = 2;
const int TURTLE_INITIATIVE = 1;
const int TURTLE_SPEED = BASE_ANIMAL_SPEED;
const char TURTLE_SYMBOL = 'T';
const int TURTLE_MOVEMENT_CHANCE_BASE = 4;
const int TURTLE_MOVEMENT_THRESHOLD = 3;
const int TURTLE_DEFENSE = 5;


//Human
const int HUMAN_STRENGTH = 50;
const int HUMAN_INITIATIVE = 4;
const int HUMAN_SPEED = BASE_ANIMAL_SPEED;
const char HUMAN_SYMBOL = 'H';
const int HUMAN_SKILL_COOLDOWN = 5;
const int HUMAN_SKILL_DURATION = 5;


//------Plants--------

//base plant
const int SEEDING_CHANCE_BASE = 50;
const int BASE_PLANT_SEEDING_THRESHOLD = 47;
const int BASE_PLANT_STRENGTH = 0;
const int BASE_PLANT_INITIATIVE = 0;


//Grass
const char GRASS_SYMBOL = 'g';
const int GRASS_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
const int GRASS_STRENGTH = BASE_PLANT_STRENGTH;
const int GRASS_INITIATIVE = BASE_PLANT_INITIATIVE;

//Dandellion
const char DANDELLION_SYMBOL = 'd';
const int DANDELLION_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
const int DANDELLION_SEEDING_ATTEMPTS_PER_TURN = 3;
const int DANDELLION_STRENGTH = BASE_PLANT_STRENGTH;
const int DANDELLION_INITIATIVE = BASE_PLANT_INITIATIVE;

//Guarana
const char GUARANA_SYMBOL = 'r';
const int GUARANA_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
const int GUARANA_STRENGTH = BASE_PLANT_STRENGTH;
const int GUARANA_INITIATIVE = BASE_PLANT_INITIATIVE;
const int GUARANA_STRENGHT_BONUS = 3;

//nightshade - wilcze jagody
const char NIGHTSHADE_SYMBOL = 'n';
const int NIGHTSHADE_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
const int NIGHTSHADE_STRENGTH = 99;
const int NIGHTSHADE_INITIATIVE = BASE_PLANT_INITIATIVE;

//pine borscht
const char PINE_BORSCHT_SYMBOL = 'b';
const int PINE_BORSCHT_SEEDING_THRESHOLD = BASE_PLANT_SEEDING_THRESHOLD;
const int PINE_BORSCHT_STRENGTH = 10;
const int PINE_BORSCHT_INITIATIVE = BASE_PLANT_INITIATIVE;