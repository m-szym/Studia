//
// Created by M Sz on 11/04/2023.
//

#include "Human.h"

Human::Human(int new_x, int new_y, World &new_world)
        :   direction(DIR_NULL),
            skill_cooldown(HUMAN_SKILL_COOLDOWN),
            skill_active(false),
            skill_duration_left(0),
            Animal(HUMAN_STRENGTH,
                 HUMAN_INITIATIVE,
                 HUMAN_SPEED, new_x, new_y,
                 HUMAN_SYMBOL, new_world)
{}

Human::Human(XY new_location, World &new_world)
        :   direction(DIR_NULL),
            skill_cooldown(HUMAN_SKILL_COOLDOWN),
            skill_active(false),
            skill_duration_left(0),
            Animal(HUMAN_STRENGTH,
                 HUMAN_INITIATIVE,
                 HUMAN_SPEED,
                 new_location,
                 HUMAN_SYMBOL, new_world)
{}

std::string Human::login() {
    return std::string("Human");
}

int Human::decide_where_to_move() {
    return this->direction;
}

int Human::get_direction() const {
    return direction;
}

int Human::get_skill_cooldown() const
{
    return this->skill_cooldown;
}

int Human::get_skill_duration_left() const
{
    return this->skill_duration_left;
}

bool Human::get_skill_active() const
{
    return this->skill_active;
}

void Human::set_direction(int new_direction) {
    this->direction = new_direction;
}

void Human::set_skill_cooldown(int new_skill_cooldown)
{
    this->skill_cooldown = new_skill_cooldown;
}

void Human::set_skill_duration_left(int new_skill_duration_left)
{
    this->skill_duration_left = new_skill_duration_left;
}

void Human::set_skill_active(bool new_skill_active)
{
    this->skill_active = new_skill_active;
}

void Human::control(int command)
{
    if (command == KEY_0_UP)
    {
        this->direction = DIR_UP;
    }
    else if (command == KEY_0_DOWN)
    {
        this->direction = DIR_DOWN;
    }
    else if (command == KEY_0_LEFT)
    {
        this->direction = DIR_LEFT;
    }
    else if (command == KEY_0_RIGHT)
    {
        this->direction = DIR_RIGHT;
    }
    else if (command == HUMAN_SKILL_KEY)
    {
        this->activate_skill();
    }


}

Animal *Human::procreate(int spawnpoint_x, int spawnpoint_y) {
    return nullptr;
}



void Human::action() {
    this->skill();

    Animal::action();

    this->direction = DIR_NULL;
}

void Human::skill() {
    if (!skill_active && skill_cooldown > 0) {
        skill_cooldown--;
    }

    if (skill_active && skill_duration_left > 1) {
        skill_duration_left--;
    } else if (skill_active && skill_duration_left == 1) {
        skill_duration_left = 0;
        skill_active = false;
        skill_cooldown = HUMAN_SKILL_COOLDOWN;
    }

    if (skill_active)
        this->balefire();
}

void Human::balefire() {
    this->log("uses balefire");
    Map& map = this->get_world().get_map();
    Organism* target = nullptr;

    target = this->get_world().get_map().get_neighbour(this->get_location(), DIR_UP);
    if (target != nullptr)
        target->kill_self();

    target = this->get_world().get_map().get_neighbour(this->get_location(), DIR_DOWN);
    if (target != nullptr)
        target->kill_self();

    target = this->get_world().get_map().get_neighbour(this->get_location(), DIR_LEFT);
    if (target != nullptr)
        target->kill_self();

    target = this->get_world().get_map().get_neighbour(this->get_location(), DIR_RIGHT);
    if (target != nullptr)
        target->kill_self();
}

void Human::activate_skill()
{
    this->skill_active = true;
    this->skill_duration_left = HUMAN_SKILL_DURATION;
}

MinHuman Human::minify_human() {
    MinHuman min;
    min.x = this->get_x();
    min.y = this->get_y();
    min.skill_cooldown = this->skill_cooldown;
    min.skill_duration_left = this->skill_duration_left;
    min.strength = this->get_strength();
    min.symbol = this->get_symbol();
    min.id = this->get_id();

    return min;
}