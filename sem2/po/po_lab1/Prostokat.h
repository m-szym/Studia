//
// Created by M Sz on 27/02/2023.
//

#ifndef LAB1_PROSTOKAT_H
#define LAB1_PROSTOKAT_H

#include "FiguraPlaska.h"

class Prostokat : public FiguraPlaska {
private:
    double a, b;
protected:
    void Wypisz(std::ostream& out) const override;
public:
    Prostokat(double a, double b);

    double GetA() const;

    double GetB() const;

    void SetA(double a);

    void SetB(double b);

    double Obwod() override;
    double Pole() override;

    ~Prostokat() override;
};


#endif //LAB1_PROSTOKAT_H
