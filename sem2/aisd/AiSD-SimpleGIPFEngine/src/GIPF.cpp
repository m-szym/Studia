//
// Created by M Sz on 17/05/2023.
//

#include "../include/GIPF.h"
#include "GIPF.h"

GIPF::GIPF(int params[], char starting_player, std::vector<char> flat_board, bool &good_state)
    : board(params[0]), size(params[0]), killingNumber(params[1]), startingWhitePieces(params[2]),
      startingBlackPieces(params[3]), prisonersOfWhite(0), prisonersOfBlack(0), whiteReserve(params[4]), blackReserve(params[5]),
      state(IN_PROGRESS)
{
    prisonersOfWhite = 0;
    prisonersOfBlack = 0;

    currentPlayer = starting_player;
    nextPlayer = (starting_player == WHITE_SYMBOL) ? BLACK_SYMBOL : WHITE_SYMBOL;

    board.constructMap(coordsHexToString, coordsStringToHex);
    board.readMap(std::move(flat_board));
    good_state = checkMap(false);
    board.restoreBoard();
}

GIPF::GIPF(const GIPF &other)
    : board(other.board), size(other.size), killingNumber(other.killingNumber), startingWhitePieces(other.startingWhitePieces),
      startingBlackPieces(other.startingBlackPieces), prisonersOfWhite(other.prisonersOfWhite), prisonersOfBlack(other.prisonersOfBlack),
      whiteReserve(other.whiteReserve), blackReserve(other.blackReserve), currentPlayer(other.currentPlayer), nextPlayer(other.nextPlayer),
      coordsStringToHex(other.coordsStringToHex), coordsHexToString(other.coordsHexToString), state(other.state)
{
}

bool GIPF::checkMap(bool SILENT)
{
    auto dotlines = board.getDotlines();
    int incorrect_rows = 0;
    int white_row = 0;
    int black_row = 0;

    for (const auto &line : dotlines)
    {
        white_row = 0;
        black_row = 0;

        for (auto hex : line)
        {
            if (board[hex] == WHITE_SYMBOL)
            {
                white_row++;
                black_row = 0;
            }
            else if (board[hex] == BLACK_SYMBOL)
            {
                white_row = 0;
                black_row++;
            }
            else if (board[hex] == EMPTY_PLACE_SYMBOL)
            {
                white_row = 0;
                black_row = 0;
            }

            if (white_row >= killingNumber || black_row >= killingNumber)
            {
                incorrect_rows++;
                break;
            }
        }
    }
    if (incorrect_rows == 0)
    {
        return true;
    }
    else if (incorrect_rows == 1)
    {
        if (!SILENT)
            std::cout << "ERROR_FOUND_1_ROW_OF_LENGTH_K" << std::endl;
    }
    else
    {
        if (!SILENT)
            std::cout << "ERROR_FOUND_" << incorrect_rows << "_ROWS_OF_LENGTH_K" << std::endl;
    }
    return false;
}

std::pair<std::vector<Hex>, char> GIPF::readMove(bool SILENT)
{
    std::string raw_command;
    std::cin >> raw_command;

    char delimiter = '-';
    std::string dot_position = raw_command.substr(0, raw_command.find(delimiter));
    std::string entry_position = raw_command.substr(raw_command.find(delimiter) + 1, raw_command.length());

    Hex dot = translate(dot_position);          // dot - starting position on the edge of the board where the piece will be pushed
    Hex entry = translate(entry_position);      // entry - destination Hex where the piece will be pushed
    
    // validate if the given coordinates were correct
    if (dot == EMPTY_HEX)
    {
        if (!SILENT)
            std::cout << "BAD_MOVE_" << dot_position << "_IS_WRONG_INDEX" << std::endl;
        state = "BAD_MOVE ";
        state += currentPlayer;
        state += " " + raw_command;
        return {{EMPTY_HEX}, DOT_SYMBOL};
    }
    if (entry == EMPTY_HEX)
    {
        if (!SILENT)
            std::cout << "BAD_MOVE_" << entry_position << "_IS_WRONG_INDEX" << std::endl;
        state = std::string("BAD_MOVE " + std::to_string((char)currentPlayer) + raw_command);
        state = "BAD_MOVE ";
        state += currentPlayer;
        state += " " + raw_command;
        return {{EMPTY_HEX}, DOT_SYMBOL};
    }

    std::vector move = {dot, entry};

    // in some cases a move can be more complex, with additional information needed
    // to specify which pieces will be removed from the board 
    // (as per GIPF rules players can decide if there is ambiguity)
    // in such cases the move is specified as "b: a1 a2 a3 a4" or "w: a1 a2 a3 a4"
    // where b: or w: specifies the color of the player, and a1 a2 a3 a4 are the coordinates of the pieces to be removed
    // if the move is not complex, the move is returned as {move, DOT_SYMBOL} 
    // if the move is complex, the move is returned as {move, player}
    // parseMoveDetails() is used to parse the additional information
    char player = DOT_SYMBOL;

    std::string details;
    std::getline(std::cin, details);
    if (details.length() > 0)
    {
        if (parseMoveDetails(details, move, player, false))
        {
            if (move.size() == 4)
            {
                return {move, player};
            }
        }
        else
        {
            state = "BAD_MOVE ";
            state += currentPlayer;
            state += " " + raw_command;
            state += " " + details;
            return {{EMPTY_HEX}, DOT_SYMBOL};
        }
    }
    else
    {
        return {move, player};
    }

    state = "BAD_MOVE ";
    state += currentPlayer;
    state += " " + raw_command;
    return {{EMPTY_HEX}, DOT_SYMBOL};
}

