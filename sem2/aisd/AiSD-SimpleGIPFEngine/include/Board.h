//
// Created by M Sz on 15/05/2023.
//

#ifndef GIPF_BOARD_H
#define GIPF_BOARD_H

#include <string>
#include <unordered_map>
#include <algorithm>

#include "Hex.h"
#include "constants.h"

// Class that represents the board of the GIPF game
// It has a map that stores the pieces of the board in the format of: 
//    Hex (location on map) -> char (value of the piece on that location)
// The board is a hexagon with an edge of size = realSize
// The immediate outer edge of the board is filled with DOT_SYMBOL characters
// These are the starting positions for the pieces in a GIPF game
// The rest of the hexagons are filled with EMPTY_SYMBOL characters and represent actual board
class Board {
public:
    int realSize;                           // Real size of the board is the size of the playing field + the size of the border
    int playingFieldSize;                   // Size of the playing field (board without the border)
    std::unordered_map<Hex, char> map;      // Map that stores the state of the board
                                            // for each Hex there is a char that represents the piece on that location

    explicit Board(int size);
    Board(const Board& other);  

    // Returns the value of the piece on the given position by the Hex object
    char operator[](const Hex& hex) const;
    // Check if the given position is a 'dot' - one of the starting positions in a GIPF game
    bool isDot(Hex hex) const;

    // Prints the board in different formats
    // print_gipf - prints the board in the format of the GIPF game
    // print_xN - prints the board in the same format as print_gipf but also includes the coordinates of the Hexes
    // print_cont - prints the board similiar to the format of the GIPF game but rotated by 60 degrees (this is often more readable due to the nature of GIPF coordinate system) 
    void print_gipf () const;
    void print_xN() const;
    void print_rot() const;

    // Reads the board from the standard input
    void readMap();
    // Reads the board from a vector of characters
    void readMap(std::vector<char> flat_board);
    // Marks the positions of 'dot' pieces - the starting positions in a GIPF game
    void findDots();

    // Constructs the empty board of the appropriate size
    // The board is a hexagon with an edge of size = realSize
    // The immediate outer edge of the board is filled with DOT_SYMBOL characters
    // These are the starting positions for the pieces in a GIPF game
    // The rest of the hexagons are filled with EMPTY_SYMBOL characters and represent actual board
    // The 2 unordered_maps are used to convert between strings of coordinates and actual Hex objects 
    // and filled by this method
    void constructMap(std::unordered_map<Hex, std::string> &hex_coords,
                      std::unordered_map<std::string, Hex> &coords_hex);

    // Returns all Hexes in straight line from starting_hex in the given direction
    std::vector<Hex> getLine(Hex startHex, int direction);
    // Returns all Hexes in straight line from starting_hex to ending_hex
    std::vector<Hex> getLine(Hex startHex, Hex endHex);
    // Returns all Hexes in color (i.e. symbol) straight line from starting_hex to ending_hex
    std::vector<Hex> getColoredLine(Hex startHex, Hex endHex, char color);
    // Returns all lines (groups of Hexes in straight line) that start from 'dot' positions
    // Each Hex appears only in 1 of the returned lines
    // These lines are used to determine the possible moves in a GIPF game
    // as the pieces can only be placed on the 'dot' positions
    // and then pushed in a straight line from that position
    std::vector<std::vector<Hex>> getDotlines();

    // Checks if all Hexes in given line have already been processed in the current move
    bool lineVisited(const std::vector<Hex> &line) const;
    // Checks if the given line contains empty Hex (i.e. Hex with corresponding EMPTY_SYMBOL character)
    bool lineHasEmptyHex(const std::vector<Hex>& line);

    // Pushes all pieces in the given line, emplacing new piece with given value at the start of the line
    // This corresponds to basic move in the GIPF game - placing piece on the edge of the board ('dot' position here)
    // and pushing the piece (and possibly other pieces) in the given direction in a straight line thereby changing board state
    void pushIntoLine(std::vector<Hex> line, char value);

    // Sets the value of the piece on the given position by the Hex object
    char set(Hex hex, char value);

    // Restores symbols on board to their proper values
    // after using temporary values during move evaluation
    void restoreBoard();
};




#endif //GIPF_BOARD_H
