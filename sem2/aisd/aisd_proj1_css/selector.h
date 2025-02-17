#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

#pragma once
class Selector
{
public:
	char* name;

	Selector();
	Selector(char* name);

	void set_name(char* name);
	const char* get_name();

	~Selector();
};

