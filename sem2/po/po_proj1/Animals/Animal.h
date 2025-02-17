#pragma once
#include <cstdlib>
#include <ctime>

#include "../constants.h"
#include "../config.h"
#include "../world_organism_map.h"

class Animal : public Organism
{
private:
    int speed;

    virtual int decide_where_to_move();   
    XY chose_location();
    bool would_leave_map(int direction);

    virtual Animal* procreate(int spawnpoint_x, int spawnpoint_y) = 0;

protected:    
    void move();
    XY get_new_location(int direction);

    Animal* mate();
 
    virtual bool reflect_attack(Animal* attacker);
    virtual void pre_collision(Organism* target);   

public:
    Animal(int new_strength, int new_initiative, int new_speed, int new_x, int new_y, char new_symbol, World& new_world);
    Animal(int new_strength, int new_initiative, int new_speed, XY new_map_location, char new_symbol, World& new_world);

    void action() override;
    void collision(Organism* invading_organism) override;

    void attack(Animal* target);

    std::string login() override;

    static bool same_animal_types(Animal* animal1, Animal* animal2);

    int get_speed() const;
    void set_speed(int new_speed);
};
