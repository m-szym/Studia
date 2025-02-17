#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "MapData.h"
#include "Graph.h"
#include "constanst.h"


// We traverse the map (left to right, top to bottom) looking for city name labels (groups of allowed letters)
// upon finding such symbol we read the entire name, create a new node and append it to the graph.
// We also mark the location of the city on the cityNodesMask layer of MapData with a pointer to the node
// it'll be used later to quickly find the shortest immediate paths between cities.
void loadCities(MapData& m, Graph& g);

// We find direct connections between cities and add them to the graph.
// BFS is used to traverse the map.
void findDirectCityConnections(MapData& m, Graph& g);

// We read the flights (directed connections between city nodes) from input and add them to the directly to the graph.
void loadFlights(Graph& g);

