//
// Created by M Sz on 15/05/2023.
//

#ifndef GIPF_HEX_H
#define GIPF_HEX_H

#include <cmath>
#include <vector>
#include <iostream>
#include <climits>

// Enum DIRS represents the 6 directions in a hexagonal grid.
// In a system where the hexagon is oriented with one of its vertices pointing up.
const int HEX_DIRECTIONS_COUNT = 6;
enum DIRS {
    SE,
    NE,
    N,
    NW,
    SW,
    S
};

// Class Hex represents a single hexagon in a hexagonal grid.
// It is defined by three coordinates: q, r, s on a 3 axis system.
// The sum of these coordinates is always 0.
// The class provides methods for calculating distance between hexagons, length of a hexagon, and other basic operations.
// It also provides a set of operators for basic arithmetic
// and comparison
class Hex {
private:
    int iq, ir;

public:
    Hex(int q, int r); 

    // Length of a hexagon - the distance from the center to any of its vertices
    int length() const;
    // Distance between two hexagons
    int distance(const Hex& other) const;
    // Returns the neighbour of a hexagon in a given direction
    Hex neighbourInDirection(int direction) const;
    // Returns the direction of a neighbour of a hexagon
    int neighbour_direction(const Hex& neighbour) const;

    // Getters
    int q() const;
    int r() const;
    int s() const;

    void print() const {
        std::cout << "q: " << iq << " r: " << ir << " s: " << s() << std::endl;
    }
};

// Operators for comparison 
bool operator==(const Hex& first, const Hex& second);
bool operator!=(const Hex& first, const Hex& second);

// Addition and subtraction of two hexagons gives a new heaxgon with coordinates 
// equal to the sum or difference of the coordinates of the two hexagons
Hex operator+(const Hex& first, const Hex& second);
Hex operator-(const Hex& first, const Hex& second);

// Multiplication of a hexagon by a scalar gives a new hexagon with coordinates 
// equal to the product of the coordinates of the hexagon and the scalar
Hex operator*(const Hex& first, int k);

// Returns the distance between two hexagons
int distance(const Hex& first, const Hex& second);
// Returns the neighbour of given hexagon in a given direction
Hex neighbourInDirection(const Hex& hex, int direction);

// Returns new Hex object representing the rotation of the given Hex object to the right or left by 60 degrees
Hex rotateRight(const Hex& hex);
Hex rotateLeft(const Hex& hex);

inline int invert_direction(int direction) { return (direction + (HEX_DIRECTIONS_COUNT / 2)) % HEX_DIRECTIONS_COUNT; }

// Hex object representing an empty hexagon - used as a default value
const Hex EMPTY_HEX(INT_MAX, INT_MAX);

// Directions in a hexagonal grid expressed as a vector of Hex objects
// Due to the nature of Hex implementation adding one of these Hex objects to another Hex object
// will result in a new Hex object that is the neighbour of the original Hex object in the direction represented by the Hex object in the vector
const std::vector<Hex> HEX_DIRS = {
        {1,  0},
        {1,  -1},
        {0,  -1},
        {-1, 0},
        {-1, 1},
        {0,  1}
};

// Hash function for Hex objects used in unordered_map
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
