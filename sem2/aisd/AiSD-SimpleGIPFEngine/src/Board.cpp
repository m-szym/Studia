//
// Created by M Sz on 15/05/2023.
//

#include "../include/Board.h"

Board::Board(int size)
    : realSize(size + 1), playingFieldSize(size), map{}
{}

Board::Board(const Board &other)
    : realSize(other.realSize), playingFieldSize(other.playingFieldSize) {
    for (auto kv : other.map) {
        map.emplace(kv.first, kv.second);
    }
}

void Board::constructMap(std::unordered_map<Hex, std::string> &hex_coords,
                          std::unordered_map<std::string, Hex> &coords_hex) {
    int size = playingFieldSize;
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

    findDots();
}

void Board::findDots() {
    for (auto kv : map) {
        for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
            try {
                map.at(kv.first.neighbourInDirection(i));
            } catch (std::out_of_range& e) {
                map[kv.first] = DOT_SYMBOL;
                break;
            }
        }
    }
}

void Board::print_xN() const
{
    int n = playingFieldSize;

    int x = 1;
    char N = 'a';

    for (int q = -n; q <= n; q++) {
        int r1 = std::max(-n, -q - n);
        int r2 = std::min( n, -q + n);
        for (int i = -n; i < n - r2 + r1; i++) {
            std::cout << "  ";
        }
        for (int r = r1; r <= r2; r++) {
            std::cout << std::string(1, N) + std::to_string(x)<< "  ";
            x++;
        }
        std::cout << std::endl;
        x = 1;
        N++;
    }
}

void Board::print_rot() const
{
    int n = playingFieldSize;

    int x = 0;
    char N = 'A';

    for (int q = -n; q <= n; q++) {
        int r1 = std::max(-n, -q - n);
        int r2 = std::min( n, -q + n);
        for (int i = -n; i < n - r2 + r1; i++) {
            std::cout << " ";
        }
        for (int r = r1; r <= r2; r++) {
            std::cout << (char) map.at(Hex(q, r)) << " ";
            x++;
        }
        std::cout << std::endl;
        x = 0;
        N++;
    }
}

