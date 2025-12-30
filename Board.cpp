#include "Board.hpp"
#include "chess.hpp"

Board::Board() {

    board[0][0] = new Rook();
    board[0][1] = new Knight();
    board[0][2] = new Bishop();
    board[0][3] = new Queen();
    board[0][4] = new King();
    board[0][5] = new Bishop();
    board[0][6] = new Knight();
    board[0][7] = new Rook();

    for (int i = 0; i < 8; i++){
        board[1][i] = new Pawn();
    }

    for (int i = 2; i < 6; i++){
        for (int j = 0; j < 8; j++){
            board[i][j] = new Blank();
        }
    }
    
    for(int i = 0; i < 8; i++){
        board[6][i] = new Pawn();
    }

    board[7][0] = new Rook();
    board[7][1] = new Knight();
    board[7][2] = new Bishop();
    board[7][3] = new King();
    board[7][4] = new Queen();
    board[7][5] = new Bishop();
    board[7][6] = new Knight();
    board[7][7] = new Rook();

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(i < 2){
                board[i][j]->setTeam(Black);
            }
            else if (i < 6){
                board[i][j]->setTeam(None);
            }
            else{
                board[i][j]->setTeam(White);
            }
        }
    }

    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            positions[i][j] = std::pair<int, int>{i, j};
        }
    }
}

void Board::printBoard(){
    std::cout << "  ";
    for (int j = 0; j < 8; j++){
        std::cout << j << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < 8; i++){
        std::cout << i << " ";
        for (int j = 0; j < 8; j++){
            bool dark = (i + j) % 2;
            board[i][j]->printName();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}
