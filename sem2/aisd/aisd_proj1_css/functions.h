#pragma once
#include "includes.h"

char* read_command(int& flag);
char* read_attr(int& flag);
char* read_sel(int& flag);

bool is_number(char* string);

Section* get_nth_notempty_section(int n, List2d<Sections_Package>* root);
List2d<Sections_Package>* get_sections_package_of_nth_notempty_section(int n, List2d<Sections_Package>* root);
int count_all_select_selectors(List2d<Sections_Package>* root, const char* name);
int count_all_select_attributes(List2d<Sections_Package>* root, const char* name);