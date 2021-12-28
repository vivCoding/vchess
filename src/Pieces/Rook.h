#ifndef ROOK_H
#define ROOK_H

#include "FastPiece.h"

/*
 * Represents a rook chess piece. Derived from FastPiece class
*/
class Rook : public FastPiece {
public:
    Rook(Color color, Vector starting_pos) : FastPiece(color, ROOK, 50, starting_pos) {
        this->num_moves = 4;
        this->moves = new Vector[num_moves] {
            Vector(0, 1),
            Vector(1, 0),
            Vector(0, -1),
            Vector(-1, 0),
        };
        this->square_table = new int[64] {
            0,  0,  0,  0,  0,  0,  0,  0,
            5, 10, 10, 10, 10, 10, 10,  5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            0,  0,  0,  5,  5,  0,  0,  0
        };
        this->end_square_table = NULL;
    }
};

#endif
