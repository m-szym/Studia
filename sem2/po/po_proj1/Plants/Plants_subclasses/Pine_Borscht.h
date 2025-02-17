//
// Created by M Sz on 09/04/2023.
//

#ifndef PROG_OB_P1_PINE_BORSCHT_H
#define PROG_OB_P1_PINE_BORSCHT_H


#include "../Plant.h"
#include "../../Animals/Animal.h"

class Pine_Borscht : public Plant {
private:
    Plant* seed_new_plant(int spawnpoint_x, int spawnpoint_y) override;
    void kill_neighbours();

protected:
    std::string login() override;

public:
    Pine_Borscht(int new_x, int new_y, World& new_world);
    void action() override;
    void collision(Organism *invading_organism) override;
};


#endif //PROG_OB_P1_PINE_BORSCHT_H
