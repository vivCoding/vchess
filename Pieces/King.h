#include "Piece.h"
#include "../Board/Colors.h"

#ifndef KING_H
#define KING_H

class King : public Piece {
public:
    King(Color color, Vector startPos) {
        this->color = color;
        this->position = Vector(startPos.x, startPos.y);
        this->symbol = 'K';
        this->num_moves = 8;
        Vector moves[8] = {
            Vector(0, 1),
            Vector(1, 1),
            Vector(1, 0),
            Vector(1, -1),
            Vector(0, -1),
            Vector(-1, -1),
            Vector(-1, 0),
            Vector(-1, 1),
        };
        this->moves = moves;
    }
};

#endif