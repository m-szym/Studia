#include "../include/dataReadingAndManip.h"

// Check if the char is a part of a city name label 
bool isCityNameSymbol(char c)
{
    return (c != ROAD_SYMBOL && 
            c != EMPTY_SYMBOL && 
            c != CITY_SYMBOL);
}

// Count the number of city name symbols in a row starting from the given position.
// Used to determine the length of the city name label.
int countSymbolsOnMap(const MapData& m, int x, int y, int count)
{
    if (x + 1 < m.width)
    {
        if (isCityNameSymbol(m.map[y][x + 1]))
        {
            return countSymbolsOnMap(m, x + 1, y, count) + 1;
        }
    }
    return 0;
}

// Read the city name label from the map starting at (x, y) position and return it as char* or nullptr if no city name label was found.
char* readNameFromMap(const MapData& m, int x, int y)
{
    int letters = countSymbolsOnMap(m, x, y, 0) + 1;

    if (letters > 0)
    {
        char* name = new char[letters + 1];
        name[letters] = '\0';

        for (int i = 0; i < letters; i++)
        {
            if (isCityNameSymbol(m.map[y][x + i]))  
            {
                name[i] = m.map[y][x + i];
            }     
        }
        return name;
    }
    return nullptr;
}

// Mark the city on the cityNodesMask layer of MapData with a pointer to the corresponding graph node.
// As we know the map location of the city name label and not the location of it's city symbol (i.e. it's actual location on the map)
// we need to find the city symbol by checking the surrounding tiles around the label.
void markCity(MapData& m, Node* ptrNode, int nameStartX, int nameStartY, int nameLen)
{
    for (int c = 0; c < nameLen; c += nameLen - 1)
    {
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0) 
                    continue;

                if (!m.outOfMap(nameStartY + i, nameStartX + c + j))
                {
                    if (m.map[nameStartY + i][nameStartX + c + j] == CITY_SYMBOL)
                    {
                        m.cityNodesMask[nameStartY + i][nameStartX + c + j] = ptrNode;
                        return;
                    }
                                
                }
                        
            }
                
        }
        
    }
}

void loadCities(MapData& m, Graph& g)
{
    int nodeNr = 0;                 // Used to assign a unique number to each city node in the graph.
    char* nodeName = nullptr;       // Used to store the city name label.
    int lettersToSkip = 0;          // Used to skip the city name label after it's been read.
    Node* newNode = nullptr;        

    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            if (isCityNameSymbol(m.map[i][j]))
            {
                if (lettersToSkip == 0)
                {
                    nodeName = readNameFromMap(m, j, i);
                    if (nodeName != nullptr)
                    {
                        lettersToSkip = strlen(nodeName) - 1;

                        newNode = new Node(nodeName, nodeNr); 
                        g.insertNode(newNode);
                        markCity(m, newNode, j, i, strlen(nodeName));

                        delete[] nodeName;
                    }
                    nodeNr++;             
                }
                else
                    lettersToSkip--;            
            }   
        }
    }
}


// Simple struct used to store three integers at one time.
// Without tuples it's used to quickly store and read triplets of integers.
struct XYZ
{
    int x, y, z;
};

XYZ packXYZ(int x, int y, int z)
{
    XYZ xyz;
    xyz.x = x;
    xyz.y = y;
    xyz.z = z;
    return xyz;
}

void unpackXYZ(const XYZ& xyz, int& x, int& y, int& z)
{
    x = xyz.x;
    y = xyz.y;
    z = xyz.z;
}

