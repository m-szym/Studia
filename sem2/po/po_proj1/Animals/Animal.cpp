#include "Animal.h"


void Animal::move()
{
    XY this_new_location = chose_location();

    if (this_new_location == this->get_location())
        return;

    Organism* organism_at_new_location = this->get_world().get_organism_at_location(this_new_location);
    if (organism_at_new_location != nullptr && organism_at_new_location != this) {
        this->pre_collision(organism_at_new_location);
        
    }
    else {
        this->Organism::update_location(this_new_location);
    }
    
}

void Animal::pre_collision(Organism* target)
{
    target->collision(this);
}

XY Animal::chose_location()
{
    int direction = this->decide_where_to_move();

    if (direction == DIR_NULL || this->would_leave_map(direction) == true)
        return this->get_location();

    return this->get_new_location(direction);

}


bool Animal::would_leave_map(const int direction)
{
    return this->get_world().get_map().would_be_out_of_map(
                                                            this->get_location(),
                                                            this->get_speed(),
                                                            direction);
}



XY Animal::get_new_location(const int direction) {
    if (direction == DIR_NULL) return this->get_location();

    XY new_location = this->get_location();

    if (direction == DIR_UP)
    {
        new_location.y -= this->get_speed();
    }
    else if (direction == DIR_DOWN)
    {
        new_location.y += this->get_speed();
    }
    else if (direction == DIR_LEFT)
    {
        new_location.x -= this->get_speed();
    }
    else if (direction == DIR_RIGHT)
    {
        new_location.x += this->get_speed();
    }

    return new_location;
}




Animal* Animal::mate() {
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (i == 0 && j == 0)
                continue;

            if (!this->get_world().get_map().is_out_of_map(this->get_x() + i, this->get_y() + j)) {
                if (this->get_world().get_organism_at_location(this->get_x() + i, this->get_y() + j) == nullptr) {

                    return dynamic_cast<Animal*>(this->get_world().add_organism(
                                                                                this->procreate(
                                                                                                this->get_x() + i,
                                                                                                this->get_y() + j
                                                                                               )
                                                                               )
                                                );
                }
            }
        }
    }
    return nullptr;
}


void Animal::action()
{
    this->move();

}

void Animal::attack(Animal* target) {
    std::string s(ATTACK_MESSAGE);
    s += target->login();
    s += target->get_location().to_string();
    this->log(s);

    if (this->get_strength() >= target->get_strength()) {
        Organism::update_location(this->get_location());
        target->kill_self();

        this->log(ATTACK_SUCCES_MESSAGE);
    }
    else {
        this->kill_self();

        target->log(ATTACK_FAILURE_MESSAGE);
    }
}

void Animal::collision(Organism* invading_organism) {
    auto* invading_animal = dynamic_cast<Animal*>(invading_organism);
    if (invading_animal == nullptr)
        return;

    if (Animal::same_animal_types(this, invading_animal)) {
        std::string s(MATING_MESSAGE);
        s += " ";
        s += invading_animal->login();
        s += invading_animal->get_location().to_string();
        this->log(s);

        this->mate();
        return;
    }

    if (!this->reflect_attack(invading_animal)) {
        invading_animal->attack(this);
        return;
    }

}



void Animal::set_speed(const int new_speed) {
    this->speed = new_speed;
}


int Animal::get_speed() const {
    return this->speed;
}


int Animal::decide_where_to_move() {
    if (CAN_STAY_IN_PLACE)
        return rand() % DIRECTIONS_N;
    else
        return (rand() % DIRECTIONS_N) + 1;;
}

Animal::Animal(int new_strength, int new_initiative, int new_speed, int new_x, int new_y, char new_symbol, World& new_world)
    : Organism(new_strength, new_initiative, new_x, new_y, new_symbol, new_world), speed(new_speed) {
}

Animal::Animal(int new_strength, int new_initiative, int new_speed, XY new_map_location, char new_symbol, World& new_world)
    : Organism(new_strength, new_initiative, new_map_location, new_symbol, new_world), speed(new_speed)
{

}

bool Animal::reflect_attack(Animal* attacker) {
    return false;
}

bool Animal::same_animal_types(Animal* animal1, Animal* animal2) {
    if (animal1->get_symbol() == animal2->get_symbol())
        return true;
    else
        return false;
}

std::string Animal::login() {
    return std::string("Animal");
}





