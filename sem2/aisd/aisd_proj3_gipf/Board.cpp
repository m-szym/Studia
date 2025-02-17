//
// Created by M Sz on 15/05/2023.
//

#include "Board.h"

Board::Board(int size)
    : real_size(size + 1), playing_field_size(size), map{}
{}

Board::Board(const Board &other)
    : real_size(other.real_size), playing_field_size(other.playing_field_size) {
    for (auto kv : other.map) {
        map.emplace(kv.first, kv.second);
    }
}

void Board::construct_map_translator(std::unordered_map<Hex, std::string> &hex_coords,
                                     std::unordered_map<std::string, Hex> &coords_hex) {
    int size = playing_field_size;
    int x = GIPF_INDEX_START_INT;
    char N = GIPF_INDEX_START_CHAR;

    for (int q = -size; q <= size; q++) {
        int r1 = std::max(-size, -q - size);
        int r2 = std::min(size, -q + size);
        for (int r = r1; r <= r2; r++) {
            Hex h(q, r);
            std::string coords = std::string(1, N) + std::to_string(x);
            hex_coords.emplace(h, coords);
            coords_hex.emplace(coords, h);

            map.emplace(h, EMPTY_PLACE_SYMBOL);
            x++;
        }
        x = GIPF_INDEX_START_INT;
        N++;
    }
}

void Board::find_dots() {
    for (auto kv : map) {
        for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
            try {
                map.at(kv.first.hex_neighbour(i));
            } catch (std::out_of_range& e) {
                map[kv.first] = DOT_SYMBOL;
                break;
            }
        }
    }
}


void Board::print_gipf() const {
    int n = playing_field_size;

    for (int q = -n; q <= n; q++) {
        int r1 = std::max(-n, -q - n);
        int r2 = std::min(n, -q + n);

        if (q == -n || q == n) continue;

        for (int i = -n; i < n - r2 + r1; i++) {
            std::cout << SPACER;
        }

        for (int r = r1; r <= r2; r++) {
            Hex left_rotated = rotate_left(Hex(q, r));
            if (map.at(left_rotated) == DOT_SYMBOL)
                continue;
            else
                std::cout << (char) map.at(left_rotated) << SPACER;
        }
        std::cout << std::endl;
    }
}

char Board::operator[](const Hex& hex) const {
    try {
        return map.at(hex);
    } catch (std::out_of_range &e) {
        return ERROR_SYMBOL;
    }
}


void Board::load_board(std::vector<char> flat_board) {
    int n = playing_field_size - 1;

    auto it = flat_board.begin();
    for (int q = -n; q <= n; q++) {
        int r1 = std::max(-n, -q - n);
        int r2 = std::min( n, -q + n);
        for (int r = r1; r <= r2; r++) {
            map[rotate_left(Hex(q, r))] = *it;
            it++;
        }
    }
}

std::vector<Hex> Board::get_fullline(Hex starting_hex, int direction) {
    std::vector<Hex> line;
    Hex current_hex = starting_hex;
    while (map.find(current_hex) != map.end()) {
        if (map.at(current_hex) != DOT_SYMBOL && map.at(current_hex) != USED_DOT_SYMBOL)
            line.push_back(current_hex);
        current_hex = current_hex.hex_neighbour(direction);
    }
    return line;
}

char Board::set(Hex hex, char value) {
    try {
        char old_value = map.at(hex);
        map[hex] = value;
        return old_value;
    } catch (std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
        return ERROR_SYMBOL;
    }
}

bool Board::line_has_empty_hex(const std::vector<Hex>& line) {
    for (Hex hex : line) {
        if (map.at(hex) == EMPTY_PLACE_SYMBOL)
            return true;
    }
    return false;
}

void Board::push_line(std::vector<Hex> line, char value) {
    auto it = std::find_if(line.begin(), line.end(),
                           [this](Hex hex) { return map.at(hex) == EMPTY_PLACE_SYMBOL; });
    auto prev = it - 1;

    while (it != line.begin()) {
        if (map.at(*it) == EMPTY_PLACE_SYMBOL) {
            map[*it] = map[*prev];
            map[*prev] = EMPTY_PLACE_SYMBOL;
        }
        it--;
        prev--;
    }
    map[line.front()] = value;
}

