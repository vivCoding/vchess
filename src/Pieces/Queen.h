#ifndef QUEEN_H
#define QUEEN_H

#include "FastPiece.h"

/*
 * Represents a queen chess piece. Derived from FastPiece class
*/
class Queen : public FastPiece {
public:
    Queen(Color color, Vector starting_pos) : FastPiece(color, QUEEN, 90, starting_pos) {
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
        this->square_table = new int[64] {
            -20,-10,-10, -5, -5,-10,-10,-20,
            -10,  0,  0,  0,  0,  0,  0,-10,
            -10,  0,  5,  5,  5,  5,  0,-10,
            -5,  0,  5,  5,  5,  5,  0, -5,
            0,  0,  5,  5,  5,  5,  0, -5,
            -10,  5,  5,  5,  5,  5,  0,-10,
            -10,  0,  5,  0,  0,  0,  0,-10,
            -20,-10,-10, -5, -5,-10,-10,-20
        };
        this->end_square_table = NULL;
    }
};

#endif
