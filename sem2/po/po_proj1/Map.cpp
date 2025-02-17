//
// Created by M Sz on 05/04/2023.
//
#include "Map.h"

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
    : size_x(map_size_x), size_y(map_size_y)
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
        else
            return nullptr;
    }
    else
        return nullptr;
}

void Map::draw() const {
    for (int i = -1; i < this->size_y; ++i) {
        if (i == -1) std::cout << "  ";
        else std::cout << i << " ";
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
