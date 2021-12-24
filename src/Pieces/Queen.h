#ifndef QUEEN_H
#define QUEEN_H

#include "FastPiece.h"

/*
 * Represents a queen chess piece. Derived from FastPiece class
*/
class Queen : public FastPiece {
public:
    Queen(Color color, Vector starting_pos) : FastPiece(color, QUEEN, 9, starting_pos) {
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
