//
// Created by M Sz on 17/05/2023.
//

#ifndef GIPF_GIPF_H
#define GIPF_GIPF_H

#include <sstream>
#include <iterator>
#include <unordered_map>
#include <utility>

#include "Board.h"
#include "other.h"

// GIPF game class
// It has a Board object that represents the board of the game
// As per projects requirements instances of the GIPF game can be configured with the following parameters:
//    - size (params[0]): size of the board (refer to Board.h for more details)
//    - killingNumber (params[1]): number of pieces that need to be in a
//                                 straight line to be removed from the board
//    - startingWhitePieces (params[2]): number of white pieces on the board at the start of the game
//    - startingBlackPieces (params[3]): number of black pieces on the board at the start of the game
//    - whiteReserve (params[4]): number of white pieces in the White reserve at the start of the game
//    - blackReserve (params[5]): number of black pieces in the Black reserve at the start of the game
// which are passed as an array of integers - params[6]
class GIPF {
public:
    // Board of the GIPF game (see Board.h for more details)
    Board board;

    // Basic parameters of the GIPF game
    const int size;
    const int killingNumber;
    const int startingWhitePieces;
    const int startingBlackPieces;

    // GIPF game parameters which change during the game
    // White and Black pieces which are not on the board and can be used by the players
    int whiteReserve;
    int blackReserve;

    // White and Black pieces captured by the opponent
    int prisonersOfWhite;
    int prisonersOfBlack;

    char currentPlayer;
    char nextPlayer;

    // The current state of the game
    // Possible states:
    //      - in_progress
    //      - white_win
    //      - black_win
    //      - dead_lock
    //      - bad_move [details]
    std::string state;

    // These 2 maps are used to quickly translate between coordinates in the form of string and corresponding Hex objects
    // This is used to simplify the process of reading input from the user and presenting game state in a human-readable format
    // Additionally, as the operation of switching between the two representations is quite common, the maps are used to speed up the process
    // The maps are created during the construction of the GIPF object (specifically during construction of the Board object)
    // The maps are used in the following way:
    //     - coordsStringToHex[coords] returns the Hex object corresponding to the given coordinates
    //     - coordsHexToString[hex] returns the string representation of the given Hex object
    // Overloaded method GIPF::translate() is used for accessing the maps:
    std::unordered_map<std::string, Hex> coordsStringToHex;
    std::unordered_map<Hex, std::string> coordsHexToString;


    // Constructor of the GIPF game
    // It creates a Board object with the given size and constructs the maps for translating between coordinates and Hex objects
    // Parameters:
    //    - params: array of integers containing the basic parameters of the GIPF game (as described above)
    //    - startingPlayer: character representing the player that starts the game ('W' or 'B')
    //    - faltBoard: vector of characters representing the initial state of the board (read from standard input), 
    //                  the vector is used to initialize the Board object
    //    - validGameState: reference to a boolean variable that is set to false if the initial state of the board is invalid
    GIPF(int params[], char startingPlayer, std::vector<char> faltBoard, bool &validGameState);
    // Copy constructor of the GIPF game
    GIPF(const GIPF& other);       

    // Checks if all the rows of the current board are in valid state by the rules of the GIPF game
    // If the SILENT flag is set to true, the method does not print any output
    // otherwise DEBUG messages are printed to the standard output
    // Returns true if the board is in a valid state, false otherwise
    bool checkMap(bool SILENT);

    // Checks and returns the current state of the game
    std::string checkState();

    // Prints the info about current state of the game to the standard output
    // Format (per project requirements): 
    //      "size killingNumber startingWhitePieces startingBlackPieces"
    //      "whiteReserve blackReserve currentPlayer nextPlayer state"
    //      board in gipf format (Board::print_gipf())
    void printGameInfo() const;

    // Prints given line of the board to the standard output
    // Used mostly for debugging purposes, but useful for seeing how lines are defined during evaluation 
    void printLine(const std::vector<Hex>& line) const;

