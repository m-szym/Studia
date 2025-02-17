#include "Selector.h"

Selector::Selector()
	: name(nullptr)
{
    //std::cout << "Sel null" << std::endl;
}

Selector::Selector(char* name)
{
	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
    //std::cout << "Sel " << name << std::endl;
}

void Selector::set_name(char* name)
{
    delete this->name;
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
}

const char* Selector::get_name()
{
	return this->name;
}

Selector::~Selector()
{
    //std::cout << "~Sel";
    //if (name != nullptr) std::cout << name << std::endl;
    //else std::cout << "null" << std::endl;
	delete this->name;
}