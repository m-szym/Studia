//
// Created by M Sz on 27/02/2023.
//

#include "Prostokat.h"
#include <iostream>

Prostokat::Prostokat(double a, double b)
: a(a), b(b) {
    std::cout << "Kontruktor prostokąta(" << a << "," << b <<")" << std::endl;
}

double Prostokat::GetA() const {
    return a;
}

double Prostokat::GetB() const {
    return b;
}

void Prostokat::SetA(double a) {
    this->a = a;
}

void Prostokat::SetB(double a) {
    this->a = b;
}


double Prostokat::Obwod() {
    return 2*(a + b);
}
double Prostokat::Pole() {
    return a * b;
}
void Prostokat::Wypisz(std::ostream& out) const {
    //TODO 3
}
Prostokat::~Prostokat() {
    std::cout << "Dekontruktor prostokąta(" << a << "," << b <<")" << std::endl;
}
