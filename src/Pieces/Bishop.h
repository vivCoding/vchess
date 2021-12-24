#ifndef BISHOP_H
#define BISHOP_H

#include "FastPiece.h"

/*
 * Represents a bishop chess piece. Derived from FastPiece class
*/
class Bishop : public FastPiece {
public:
    Bishop(Color color, Vector starting_pos) : FastPiece(color, BISHOP, 3, starting_pos) {
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