bool GIPF::parseMoveDetails(const std::string &details, std::vector<Hex> &move, char &killer, bool SILENT)
{
    std::vector<std::string> tokens = split_string(details);

    if (tokens.empty())
    {
        return true;
    }

    if (tokens.size() != 3)
    {
        state = "BAD_MOVE ";
        state += currentPlayer;
        state += " " + translate(move[0]) + "-" + translate(move[1]) + " " + details;
        return false;
    }

    std::vector<Hex> tmp;
    if (tokens[0] == "b:" || tokens[0] == "w:")
    {
        killer = (tokens[0] == "w:") ? WHITE_SYMBOL : BLACK_SYMBOL;

        auto it = tokens.begin() + 1;
        while (it != tokens.end())
        {
            Hex hex = translate(*it);
            if (hex == EMPTY_HEX)
            {
                if (!SILENT)
                    std::cout << "BAD_MOVE_" << *it << "_IS_WRONG_INDEX" << std::endl;
                state = "BAD_MOVE ";
                state += currentPlayer;
                state += " " + translate(move[0]) + "-" + translate(move[1]) + " " + details;
                return false;
            }
            else
            {
                if (board[hex] != DOT_SYMBOL)
                {
                    tmp.push_back(hex);
                }
                else
                {
                    state = "BAD_MOVE ";
                    state += currentPlayer;
                    state += " " + translate(move[0]) + "-" + translate(move[1]) + " " + details;
                    return false;
                }
            }
            it++;
        }
        move.insert(move.end(), tmp.begin(), tmp.end());
        return true;
    }
    else
    {
        state = "BAD_MOVE ";
        state += currentPlayer;
        state += " " + translate(move[0]) + "-" + translate(move[1]) + " " + details;
        return false;
    }
}

bool GIPF::makeMove(const std::pair<std::vector<Hex>, char> &move, bool SILENT)
{
    if (!isMoveDeclarationValid(move.first, false))
        return false;

    int dir = move.first[0].neighbour_direction(move.first[1]);
    auto line = board.getLine(move.first[0], dir);

    board.pushIntoLine(line, currentPlayer);

    if (currentPlayer == WHITE_SYMBOL)
        whiteReserve--;
    else
        blackReserve--;

    nextPlayer = (nextPlayer == WHITE_SYMBOL) ? BLACK_SYMBOL : WHITE_SYMBOL;
    currentPlayer = (currentPlayer == WHITE_SYMBOL) ? BLACK_SYMBOL : WHITE_SYMBOL;

    return true;
}

bool GIPF::isMoveDeclarationValid(std::vector<Hex> move, bool SILENT)
{
    if (move[0] == EMPTY_HEX || move[1] == EMPTY_HEX)
    {
        return false;
    }

    if (move[0].distance(move[1]) != 1)
    {
        if (!SILENT)
            std::cout << "UNKNOWN_MOVE_DIRECTION" << std::endl;
        return false;
    }

    if (board[move[0]] != DOT_SYMBOL)
    {
        if (!SILENT)
            std::cout << "BAD_MOVE_" << translate(move[0]) << "_IS_WRONG_STARTING_FIELD" << std::endl;
        return false;
    }

    if (board[move[1]] != WHITE_SYMBOL && board[move[1]] != BLACK_SYMBOL && board[move[1]] != EMPTY_PLACE_SYMBOL)
    {
        if (!SILENT)
            std::cout << "BAD_MOVE_" << translate(move[1]) << "_IS_WRONG_DESTINATION_FIELD" << std::endl;
        return false;
    }

    if (move.size() == 4)
    {
        if (distance(move[2], move[3]) != killingNumber - 1)
        {
            if (!SILENT)
                std::cout << "WRONG_INDEX_OF_CHOSEN_ROW" << std::endl;
            return false;
        }
    }

    int dir = move[0].neighbour_direction(move[1]);
    if (dir < 0 || dir >= HEX_DIRECTIONS_COUNT)
    {
        if (!SILENT)
            std::cout << "UNKNOWN_MOVE_DIRECTION" << std::endl;
        return false;
    }

    auto line = board.getLine(move[0], dir);
    if (!board.lineHasEmptyHex(line))
    {
        if (!SILENT)
            std::cout << "BAD_MOVE_ROW_IS_FULL" << std::endl;
        return false;
    }

    return true;
}

