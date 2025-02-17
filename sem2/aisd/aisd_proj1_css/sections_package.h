#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Section.h"
#include "constants.h"

class Sections_Package
{
public:
	Section sections[SECTIONS_PACKAGE_SIZE];
	unsigned int filled;

	Sections_Package();
	~Sections_Package();



	Section* get_nth_section(int n);

	//Section* get_next_section();
	Section* get_next_empty_section();
	//Section* get_next_not_empty_section();

	Section* get_first_section();
	Section* get_last_section();

	Section* get_first_empty_section();
	Section* get_last_not_empty_section();

	int count_attributes_all();
	int count_selectors_all();

	void clear_section_n(int n);

    bool has_empty_section();


	Attribute* add_attribute_to_nth_section(int n, char* name, char* value);
	Selector* add_selector_to_nth_section(int n, char* name);

	void remove_attribute_by_name_from_nth_section(int n, char* name_of_attribute_to_remove);



	int count_attributes_in_nth_section(int n);
	int count_selectors_in_nth_section(int n);


};

