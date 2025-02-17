#include "World.h"


//////////////////////////////////////////////////////

World::World(int new_size_x, int new_size_y)
    : map(new_size_x, new_size_y), human(nullptr)
{}

World::~World()
{
    while (!org.empty())
    {
        delete org.front();
        org.pop_front();
    }

    org.clear();
}

Organism* World::add_organism(Organism* new_organism)
{
    org.push_front(new_organism);

    map.place_object(new_organism->get_location(), new_organism);

    new_organism->log(SPAWN_MESSAGE);
    return new_organism;
}


Map& World::get_map() {
    return this->map;
}

Organism* World::get_organism_at_location(XY location) {
    return this->map.get_object(location);
}

Organism* World::get_organism_at_location(int location_x, int location_y) {
    XY location(location_x, location_y);
    return this->map.get_object(location);
}


void World::make_turn() {
    this->roll_initiative();

    //for each (Organism * organism in org)
    //{
    //    organism->action();
    //}

    auto it = org.begin();

    while (it != org.end())
    {
        if ((*it)->get_marker() == DEAD_MARKER)
            it = org.erase(it);
        else
        {
            (*it)->action();
            ++it;
        }
    }


}

void World::roll_initiative()
{
    org.sort(OrganismComparator());
}

void World::draw_world() {
    this->map.draw();

}

Organism* World::get_human() const {
    return dynamic_cast<Organism*>(human);
}

void World::set_human(Organism* new_human) {
    World::human = new_human;
}

std::list<Organism*> World::get_orgs()
{
    return org;
}

void World::take_input()
{
    int key_pressed = 0;
    int is_arrow_key = 0;

    is_arrow_key = 0;
    key_pressed = getch();

    if (key_pressed == 0 || key_pressed == 224)
    {
        is_arrow_key = 1;
        key_pressed = getch();
        this->human->control(key_pressed);
    }
    else if (key_pressed == HUMAN_SKILL_KEY)
    {
        this->human->control(key_pressed);
    }

    this->make_turn();

}

