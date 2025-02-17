#include <iostream>
#include <string>
#include <memory>

#include "../include/Board.h"
#include "../include/GIPF.h"
#include "../include/other.h"

//
//           W _ _ B
//          _ _ _ _ _
//         _ _ _ _ _ _
//        B _ _ _ _ _ W
//         _ _ _ _ _ _
//          _ _ _ _ _
//           W _ _ B

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

int main() {
    std::string input;
    std::unique_ptr<GIPF> g = nullptr;

    while (std::cin) {
        if (std::cin.eof()) break;
        input = "";
        std::cin >> input;

        if (input == "exit") {
            // Exit program 
            break;
        } else if (input == LOAD_BOARD_COMMAND) {
            // Load new game state into g
            // if it's impossible skip to next command

            if (g != nullptr) g.reset();

            // Load new game parameters
            int params[6] = {0};
            char next_player = ' ';
            std::cin >> params[0] >> params[1] >> params[2];
            std::cin >> params[3] >> params[4] >> params[5] >> next_player;

            // Load new game board state
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

            // First round of inpurt validation
            int size = 0;
            int row = params[0];
            for (int j = row; j < ((2 * row) - 1); j++) {
                size += j;
            }
            size *= 2;
            size += (2 * row) - 1;
            if (fields.size() != size) {
                std::cout << INVALID_BOARD_ROW_ERROR << std::endl;
                continue;
            } 

            if (((params[2]) - whites) < params[4]) {
                std::cout << INVALID_BOARD_WHITE_PIECES_ERROR << std::endl;
                continue;
            } else if (params[3] - blacks < params[5]) {
                std::cout << INVALID_BOARD_BLACK_PIECES_ERROR << std::endl;
                continue;
            } 
            
            // Try to initilize new game from the given paremeters and board state
            bool gameStateValid = false;
            g = std::make_unique<GIPF>(params, next_player, fields, gameStateValid);

            if (gameStateValid)
                std::cout << BOARD_LOAD_OK << std::endl;
            else
                g.reset();
            
            
            std::cout << std::endl;
        } else if (input == DO_MOVE_COMMAND) {
            // Read new move from standard input, try to commit it and if the move was valid update game state
            // if no moves can be made (either the current game is over or no game state is held in g) skip to next command
            // if inputed move was invalid (per the GIPF rules and this engine's implementation) print ERROR and skip to next command 
            // (the invalid move is not commited)
            if (g == nullptr) continue;
            if (g->state == WHITE_WIN || g->state == BLACK_WIN || g->state.find(DEAD_LOCK) != std::string::npos) {
                std::cout << "GAME_OVER " << g->state << std::endl;
                continue;
            }

            auto gcopy = std::make_unique<GIPF>(*g);

            if(!g->newMove()) {
                gcopy->state = g->state;
                g.swap(gcopy);
            } else {
                g->checkState();
                std::cout << "MOVE_COMMITTED" << std::endl;
            }

            std::cout << std::endl;
        } else if (input == PRINT_GAME_COMMAND) {
            // Print info about current game - stats of players (nr. of pieces, nr. of prisoners etc.) and the board
            if (g == nullptr) continue;

            g->printGameInfo();
            std::cout << std::endl;
        } else if (input == PRINT_STATE_COMMAND) {
            // Print only the state of the current game - IN_PROGRESS / WHITE_WIN / BLACK_WIN
            if (g == nullptr) continue;

            std::cout << g->state << std::endl;
            std::cout << std::endl;
        }
    }

    return 0;
}