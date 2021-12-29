#ifndef BISHOP_H
#define BISHOP_H

#include "FastPiece.h"

/*
 * Represents a bishop chess piece. Derived from FastPiece class
*/
class Bishop : public FastPiece {
public:
    Bishop(Color color, Vector starting_pos) : FastPiece(color, BISHOP, 30, starting_pos) {
        this->num_moves = 4;
        this->moves = new Vector[num_moves] {
            Vector(1, 1),
            Vector(1, -1),
            Vector(-1, -1),
            Vector(-1, 1),
        };
        this->square_table = new int[64] {
            -20,-10,-10,-10,-10,-10,-10,-20,
            -10,  0,  0,  0,  0,  0,  0,-10,
            -10,  0,  5, 10, 10,  5,  0,-10,
            -10,  5,  5, 10, 10,  5,  5,-10,
            -10,  0, 10, 10, 10, 10,  0,-10,
            -10, 10, 10, 10, 10, 10, 10,-10,
            -10,  5,  0,  0,  0,  0,  5,-10,
            -20,-10,-10,-10,-10,-10,-10,-20,  
        };
        this->end_square_table = NULL;
    }
};

#endif
