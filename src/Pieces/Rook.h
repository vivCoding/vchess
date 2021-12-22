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
        this->is_valid = true;
        this->num_moves = 4;
        this->moves = new Vector[num_moves] {
            Vector(0, 1),
            Vector(1, 0),
            Vector(0, -1),
            Vector(-1, 0),
        };
    }
};

#endif