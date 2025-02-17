//
// Created by M Sz on 06/04/2023.
//
#include "world_organism_map.h"


int Organism::organisms_counter = 0;

void Organism::draw()
{
    //draw_symbol_at_xy(this->symbol, this->map_location);
}

int Organism::get_strength() const
{
    return this->strength;
}

int Organism::get_initiative() const
{
    return this->initiative;
}

XY Organism::get_location()
{
    return this->map_location;
}

int Organism::get_id() const
{
    return this->id;
}

int Organism::get_x() const
{
    return this->map_location.x;
}

int Organism::get_y() const
{
    return this->map_location.y;
}

char Organism::get_symbol() const
{
    return this->symbol;
}

World& Organism::get_world()
{
    return this->world;
}

int Organism::get_marker() const
{
    return this->marker;
}

void Organism::set_marker(int new_marker) 
{
    this->marker = new_marker;
}

void Organism::set_id(int new_id)
{
    this->id = new_id;
}


void Organism::set_strength(const int new_strength)
{
    this->strength = new_strength;
}

void Organism::set_initiative(const int new_initiative)
{
    this->initiative = new_initiative;
}

void Organism::set_location(const XY new_location)
{
    this->map_location = new_location;
}

void Organism::set_x(const int new_x)
{
    this->map_location.x = new_x;
}

void Organism::set_y(const int new_y)
{
    this->map_location.y = new_y;
}

void Organism::set_symbol(char new_symbol)
{
    this->symbol = new_symbol;
}

void Organism::set_world(World& new_world)
{
    this->world = new_world;
}



Organism::Organism(int new_strength, int new_initiative, XY new_map_location, char new_symbol, World& new_world)
    : strength(new_strength), initiative(new_initiative), map_location(new_map_location), world(new_world),
    id(organisms_counter + 1), symbol(new_symbol), marker(NULL_MARKER)
{
    organisms_counter++;
}

Organism::Organism(int new_strength, int new_initiative, int new_x, int new_y, char new_symbol, World& new_world)
    : strength(new_strength), initiative(new_initiative), world(new_world), map_location(XY(new_x, new_y)),
    id(organisms_counter + 1), symbol(new_symbol), marker(NULL_MARKER)
{
    organisms_counter++;
}


Organism::~Organism()
{}

void Organism::kill_self() {
    //oznacza organizm jako nieżywy - do usunięcia z listy organizmów
    this->set_marker(DEAD_MARKER);

    //log śmierć orgainzmu
    this->log(DEATH_MESSAGE);

    //zdjęcie z mapy
    if (this->world.map.get_object(this->map_location) == this)
        this->world.map.lift_object_from_location(this->map_location);

    //zostanie usunięty z listy organizmów w kolejnym obiegu świata
}

void Organism::update_location(XY new_location) {

    std::string s(MOVEMENT_MESSAGE);
    s += new_location.to_string();
    this->log(s);

    this->world.map.move_object(new_location, this);
    this->set_location(new_location);
}

void Organism::log(std::string info) {
    std::cout << "\n\t" << this->login() << this->get_location().to_string() << info;
}

std::string Organism::login() {
    return std::string("Organism");
}

bool Organism::is_plant() {
    if (this->initiative == 0) return true;
    return false;
}

bool Organism::is_plant(Organism* target) {
    if (target->get_initiative() == 0) return true;
    return false;
}

void Organism::control(int command)
{}

