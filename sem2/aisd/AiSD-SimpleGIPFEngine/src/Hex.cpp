//
// Created by M Sz on 15/05/2023.
//

#include "../include/Hex.h"

Hex::Hex(int q, int r)
    : iq(q), ir(r)
{}

int Hex::q() const {
    return iq;
}

int Hex::r() const {
    return ir;
}

int Hex::s() const {
    return -iq -ir;
}


int Hex::distance(const Hex &other) const {
    return (*this - other).length();
}

int Hex::length() const {
    return int((abs(iq) + abs(ir) + abs(s())) / 2);
}

Hex Hex::neighbourInDirection(int direction) const {
    return (*this + HEX_DIRS[direction]);
}

int Hex::neighbour_direction(const Hex& neighbour) const {
    for (int i = 0; i < HEX_DIRECTIONS_COUNT; i++) {
        if (neighbour == HEX_DIRS[i])
            return i;
    }
    return -1;
}


bool operator==(const Hex &first, const Hex &second) {
    if (first.q() == second.q() && first.r() == second.r() && first.s() == second.s())
        return true;
    else
        return false;
}

bool operator!=(const Hex &first, const Hex &second) {
    return !(first == second);
}

Hex operator+(const Hex &first, const Hex &second) {
    return {first.q() + second.q(), first.r() + second.r()};
}

Hex operator-(const Hex &first, const Hex &second) {
    return {first.q() - second.q(), first.r() - second.r()};
}

Hex operator*(const Hex &first, int k) {
    return {first.q() * k, first.r() * k};
}

int length(const Hex &hex) {
    return (int) (abs(hex.q()) + abs(hex.r()) + abs(hex.s())) / 2;
}

int distance(const Hex &first, const Hex &second) {
    return (int) length((first - second));
}

Hex neighbourInDirection(const Hex &hex, int direction) {
    return (hex + HEX_DIRS[direction]);
}

Hex rotateRight(const Hex &hex) {
    return {-hex.r(), -hex.s()};
}

Hex rotateLeft(const Hex &hex) {
    return {-hex.s(), -hex.q()};
}
