#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>

template <typename content_type> class List2d
{

public:
	List2d* next;
	List2d* prev;
	content_type* cont;	// zawsze przydziela� dynamicznie

	explicit List2d(content_type* cont = nullptr, List2d* next = nullptr, List2d* prev = nullptr);

	int root_get_lenght();
	int get_lenght_up();
	int get_lenght_down();
	List2d<content_type>* get_first();
	List2d<content_type>* get_last();


	List2d<content_type>* add_after(content_type* content);
	List2d<content_type>* add_before(content_type* content);

	List2d<content_type>* add_at_end(content_type* content);

	void remove_self();
	List2d<content_type>* remove_after();
	List2d<content_type>* remove_before();

	List2d<content_type>* root_delete_list();





	~List2d();
};


template <typename cont> int get_length(List2d<cont>* start);
template <typename cont> List2d<cont>* get_item_at(List2d<cont>* start, unsigned int position);
template <typename cont> List2d<cont>* get_first(List2d<cont>* start);
template <typename cont> List2d<cont>* get_last(List2d<cont>* start);

template <typename cont> void add_before(List2d<cont>* node, cont* content);
template <typename cont> void add_after(List2d<cont>* node, cont* content);

template <typename cont> void add_first(List2d<cont>* start, cont* content);
template <typename cont> void add_last(List2d<cont>* start, cont* content);

template <typename cont> void remove_before(List2d<cont>* node);
template <typename cont> void remove_after(List2d<cont>* node);

template <typename cont> void remove_first(List2d<cont>* start);
template <typename cont> void remove_last(List2d<cont>* start);



template <typename cont> void print_up(List2d<cont>* floor);
template <typename cont> void print_down(List2d<cont>* ceiling);


//		METODY

template <typename content_type> 
List2d<content_type>::List2d(content_type* cont, List2d* next, List2d* prev)
	: cont(cont), next(next), prev(prev)
{
       // std::cout << "List2d" << std::endl;
}

template<typename content_type> 
int List2d<content_type>::root_get_lenght()
{
	//zawsze da 1, bo policzy start
	if (this->prev != nullptr)
		return 0;

	int length = 0;
	List2d<content_type>* tmp = this;
	while (tmp != nullptr)
	{
		length++;
		tmp = tmp->next;
	}
	return length;
}

template<typename content_type>
List2d<content_type>* List2d<content_type>::add_after(content_type* content)
{
	if (this != nullptr)
	{
		auto* new_node = new List2d<content_type>(content);
		new_node->next = this->next;
		new_node->prev = this;
		if (this->next != nullptr)
			this->next->prev = new_node;
		this->next = new_node;
		return new_node;
	}
	return nullptr;
}

template<typename content_type>
List2d<content_type>* List2d<content_type>::add_before(content_type* content)
{
	//uwaga na root
	if (this->prev == nullptr)
		return nullptr;

	auto* new_node = new List2d<content_type>(content);
	new_node->next = this;
	new_node->prev = this->prev;
	if (this->prev != nullptr)
		this->prev->next = new_node;
	this->prev = new_node;
	return new_node;
}

template<typename content_type>
inline List2d<content_type>* List2d<content_type>::add_at_end(content_type* content)
{
	if (this != nullptr)
	{
		if (content != nullptr)
		{
			List2d<content_type>* node = this->get_last();
			if (node != nullptr)
			{
				List2d<content_type>* new_node = node->add_after(content);
				if (new_node != nullptr)
				{
					return new_node;
				}
			}
			
		}
	}
	return nullptr;
}

template<typename content_type>
List2d<content_type>* List2d<content_type>::remove_after()
{
	List2d<content_type>* tmp = this->next;
	this->next = tmp->next;
	if (tmp->next != nullptr)
		tmp->next->prev = this;

	//delete tmp->cont;
	delete tmp;

	return this;
}

template<typename content_type>
List2d<content_type>* List2d<content_type>::remove_before()
{
	//uwaga na root
	if (this->prev == nullptr)
		return nullptr;

	List2d<content_type>* tmp = this->prev;
	this->prev = tmp->prev;
	if (tmp->prev != nullptr)
		tmp->prev->next = this;
	delete tmp;

	return this;
}

