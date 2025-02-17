#pragma once

#include "misc.h"
#include <list>
#include <iostream>
//#include "Organism.h"
#include "Map.h"

class Organism;

class World
{
private:

    Organism* human;
    std::list<Organism*> org;

protected:
    Map map;

    friend Organism;

public:
    World(int new_size_x, int new_size_y);

    ~World();


    Organism* get_organism_at_location(XY location);
    Organism* get_organism_at_location(int location_x, int location_y);

    void make_turn();   //tutaj sortowanie
    void roll_initiative();
    void draw_world();

    Map& get_map();


    Organism* add_organism(Organism* new_organism);

    Organism* get_human() const;
    void set_human(Organism* new_human);

    std::list<Organism*> get_orgs();

    void take_input();


};










