//
// Created by M Sz on 15/05/2023.
// Hexagonal board implementation inspired by https://www.redblobgames.com/grids/hexagons/
// and https://www.redblobgames.com/grids/hexagons/implementation.html
// Extended to accommodate Gipf rules and operations
//

#ifndef GIPF_BOARD_H
#define GIPF_BOARD_H

#include <string>
#include <unordered_map>
#include <algorithm>

#include "Hex.h"
#include "constants.h"

class Board {
public:
    int real_size;
    int playing_field_size;
    std::unordered_map<Hex, char> map;

    explicit Board(int size);
    Board(const Board& other);  //copy constructor

    char operator[](const Hex& hex) const;
    bool is_dot(Hex hex) const;
    char set(Hex hex, char value);

    void print_gipf () const;

    void load_board(std::vector<char> flat_board);
    void find_dots();
    void construct_map_translator(std::unordered_map<Hex, std::string> &hex_coords,
                                  std::unordered_map<std::string, Hex> &coords_hex);

    std::vector<Hex> get_fullline(Hex starting_hex, int direction);
    std::vector<Hex> simple_get_line(Hex starting_hex, Hex ending_hex);
    std::vector<std::vector<Hex>> get_dotlines();
    std::vector<Hex> color_get_line(Hex starting_hex, Hex ending_hex, char color);

    bool line_was_visited(const std::vector<Hex> &line) const;
    bool line_has_empty_hex(const std::vector<Hex>& line);

    void push_line(std::vector<Hex> line, char value);

    void clear_board();
};

bool operator==(const Board& lhs, const Board& rhs);


#endif //GIPF_BOARD_H
