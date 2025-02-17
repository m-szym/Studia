//
// Created by M Sz on 09/04/2023.
//

#include "Turtle.h"

Turtle::Turtle(int new_turtle_x, int new_turtle_y, World& world)
    : Animal(TURTLE_STRENGTH, TURTLE_INITIATIVE, TURTLE_SPEED, new_turtle_x, new_turtle_y, TURTLE_SYMBOL, world)
{
}

void Turtle::action()
{
    int move_chance = rand() % TURTLE_MOVEMENT_CHANCE_BASE;
    if (move_chance >= TURTLE_MOVEMENT_THRESHOLD)
        this->move();
    else
        this->log(LAZY_MESSAGE);
}

std::string Turtle::login()
{
    return std::string("Turtle");
}

Animal* Turtle::procreate(int spawnpoint_x, int spawnpoint_y) {
    return new Turtle(spawnpoint_x, spawnpoint_y, this->get_world());
}

bool Turtle::reflect_attack(Animal* attacker)
{
    if (attacker->get_strength() < TURTLE_DEFENSE)
    {
        this->log(ATTACK_REFLECT_MESSAGE);
        return true;
    }
    else
        return false;
}


