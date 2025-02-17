//
// Created by M Sz on 08/03/2023.
//

#ifndef PO_LAB2_VECTOR_H
#define PO_LAB2_VECTOR_H

#include <initializer_list>
#include <iostream>
#include <algorithm>

class Vector {
    double* array;
    std::size_t size;
public:
//Parametr typu std::initializer_list pozwoli na uruchomienie konstruktora
//z dowolną liczbą wystąpień liczb typu double. Będzie to wyglądało jak
//inicjalizacjia tablicy. Przykład:
//Vector v1({1,2,3,4,5,5.5});
//lub
//Vector v1{1,2,3,4,5,5.5};
//lub
//Vector v1 = {1,2,3,4,5,5.5};
//Jest to cecha C++11
    Vector(std::initializer_list<double> initList)
            : size{initList.size()}, array{new double[initList.size()]} {
        std::cout << "Vector(std::initializer_list)" << std::endl; std::size_t i = 0;
        for(double v : initList)
        {
            array[i] = v;
            i++; }
    }
    Vector(const Vector& other) //Konstruktor kopiujacy
            : size{other.size}, array{new double[other.size]} {
        std::cout << "Vector(const Vector&)" << std::endl;
        for(std::size_t i=0; i < size; i++) {
            array[i] = other.array[i];
        }
    }
    Vector(Vector&& other) {
        std::cout << "Vector(Vector&&)" << std::endl;
        array = other.array;
        size = other.size;

        other.array = nullptr;
        other.size = 0;
    }
    Vector(std::size_t size)
            : size{size}, array{new double[size]}
    {
        std::cout << "Vector("<< size << ")" << std::endl;
    }

    Vector()
            : Vector(0)
    {
        std::cout << "Vector()" << std::endl;
    }
    Vector(std::size_t size, double init)
        : Vector(size)
    {
        for(std::size_t i = 0; i < size; i++) {
            array[i] = init;
        }
    }
//Implementacja operatora przypisania z wykorzystanie copy-swap
    Vector& operator=(const Vector& right) {
        std::cout << "operator=(const Vector&)" << std::endl;
        Vector tmp = right; //Tworzenie obiektu tymczasowego
        std::swap(array,tmp.array);// Zamiana wskaźników na tablic miejscami
        std::swap(size,tmp.size); //Zamiana informacji o wielkości tablicy
        return *this;
    }
//Po wyjściu z ciała operatora obiekt tmp jest niszczony
// a wraz z nim stara zawartość obiektu głównego

    Vector& operator=(Vector&& right) {
        std::cout << "operator=(Vector&&)" << std::endl;
        std::swap(array,right.array); //Zamiana wskaźników na tablice miejscami
        std::swap(size,right.size); //Zamiana informacji o wielkości tablicy
        return *this;
    }
    //Po wyjściu z ciała operatora obiekt, na który wskazuje referancja na right
    //został pozostawiony w poprawnym stanie.

    std::size_t GetSize() const { return size;
    }
    double& operator[](std::size_t i) {
        return array[i];
    }
    const double& operator[](std::size_t i) const {
        return array[i];
    }
    ~Vector() {
        std::cout << "~Vector()" << std::endl;
        if(array != nullptr)
        {
            std::cout << "Releasing memory " << array << std::endl;
            delete[] array;
        }
    }
};


#endif //PO_LAB2_VECTOR_H
