//
// Created by M Sz on 15/05/2023.
// Adapted from https://www.redblobgames.com/grids/hexagons/
// Some changes were made to ease board representation
//

#ifndef GIPF_HEX_H
#define GIPF_HEX_H

#include <cmath>
#include <vector>
#include <iostream>

class Hex;

const int HEX_DIRECTIONS_COUNT = 6;
enum DIRS {
    SE,
    NE,
    N,
    NW,
    SW,
    S
};

class Hex {
private:
    int iq, ir;

public:
    Hex(int q, int r);
    Hex(int q, int r, int s);   //TODO: check s != -q - r

    int distance(const Hex& other) const;
    int length() const;

    static Hex hex_direction(int direction) ;
    Hex hex_neighbour(int direction) const;
    int neighbour_direction(const Hex& neighbour) const;

    int q() const;
    int r() const;
    int s() const;

    void print() const {
        std::cout << "q: " << iq << " r: " << ir << " s: " << s() << std::endl;
    }
};

bool operator==(const Hex& first, const Hex& second);
bool operator!=(const Hex& first, const Hex& second);
Hex operator+(const Hex& first, const Hex& second);
Hex operator-(const Hex& first, const Hex& second);
Hex operator*(const Hex& first, int k);

int length(const Hex& hex);
int distance(const Hex& first, const Hex& second);

Hex hex_direction(int direction);
Hex hex_neighbour(const Hex& hex, int direction);

Hex rotate_right(const Hex& hex);
Hex rotate_left(const Hex& hex);

inline int invert_direction(int direction) { return (direction + (HEX_DIRECTIONS_COUNT / 2)) % HEX_DIRECTIONS_COUNT; }

const Hex EMPTY_HEX(INT_MAX, INT_MAX);

const std::vector<Hex> hex_directions = {
        {1,  0},
        {1,  -1},
        {0,  -1},
        {-1, 0},
        {-1, 1},
        {0,  1}
};

namespace std {
    template <> struct hash<Hex> {
        size_t operator()(const Hex& h) const {
            hash<int> int_hash;
            size_t hq = int_hash(h.q());
            size_t hr = int_hash(h.r());
            return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
        }
    };
}
#endif //GIPF_HEX_H
