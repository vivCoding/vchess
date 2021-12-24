#ifndef KING_H
#define KING_H

#include "Piece.h"

/*
 * Represents a king chess piece. Derived from Piece class
*/
class King : public Piece {
public:
    King(Color color, Vector starting_pos) : Piece(color, KING, INT32_MAX, starting_pos) {
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