bool GIPF::newMove()
{
    auto move = readMove(false);
    if (!makeMove(move, false))
        return false;
    return evaluateTurn(move, false);
}

bool GIPF::newMove(const std::vector<Hex> &move)
{
    if (!makeMove({move, DOT_SYMBOL}, true))
        return false;
    return evaluateTurn({move, DOT_SYMBOL}, true);
}

bool GIPF::markTargetsInLine(const std::vector<Hex> &line)
{
    if (line.size() < killingNumber)
        return false;

    int whiteInLine = 0;
    int blackInLine = 0;
    bool collisionDetected = false;
    std::vector<Hex> targetsToMark;
    for (auto hex : line)
    {
        // All connected pieces in one color that should be removed from the line have been found (and added to targetsToMark)
        if ((whiteInLine >= killingNumber || blackInLine >= killingNumber) && board[hex] == EMPTY_PLACE_SYMBOL)
            break;

        // White piece found
        if (board[hex] == WHITE_SYMBOL || board[hex] == WHITE_TARGET_OF_BLACK_SYMBOL || board[hex] == WHITE_TARGET_OF_WHITE_SYMBOL)
        {
            targetsToMark.push_back(hex);
            if (blackInLine < killingNumber)
            {
                whiteInLine++;
                if (blackInLine)
                    blackInLine = 0;
            }
        }
        // Black piece found
        else if (board[hex] == BLACK_SYMBOL || board[hex] == BLACK_TARGET_OF_BLACK_SYMBOL || board[hex] == BLACK_TARGET_OF_WHITE_SYMBOL)
        {
            targetsToMark.push_back(hex);
            if (whiteInLine < killingNumber)
            {
                blackInLine++;
                if (whiteInLine)
                    whiteInLine = 0;
            }
        }
        // Empty hex found - chain of connected, one-color pieces broken
        else if (board[hex] == EMPTY_PLACE_SYMBOL)
        {
            if (!targetsToMark.empty())
                targetsToMark.clear();
            if (whiteInLine < killingNumber)
                whiteInLine = 0;
            if (blackInLine < killingNumber)
                blackInLine = 0;
        }

        // Found a piece marked as target during evaluation of a different line 
        // thus these 2 lines have a collision (in the sense that removing pieces from line A changes state of line B)
        // per GIPF rules such state is ambigious and should be resolved by the player making the move
        // per this engine's implementation such state is invalid, as it occuring here means that player making a move
        // has not provided enough details to properly resolve it 
        // (the resolution, as specified by the player, has, at this point in code, already been done in resolveComplexMove())
        if (board[hex] == WHITE_TARGET_OF_BLACK_SYMBOL || 
            board[hex] == WHITE_TARGET_OF_WHITE_SYMBOL || 
            board[hex] == BLACK_TARGET_OF_BLACK_SYMBOL || 
            board[hex] == BLACK_TARGET_OF_WHITE_SYMBOL)
        {
            collisionDetected = true;
        }
    }

    // No pieces to remove found by evaluation of this single line
    if (whiteInLine < killingNumber && blackInLine < killingNumber)
        return false;

    // Collision detected
    if (collisionDetected)
        return true;

    // Mark pieces to remove from this line
    if (whiteInLine >= killingNumber)
    {
        for (auto hex : targetsToMark)
        {
            if (board[hex] == BLACK_SYMBOL)
            {
                board.set(hex, BLACK_TARGET_OF_WHITE_SYMBOL);
            }
            else if (board[hex] == WHITE_SYMBOL)
            {
                board.set(hex, WHITE_TARGET_OF_WHITE_SYMBOL);
            }

        }
    }
    else if (blackInLine >= killingNumber)
    {
        for (auto hex : targetsToMark)
        {
            if (board[hex] == BLACK_SYMBOL)
            {
                board.set(hex, BLACK_TARGET_OF_BLACK_SYMBOL);
            }
            else if (board[hex] == WHITE_SYMBOL)
            {
                board.set(hex, WHITE_TARGET_OF_BLACK_SYMBOL);
            }
        }
    }

    return false;
}

