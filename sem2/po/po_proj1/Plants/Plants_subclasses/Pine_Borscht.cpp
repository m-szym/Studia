//
// Created by M Sz on 09/04/2023.
//

#include "Pine_Borscht.h"


Pine_Borscht::Pine_Borscht(int new_x, int new_y, World &new_world)
        : Plant(PINE_BORSCHT_STRENGTH, new_x, new_y, PINE_BORSCHT_SYMBOL, PINE_BORSCHT_SEEDING_THRESHOLD, new_world)
{}

Plant *Pine_Borscht::seed_new_plant(int spawnpoint_x, int spawnpoint_y) {
    return new Pine_Borscht(spawnpoint_x, spawnpoint_y, this->get_world());
}

void Pine_Borscht::action() {
    this->kill_neighbours();
    Plant::seed();
}


void Pine_Borscht::kill_neighbours() {
    Map& map = this->get_world().get_map();
    Organism* target = nullptr;
    XY this_location = this->get_location();

   target = this->get_world().get_map().get_neighbour(this_location, DIR_UP);
   if (target != nullptr && !target->is_plant())
       target->kill_self();

   target = this->get_world().get_map().get_neighbour(this_location, DIR_DOWN);
   if (target != nullptr && !target->is_plant())
       target->kill_self();

   target = this->get_world().get_map().get_neighbour(this_location, DIR_LEFT);
   if (target != nullptr && !target->is_plant())
       target->kill_self();

   target = this->get_world().get_map().get_neighbour(this_location, DIR_RIGHT);
   if (target != nullptr && !target->is_plant())
       target->kill_self();


}

std::string Pine_Borscht::login()
{
    return std::string("Pine Borscht");
}

void Pine_Borscht::collision(Organism *invading_organism) {
    invading_organism->kill_self();
}
