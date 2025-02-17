//
// Created by M Sz on 06/04/2023.
//

#ifndef PROG_OB_P1_GRASS_H
#define PROG_OB_P1_GRASS_H


#include "../Plant.h"

class Grass : public Plant {
private:
     Plant* seed_new_plant(int spawnpoint_x, int spawnpoint_y) override;

protected:
    std::string login() override;

public:
    Grass(int new_grass_x, int new_grass_y, World& new_world);
};


#endif //PROG_OB_P1_GRASS_H
