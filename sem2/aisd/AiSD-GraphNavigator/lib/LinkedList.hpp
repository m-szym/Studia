#define _CRT_SECURE_NO_WARNINGS
#pragma once
#ifndef LINKEDLIST_HPP

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <functional>

template <typename T>
class LinkedListNode
{
private:
    T data;
    LinkedListNode* next;
    LinkedListNode* prev;
public:
    LinkedListNode(T data, LinkedListNode* next = nullptr, LinkedListNode* prev = nullptr) 
        : data(data), next(next), prev(prev) {}
    ~LinkedListNode() {}

    T getData() { return data; }
    LinkedListNode* getNext() { return next; }
    LinkedListNode* getPrev() { return prev; }

    void setData(T data) { this->data = data; }
    void setNext(LinkedListNode* next) { this->next = next; }
    void setPrev(LinkedListNode* prev) { this->prev = prev; }


    LinkedListNode* removeSelf() {
        if (prev != nullptr)
            prev->setNext(next);
        if (next != nullptr)
            next->setPrev(prev);
        return this;
    }
    void print() { std::cout << data << " "; }

friend class LinkedList;
};



template <typename T>
class LinkedList
{
private:
    LinkedListNode<T>* head;
    LinkedListNode<T>* tail;
    int size;

public:
    LinkedList()                                        // empty constructor
        : head(nullptr), tail(nullptr), size(0) {}
    LinkedList(T data);                                 // data constructor
    LinkedList(const LinkedList& other);                // copy constructor
    LinkedList(std::initializer_list<T> initList);      // initializer list constructor
    LinkedList(LinkedList&& other);                     // move constructor
    LinkedList& operator=(const LinkedList& other);     // copy assignment
    LinkedList& operator=(LinkedList&& other);          // move assignment
    ~LinkedList() { clear(); }


    void print();

    void pushBack(T data);
    void pushFront(T data);
    void setData(T data, int index);
    void insert(T data, int index);
    void insertAfter(T data, LinkedListNode<T>* node);
    void insertBefore(T data, LinkedListNode<T>* node);


    int getSize() { return size; }
    T getData(int index);
    T getHeadData() { return head->getData(); }
    T getTailData() { return tail->getData(); }
    LinkedListNode<T>* getHead() { return head; }
    LinkedListNode<T>* getTail() { return tail; }
    LinkedListNode<T>* find(T data);
    LinkedListNode<T>* find(int index);
    LinkedListNode<T> popBack();
    LinkedListNode<T> popFront();

    void clear();
    void remove(int index);
    void remove(T data);
    void remove(LinkedListNode<T>* node);

    T getData(std::function<bool(T)> predicate);
    void remove(std::function<bool(T)> predicate);


    void reverse();
    void swap(LinkedList& other);


};

template <typename T>
LinkedList<T>::LinkedList(T data)
    : head(new LinkedListNode<T>(data)), tail(head), size(1)
{}

