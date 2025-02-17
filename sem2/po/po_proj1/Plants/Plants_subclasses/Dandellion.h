//
// Created by M Sz on 09/04/2023.
//

#ifndef PROG_OB_P1_DANDELLION_H
#define PROG_OB_P1_DANDELLION_H


#include "../Plant.h"

class Dandellion : public Plant{
private:
    Plant* seed_new_plant(int spawnpoint_x, int spawnpoint_y) override;

protected:
    std::string login() override;

public:
    Dandellion(int new_x, int new_y, World& new_world);
    void action() override;
};


#endif //PROG_OB_P1_DANDELLION_H
