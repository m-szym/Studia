#include <iostream>
#include <string>
#include <memory>

#include "Board.h"
#include "GIPF.h"
#include "other.h"
#include "Solver.h"

/*
 *     N              NW SW
 *  NW * NE          N  *  S
 *  SW * SE           NE SE
 *     S
 */

/*
 *       SE = 0
 *       NE = 1               SW SS
 *       N  = 2              NW * SE
 *       NW = 3               NN NE
 *       SW = 4
 *       S  = 5
 */

void load_game(std::unique_ptr<GIPF> &g);
void do_move(std::unique_ptr<GIPF> &g);
void gen_all_pos_move_ext_num(std::unique_ptr<GIPF> &g);


int main() {
    std::string input;
    std::unique_ptr<GIPF> g = nullptr;

    while (std::cin) {
        if (std::cin.eof()) break;
        input = "";
        std::cin >> input;

        if (input == LOAD_BOARD_COMMAND) {
            if (g != nullptr) g.reset();

            load_game(g);
        }
        else if (input == DO_MOVE_COMMAND) {
            if (g == nullptr) continue;

            do_move(g);
        }
        else if (input == PRINT_GAME_COMMAND) {
            if (g == nullptr) {
                std::cout << "EMPTY_BOARD" << std::endl;
                continue;
            }

            g->print_game_state();
            std::cout << std::endl;
        } else if (input == "IS_GAME_OVER") {
            if (g == nullptr) continue;

            g->update_game_state();
            std::cout << g->state << std::endl << std::endl;

        } else if (input == "GEN_ALL_POS_MOV_NUM") {
            if (g == nullptr) continue;

            Solver solver((GIPF(*g)));
            solver.grow_one_level(&solver.root);

            std::cout << solver.root.children.size() << "_UNIQUE_MOVES" << std::endl << std::endl;

        } else if (input == "GEN_ALL_POS_MOV_EXT_NUM") {
            if (g == nullptr) continue;

            gen_all_pos_move_ext_num(g);
        }

    }

    return 0;
}

void load_game(std::unique_ptr<GIPF> &g) {
    int int_params[6] = {0};
    char next_player = ' ';

    std::cin >> int_params[0] >> int_params[1] >> int_params[2];
    std::cin >> int_params[3] >> int_params[4] >> int_params[5] >> next_player;


    std::vector<char> fields;

    int whites = 0;
    int blacks = 0;
    while (!std::cin.eof()) {
        int n = std::cin.peek();
        if (n == '\n' || n == ' ') {
            std::cin.get();
            continue;
        } else if (n == EMPTY_PLACE_SYMBOL || n == WHITE_SYMBOL || n == BLACK_SYMBOL) {
            if (n == WHITE_SYMBOL) whites++;
            else if (n == BLACK_SYMBOL) blacks++;
            fields.push_back((char) std::cin.get());
        } else
            break;
    }

    int size = 0;
    int row = int_params[0];
    for (int j = row; j < ((2 * row) - 1); j++) {
        size += j;
    }
    size *= 2;
    size += (2 * row) - 1;
    if (fields.size() != size) {
        std::cout << INVALID_BOARD_ROW_ERROR << std::endl;
    } else {

        if (((int_params[2]) - whites) < int_params[4]) {
            std::cout << INVALID_BOARD_WHITE_PIECES_ERROR << std::endl;
        } else if (int_params[3] - blacks < int_params[5]) {
            std::cout << INVALID_BOARD_BLACK_PIECES_ERROR << std::endl;
        } else {
            bool good_state = false;
            g = std::make_unique<GIPF>(int_params, next_player, fields, good_state);

            if (good_state)
                std::cout << BOARD_LOAD_OK << std::endl;
            else
                g.reset();
        }
    }
    std::cout << std::endl;
}

void do_move(std::unique_ptr<GIPF> &g) {
    auto gcopy = std::make_unique<GIPF>(*g);

    if(!g->simple_move()) {
        gcopy->state = g->state;
        g.swap(gcopy);
    } else {
        g->update_game_state();
        std::cout << "MOVE_COMMITTED" << std::endl;
    }

    std::cout << std::endl;
}

void gen_all_pos_move_ext_num(std::unique_ptr<GIPF> &g) {
    Solver solver((GIPF(*g)));
    solver.grow_one_level(&solver.root);

    bool found_win = false;
    for (auto a: solver.root.children) {
        a->data.update_game_state();
        if (a->data.state == WHITE_WIN || a->data.state == BLACK_WIN) {
            std::cout << "1_UNIQUE_MOVES" << std::endl << std::endl;
            found_win = true;
            break;
        }
    }
    if(!found_win)
        std::cout << solver.root.children.size() << "_UNIQUE_MOVES" << std::endl << std::endl;
}