// Classic BFS, but written iteratively and without real queue, using array instead.
// The function is used to find all the cities that are directly connected to the starting city and save the data in the graph.
// Although the function is quite convoluted recursion was unacceptable as the amount of data caused stack overflows with recurive variant,
// and the iterative version was faster and more memory efficient. 
// Array is used in place of queue due to the project requirements and to ensure fastest possible performance.
void bfs(MapData& m, Node* startNode, XYZ* queue, XYZ start)
{
    static int searchCycleNr = 0;    // Used to mark the tiles that have been visited during this cycle of BFS, persistent between calls.

    int y = 0;                       // Coordinates of the current tile.
    int x = 0;
    int distance = 0;                // Distance from the starting tile (starting city).

    
    queue[0] = start;                            
    int queueHead = 0;
    int queueTail = 1;

    // Classic BFS loop.
    // In each iteration we check the surrounding tiles of the current tile and:
    // - if they are a road tile (have ROAD_SYMBOL) and have not been visited in this cycle, then we add them to the queue
    // - if they are a city tile (have CITY_SYMBOL) and have a corresponding node in the cityNodesMask, then we add a connection between this city node and the starting one.
    // The distance between the tiles is calculated as the number of tiles between the starting tile and the current tile.
    // The distance is used as the weight of the link between the nodes.
    while (queueHead < queueTail)
    {
        unpackXYZ(queue[queueHead], x, y, distance);
        queueHead++;

        if (y - 1 >= 0)
        {
            if (m.map[y - 1][x] == ROAD_SYMBOL && m.lastVisitCycleNr[y - 1][x] != searchCycleNr)
            {
                m.lastVisitCycleNr[y - 1][x] = searchCycleNr;        
                queue[queueTail] = packXYZ(x, y - 1, distance + 1);
                queueTail++;
            }
            else if (m.map[y - 1][x] == CITY_SYMBOL && m.cityNodesMask[y - 1][x] != nullptr)
            {
                startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y - 1][x]));
                m.cityNodesMask[y - 1][x]->addLink(new Link(distance, m.cityNodesMask[y - 1][x], startNode));
            }
        }

        if (y + 1 < m.height)
        {
            if (m.map[y + 1][x] == ROAD_SYMBOL && m.lastVisitCycleNr[y + 1][x] != searchCycleNr)
            {
                m.lastVisitCycleNr[y + 1][x] = searchCycleNr;
                queue[queueTail] = packXYZ(x, y + 1, distance + 1);
                queueTail++;
            }
            else if (m.map[y + 1][x] == CITY_SYMBOL)
            {
                if (m.cityNodesMask[y + 1][x] != nullptr)    
                {
                    startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y + 1][x]));
                    m.cityNodesMask[y + 1][x]->addLink(new Link(distance, m.cityNodesMask[y + 1][x], startNode));
                }
            }
        }

        if (x - 1 >= 0)
        {
            if (m.map[y][x - 1] == ROAD_SYMBOL && m.lastVisitCycleNr[y][x - 1] != searchCycleNr)
            {
                m.lastVisitCycleNr[y][x - 1] = searchCycleNr;
                queue[queueTail] = packXYZ(x - 1, y, distance + 1);
                queueTail++;
            }
            else if (m.map[y][x - 1] == CITY_SYMBOL)
            {
                if (m.cityNodesMask[y][x - 1] != nullptr)
                {
                    startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y][x - 1]));
                    m.cityNodesMask[y][x - 1]->addLink(new Link(distance, m.cityNodesMask[y][x - 1], startNode));
                }
            }
        }

        if (x + 1 < m.width)
        {
            if (m.map[y][x + 1] == ROAD_SYMBOL && m.lastVisitCycleNr[y][x + 1] != searchCycleNr)
            {
                m.lastVisitCycleNr[y][x + 1] = searchCycleNr;
                queue[queueTail] = packXYZ(x + 1, y, distance + 1);
                queueTail++;
            
            }
            else if (m.map[y][x + 1] == CITY_SYMBOL)
            {
                if (m.cityNodesMask[y][x + 1] != nullptr)    
                {
                    startNode->addLink(new Link(distance, startNode, m.cityNodesMask[y][x + 1]));
                    m.cityNodesMask[y][x + 1]->addLink(new Link(distance, m.cityNodesMask[y][x + 1], startNode));
                }     
            }    
        }
    }

    ++searchCycleNr;
}

void findDirectCityConnections(MapData& m, Graph& g)
{
    XYZ queue[m.width * m.height];      // Array of integer triplets used as a queue for BFS.

    for (int i = 0; i < m.height; i++)
    {
        for (int j = 0; j < m.width; j++)
        {
            if (m.map[i][j] == CITY_SYMBOL && m.cityNodesMask[i][j] != nullptr)
            {
                bfs(m, m.cityNodesMask[i][j], queue, packXYZ(j, i, 0));
            }    
        }
    }
}

// Read the flight declaration from input and add it to the graph.
// The flight declaration was given in the form of "city1 city2 time" where time is the time it takes to fly from city1 to city2.
// The time must be a positive integer.
// The function reads the declaration, checks if it's correct and if so adds an edge between the two cities with the given time as the weight.
void read_flight(Graph &g)
{
    int tokens;
    char* flightDeclaration = readString();
    char** flightData = tokenizeString(flightDeclaration, " ", tokens);


    if (flightDeclaration != NULL && flightData != NULL)
    {
        if (tokens == 3)
        {
            if (isNumber(flightData[2]))
            {
                Node* startCity = g.getNode(flightData[0]);
                Node* endCity   = g.getNode(flightData[1]);
                int flightTime  = atoi(flightData[2]);

                if (startCity != nullptr && 
                    endCity != nullptr   && 
                    flightTime > 0)
                {
                    startCity->addLink(new Link(flightTime, startCity, endCity, true));
                }
            }
        }
    }

    free(flightDeclaration);
    free(flightData);
}

void loadFlights(Graph& g)
{
    int flights = 0;
    std::cin >> flights;
    while (flights >= 0)
    {
        read_flight(g);
        flights--;
    }
}