template<typename content_type>
List2d<content_type>* List2d<content_type>::root_delete_list()
{
	if (this->prev != nullptr)	//tylko na roocie u�ywa�
		return nullptr;

	while (this->next != nullptr)
	{
		this->remove_after();
	}
	return this;
}



template<typename content_type> 
List2d<content_type>::~List2d()
{
    //std::cout << "~List2d" << std::endl;
	delete this->cont;	//i mie� nadziej�, �e b�dzie ok
}

template<typename content_type>
void List2d<content_type>::remove_self() {
    if (this->prev == nullptr)//root
        return;

    this->prev->remove_after();
}

template<typename content_type>
List2d<content_type> *List2d<content_type>::get_last() {
    List2d<content_type>* cur = this;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}



//		KONIEC METOD
//			FUNKCJE

template <typename cont>
int get_length(List2d<cont>* start)
{
	int length = 0;
	List2d<cont>* tmp = start;
	while (tmp != nullptr)
	{
		length++;
		tmp = tmp->next;
	}
	return length;
}

template<typename cont>
List2d<cont>* get_item_at(List2d<cont>* start, unsigned int position)
{
	int current_position = 0;
	List2d<cont>* tmp = start;
	while (tmp != nullptr)
	{
		if (current_position == position)
			return tmp;
		else if (current_position > position)
			return nullptr;
		else
		{
			current_position++;
			tmp = tmp->next;
		}
	}


}

template<typename cont>
List2d<cont>* get_first(List2d<cont>* start)
{
	List2d<cont>* tmp = start;
	while (tmp != nullptr)
	{
		tmp = tmp->prev;
	}
	return tmp;
}

template<typename cont>
List2d<cont>* get_last(List2d<cont>* start)
{
	List2d<cont>* tmp = start;
	while (tmp != nullptr)
	{
		tmp = tmp->next;
	}
	return tmp;
}


template<typename cont>
void add_before(List2d<cont>* node, cont* content)
{
	//uwaga na root
	auto* new_node = new List2d<cont>(content);
	new_node->next = node;
	new_node->prev = node->prev;
	if (node->prev != nullptr)
		node->prev->next = new_node;
	node->prev = new_node;
}

template<typename cont>
void add_after(List2d<cont>* node, cont* content)
{
	auto* new_node = new List2d<cont>(content);
	new_node->next = node->next;
	new_node->prev = node;
	if (node->next != nullptr)
		node->next->prev = new_node;
	node->next = new_node;
}


template<typename cont>
void add_first(List2d<cont>* start, cont* content)
{
	add_before(get_first(start), content);
}

template<typename cont>
void add_last(List2d<cont>* start, cont* content)
{
	add_after(get_last(start), content);
}


template<typename cont>
void remove_before(List2d<cont>* node)
{
	//uwaga na root
	List2d<cont>* tmp = node->prev;
	node->prev = tmp->prev;
	if (tmp->prev != nullptr)
		tmp->prev->next = node;
	delete tmp;
}

template<typename cont>
void remove_after(List2d<cont>* node)
{
	List2d<cont>* tmp = node->next;
	node->next = tmp->next;
	if (tmp->next != nullptr)
		tmp->next->prev = node;
	delete tmp;
}


template<typename cont>	//TODO
void remove_first(List2d<cont>* start)
{

}

template<typename cont>	//TODO
void remove_last_any_node(List2d<cont>* start)
{
	remove_after(get_last(start));
}


template<typename cont>
void remove_node(List2d<cont>* node)
{
	if (node->prev != nullptr)
		node->prev->next = node->next;
	if (node->next != nullptr)
		node->next->prev = node->prev;
	delete node;
}


template<typename cont>
void print_up(List2d<cont>* floor)
{
	//if (floor->cont == nullptr)
	if (floor->next != nullptr)
		floor = floor->next;
	else
		return;

	while (floor != nullptr)
	{
		std::cout << floor->cont << std::endl;
		floor = floor->next;
	}
}


template<typename cont>
void print_down(List2d<cont>* ceiling)
{
	//if (ceiling->cont == nullptr)
	if (ceiling->prev != nullptr)
		ceiling = ceiling->prev;
	else
		return;

	while (ceiling != nullptr)
	{
		std::cout << ceiling->cont << std::endl;
		ceiling = ceiling->prev;
	}
}












