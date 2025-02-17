//
// Created by M Sz on 06/04/2023.
//
#pragma once
#ifndef PROG_OB_P1_WORLD_ORGANISM_MAP_H

#include <list>
#include <string>
#include <iostream>

#include "misc.h"
#include "config.h"
#include "constants.h"
#include "conio2.h"


class World;

struct MinOrganism {
    int x;
    int y;
    int strength;
    char symbol;
    int id;
};

class Organism
{
private:
    int strength;
    int initiative;
    XY map_location;
    char symbol;


    int marker;
    int id;                   
    static int organisms_counter;   
    World& world;

public:
    Organism(int new_strength, int new_initiative, XY new_map_location, char new_symbol, World& new_world);
    Organism(int new_strength, int new_initiative, int new_x, int new_y, char new_symbol, World& new_world);

    virtual ~Organism();

    virtual void action() = 0;
    virtual void collision(Organism* invading_organism) = 0;   

    virtual void control(int command);
    void update_location(XY new_location);   
    void kill_self();  

    void draw();
    void log(std::string info);
    virtual std::string login();

    MinOrganism minify();

    bool is_plant();
    static bool is_plant(Organism* target);
    

    int get_id() const;
    int get_strength() const;
    int get_initiative() const;
    XY get_location();
    int get_x() const;
    int get_y() const;
    char get_symbol() const;
    World& get_world();
    int get_marker() const;

    void set_strength(int new_strength);
    void set_initiative(int new_initiative);
    void set_location(XY new_location);
    void set_x(int new_x);
    void set_y(int new_y);
    void set_symbol(char new_symbol);
    void set_world(World& new_world);
    void set_marker(int new_marker);
    void set_id(int new_id);
};

struct OrganismComparator
{
    bool operator ()(const Organism* organism1, const Organism* organism2)
    {
        if (organism1 != nullptr && organism2 != nullptr)
        {
            if (organism1->get_initiative() == organism2->get_initiative())
                return organism1->get_id() < organism2->get_id();

            return organism1->get_initiative() > organism2->get_initiative();
        }

        return false;
    }
};
////////////////////////////////////////////////////////////////////////////


class Map {
private:
    Organism*** map;
    int size_x;
    int size_y;

public:
    Map(int map_size_x, int map_size_y);

    ~Map();

    int get_size_x() const;
    int get_size_y() const;
    Organism*** get_internal_map() const;

    bool is_out_of_map(XY location) const;
    bool is_out_of_map(int x, int y) const;
    bool would_be_out_of_map(XY location, int speed, int direction) const;
    bool would_be_out_of_map(int x, int y, int speed, int direction) const;

    Organism* place_object(XY location, Organism* object);
    Organism* move_object(XY location, Organism* object);
    Organism* lift_object_from_location(XY location);
    Organism* get_object(XY location);

    Organism* get_neighbour(XY location, int direction);

    void draw() const;
};
////////////////////////////////////////////////////////////////////////////

class World
{
private:

    Organism* human;
    std::list<Organism*> organisms_list;

protected:
    friend Organism;

    Map map;

public:
    World(int new_size_x, int new_size_y);

    ~World();
 
    void make_turn();   
    void update_initiative_order();
    void draw_world();
    void take_input();
    Organism* add_organism(Organism* new_organism);
    
    Map& get_map();
    Organism* get_organism_at_location(XY location);
    Organism* get_organism_at_location(int location_x, int location_y);
    Organism* get_human() const;
    std::list<Organism*> get_organisms_list();

    void set_human(Organism* new_human);
};

#define PROG_OB_P1_WORLD_ORGANISM_MAP_H

#endif //PROG_OB_P1_WORLD_ORGANISM_MAP_H