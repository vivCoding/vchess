#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

/*
 * Represents a bishop chess piece
*/
class Bishop : public Piece {
public:
    Bishop(Color color, Vector starting_pos) : Piece(
        BISHOP, 35, color, starting_pos, 
        {
            Vector(1, 1),
            Vector(1, -1),
            Vector(-1, -1),
            Vector(-1, 1),
        },
        new int[64] {
            -20,-10,-10,-10,-10,-10,-10,-20,
            -10,  0,  0,  0,  0,  0,  0,-10,
            -10,  0,  5, 10, 10,  5,  0,-10,
            -10,  5,  5, 10, 10,  5,  5,-10,
            -10,  0, 10, 10, 10, 10,  0,-10,
            -10, 10, 10, 10, 10, 10, 10,-10,
            -10,  5,  0,  0,  0,  0,  5,-10,
            -20,-10,-10,-10,-10,-10,-10,-20,  
        },
        NULL
    ) {}
};

#endif
