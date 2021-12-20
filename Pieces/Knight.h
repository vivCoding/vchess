#include "Piece.h"
#include "../Board/Colors.h"

#ifndef KNIGHT_H
#define KNIGHT_H

class Knight : public Piece {
public:
    Knight(Color color, Vector startPos) {
        this->color = color;
        this->position = Vector(startPos.x, startPos.y);
        this->symbol = 'N';
        this->num_moves = 8;
        Vector moves[8] = {
            Vector(-2, 1),
            Vector(-2, -1),
            Vector(-1, 2),
            Vector(-1, -2),
            Vector(1, 2),
            Vector(1, -2),
            Vector(2, 1),
            Vector(2, -1),
        };
        this->moves = moves;
    }
};

#endif