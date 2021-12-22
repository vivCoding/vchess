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
        this->is_valid = true;
        this->num_moves = 4;
        this->moves = new Vector[num_moves] {
            Vector(1, 1),
            Vector(1, -1),
            Vector(-1, -1),
            Vector(-1, 1),
        };
    }
};

#endif