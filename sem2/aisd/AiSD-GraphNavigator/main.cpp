#include "../include/dataReadingAndManip.h"
#include "../include/cstringHelpers.h"


int main()
{
    // read map (in text format) from standard input into MapData object
    MapData m;
    m.load();
    
    // prepare graph of cities on the map
    Graph g(m.citiesNr);

    // load cities from map into the graph
    loadCities(m, g);

    // load flights from stdin, parse them 
    // and add directly into the graph (as directed, weighted edges)
    loadFlights(g);

    // find direct connections (roads) between cities on map (with BFS)
    // and add them to the graph (as undirected, weighted edges)
    findDirectCityConnections(m, g);
    
    // as we don't need the map anymore, release its memory
    m.clear();

    // at this point we have a graph with cities (as vertices) 
    // and connections (i.e. roads and flights) (as edges) between them
    // we can now run the queries,
    // each one asking for the shortest path between two cities
    // The query declaration are given in the format of "city1 city2 mode" where mode is the output mode of the query
    // The mode may be either:
    //      0 - print the distance between the two cities
    //      1 - print the path between the two cities
    int queriesNr = 0;
    int tokens;
    char* queryDeclaration;
    char** queryData;

    std::cin >> queriesNr;

    while (queriesNr >= 0)
    {
        queryDeclaration = readString();
        queryData = tokenizeString(queryDeclaration, " ", tokens);

        if (queryDeclaration != NULL && queryData != NULL)
        {
            if (tokens == 3)
            {
                if (isNumber(queryData[2]))
                {
                    Node* startCity = g.getNode(queryData[0]);
                    Node* endCity   = g.getNode(queryData[1]);
                    int mode        = atoi(queryData[2]);

                    if (startCity != nullptr && 
                        endCity   != nullptr && 
                        mode > 0)
                    {
                        g.dijkstra(startCity, endCity, mode);
                    }
                }
            }
        }

        free(queryDeclaration);
        free(queryData);
        queriesNr--;  
    }
}