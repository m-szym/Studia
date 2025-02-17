//
// Created by M Sz on 04/04/2023.
//

#include "Wolf.h"

Wolf::Wolf(int new_wolf_x, int new_wolf_y, World& world)
    : Animal(WOLF_STRENGTH, WOLF_INITIATIVE, WOLF_SPEED, new_wolf_x, new_wolf_y, WOLF_SYMBOL, world)
{
}

Animal *Wolf::procreate(int spawnpoint_x, int spawnpoint_y) {
    return new Wolf(spawnpoint_x, spawnpoint_y, this->get_world());
}

std::string Wolf::login() {
    return std::string("Wolf");
}

