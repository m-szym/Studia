//
// Created by M Sz on 11/04/2023.
//

#ifndef PROG_OB_P1_HUMAN_H
#define PROG_OB_P1_HUMAN_H


#include "Animal.h"

struct MinHuman
{
    int x;
    int y;
    char symbol;
    int strength;
    int skill_cooldown;
    int skill_duration_left;
    int id;
};

class Human : public Animal {
private:
    int direction;
    int skill_cooldown;
    int skill_duration_left;
    bool skill_active;

    void skill();
    void balefire();
    void activate_skill();

protected:
    std::string login() override;
    int decide_where_to_move() override;

    Animal* procreate(int spawnpoint_x, int spawnpoint_y) override;

public:
    Human(int new_x, int new_y, World &new_world);
    Human(XY new_location, World &new_world);

    void control(int command) override;
    void action() override;

    int get_direction() const;
    int get_skill_cooldown() const;
    int get_skill_duration_left() const;
    bool get_skill_active() const;

    void set_direction(int new_direction);
    void set_skill_cooldown(int new_skill_cooldown) ;
    void set_skill_duration_left(int new_skill_duration_left);
    void set_skill_active(bool new_skill_active);

    MinHuman minify_human();
};


#endif //PROG_OB_P1_HUMAN_H
