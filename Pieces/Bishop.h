#include "FastPiece.h"
#include "../Board/Colors.h"

#ifndef BISHOP_H
#define BISHOP_H

class Bishop : public FastPiece {
public:
    Bishop(Color color, Vector startPos) {
        this->color = color;
        this->position = Vector(startPos.x, startPos.y);
        this->symbol = 'B';
        this->num_moves = 4;
        Vector moves[4] = {
            Vector(1, 1),
            Vector(1, -1),
            Vector(-1, -1),
            Vector(-1, 1),
        };
        this->moves = moves;
    }
};

#endif