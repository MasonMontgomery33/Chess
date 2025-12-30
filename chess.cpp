#include <iostream>
#include <array>
#include <string>
#include <utility>
#include <vector>
#include "chess.hpp"
#include "Board.hpp"

template <typename PieceType>
bool check(std::pair<int, int> start, std::pair<int, int> end, Board& b, const std::vector<std::pair<int, int>>& offsetsVec)
{
    int starty = start.first;
    int startx = start.second;

    int endy = end.first;
    int endx = end.second;

    std::pair<int, int> endPair{endy, endx};

    std::vector<std::pair<int, int>> offsets = offsetsVec;

    std::vector<std::pair<int, int>> moves;

    for (auto pair : offsets) {
        int newy = pair.first + starty;
        int newx = pair.second + startx;

        if (newy >= 0 && newy < 8 && newx >= 0 && newx < 8) {
            moves.push_back({newy, newx});
        }
    }

    for (auto m : moves) {
        if (m == endPair &&
            b.board[endy][endx]->getTeam() != b.board[starty][startx]->getTeam()) {

            delete b.board[endy][endx];
            b.board[endy][endx] = new PieceType();
            b.board[endy][endx]->setTeam(b.board[starty][startx]->getTeam());

            delete b.board[starty][startx];
            b.board[starty][startx] = new Blank();
            b.board[starty][startx]->setTeam(None);

            return true;
        }
    }

    std::cout << "Invalid Move" << std::endl;
    return false;
}

bool King::move(std::pair<int, int> start, std::pair<int, int> end, Board& b) {
     std::vector<std::pair<int, int>> offsets = {{
     { 0,  1}, { 1,  1},
     {1, 0}, {1,  -1},
     {0, -1}, {-1, -1},
     { -1, 0}, { -1, 1}
     }};

     return check<King>(start, end, b, offsets);
}

bool Knight::move(std::pair<int, int> start, std::pair<int, int> end, Board& b) {
     
     std::vector<std::pair<int, int>> offsets = {{
     { 2,  1}, { 1,  2},
     {-1,  2}, {-2,  1},
     {-2, -1}, {-1, -2},
     { 1, -2}, { 2, -1}
     }};

     return check<Knight>(start, end, b, offsets);
}

bool Queen::move(std::pair<int, int> start, std::pair<int, int> end, Board& b) {
    constexpr std::array<std::pair<int,int>, 8> changes = {{
        {0, 1}, {1, 1}, {1, 0}, {1, -1},
        {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    }};

    std::vector<std::pair<int,int>> offsets;

    for (auto change : changes) {
        int dy = change.first;
        int dx = change.second;

        int y = start.first + dy;
        int x = start.second + dx;

        while (y >= 0 && y < 8 && x >= 0 && x < 8) {
            if (b.board[y][x]->getTeam() != None) {
                if (b.board[y][x]->getTeam() != b.board[start.first][start.second]->getTeam()) {
                    offsets.push_back({y - start.first, x - start.second});
                }
                break;
            }
            offsets.push_back({y - start.first, x - start.second});
            y += dy;
            x += dx;
        }
    }

    return check<Queen>(start, end, b, offsets);
} 

bool Rook::move(std::pair<int, int> start, std::pair<int, int> end, Board& b) {
    constexpr std::array<std::pair<int,int>, 4> directions = {{
        {0, 1}, {1, 0}, {0, -1}, {-1, 0}
    }};

    std::vector<std::pair<int,int>> offsets;

    for (auto dir : directions) {
        int dy = dir.first;
        int dx = dir.second;

        int y = start.first + dy;
        int x = start.second + dx;

        while (y >= 0 && y < 8 && x >= 0 && x < 8) {
            if (b.board[y][x]->getTeam() != None) {
                if (b.board[y][x]->getTeam() != b.board[start.first][start.second]->getTeam()) {
                    offsets.push_back({y - start.first, x - start.second});
                }
                break;
            }

            offsets.push_back({y - start.first, x - start.second});
            y += dy;
            x += dx;
        }
    }

    return check<Rook>(start, end, b, offsets);
}

bool Bishop::move(std::pair<int, int> start, std::pair<int, int> end, Board& b) {
    constexpr std::array<std::pair<int,int>, 4> directions = {{
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}
    }};

    std::vector<std::pair<int,int>> offsets;

    for (auto dir : directions) {
        int dy = dir.first;
        int dx = dir.second;

        int y = start.first + dy;
        int x = start.second + dx;

        while (y >= 0 && y < 8 && x >= 0 && x < 8) {
            if (b.board[y][x]->getTeam() != None) {
                if (b.board[y][x]->getTeam() != b.board[start.first][start.second]->getTeam()) {
                    offsets.push_back({y - start.first, x - start.second});
                }
                break;
            }

            offsets.push_back({y - start.first, x - start.second});
            y += dy;
            x += dx;
        }
    }

    return check<Bishop>(start, end, b, offsets);
}

bool Pawn::move(std::pair<int,int> start, std::pair<int,int> end, Board& b) {
    int startY = start.first;
    int startX = start.second;
    int endY = end.first;
    int endX = end.second;

    Team team = b.board[startY][startX]->getTeam();
    int direction = (team == White) ? -1 : 1;

    if (endX == startX && endY == startY + direction) {
        if (b.board[endY][endX]->getTeam() == None) {
            delete b.board[endY][endX];
            b.board[endY][endX] = new Pawn();
            b.board[endY][endX]->setTeam(team);

            delete b.board[startY][startX];
            b.board[startY][startX] = new Blank();
            b.board[startY][startX]->setTeam(None);
            return true;
        }
    }

    if (endX == startX && endY == startY + 2 * direction) {
        int startRow = (team == White) ? 6 : 1;
        if (startY == startRow &&
            b.board[startY + direction][startX]->getTeam() == None &&
            b.board[endY][endX]->getTeam() == None) {

            delete b.board[endY][endX];
            b.board[endY][endX] = new Pawn();
            b.board[endY][endX]->setTeam(team);

            delete b.board[startY][startX];
            b.board[startY][startX] = new Blank();
            b.board[startY][startX]->setTeam(None);
            return true;
        }
    }

    if ((endX == startX + 1 || endX == startX - 1) && endY == startY + direction) {
        if (b.board[endY][endX]->getTeam() != None && b.board[endY][endX]->getTeam() != team) {
            delete b.board[endY][endX];
            b.board[endY][endX] = new Pawn();
            b.board[endY][endX]->setTeam(team);

            delete b.board[startY][startX];
            b.board[startY][startX] = new Blank();
            b.board[startY][startX]->setTeam(None);
            return true;
        }
    }

    std::cout << "Invalid Pawn Move" << std::endl;
    return false;
}

bool Blank::move(std::pair<int,int> start, std::pair<int,int> end, Board& b){
     std::cout << "Invalid Blank Move" << std::endl;
     return false;
}