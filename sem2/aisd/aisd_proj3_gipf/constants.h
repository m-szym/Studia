//
// Created by M Sz on 17/05/2023.
//

#ifndef GIPF_CONSTANTS_H
#define GIPF_CONSTANTS_H

const std::string SPACER = " ";
const int GIPF_INDEX_START_INT = 1;
const char GIPF_INDEX_START_CHAR = 'a';


const char EMPTY_PLACE_SYMBOL = '_';
const char WHITE_SYMBOL = 'W';
const char BLACK_SYMBOL = 'B';
const char DOT_SYMBOL = '*';
const char USED_DOT_SYMBOL = '#';
const char WHITE_TARGET_OF_BLACK_SYMBOL = '{';
const char BLACK_TARGET_OF_WHITE_SYMBOL = '}';
const char WHITE_TARGET_OF_WHITE_SYMBOL = '[';
const char BLACK_TARGET_OF_BLACK_SYMBOL = ']';
const char EMPTY_TARGET_SYMBOL = 'e';
const char ERROR_SYMBOL = 'X';

const std::string BAD_MOVE_ERROR = "illegal move";
const std::string BAD_COORDINATES_ERROR = "illegal coordinates";
const std::string BAD_COMMAND_FORMAT_ERROR = "illegal command format";
const std::string BAD_COMMAND_ERROR = "illegal command";

const std::string LOAD_BOARD_COMMAND = "LOAD_GAME_BOARD";
const std::string DO_MOVE_COMMAND = "DO_MOVE";
const std::string PRINT_GAME_COMMAND = "PRINT_GAME_BOARD";
const std::string PRINT_STATE_COMMAND = "PRINT_GAME_STATE";

const std::string INVALID_BOARD_WHITE_PIECES_ERROR = "WRONG_WHITE_PAWNS_NUMBER";
const std::string INVALID_BOARD_BLACK_PIECES_ERROR = "WRONG_BLACK_PAWNS_NUMBER";
const std::string INVALID_BOARD_ROW_ERROR = "WRONG_BOARD_ROW_LENGTH";
const std::string BAD_MOVE_START = "BAD_MOVE_";
const std::string BAD_MOVE_IS_WRONG_INDEX = "_IS_WRONG_INDEX";

const std::string BOARD_LOAD_OK = "BOARD_STATE_OK";

const std::string IN_PROGRESS = "GAME_IN_PROGRESS";
const std::string BLACK_WIN = "THE_WINNER_IS_BLACK";
const std::string WHITE_WIN = "THE_WINNER_IS_WHITE";
const std::string DEAD_LOCK = "DEAD_LOCK";
const std::string BAD_MOVE_ = "BAD_MOVE ";


#endif //GIPF_CONSTANTS_H
