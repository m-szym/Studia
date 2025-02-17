//
// Created by M Sz on 27/02/2023.
//

#ifndef LAB1_FIGURAPLASKA_H
#define LAB1_FIGURAPLASKA_H

#include <iostream>

class FiguraPlaska {
protected:
    virtual void Wypisz(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const FiguraPlaska& figura);

public:

    virtual double Pole() = 0;

    virtual double Obwod() = 0;

    virtual ~FiguraPlaska();
};


#endif //LAB1_FIGURAPLASKA_H
