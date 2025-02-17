//
// Created by M Sz on 09/04/2023.
//

#include "Nightshade.h"

Nightshade::Nightshade(int new_x, int new_y, World &new_world)
        : Plant(NIGHTSHADE_STRENGTH, new_x, new_y, NIGHTSHADE_SYMBOL, NIGHTSHADE_SEEDING_THRESHOLD, new_world)
{}

Plant *Nightshade::seed_new_plant(int spawnpoint_x, int spawnpoint_y) {
    return new Nightshade(spawnpoint_x, spawnpoint_y, this->get_world());
}

std::string Nightshade::login()
{
    return std::string("Nightshade");
}

void Nightshade::collision(Organism *invading_organism) {
    invading_organism->kill_self();
    this->kill_self();
}
