#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>

#include "cstringHelpers.h"
#include "../lib/LinkedList.hpp"

class Link;

// Class representing a node in a graph and in the context of this program - a city on map.
// As such it contains a name of the city, an index (of the node in the graph) and a list of links (edges) to other nodes. 
class Node
{
private:
    char* name;
    int index;
    LinkedList<Link*> links;

public:
    Node();
    Node(char* name, int index = -1);
    ~Node();

    void print();

    void setName(char* newName);
    Link* addLink(Link* newLink);
    
    char* getName() { return name; }
    int getIndex() { return index; }
    LinkedList<Link*>& getLinks() { return links; }

friend class Graph;
friend class Link;
};

// Class representing a link (edge) between two nodes in a graph and in the context of this program - a connection between two cities.
// As such it contains a length of the link, a flag indicating if the link represents a flight instead of road and pointers to the connected nodes.
class Link
{
private:
    int length;
    bool special;
    Node* startNode;
    Node* endNode;

public:
    Link(int newLength, Node* newStartNode, Node* newEndNode, bool isSpecial = false);

    void print();

    int getLength() { return length; }
    bool isSpecial() { return special; }
    Node* getStartNode() { return startNode; }
    Node* getEndNode() { return endNode; }

friend class Node;
friend class Graph;
};