template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> initList)
    : head(nullptr), tail(nullptr), size(0)
{
    for (auto it = initList.begin(); it != initList.end(); it++)
        pushBack(*it);
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other)
    : head(nullptr), tail(nullptr), size(0)
{
    LinkedListNode<T>* current = other.head;
    while (current != nullptr)
    {
        pushBack(current->getData());
        current = current->getNext();
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other)
    : head(other.head), tail(other.tail), size(other.size)
{
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template <typename T>
void LinkedList<T>::pushBack(T data)
{
    if (head == nullptr)
    {
        head = new LinkedListNode<T>(data);
        tail = head;
    }
    else
    {
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data, nullptr, tail);
        tail->setNext(newNode);
        tail = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::pushFront(T data)
{
    if (head == nullptr)
    {
        head = new LinkedListNode<T>(data);
        tail = head;
    }
    else
    {
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data, head);
        head->setPrev(newNode);
        head = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::setData(T data, int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    LinkedListNode<T>* current = head;
    for (int i = 0; i < index; i++)
        current = current->getNext();
    current->setData(data);
}

template <typename T>
void LinkedList<T>::insert(T data, int index)
{
    if (index < 0 || index > size)
        throw std::out_of_range("Index out of range");

    if (index == 0)
        pushFront(data);
    else if (index == size)
        pushBack(data);
    else
    {
        LinkedListNode<T>* current = head;
        for (int i = 0; i < index; i++)
            current = current->getNext();
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data, current, current->getPrev());
        current->getPrev()->setNext(newNode);
        current->setPrev(newNode);
        size++;
    }
}

template <typename T>
void LinkedList<T>::insertAfter(T data, LinkedListNode<T>* node)
{
    if (node == tail)
        pushBack(data);
    else
    {
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data, node->getNext(), node);
        node->getNext()->setPrev(newNode);
        node->setNext(newNode);
        size++;
    }
}

template <typename T>
void LinkedList<T>::insertBefore(T data, LinkedListNode<T>* node)
{
    if (node == head)
        pushFront(data);
    else
    {
        LinkedListNode<T>* newNode = new LinkedListNode<T>(data, node, node->getPrev());
        node->getPrev()->setNext(newNode);
        node->setPrev(newNode);
        size++;
    }
}

template <typename T>
T LinkedList<T>::getData(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    LinkedListNode<T>* current = head;
    for (int i = 0; i < index; i++)
        current = current->getNext();
    return current->getData();
}

template <typename T>
LinkedListNode<T>* LinkedList<T>::find(T data)
{
    LinkedListNode<T>* current = head;
    while (current != nullptr)
    {
        if (current->getData() == data)
            return current;
        current = current->getNext();
    }
    return nullptr;
}

template <typename T>
LinkedListNode<T>* LinkedList<T>::find(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    LinkedListNode<T>* current = head;
    for (int i = 0; i < index; i++)
        current = current->getNext();
    return current;
}

template <typename T>
LinkedListNode<T> LinkedList<T>::popBack()
{
    if (size == 0)
        throw std::out_of_range("List is empty");

    LinkedListNode<T>* node = tail;
    tail = tail->getPrev();
    if (tail != nullptr)
        tail->setNext(nullptr);
    else
        head = nullptr;
    size--;
    return *node;
}

template <typename T>
LinkedListNode<T> LinkedList<T>::popFront()
{
    if (size == 0)
        throw std::out_of_range("List is empty");

    LinkedListNode<T>* node = head;
    head = head->getNext();
    if (head != nullptr)
        head->setPrev(nullptr);
    else
        tail = nullptr;
    size--;
    return *node;
}

template <typename T>
void LinkedList<T>::clear()
{
    while (size > 0)
        delete popBack();
}

template <typename T>
void LinkedList<T>::remove(int index)
{
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    if (index == 0)
        popFront();
    else if (index == size - 1)
        popBack();
    else
    {
        LinkedListNode<T>* current = head;
        for (int i = 0; i < index; i++)
            current = current->getNext();
        current->getPrev()->setNext(current->getNext());
        current->getNext()->setPrev(current->getPrev());
        size--;
        delete current;
    }
}

template <typename T>
void LinkedList<T>::remove(T data)
{
    LinkedListNode<T>* current = head;
    while (current != nullptr)
    {
        if (current->getData() == data)
        {
            if (current == head)
                popFront();
            else if (current == tail)
                popBack();
            else
            {
                current->getPrev()->setNext(current->getNext());
                current->getNext()->setPrev(current->getPrev());
                size--;
                delete current;
            }
            return;
        }
        current = current->getNext();
    }
}

template <typename T>
void LinkedList<T>::remove(LinkedListNode<T>* node)
{
    if (node == head)
        popFront();
    else if (node == tail)
        popBack();
    else
    {
        node->getPrev()->setNext(node->getNext());
        node->getNext()->setPrev(node->getPrev());
        size--;
        delete node;
    }
}

template <typename T>
void LinkedList<T>::remove(std::function<bool(T)> predicate)
{
    LinkedListNode<T>* current = head;
    while (current != nullptr)
    {
        if (predicate(current->getData()))
        {
            LinkedListNode<T>* temp = current;
            current = current->getNext();
            remove(temp);
        }
        else
            current = current->getNext();
    }
}

template <typename T>
void LinkedList<T>::reverse()
{
    LinkedListNode<T>* current = head;
    while (current != nullptr)
    {
        LinkedListNode<T>* temp = current->getNext();
        current->setNext(current->getPrev());
        current->setPrev(temp);
        current = temp;
    }
    std::swap(head, tail);
}

template <typename T>
void LinkedList<T>::swap(LinkedList& other)
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
{
    if (this != &other)
    {
        clear();
        LinkedListNode<T>* current = other.head;
        while (current != nullptr)
        {
            pushBack(current->getData());
            current = current->getNext();
        }
    }
    return *this;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other)
{
    if (this != &other)
    {
        clear();
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}

template <typename T>
void LinkedList<T>::print()
{
    LinkedListNode<T>* current = head;
    while (current != nullptr)
    {
        current->print();
        current = current->getNext();
    }
    std::cout << std::endl;
}


template <typename T>
T LinkedList<T>::getData(std::function<bool(T)> predicate) {
    LinkedListNode<T>* current = head;
    while (current != nullptr) {
        if (lambda(current->getData())) {
            return current->getData();
        }
        current = current->getNext();
    }
    return nullptr;
}

#endif // !LINKEDLIST_HPP
