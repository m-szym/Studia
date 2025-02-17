#define _CRT_SECURE_NO_WARNINGS
#include "Section.h"

Section::Section()
{
    //std::cout << "Sect null" << std::endl;
	this->attributes = new List2d<Attribute>;
	this->selectors = new List2d<Selector>;
	this->not_empty = false;
}

Section::~Section()
{
    /*std::cout << "~Sect ";
    if (not_empty) std::cout << "not empty";
    else std::cout << "empty";
    std::cout << std::endl;*/

	this->attributes->root_delete_list();
	this->selectors->root_delete_list();

	delete this->attributes;
	delete this->selectors;
}

char* rl_strip(char* string)
{
    int string_i = 0;
    int new_i = 0;
    int real_chars = 0;
    int s = strlen(string) + 1;

    char* st = (char*)malloc(s * sizeof(char));
    char* stt = nullptr;

    for (int i = 0; i < s; i++)
        st[i] = '\0';

    while (string[string_i] != '\0')
    {
        //if ((string_i == 0 && string[string_i] == ' ') || (string_i == (s - 2) && string[string_i] == ' '))
        //{
        //    string_i++;
        //    continue;
        //}

        if (string[string_i] == ' ') {
            if (real_chars == 0) {//pomiñ spacje na pocz¹tku
                string_i++;
                continue;
            }
            else {
                int j = string_i;
                int rc = 0;
                while (string[j] != '\0')
                {
                    if (string[j] != ' ') rc++;;
                    j++;
                }
                if (rc == 0)
                {
                    st[new_i] = '\0';
                    return st;
                }


                
            }
        }real_chars++;



        st[new_i] = string[string_i];

        string_i++;
        new_i++;

    }
    //st[new_i] = '\0';
    return st;
}

Attribute* Section::add_attribute(char* name, char* value)
{
    char* new_name = rl_strip(name);
    char* new_value = rl_strip(value);

    if (!not_empty)
		not_empty = true;
    else {
        Attribute* dup = this->get_attribute_by_name(new_name);
        if (dup != nullptr)
        {
            this->remove_attribute_by_name(new_name);
        }
    }

    //char* new_name = rl_strip(name);
    //char* new_value = rl_strip(value);

	List2d<Attribute>* new_attributes_list_item = attributes->add_after(new Attribute(new_name, new_value));
    free(new_name);
    free(new_value);
	
	return new_attributes_list_item->cont;
}



//Selector* Section::add_selector(char* name)
//{
//    if (!not_empty)
//		not_empty = true;
//    //else
//    //{
//    //    Selector* sel = nullptr;
//    //    sel = this->get_selector_by_name(name);
//    //    if (sel != nullptr)
//    //    {
//    //        this->remove_selector_by_name(name);
//    //    }
//    //    
//    //} 
//     
//	return this->selectors->add_at_end(new Selector(name))->cont;
//    //return this->selectors->add_after(new Selector(name))->cont;
//}

Selector* Section::add_selector(char* name)
{
    if (this != nullptr)
    {
        if (this->selectors != nullptr)
        {
            if (name != NULL)
            {
                char* new_name = rl_strip(name);
                if (new_name != NULL)
                {
                    if (!this->not_empty)
                        this->not_empty = true;
                    else {
                        Selector* dup = this->get_selector_by_name(new_name);
                        if (dup != nullptr)
                        {
                            this->remove_selector_by_name(new_name);
                        }
                    }


                    List2d<Selector>* new_selectors_list_item = nullptr;
                    Selector* ns = new Selector(new_name);
                    if (ns != nullptr)
                    {
                        try {
                            new_selectors_list_item = selectors->add_at_end(ns);
                        }
                        catch (...) {
                            return nullptr;
                        }
                    }
                    free(new_name);

                    if (new_selectors_list_item != nullptr) return new_selectors_list_item->cont;
                }
                free(new_name);
            }
        }
    }
    return nullptr;
}

int Section::count_attributes() const {
    return attributes->root_get_lenght();
}

int Section::count_selectors() const {
    return selectors->root_get_lenght();
}

Attribute *Section::get_attribute_by_name(const char *name) {
    char* new_name = rl_strip((char*)name);
    
    if (this->not_empty != false)
    {
        if (this != nullptr)
        {   
            if (name != NULL)
            //if (this->not_empty == true)
            {
                if (this->attributes != nullptr)
                {
                    if (this->attributes->next != nullptr)
                    {
                        List2d<Attribute>* cursor = this->attributes->next;
                        while (cursor != nullptr)
                        {
                            if (cursor->cont != nullptr)
                            {
                                if (cursor->cont->name != nullptr)
                                {
                                    //if (strstr(cursor->cont->name, name) != NULL)
                                    if (new_name[0] != '\0' && cursor->cont->name[0] != '\0')
                                    {
                                        if (strcmp(cursor->cont->name, new_name) == 0)
                                        {
                                            return cursor->cont;
                                        }
                                    }
                                }
                            }
                            cursor = cursor->next;
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

Selector *Section::get_selector_by_name(const char *name) {
    if (this->selectors != nullptr)
    {
        List2d<Selector>* cursor = this->selectors->next;
        while (cursor != nullptr)
        {
            if (cursor->cont != nullptr)
            {
                if (cursor->cont->name != nullptr)
                {
                    //if (strstr(cursor->cont->name, name) != NULL)
                    if(strcmp(cursor->cont->name, name) == 0)
                    {
                        return cursor->cont;
                    }
                }
            }
            cursor = cursor->next;
        }
    }
    return nullptr;
}

void Section::remove_attribute(Attribute *attribute) {
    List2d<Attribute>* cursor = this->attributes;
    while (cursor != nullptr)
    {
        if (cursor->cont == attribute)
        {
            cursor->remove_self();
            break;
        }
    }
}

void Section::remove_attribute_by_name(const char *name_of_attribute_to_remove) {
    List2d<Attribute>* cursor = this->attributes->next;
    while (cursor != nullptr)
    {
        //if (strstr(cursor->cont->get_name(), name_of_attribute_to_remove) != NULL)
        if (strcmp(cursor->cont->name, name_of_attribute_to_remove) == 0)
        {
            cursor->remove_self();
            break;
        }
        cursor = cursor->next;
    }
}

void Section::remove_selector_by_name(const char* name_of_selector_to_remove) {
    List2d<Selector>* cursor = this->selectors->next;
    while (cursor != nullptr)
    {
        if (strstr(cursor->cont->get_name(), name_of_selector_to_remove) != NULL)
        {
            cursor->remove_self();
            break;
        }
    }
}

int Section::clear_self()
{
    this->attributes->root_delete_list();
    this->selectors->root_delete_list();
    this->not_empty = false;
    return 0;
}

Selector *Section::get_nth_selector(int n) {
    List2d<Selector>* s = this->selectors->next;
    while (s != nullptr)
    {
        if (n == 0) return s->cont;
        else if (n < 0) return nullptr;
        else n--;
        s = s->next;
    }
    return nullptr;
}
