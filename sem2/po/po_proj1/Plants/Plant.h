//
// Created by M Sz on 05/04/2023.
//
#pragma once
#ifndef PROG_OB_P1_PLANT_H
#define PROG_OB_P1_PLANT_H

#include <cstdlib>
#include <ctime>
#include "../world_organism_map.h"
//#include "../Organism.h"


class Plant : public Organism {
private:
    int seeding_threshold;
    virtual Plant* seed_new_plant(int spawnpoint_x, int spawnpoint_y) = 0;

protected:
    void seed();

public:
    Plant(int new_strength, int new_x, int new_y, char new_symbol, int seeding_chance, World& new_world);
    Plant(int new_strength, XY new_map_location, char new_symbol, int seeding_chance, World& new_world);

    void action() override;
    void collision(Organism *invading_organism) override;

    std::string login() override;

    void set_seeding_threshold(int new_seeding_threshold);
    int get_seeding_threshold() const;

};


#endif //PROG_OB_P1_PLANT_H
