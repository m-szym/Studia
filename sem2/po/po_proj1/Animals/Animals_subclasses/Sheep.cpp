//
// Created by M Sz on 05/04/2023.
//

#include "Sheep.h"
Sheep::Sheep(int new_Sheep_x, int new_Sheep_y, World& world)
        : Animal(SHEEP_STRENGTH, SHEEP_INITIATIVE, SHEEP_SPEED, new_Sheep_x, new_Sheep_y, SHEEP_SYMBOL, world)
{
}

Animal *Sheep::procreate(int spawnpoint_x, int spawnpoint_y) {
    return new Sheep(spawnpoint_x, spawnpoint_y, this->get_world());
}

std::string Sheep::login() {
    return std::string("Sheep");
}



