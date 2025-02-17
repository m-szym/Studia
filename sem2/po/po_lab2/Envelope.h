//
// Created by M Sz on 08/03/2023.
//
#include <iostream>
using namespace std;
#include "Vector.h"
#ifndef PO_LAB2_ENVELOPE_H
#define PO_LAB2_ENVELOPE_H

class Envelope
{
    Vector vector;
    friend std::ostream& operator<<(std::ostream&, const Envelope&); public:
    Envelope(const Vector& vector) :
            vector{vector} {
        std::cout << "Envelope(const Vector&)" << std::endl;
    }
    Envelope(Vector&& vector) : vector{std::move(vector)} {
        std::cout << "Envelope(Vector&&)" << std::endl; }
    Envelope(const Envelope& other) : vector{other.vector} {
        std::cout << "Envelope(const Envelope&)" << std::endl; }
    Envelope(Envelope&& other) : vector{std::move(other.vector)} {
        std::cout << "Envelope(Envelope&&)" << std::endl; }
    Envelope& operator=(const Envelope& right) {
        std::cout << "operator=(const Envelope&)" << std::endl; Envelope tmp(right);
        std::cout << "operator=(const Envelope&) swap początek" <<
                  std::endl;
        std::swap(vector, tmp.vector);
        std::cout << "operator=(const Envelope&) swap koniec" << std::endl;
        return *this;
    }
    Envelope& operator=(Envelope&& right) {
        std::cout << "operator=(Envelope&&)" << std::endl; vector = std::move(right.vector);
        return *this;
    }
    ~Envelope() {
        std::cout << "~Envelope()" << std::endl; }
};

#endif //PO_LAB2_ENVELOPE_H
