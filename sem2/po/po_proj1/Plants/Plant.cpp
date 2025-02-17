//
// Created by M Sz on 05/04/2023.
//

#include "Plant.h"

Plant::Plant(int new_strength, int new_x, int new_y, char new_symbol,int seeding_chance, World &new_world)
        : Organism(new_strength, BASE_PLANT_INITIATIVE, new_x, new_y, new_symbol, new_world), seeding_threshold(seeding_chance)
{}

Plant::Plant(int new_strength, XY new_map_location, char new_symbol,int seeding_chance, World &new_world)
        : Organism(new_strength, BASE_PLANT_INITIATIVE, new_map_location, new_symbol, new_world), seeding_threshold(seeding_chance)
{}

void Plant::action() {
    this->seed();
}

void Plant::seed() {
    if (rand() % SEEDING_CHANCE_BASE < this->get_seeding_threshold()) {
        //this->log(PLANT_IDLE_MESSAGE);
        return;
    }


    
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i == 0 && j == 0)
                continue;

            if (!this->get_world().get_map().is_out_of_map(this->get_x() + i, this->get_y() + j)) {
                if (this->get_world().get_organism_at_location(this->get_x() + i, this->get_y() + j) == nullptr) {

                    this->get_world().add_organism(this->seed_new_plant(this->get_x() + i, this->get_y() + j));

                    std::string s(SEEDING_MESSAGE);
                    s += this->login();
                    s += " (";
                    s += std::to_string(this->get_x() + i);
                    s += ", ";
                    s += std::to_string(this->get_y() + j);
                    s += ")";

                    this->log(s);

                    return;
                }
            }
        }
    }
}

void Plant::set_seeding_threshold(int new_seeding_threshold) {
    this->seeding_threshold = new_seeding_threshold;
}

int Plant::get_seeding_threshold() const {
    return this->seeding_threshold;
}

void Plant::collision(Organism *invading_organism) {
    invading_organism->update_location(this->get_location());
    this->kill_self();
    }

std::string Plant::login() {
    return std::string("Plant");
}