    // Reads a move from the standard input (either in simple format or with additional details)
    // If the SILENT flag is set to false, the method debug information is printed to the standard output
    // Returns a pair of:
    //      - vector V of Hex objects representing the move in following format:
    //          - V[0] is the immediate starting position of the new piece ('dot' position on edge of the board)
    //          - V[1] is the final position of the new piece (neighbour of the starting position, where the piece is pushed)
    //          - optionally V[n > 1] are the Hex objects representing the pieces that need to be removed from the board,
    //            but due to ambiguity of the move, additional details are needed to determine the exact pieces
    //      - character marking the player that made the move ('W' or 'B')
    std::pair<std::vector<Hex>, char> readMove(bool SILENT);
    // Parses details of a complex move (by GIPF rules, a move with additional clarification neccessary) from the given string
    // The details are in the following format:
    //      "[player symbol (w / b)]: hex1 hex2 hex3 ..."
    // Returns a boolean indicating if details of the move are valid
    // If the details are valid, the method appends the Hexes of the pieces that need to be removed to the given 'move' vector
    // and sets the 'killer' character to the symbol of the player whose pieces will be removed from the board
    bool parseMoveDetails(const std::string &details, std::vector<Hex> &move, char &killer, bool SILENT);

    // Read a move from the standard input, validate it and if possible commit it and update the game state
    bool newMove();
    // Take the move in form of vector (as explained above in readMove()), validate it and if possible commit it and update the game state
    // This method is used when proccessing moves generated by software and not input from user
    bool newMove(const std::vector<Hex>& move);
    // Checks if the move declaration (in the form explained above (see GIPF::readMove()) is valid
    // If the SILENT flag is set to false, debug information is printed to the standard output
    // Returns true if the move is valid, false otherwise
    bool isMoveDeclarationValid(std::vector<Hex> move, bool SILENT);
    // Takes a move (in the format described above(see GIPF::readMove()), checks if it is valid and commits it to the board
    // In terms of the GIPF game - the new piece is placed on the edge of the board and then pushed into the board proper,
    // if neccessary moving other pieces in the row
    // If the SILENT flag is set to false, debug information is printed to the standard output
    // Returns true if the move is valid, false otherwise (and the board is not modified - the move is not committed)
    bool makeMove(const std::pair<std::vector<Hex>, char> &move, bool SILENT);

    // Evaluates given line (without context, only the given line) and marks pieces that should be removed per the GIPF rules ('killed')
    // Returns true if a collision (ambiguity regarding removing intersecting groups of pieces in 2 lines) has been detected
    // per this engine's implementation such state of the game board is considered invalid 
    // (as it is not possible to resolve without player input and the player have not provided enough information ('details' of a 'complex move') to resolve it)
    bool markTargetsInLine(const std::vector<Hex>& line);
    // Evaluates state of the game after latest move, removes pieces and updates the game 
    // If the SILENT flag is set to false, debug information is printed to the standard output
    // The evaluation is done in the following way:
    //      1. if the move is considered a 'complex move' (with additional information from the player
    //         required to resolve it) the additional information ('details') are processed
    //         and, if the provided details are correct, pieces causing the ambiguity are removed from the board before others
    //      2. in each row of the board pieces meeting condition to be removed 
    //         (per GIPF rules: pieces in one color, forming continous, connected chain at least as long as killingNumber parameter)
    //         are marked as 'targets' to be removed after the entire board has been evaluated
    //         If a collision (ambiqious state) is detected during this phase the whole procces fails and the latest move is revoked
    //      3. pieces marked as 'targets' are removed from the board and the appropirate statistics updated
    //      4. all leftover markers on pieces are removed and thus the pieces' normal values are restored
    bool evaluateTurn(const std::pair<std::vector<Hex>, char> &last_move, bool SILENT);
    // Removes ambigious pieces from the board, as specified by the player input recorded in the move vector
    // If the SILENT flag is set to false, debug information is printed to the standard output
    // Returns false if the details provided by the player are invalid and the pieces can't be removed (per the GIPF rules)
    bool resolveComplexMove(std::vector<Hex> &move, char player, bool SILENT);
    // Final method for evaluating the turn
    // Removes all the pieces marked as 'targets' (pieces that will die by the GIPF rules) during evaluation from the board
    // and updates reserves and prisoners scores of players
    void removeTargets();

    // Overloaded method for placing a new piece on the board
    // Either string coordinates or Hex object can be used to specify the position of the piece
    char placePiece(const std::string& coords, char piece) { return board.set(translate(coords), piece); }
    char placePiece(const Hex& hex, char piece) { return board.set(hex, piece); }

    // Overloaded method for translating between coordinates and Hex objects
    // If the given parameter is a string, the method uses the coordsStringToHex map to return the corresponding Hex object
    // If the given parameter is a Hex object, the method uses the coordsHexToString map to return the corresponding string
    std::string translate(const Hex& hex) const;        // returns "XXX" if the hex is not present in the map
    Hex translate(const std::string& coords) const;     // returns EMPTY_HEX if the coords is not present in the map
};


#endif //GIPF_GIPF_H
