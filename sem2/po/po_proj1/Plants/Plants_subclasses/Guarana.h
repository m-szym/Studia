//
// Created by M Sz on 09/04/2023.
//

#ifndef PROG_OB_P1_GUARANA_H
#define PROG_OB_P1_GUARANA_H


#include "../Plant.h"

class Guarana : public Plant{
private:
    Plant* seed_new_plant(int spawnpoint_x, int spawnpoint_y) override;

protected:
    std::string login() override;

public:
    Guarana(int new_x, int new_y, World& new_world);
    void collision(Organism *invading_organism) override;
};


#endif //PROG_OB_P1_GUARANA_H
