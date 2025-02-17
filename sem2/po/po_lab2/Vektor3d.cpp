//
// Created by M Sz on 08/03/2023.
//

#include "Vektor3d.h"

Vektor3d::Vektor3d(double x1, double x2, double x3) {
    std::cout << "KStart(" << x1 << "," << x2 << ")" << std::endl;
    array[0] = x1;
    array[1] = x2;
    array[2] = x3;
}

const double &Vektor3d::operator[](std::size_t i) const {
    return array[i];
}