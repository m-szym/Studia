//
// Created by M Sz on 06/04/2023.
//

#include "Grass.h"

Grass::Grass(int new_grass_x, int new_grass_y, World &new_world)
    : Plant(GRASS_STRENGTH, new_grass_x, new_grass_y, GRASS_SYMBOL, GRASS_SEEDING_THRESHOLD, new_world)
{}

Plant *Grass::seed_new_plant(int spawnpoint_x, int spawnpoint_y) {
    return dynamic_cast<Plant*>(new Grass(spawnpoint_x, spawnpoint_y, this->get_world()));
}

std::string Grass::login()
{
    return std::string("Grass");
}
