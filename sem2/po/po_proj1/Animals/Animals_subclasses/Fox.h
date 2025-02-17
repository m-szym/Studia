//
// Created by M Sz on 09/04/2023.
//

#ifndef PROG_OB_P1_FOX_H
#define PROG_OB_P1_FOX_H


#include "../Animal.h"

class Fox : public Animal{
private:
    Animal* procreate(int spawnpoint_x, int spawnpoint_y) override;
    
protected:
    void pre_collision(Organism* target) override;

public:
    Fox(int new_x, int new_y, World& world);
    std::string login() override;

};


#endif //PROG_OB_P1_FOX_H