MinOrganism Organism::minify() {
    MinOrganism min;
    min.x = this->get_x();
    min.y = this->get_y();
    min.strength = this->get_strength();
    min.symbol = this->get_symbol();
    min.id = this->get_id();

    return min;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int Map::get_size_x() const
{
    return this->size_x;
}

int Map::get_size_y() const
{
    return this->size_y;
}

bool Map::is_out_of_map(const XY location) const
{
    if (location.x < 0 || location.x >= this->size_x)
        return true;
    if (location.y < 0 || location.y >= this->size_y)
        return true;

    return false;
}

bool Map::is_out_of_map(const int x, const int y) const
{
    if (x < 0 || x >= this->size_x)
        return true;
    if (y < 0 || y >= this->size_y)
        return true;

    return false;
}

bool Map::would_be_out_of_map(const XY location, const int speed, const int direction) const
{
    if (direction == DIR_UP)
    {
        if (location.y - speed < 0)
            return true;
    }
    else if (direction == DIR_DOWN)
    {
        if (location.y + speed >= this->size_y)
            return true;
    }
    else if (direction == DIR_LEFT)
    {
        if (location.x - speed < 0)
            return true;
    }
    else if (direction == DIR_RIGHT)
    {
        if (location.x + speed >= this->size_x)
            return true;
    }

    return false;
}

bool Map::would_be_out_of_map(const int x, const int y, const int speed, const int direction) const
{
    XY location(x, y);
    return would_be_out_of_map(location, speed, direction);
}

Map::Map(int map_size_x, int map_size_y)
    : size_x(map_size_x), size_y(map_size_y), map(nullptr)
{
    if (map_size_x > 0 && map_size_y > 0)
    {
        this->map = new Organism * *[map_size_y];
        for (int i = 0; i < map_size_y; ++i) {
            this->map[i] = new Organism * [map_size_x];
            for (int j = 0; j < map_size_x; ++j) {
                map[i][j] = nullptr;
            }
        }
    }
}

Map::~Map() {
    if (map != nullptr)
    {
        if (size_x > 0 && size_y > 0)
        {
            for (int i = 0; i < size_y; ++i)
            {
                delete[] map[i];
            }
            delete[] map;
        }
    }
}

Organism*** Map::get_internal_map() const {
    return this->map;
}

Organism* Map::place_object(XY location, Organism* object) {

    this->map[location.y][location.x] = object;

    return this->map[location.y][location.x];
}

Organism* Map::lift_object_from_location(XY location) {

    this->map[location.y][location.x] = nullptr;

    return this->map[location.y][location.x];
}

Organism* Map::move_object(XY new_location, Organism* object) {
    lift_object_from_location(object->get_location());
    place_object(new_location, object);

    return this->map[new_location.y][new_location.x];
}

Organism* Map::get_object(XY location) {
    return this->map[location.y][location.x];
}

Organism* Map::get_neighbour(XY location, int direction) {
    if (!would_be_out_of_map(location, 1, direction)) {
        if (direction == DIR_UP) {
            return this->map[location.y - 1][location.x];
        }
        else if (direction == DIR_DOWN) {
            return this->map[location.y + 1][location.x];
        }
        else if (direction == DIR_LEFT) {
            return this->map[location.y][location.x - 1];
        }
        else if (direction == DIR_RIGHT) {
            return this->map[location.y][location.x + 1];
        }
    }
    else
        return nullptr;
}

void Map::draw() const {
    std::cout << "\n";
    for (int i = -1; i < this->size_y; ++i) {
        if (i == -1) std::cout << "  ";
        else if (i < 10) std::cout << i << " ";
        else std::cout << i;
        for (int j = 0; j < this->size_x; ++j) {
            if (i == -1) {
                if (j == -1) std::cout << "  ";
                else if (j < 10) std::cout << j << " ";
                else std::cout << j;
                continue;
            }


            if (map[i][j] != nullptr)
                std::cout << map[i][j]->get_symbol();
            else
                std::cout << ".";
            std::cout << " ";

        }
        std::cout << "\n";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

World::World(int new_size_x, int new_size_y)
    : map(new_size_x, new_size_y), human(nullptr)
{}

World::~World()
{
    while (!organisms_list.empty())
    {
        delete organisms_list.front();
        organisms_list.pop_front();
    }

    organisms_list.clear();
}

Organism* World::add_organism(Organism* new_organism)
{
    organisms_list.push_front(new_organism);

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
    this->update_initiative_order();

    auto it = organisms_list.begin();

    while (it != organisms_list.end())
    {
        if ((*it)->get_marker() == DEAD_MARKER)
            it = organisms_list.erase(it);
        else
        {
            (*it)->action();
            ++it;
        }
    }


}

void World::update_initiative_order()
{
    organisms_list.sort(OrganismComparator());
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

std::list<Organism*> World::get_organisms_list()
{
    return organisms_list;
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







