//
// Created by M Sz on 04/04/2023.
//
#pragma once
#ifndef PROG_OB_P1_WOLF_H
#define PROG_OB_P1_WOLF_H
#include "../Animal.h"

class Wolf : public Animal {
private:
    Animal* procreate(int spawnpoint_x, int spawnpoint_y) override;
public:
    Wolf(int new_wolf_x, int new_wolf_y, World& world);
    std::string login() override;

};


#endif //PROG_OB_P1_WOLF_H
