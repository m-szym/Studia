#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#pragma once
class Attribute
{
public:
	char* name;
	char* value;

	Attribute();	
	Attribute(char* name, char* value);

	void set_name(char* name);
	void set_value(char* value);

	const char* get_name();
	const char* get_value();

	~Attribute();
};

