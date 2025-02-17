#pragma once
#include <iostream>
#include <fstream>
#include <list>

#include "conio2.h"

//Main classses
#include "world_organism_map.h"

//Animals
#include "Animals/Human.h"
#include "Animals/Animals_subclasses/Wolf.h"
#include "Animals/Animals_subclasses/Sheep.h"
#include "Animals/Animals_subclasses/Fox.h"
#include "Animals/Animals_subclasses/Antelope.h"
#include "Animals/Animals_subclasses/Turtle.h"

//Plants
#include "Plants/Plants_subclasses/Grass.h"
#include "Plants/Plants_subclasses/Dandellion.h"
#include "Plants/Plants_subclasses/Guarana.h"
#include "Plants/Plants_subclasses/Nightshade.h"
#include "Plants/Plants_subclasses/Pine_Borscht.h"

class Simulator {
private:
	static Simulator* self;
	World* world;
	int turn_number;

	static Simulator* Init_World();
	static Simulator* MainMenu();

	int save_world(World* w);
	static World* load_world();

	void populate_world();
	void spawn_organism(int x, int y, int type);

protected:
	Simulator(int world_size_x, int world_size_y);
	Simulator();
	~Simulator();

public:
	static Simulator* Instance();
	void simulate_world();
	World& getw() { return *(self->world); }
	void add_organism_to_world(Organism* newo) {
		self->world->add_organism(newo);
	}
};

