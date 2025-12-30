#pragma once

#include <iostream>
#include <string>
#include <utility>

enum Team{
    White,
    Black,
    None
};

struct Board;

class Peice{
    public:
        std::string nameW;
        std::string nameB;

        Team team;

        Peice(const std::string& nw, const std::string& nb) : nameW(nw), nameB(nb) {}

        virtual bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) = 0;
        virtual ~Peice() = default; 

        void printName(){
            if(team == White){
                std::cout << nameW;
            }
            else{
                std::cout << nameB;
            }
        }

        void setTeam(Team t){
            team = t;
        }
        Team getTeam(){
            return team;
        }
        
};

class Knight : public Peice{
    public:
        Knight() : Peice("♘", "♞") {}
        bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) override;
};

class King : public Peice{
    public:
        King() : Peice("♔", "♚") {}
        bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) override;
};

class Queen : public Peice{
    public:
        Queen() : Peice("♕", "♛") {}
        bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) override;
};

class Rook : public Peice{
    public:
        Rook() : Peice("♖", "♜") {}
        bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) override;
};

class Bishop : public Peice{
    public:
        Bishop() : Peice("♗", "♝") {}
        bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) override;
};
class Pawn : public Peice{
    public:
        Pawn() : Peice("♙", "♟") {}
        bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) override;
    };

class Blank : public Peice{
    public:
        Blank() : Peice("·", "·") {}
        bool move(std::pair<int, int> start, std::pair<int, int> end, Board& b) override;
};