bool GIPF::evaluateTurn(const std::pair<std::vector<Hex>, char> &lastMove, bool SILENT)
{
    auto move = lastMove.first;
    char player = lastMove.second;
    bool isComplexMove = ((move.size() == 4) && (player == WHITE_SYMBOL || player == BLACK_SYMBOL));

    auto dotlines = board.getDotlines();
    if (dotlines.empty())
    {
        std::cout << "BOARD ERROR" << std::endl;
        return false;
    }

    // Remove pieces that should be killed according to the GIPF rules in 'complex' move 
    // (refer to Board.h for more details)
    if (isComplexMove)
    {
        bool complexMoveValid = resolveComplexMove(move, player, SILENT);
        if (!complexMoveValid)
            return false;
    }

    for (const auto& line : dotlines) {
        markTargetsInLine(line);
    }

    removeTargets();
    board.restoreBoard();
    return true;
}

bool GIPF::resolveComplexMove(std::vector<Hex> &move, char player, bool SILENT)
{
    Hex start = move[2];
    Hex end = move[3];
    auto coloredLine = board.getColoredLine(start, end, player);

    if (coloredLine.empty())
        return false;

    if (coloredLine[0] == EMPTY_HEX)
    {
        if (!SILENT)
            std::cout << "WRONG_COLOR_OF_CHOSEN_ROW" << std::endl;
        return false;
    }

    auto it = coloredLine.begin();
    while (it != coloredLine.end())
    {
        if (board[*it] == WHITE_SYMBOL)
        {
            if (player == WHITE_SYMBOL)
            {
                board.set(*it, EMPTY_PLACE_SYMBOL);
                whiteReserve++;
            }
            else if (player == BLACK_SYMBOL)
            {
                board.set(*it, EMPTY_PLACE_SYMBOL);
                prisonersOfWhite++;
            }
        }
        else if (board[*it] == BLACK_SYMBOL)
        {
            if (player == WHITE_SYMBOL)
            {
                board.set(*it, EMPTY_PLACE_SYMBOL);
                prisonersOfBlack++;
            }
            else if (player == BLACK_SYMBOL)
            {
                board.set(*it, EMPTY_PLACE_SYMBOL);
                blackReserve++;
            }
        }
        it++;
    }

    return true;
}

void GIPF::removeTargets()
{
    for (const auto &kv : board.map)
    {
        if (kv.second == WHITE_TARGET_OF_WHITE_SYMBOL || kv.second == WHITE_TARGET_OF_BLACK_SYMBOL || kv.second == BLACK_TARGET_OF_WHITE_SYMBOL || kv.second == BLACK_TARGET_OF_BLACK_SYMBOL)
        {

            if (kv.second == WHITE_TARGET_OF_WHITE_SYMBOL)
            {
                whiteReserve++;
            }
            else if (kv.second == BLACK_TARGET_OF_WHITE_SYMBOL)
            {
                prisonersOfWhite++;
            }
            else if (kv.second == WHITE_TARGET_OF_BLACK_SYMBOL)
            {
                prisonersOfBlack++;
            }
            else if (kv.second == BLACK_TARGET_OF_BLACK_SYMBOL)
            {
                blackReserve++;
            }

            board.set(kv.first, EMPTY_PLACE_SYMBOL);
        }
    }
}

std::string GIPF::translate(const Hex &hex) const
{
    try
    {
        return coordsHexToString.at(hex);
    }
    catch (std::out_of_range &e)
    {
        return "XXX";
    }
}

Hex GIPF::translate(const std::string &coords) const
{
    try
    {
        return coordsStringToHex.at(coords);
    }
    catch (std::out_of_range &e)
    {
        return EMPTY_HEX;
    }
}

void GIPF::printGameInfo() const
{
    std::cout << size << " " << killingNumber << " " << startingWhitePieces << " " << startingBlackPieces << std::endl;
    std::cout << whiteReserve << " " << blackReserve << " " << currentPlayer << std::endl;
    board.print_gipf();
}

void GIPF::printLine(const std::vector<Hex> &line) const
{
    std::cout << "line: " << translate(line.front()) << " --> " << translate(line.back()) << std::endl;
    std::cout << "\t";
    for (const Hex &hex : line)
    {
        std::cout << translate(hex);
        if (hex != line.back())
            std::cout << " --> ";
    }
    std::cout << std::endl;
}

std::string GIPF::checkState()
{
    if (whiteReserve <= 0)
        state = BLACK_WIN;
    else if (blackReserve <= 0)
        state = WHITE_WIN;
    else
    {
        int empty = 0;
        for (auto kv : board.map)
        {
            if (kv.second == EMPTY_PLACE_SYMBOL)
                empty++;
        }
        if (empty == 0)
            state = DEAD_LOCK + currentPlayer;
        else
            state = IN_PROGRESS;
    }

    return state;
}