//
// Created by M Sz on 09/04/2023.
//
#pragma once

#ifndef PROG_OB_P1_ANTELOPE_H
#define PROG_OB_P1_ANTELOPE_H


#include "../Animal.h"

class Antelope : public Animal 
{
private:
    Animal* procreate(int spawnpoint_x, int spawnpoint_y) override;

    bool escape();
public:
    Antelope(int new_x, int new_y, World& world);

    std::string login() override;
    void collision(Organism* invading_organism) override;
};


#endif //PROG_OB_P1_ANTELOPE_H