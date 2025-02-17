//
// Created by M Sz on 09/04/2023.
//

#include "Fox.h"

Fox::Fox(int new_fox_x, int new_fox_y, World& world)
        : Animal(FOX_STRENGTH, FOX_INITIATIVE, FOX_SPEED, new_fox_x, new_fox_y, FOX_SYMBOL, world)
{
}

std::string Fox::login()
{
    return std::string("Fox");
}

Animal *Fox::procreate(int spawnpoint_x, int spawnpoint_y) {
    return new Fox(spawnpoint_x, spawnpoint_y, this->get_world());
}

void Fox::pre_collision(Organism* target) {
    if (target->get_strength() > this->get_strength())
    {
        this->log(DANGERSENSE_MESSAGE);
        return;
    }

    Animal::pre_collision(target);



}
