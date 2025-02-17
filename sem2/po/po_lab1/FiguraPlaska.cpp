//
// Created by M Sz on 27/02/2023.
//

#include "FiguraPlaska.h"

std::ostream& operator<<(std::ostream& os, const FiguraPlaska& figura) {
    figura.Wypisz(os);
    return os;
}

FiguraPlaska::~FiguraPlaska() {

}
