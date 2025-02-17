#pragma once

#include <iostream>

#include "Node.h"
#include "constanst.h"

// The MapData class is used to store raw map and additional data for specilised use in the program.
struct MapData
{
    // Dimensions of the map (in tiles)
    int height;
    int width;

    // Number of cities and road tiles (left out are empty tiles and tiles with city labels)
    int citiesNr;
    int road_tiles;

    char** map;                 // The raw map data - a 2D array of characters

    Node*** cityNodesMask;      // A 2D array of pointers to graph nodes (cities) - used to quickly find a city by its coordinates
    int** lastVisitCycleNr;     // A 2D array of integers - used in the bfs algorithm to store information whetever a tile was visited int he current bfs call.

    // Crates empty MapData object
    MapData();

    // Loads the map data from the standard input reading first the dimensions of the map and then the map itself, char by char.
    MapData* load();
    
    // Clears the map data and frees the memory
    void clear();
    ~MapData();

    // Checks if the given coordinates are out of the map bounds
    bool outOfMap(int i, int j, char direction);
    bool outOfMap(int i, int j);
};