//
// Created by M Sz on 28.05.2023.
//

#include "Solver.h"

Solver::Solver(const GIPF& og_game)
    : root(og_game)
{}

Solver::~Solver() {
    //tree deletes itslef
}

std::vector<std::vector<Hex>> Solver::get_all_possible_simple_moves() {
    auto moves = std::vector<std::vector<Hex>>();
    GIPF game = root.data;

    for (auto kv : game.board.map) {
        if (kv.second == DOT_SYMBOL) {
            Hex dot = kv.first;

            for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
                Hex entry = dot.hex_neighbour(i);

                if (game.board.map.find(entry) != game.board.map.end() && game.board.map[entry] != DOT_SYMBOL) {
                    moves.push_back({dot, entry});
                }
            }
        }
    }

    return moves;
}

std::vector<std::vector<Hex>> Solver::choose_legal_simple_moves(const std::vector<std::vector<Hex>>& moves) {
    auto legal_moves = std::vector<std::vector<Hex>>();
    GIPF game = root.data;

    std::vector<GIPF> uniq_game_states;

    for (const auto& move : moves) {
        auto game_copy = GIPF(game);

        if(game_copy.simple_move(move)) {
            bool is_unique = true;

            for (const auto& uniq_game_state : uniq_game_states) {
                if (game_copy == uniq_game_state) {
                    is_unique = false;
                    break;
                }
            }

            if (is_unique) {
                legal_moves.push_back(move);
                uniq_game_states.push_back(game_copy);
            }
        }
    }

    std::cout << "legal_moves = " << legal_moves.size() << std::endl;
    std::cout << "uniq_game_states = " << uniq_game_states.size() << std::endl;
    return legal_moves;
}

std::vector<std::string> Solver::translate_simple_moves(const std::vector<std::vector<Hex>> &moves) const {
    std::vector<std::string> translated_moves;
    translated_moves.reserve(moves.size());
    for (const auto& move : moves) {
        translated_moves.push_back(translate_simple_move(move));
    }
    return translated_moves;
}


void Solver::grow_one_level(AllTree<GIPF> *local_root) {
    GIPF game = local_root->data;

    for (auto kv : game.board.map) {
        if (kv.second == DOT_SYMBOL) {
            Hex dot = kv.first;

            for (int i = 0; i < HEX_DIRECTIONS_COUNT; ++i) {
                Hex entry = dot.hex_neighbour(i);

                if (game.board.map.find(entry) != game.board.map.end() && game.board.map[entry] != DOT_SYMBOL) {
                    auto game_copy = GIPF(game);

                    if (game_copy.simple_move({dot, entry})) {
                        bool is_unique = true;

                        for (auto *child: local_root->children) {
                            if (game_copy == child->data) {
                                is_unique = false;

                                break;
                            }
                        }

                        if (is_unique) {
                            local_root->addChild(game_copy);
                        }
                    }
                }
            }
        }
    }
}





