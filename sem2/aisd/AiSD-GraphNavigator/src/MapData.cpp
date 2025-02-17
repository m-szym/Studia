#include "../include/MapData.h"

MapData::MapData()
    :   height(0), width(0), citiesNr(0), road_tiles(0), 
        map(nullptr), cityNodesMask(nullptr), lastVisitCycleNr(nullptr)
{}

MapData* MapData::load()
{
    std::cin >> width >> height;

    map = new char* [height];

    cityNodesMask = new Node * *[height];
    lastVisitCycleNr = new int* [height];

    for (int i = 0; i < height; i++)
    {
        map[i] = new char[width];

        lastVisitCycleNr[i] = new int[width];
        cityNodesMask[i] = new Node * [width];

        for (int j = 0; j < width; j++)
        {
            std::cin >> map[i][j];
            if (map[i][j] == CITY_SYMBOL)      
                citiesNr++; 
            else if (map[i][j] == ROAD_SYMBOL) 
                road_tiles++;

            lastVisitCycleNr[i][j] = -1;
            cityNodesMask[i][j] = nullptr; 
        }   
    }

    return this;
}

void MapData::clear()
{
    for (int i = 0; i < height; i++)
    {
        delete[] map[i];
        delete[] cityNodesMask[i];
        delete[] lastVisitCycleNr[i];
    }

    delete[] map;
    delete[] cityNodesMask;
    delete[] lastVisitCycleNr;

    map = nullptr;
    cityNodesMask = nullptr;
    lastVisitCycleNr = nullptr;
}

MapData::~MapData()
{
    if (map != nullptr)
        clear();
}

bool MapData::outOfMap(int i, int j, char direction)
{
    if (direction == DIR_UP && i - 1 < 0)               return true;
    else if (direction == DIR_DOWN && i + 1 >= height)  return true;
    else if (direction == DIR_LEFT && j - 1 < 0)        return true;
    else if (direction == DIR_RIGHT && j + 1 >= width)  return true;
    else                                                
        return false;    
}

bool MapData::outOfMap(int i, int j)
{
    if ((i < 0) || (i >= height) ||
        (j < 0) || (j >= width))
        return true;
    else
        return false;
}