//
// Created by M Sz on 09/04/2023.
//

#include "Guarana.h"

Plant *Guarana::seed_new_plant(int spawnpoint_x, int spawnpoint_y) {
    return dynamic_cast<Plant*>(new Guarana(spawnpoint_x, spawnpoint_y, this->get_world()));
}

std::string Guarana::login()
{
    return std::string("Guarana");
}

Guarana::Guarana(int new_x, int new_y, World &new_world)
        : Plant(GUARANA_STRENGTH, new_x, new_y, GUARANA_SYMBOL, GUARANA_SEEDING_THRESHOLD, new_world)
{}

void Guarana::collision(Organism *invading_organism) {
    Plant::collision(invading_organism);
    invading_organism->set_strength(invading_organism->get_strength() + GUARANA_STRENGHT_BONUS);
}
