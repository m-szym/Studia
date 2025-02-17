#include "Attribute.h"

Attribute::Attribute()
	: name(nullptr), value(nullptr)
{
    //std::cout << "Att null" << std::endl;
}

Attribute::Attribute(char* name, char* value)
{
	this->name = new char[strlen(name)+1];
	this->value = new char[strlen(value)+1];
	strcpy(this->name, name);
	strcpy(this->value, value);
    //std::cout << "Att" << name << ":" << value << std::endl;
}

Attribute::~Attribute()
{
    /*std::cout << "~Att ";
    if (name != nullptr) std::cout << name;
    else std::cout << "null";
    std::cout << " : ";
    if (value != nullptr) std::cout << value;
    else std::cout << "null";
    std::cout << std::endl;*/

	delete this->name;
	delete this->value;
}

void Attribute::set_name(char* name)
{
	if (this->name != nullptr)
		delete this->name;
	this->name = new char[strlen(name)];
	strcpy(this->name, name);
}

void Attribute::set_value(char* value)
{
	if (this->value != nullptr)
		delete this->value;
	this->value = new char[strlen(value)];
	strcpy(this->value, value);
}

const char* Attribute::get_name()
{
	return this->name;
}

const char* Attribute::get_value()
{
	return this->value;
}



