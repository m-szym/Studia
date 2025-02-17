#pragma once

#include "../lib/CStringHashTable.hpp"
#include "Node.h"
#include "../lib/MinHeapQueue.h"

// The Graph class represent a weighted multi-graph used to store the cities and the connections between them.
// Nodes (corresponding to cities) are stored in an array of pointers.
// Additionally, a (self made) hash table is used for quick lookup of nodes by name of city.
// The class also contains the implementation of Dijkstra's algorithm used to find the shortest path between given two cities.
class Graph
{
    private:
    int nodesNr;
    Node** nodesArray;                                  
    CStringHashTable<Node> nodesNamesHashtable;  

    // Method used to print the results of Dijkstra's algorithm.
    void printDijkstraResults(int previousStep[], int knownDistance[], int endNodeIndex, int mode);

    public:
    Graph(int newNodesNr);
    ~Graph();

    Node* insertNode(Node* node);   // Inserts a new node into the graph (updates both the array of pointers and the hash table)
    Node* getNode(char* name);      // Returns a node by name of city (uses the hash table for lookup).
    Node* getNode(int index);       // Returns a node by index (uses the array of pointers for lookup).

    // Dijkstra's algorithm is used to find the shortest path between two cities.
    // The mode parameter can be used to specify the output format:
    // 0 - print the distance between the two cities
    // 1 - print the path between the two cities

    // The following 2 methods are just a more convenient way to call the main dijkstra method.
    void dijkstra(int startNodeIndex, int endNodeIndex, int mode);      // Overloaded for convenient use of node indeces.
    void dijkstra(char* startCityName, char* endCityName, int mode);    // Overloaded for convenient use of city names.

    // The main Dijkstra's algorithm implementation - core of the whole program.
    // A classical implementation, using self made MinHeapQueue as priority queue.
    // The algorithm is used to find the shortest path between two cities.
    // The mode parameter can be used to specify the output format as described above.
    // This method is called by the two overloaded methods above.
    void dijkstra(Node* startCity, Node* endCity, int mode);            
};