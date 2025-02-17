#include "Antelope.h"

Antelope::Antelope(int new_antelope_x, int new_antelope_y, World& world)
    : Animal(ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, ANTELOPE_SPEED, new_antelope_x, new_antelope_y, ANTELOPE_SYMBOL, world)
{
}

Animal* Antelope::procreate(int spawnpoint_x, int spawnpoint_y) {
    return new Antelope(spawnpoint_x, spawnpoint_y, this->get_world());
}

std::string Antelope::login()
{
    return std::string("Antelope");
}

void Antelope::collision(Organism* invading_organism)
{
    auto* invading_animal = dynamic_cast<Animal*>(invading_organism);
    if (invading_animal == nullptr)
        return;

    if (Animal::same_animal_types(this, invading_animal)) {
        this->log("mates with ");
        invading_animal->log("this");
        this->mate();
        return;
    }

    if (!this->reflect_attack(invading_animal)) {
        XY antelope_location = this->get_location();
        
        if (this->escape())
            invading_animal->update_location(antelope_location);
        else
            invading_animal->Animal::attack(this);

        return;
    }
}



bool Antelope::escape()
{
    int escape = rand() % ANTELOPE_ESCAPE_CHANCE_BASE;

    if (escape >= ANTELOPE_ESCAPE_THRESHOLD)
    {
        XY new_location = this->get_new_location(DIR_UP);
        Organism* organism_at_location = this->get_world().get_organism_at_location(new_location);

        for (int i = 1; i < 5; i++)
        {
            new_location = this->get_new_location(i);
            organism_at_location = this->get_world().get_organism_at_location(new_location);
            if (organism_at_location == nullptr || organism_at_location->is_plant() == true)
            {   
                this->log(FLEE_MESSAGE);
                this->update_location(new_location);
                

                return true;
            }
        }

    }
    return false;
}


