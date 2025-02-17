#include "Attribute.h"
#include "Selector.h"
#include "List2d.h"
#define _CRT_SECURE_NO_WARNINGS
#pragma once
class Section
{
public:
	List2d<Attribute>* attributes;
	List2d<Selector>* selectors;
	bool not_empty;

	Section();
	~Section();

	Attribute* add_attribute(char* name, char* value);
	Selector* add_selector(char* name);

    Attribute* get_attribute_by_name(const char* name);
    Selector* get_selector_by_name(const char* name);

    void remove_attribute(Attribute* attribute);
	void remove_attribute_by_name(const char* name_of_attribute_to_remove);
	void remove_selector_by_name(const char* name_of_selector_to_remove);

	int count_attributes() const;
	int count_selectors() const;

	Attribute* get_first_attribute();
	Selector* get_first_selector();

	Attribute* get_nth_attribute(int n);
	Selector* get_nth_selector(int n);

	Attribute* get_last_attribute();
	Selector* get_last_selector();

    int clear_self();
};

char* rl_strip(char* string);
