//
// Created by M Sz on 05/04/2023.
//
#pragma once
#ifndef PROG_OB_P1_ORGANISM_H
#define PROG_OB_P1_ORGANISM_H


#include "misc.h"
#include "World.h"

class World;

struct MinOrganism {
    int x;
    int y;
    int strength;
    char symbol;
};

class Organism
{
private:
    int strength;
    int initiative;
    XY map_location;
    char symbol;


    int marker;
    const int id;
    static int organisms_counter;
    World& world;

public:
    //konstruktory przydzielajace statystyki
    Organism(int new_strength, int new_initiative, XY new_map_location, char new_symbol, World& new_world);
    Organism(int new_strength, int new_initiative, int new_x, int new_y, char new_symbol, World& new_world);
    //konstruktory bardziej ogólne - nie potrzebne tak na prawdê


    virtual ~Organism();

    virtual void action() = 0;
    virtual void collision(Organism* invading_organism) = 0;    //mo¿na zrobiæ nie =0

    void update_location(XY new_location);      //lokalizacja w³asna && mapy

    void draw();
    void log(std::string info);
    virtual std::string login();

    void kill_self();   //posortowac listê TODO


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


    bool is_plant();
    static bool is_plant(Organism* target);

    virtual void control(int command);
    MinOrganism minify();


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


#endif //PROG_OB_P1_ORGANISM_H
