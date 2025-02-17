#pragma once
#include "constants.h"
#include <string>

struct XY
{

public:
	int x;
	int y;
    XY(int x, int y);
	bool operator==(XY other);
	std::string to_string();

};

int get_opposite_direction(int direction);


const XY get_new_xy_in_dir(const XY current_location, const int direction_x=DIR_NULL, const int speed_x=0, const int direction_y=DIR_NULL, const int speed_y=0);