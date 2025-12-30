#pragma once
#include <iostream>
#include <utility>
#include "chess.hpp"

struct Board {
    Peice* board[8][8];
    std::pair<int, int> positions[8][8];

    Board();

    void printBoard();
};