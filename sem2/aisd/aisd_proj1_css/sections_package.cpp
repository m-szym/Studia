#include "Sections_Package.h"

Sections_Package::Sections_Package()
{
    //std::cout << "SectPack\n";
	filled = 0;
}

Sections_Package::~Sections_Package()
{
    //std::cout << "~SectPack " << filled << std::endl;
	//powinien automatycznie  destruktory dla sekcji w tablicy
}

Section* Sections_Package::get_nth_section(int n)
{
	if (n >= SECTIONS_PACKAGE_SIZE)
		return nullptr;
	else
		return &(sections[n]);
}

Section* Sections_Package::get_next_empty_section()
{
	for (auto & section : sections)
	{
		if (section.not_empty == false)
			return &section;
	}
	return nullptr;
}

Section* Sections_Package::get_first_section()
{
	return &(sections[0]);
}

Section* Sections_Package::get_last_section()
{
	return &(sections[SECTIONS_PACKAGE_SIZE-1]);
}

Section* Sections_Package::get_first_empty_section()
{
	return this->get_next_empty_section();
}

Section* Sections_Package::get_last_not_empty_section()
{
	for (int i = SECTIONS_PACKAGE_SIZE-1; i >= 0; i--)
	{
		if (sections[i].not_empty)
			return &(sections[i]);
	}
	return nullptr;
}

int Sections_Package::count_attributes_all()
{
	int attributes = 0;
	for (auto & section : sections)
	{
		if (section.not_empty)
			attributes += section.count_attributes();
	}
	return attributes;
}

int Sections_Package::count_selectors_all()
{
	int selectors = 0;
	for (auto & section : sections)
	{
		if (section.not_empty)
			selectors += section.count_selectors();
	}
	return selectors;
}

void Sections_Package::clear_section_n(int n)
{
	if (sections[n].not_empty)
	{
		sections[n].attributes->root_delete_list();
		sections[n].selectors->root_delete_list();
		sections[n].not_empty = false;
	}
}

bool Sections_Package::has_empty_section() {
    for (auto & section : sections) {
        if (!section.not_empty)
            return true;
    }
    return false;
}

int Sections_Package::count_attributes_in_nth_section(int n) {
    if (n < SECTIONS_PACKAGE_SIZE)
        return this->sections[n].count_attributes();
    else
        return -1;
}

void Sections_Package::remove_attribute_by_name_from_nth_section(int n, char *name_of_attribute_to_remove) {
    if (n < SECTIONS_PACKAGE_SIZE)
       this->sections[n].remove_attribute_by_name(name_of_attribute_to_remove);
    else
        return;
}
