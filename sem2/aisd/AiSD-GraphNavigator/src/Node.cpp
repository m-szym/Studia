#include "../include/Node.h"

Node::Node()
    : name(nullptr), index(-1), links()
{
    links = LinkedList<Link*>();
}

Node::Node(char* name, int index = -1)
    : index(index)
{
    links = LinkedList<Link*>();

    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
}

Node::~Node()
{
    delete[] this->name;
}

Link* Node::addLink(Link* new_link)
{
    links.pushFront(new_link);
    return new_link;
}

void Node::setName(char* new_name)
{
    this->name = new char[strlen(new_name)+1];
    strcpy(this->name, new_name);
}


void Node::print()
{
    LinkedListNode<Link*>* currentLink = links.getHead();

    std::cout << "Wezeł - miasto o nazwie " << name << " o " << links.getSize() << " drogach o numerze " << index << "\n";
    int i = 0;
    while (currentLink != nullptr)
    {        
        std::cout << i;
        i++;
        currentLink->print();
        
        currentLink = currentLink->getNext();
        
    }
}


Link::Link(int newLength, Node* newStartNode, Node* newEndNode, bool isSpecial = false)
    : length(newLength), startNode(newStartNode), endNode(newEndNode), special(isSpecial)
{}


void Link::print()
{
    if (!special) 
        std::cout << "\tDroga o dlugości: " << length << " z miasta ";
    else if (special) 
        std::cout << "\tLot o dlugości: " << length << " z miasta ";

    if 
        (startNode != nullptr) 
        std::cout << startNode->name;
    else 
        std::cout << "null start";

    std::cout << " do miasta ";

    if (endNode != nullptr) 
        std::cout << endNode->name;
    else 
        std::cout << "null end";
    
    std::cout << "\n";
}
