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
        this->is_valid = true;
        this->num_moves = 8;
        this->moves = new Vector[this->num_moves] {
            Vector(0, 1),
            Vector(1, 1),
            Vector(1, 0),
            Vector(1, -1),
            Vector(0, -1),
            Vector(-1, -1),
            Vector(-1, 0),
            Vector(-1, 1),
        };
    }
};

#endif