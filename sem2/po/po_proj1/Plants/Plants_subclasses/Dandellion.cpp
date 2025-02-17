//
// Created by M Sz on 09/04/2023.
//

#include "Dandellion.h"

std::string Dandellion::login()
{
    return std::string("Dandellion");
}

Dandellion::Dandellion(int new_x, int new_y, World &new_world)
        : Plant(DANDELLION_STRENGTH, new_x, new_y, DANDELLION_SYMBOL, DANDELLION_SEEDING_THRESHOLD, new_world)
{}

Plant *Dandellion::seed_new_plant(int spawnpoint_x, int spawnpoint_y) {
    return new Dandellion(spawnpoint_x, spawnpoint_y, this->get_world());
}

void Dandellion::action() {
    for (int i = 0; i < DANDELLION_SEEDING_ATTEMPTS_PER_TURN; ++i) {
        this->seed();
    }
}