bool Board::is_dot(Hex hex) const {
    try {
        return map.at(hex) == DOT_SYMBOL;
    } catch (std::out_of_range& e) {
        return false;
    }
}

bool Board::line_was_visited(const std::vector<Hex> &line) const {
    for (Hex h : line) {
        if (map.at(h) == WHITE_TARGET_OF_WHITE_SYMBOL || map.at(h) == WHITE_TARGET_OF_BLACK_SYMBOL
         || map.at(h) == BLACK_TARGET_OF_WHITE_SYMBOL || map.at(h) == BLACK_TARGET_OF_BLACK_SYMBOL)
            return true;
    }
    return false;
}

std::vector<std::vector<Hex>> Board::get_dotlines() {
    std::vector<std::vector<Hex>> dotlines;

    for (auto kv : map) {
        if (kv.second == DOT_SYMBOL) {
            map[kv.first] = USED_DOT_SYMBOL;

            for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
                try {
                    if (map.at(hex_neighbour(kv.first, i)) != DOT_SYMBOL &&
                        map.at(hex_neighbour(kv.first, i)) != USED_DOT_SYMBOL) {
                        bool unvisited = false;
                        auto neighbour = hex_neighbour(kv.first, i);
                        while (map.find(neighbour) != map.end()) {
                            if (map.at(neighbour) == DOT_SYMBOL) {
                                unvisited = true;
                                break;
                            }
                            neighbour = hex_neighbour(neighbour, i);
                        }

                        if (unvisited) dotlines.push_back(get_fullline(kv.first, i));
                    }
                } catch (std::out_of_range& e) {
                    continue;
                }
            }
        }
    }
    return dotlines;
}

void Board::clear_board() {
    for (auto kv : map) {
        if (map[kv.first] == WHITE_TARGET_OF_WHITE_SYMBOL || map[kv.first] == WHITE_TARGET_OF_BLACK_SYMBOL)
            map[kv.first] = WHITE_SYMBOL;
        else if (map[kv.first] == BLACK_TARGET_OF_WHITE_SYMBOL || map[kv.first] == BLACK_TARGET_OF_BLACK_SYMBOL)
            map[kv.first] = BLACK_SYMBOL;
        else if (map[kv.first] == USED_DOT_SYMBOL)
            map[kv.first] = DOT_SYMBOL;
    }
}

std::vector<Hex> Board::simple_get_line(Hex starting_hex, Hex ending_hex) {
    int distance = starting_hex.distance(ending_hex);
    Hex cursor = starting_hex;
    std::vector<Hex> line;

    int dir = -1;
    for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
        if (starting_hex + (hex_direction(i) * distance) == ending_hex) {
            dir = i;
            break;
        }
    }

    while (map.find(cursor) != map.end()) {
        line.push_back(cursor);

        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL)
            break;

        cursor = hex_neighbour(cursor, dir);
    }

    cursor = starting_hex;
    while (map.find(cursor) != map.end()) {
        line.push_back(cursor);

        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL)
            break;

        cursor = hex_neighbour(cursor, invert_direction(dir));
    }

    return line;
}

std::vector<Hex> Board::color_get_line(Hex starting_hex, Hex ending_hex, char color) {
    int distance = starting_hex.distance(ending_hex);
    Hex cursor = starting_hex;
    std::vector<Hex> line;

    int dir = -1;
    for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
        if (starting_hex + (hex_direction(i) * distance) == ending_hex) {
            dir = i;
            break;
        }
    }
    if (dir == -1) return { EMPTY_HEX };

    bool end_reached = false;
    int colored = 0;
    while (map.find(cursor) != map.end()) {
        if (map.at(cursor) != color && !end_reached) return { EMPTY_HEX };
        line.push_back(cursor);

        if (cursor == ending_hex) {
            end_reached = true;
        }

        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL)
            break;

        cursor = hex_neighbour(cursor, dir);
    }

    cursor = starting_hex;
    while (map.find(cursor) != map.end()) {
        line.push_back(cursor);

        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL)
            break;

        cursor = hex_neighbour(cursor, invert_direction(dir));
    }

    return line;
}


bool operator==(const Board& lhs, const Board& rhs) {
    return lhs.map == rhs.map;
}









