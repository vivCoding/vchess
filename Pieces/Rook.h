#include "FastPiece.h"
#include "../Board/Colors.h"

#ifndef ROOK_H
#define ROOK_H

class Rook : public FastPiece {
public:
    Rook(Color color, Vector startPos) {
        this->color = color;
        this->position = Vector(startPos.x, startPos.y);
        this->symbol = 'R';
        this->num_moves = 4;
        Vector moves[4] = {
            Vector(0, 1),
            Vector(1, 0),
            Vector(0, -1),
            Vector(-1, 0),
        };
        this->moves = moves;
    }
};

#endif