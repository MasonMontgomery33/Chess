#include "chess.hpp"
#include <utility>
#include <vector>
#include <array>
#include "Board.hpp"

std::pair<int, int> getPosition() {
    int row, col;
    std::cout << "Enter row and column: ";
    std::cin >> row >> col;
    return {row, col};
}

int main() {
    Board b;
    b.printBoard();

    bool check = true;
    bool turn = false;

    std::cout << "Enter Your Start then End Coordinates for a move in format row col, type: 8 8 to end game" << std::endl;
    std::cout << "Start: ";
    std::pair<int, int> start = getPosition();

    std::cout << "End: ";

    std::pair<int , int> end = getPosition();

    // turn false - White -- Turn true - Black
    while(check){
        if(!turn){
            if(b.board[start.first][start.second]->getTeam() == White){
                std::string temp = b.board[end.first][end.second]->nameW;
                if(b.board[start.first][start.second]->move(start, end, b)){
                    if(temp == "♔"){
                        std::cout << "Game Over";
                        break;
                    }
                    turn = !turn;
                }
            }
            else{
                std::cout << "Not Your Turn" << std::endl;
            }
        }
        else{
            if(b.board[start.first][start.second]->getTeam() == Black){
                std::string temp = b.board[end.first][end.second]->nameW;
                if(b.board[start.first][start.second]->move(start, end, b)){
                    if(temp == "♔"){
                        std::cout << "Game Over";
                        break;
                    }
                    turn = !turn;
                }
            }
            else{
                std::cout << "Not Your Turn"  << std::endl;
            }
        }

        b.printBoard();

        std::cout << "Start: ";

        start = getPosition();

        std::cout << "End: ";

        end = getPosition();

        if(start == std::pair<int, int>{8, 8} || end == std::pair<int, int>{8, 8}){
            check = false;
        }
    }
} // g++ -Wall -Wextra -std=c++17 main.cpp Board.cpp chess.cpp -o chess