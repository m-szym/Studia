//
// Created by M Sz on 05/04/2023.
//

#ifndef PROG_OB_P1_MAP_H
#define PROG_OB_P1_MAP_H


#include "misc.h"

class Organism;

class Map {
private:
    Organism*** map;
    int size_x;
    int size_y;

public:
    Map(int map_size_x, int map_size_y);

    ~Map();

    int get_size_x() const;

    int get_size_y() const;

    Organism*** get_internal_map() const;

    bool is_out_of_map(XY location) const;

    bool is_out_of_map(int x, int y) const;

    bool would_be_out_of_map(XY location, int speed, int direction) const;

    bool would_be_out_of_map(int x, int y, int speed, int direction) const;

    Organism* place_object(XY location, Organism* object);
    Organism* move_object(XY location, Organism* object);
    Organism* lift_object_from_location(XY location);
    Organism* get_object(XY location);

    Organism* get_neighbour(XY location, int direction);

    void draw() const;
};

#endif //PROG_OB_P1_MAP_H