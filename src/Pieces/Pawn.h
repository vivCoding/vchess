#include "Piece.h"
#include "../Board/Colors.h"

#include <iostream>
using namespace std;

#ifndef PAWN_H
#define PAWN_H

class Board;

class Pawn : public Piece {
public:
    Pawn(Color color, Vector startPos) {
        this->color = color;
        this->position = Vector(startPos.x, startPos.y);
        this->symbol = 'P';
        this->is_valid = true;
        // NOTE: a very sketchy way. Figure out how to add member field to derived class, while still having Piece[][] array
        this->num_moves = 0;
        this->moves = new Vector[4] {
            Vector(0, 1),
            Vector(0, 2),
            Vector(-1, 1),
            Vector(1, 1)
        };
    }

    bool is_valid_move(Vector next_move, Board* board);
};

#endif