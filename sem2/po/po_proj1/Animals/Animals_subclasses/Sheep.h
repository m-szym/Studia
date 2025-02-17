//
// Created by M Sz on 05/04/2023.
//

#ifndef PROG_OB_P1_SHEEP_H
#define PROG_OB_P1_SHEEP_H


#include "../Animal.h"

class Sheep : public Animal {
private:
    Animal* procreate(int spawnpoint_x, int spawnpoint_y) override;
public:
    Sheep(int new_sheep_x, int new_sheep_y, World& world);
    std::string login() override;

};


#endif //PROG_OB_P1_SHEEP_H