void Board::print_gipf() const {
    int n = playingFieldSize;

    for (int q = -n; q <= n; q++) {
        int r1 = std::max(-n, -q - n);
        int r2 = std::min(n, -q + n);

        if (q == -n || q == n) continue;

        for (int i = -n; i < n - r2 + r1; i++) {
            std::cout << SPACER;
        }

        for (int r = r1; r <= r2; r++) {
            Hex left_rotated = rotateLeft(Hex(q, r));
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

void Board::readMap() {
    int n = playingFieldSize - 1;
    int c = ' ';


    for (int q = -n; q <= n; q++) {
        int r1 = std::max(-n, -q - n);
        int r2 = std::min( n, -q + n);
        for (int r = r1; r <= r2; r++) {
            c = getchar();
            while (!(c == EMPTY_PLACE_SYMBOL || c == WHITE_SYMBOL || c == BLACK_SYMBOL)) {
                c = getchar();
            }
            map[rotateRight(Hex(q, r))] = (char) c;
        }
    }
}

void Board::readMap(std::vector<char> flat_board) {
    int n = playingFieldSize - 1;

    auto it = flat_board.begin();
    for (int q = -n; q <= n; q++) {
        int r1 = std::max(-n, -q - n);
        int r2 = std::min( n, -q + n);
        for (int r = r1; r <= r2; r++) {
            map[rotateLeft(Hex(q, r))] = *it;
            it++;
        }
    }
}

std::vector<Hex> Board::getLine(Hex starting_hex, int direction) {
    std::vector<Hex> line;
    Hex current_hex = starting_hex;
    while (map.find(current_hex) != map.end()) {
        if (map.at(current_hex) != DOT_SYMBOL && map.at(current_hex) != USED_DOT_SYMBOL)
            line.push_back(current_hex);
        current_hex = current_hex.neighbourInDirection(direction);
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

bool Board::lineHasEmptyHex(const std::vector<Hex>& line) {
    for (Hex hex : line) {
        if (map.at(hex) == EMPTY_PLACE_SYMBOL)
            return true;
    }
    return false;
}

void Board::pushIntoLine(std::vector<Hex> line, char value) {
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

bool Board::isDot(Hex hex) const {
    try {
        return map.at(hex) == DOT_SYMBOL;
    } catch (std::out_of_range& e) {
        return false;
    }
}

bool Board::lineVisited(const std::vector<Hex> &line) const {
    for (Hex h : line) {
        if (map.at(h) == WHITE_TARGET_OF_WHITE_SYMBOL || map.at(h) == WHITE_TARGET_OF_BLACK_SYMBOL
         || map.at(h) == BLACK_TARGET_OF_WHITE_SYMBOL || map.at(h) == BLACK_TARGET_OF_BLACK_SYMBOL)
            return true;
    }
    return false;
}

std::vector<std::vector<Hex>> Board::getDotlines() {
    std::vector<std::vector<Hex>> dotlines;

    for (auto kv : map) {
        if (kv.second == DOT_SYMBOL) {
            map[kv.first] = USED_DOT_SYMBOL;

            for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
                try {
                    if (map.at(neighbourInDirection(kv.first, i)) != DOT_SYMBOL &&
                        map.at(neighbourInDirection(kv.first, i)) != USED_DOT_SYMBOL) {
                        bool unvisited = false;
                        auto neighbour = neighbourInDirection(kv.first, i);
                        while (map.find(neighbour) != map.end()) {
                            if (map.at(neighbour) == DOT_SYMBOL) {
                                unvisited = true;
                                break;
                            }
                            neighbour = neighbourInDirection(neighbour, i);
                        }

                        if (unvisited) dotlines.push_back(getLine(kv.first, i));
                    }
                } catch (std::out_of_range& e) {
                    continue;
                }
            }
        }
    }
    return dotlines;
}

void Board::restoreBoard() {
    for (auto kv : map) {
        if (map[kv.first] == WHITE_TARGET_OF_WHITE_SYMBOL || map[kv.first] == WHITE_TARGET_OF_BLACK_SYMBOL)
            map[kv.first] = WHITE_SYMBOL;
        else if (map[kv.first] == BLACK_TARGET_OF_WHITE_SYMBOL || map[kv.first] == BLACK_TARGET_OF_BLACK_SYMBOL)
            map[kv.first] = BLACK_SYMBOL;
        else if (map[kv.first] == USED_DOT_SYMBOL)
            map[kv.first] = DOT_SYMBOL;
    }
}

std::vector<Hex> Board::getLine(Hex starting_hex, Hex ending_hex) {
    int distance = starting_hex.distance(ending_hex);
    Hex cursor = starting_hex;
    std::vector<Hex> line;

    int dir = -1;
    for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
        if (starting_hex + (HEX_DIRS[i] * distance) == ending_hex) {
            dir = i;
            break;
        }
    }
    while (map.find(cursor) != map.end()) {
        line.push_back(cursor);
        //if (cursor == ending_hex) break;
        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL) break;
        cursor = neighbourInDirection(cursor, dir);
    }
    cursor = starting_hex;
    while (map.find(cursor) != map.end()) {
        line.push_back(cursor);
        //if (cursor == ending_hex) break;
        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL) break;
        cursor = neighbourInDirection(cursor, invert_direction(dir));
    }

    return line;
}

std::vector<Hex> Board::getColoredLine(Hex starting_hex, Hex ending_hex, char color) {
    int distance = starting_hex.distance(ending_hex);
    Hex cursor = starting_hex;
    std::vector<Hex> line;

    int dir = -1;
    for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
        if (starting_hex + (HEX_DIRS[i] * distance) == ending_hex) {
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
        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL) break;
        cursor = neighbourInDirection(cursor, dir);
    }
    cursor = starting_hex;
    while (map.find(cursor) != map.end()) {
        line.push_back(cursor);
        //if (cursor == ending_hex) break;
        if (map.at(cursor) == EMPTY_PLACE_SYMBOL || map.at(cursor) == DOT_SYMBOL) break;
        cursor = neighbourInDirection(cursor, invert_direction(dir));
    }

    return line;
}