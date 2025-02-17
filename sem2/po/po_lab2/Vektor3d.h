//
// Created by M Sz on 08/03/2023.
//

#ifndef PO_LAB2_VEKTOR3D_H
#define PO_LAB2_VEKTOR3D_H


#include <iostream>

class Vektor3d {
    double array[3]; //pole z tablicą liczb
public:
    Vektor3d(double x1, double x2, double x3); //konstruktor
    const double& operator[](std::size_t i) const;

};


#endif //PO_LAB2_VEKTOR3D_H
