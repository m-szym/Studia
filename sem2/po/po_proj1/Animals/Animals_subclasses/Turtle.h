//
// Created by M Sz on 09/04/2023.
//

#ifndef PROG_OB_P1_TURTLE_H
#define PROG_OB_P1_TURTLE_H


#include "../Animal.h"

class Turtle : public Animal {
private:
    Animal* procreate(int spawnpoint_x, int spawnpoint_y) override;
    bool reflect_attack(Animal* attacker) override;
public:
    Turtle(int new_x, int new_y, World& world);
    void action() override;
    std::string login() override;

};


#endif //PROG_OB_P1_TURTLE_H
