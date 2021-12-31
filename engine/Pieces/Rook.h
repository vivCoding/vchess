#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

/*
 * Represents a rook chess piece. Derived from FastPiece class
*/
class Rook : public Piece {
public:
    Rook(Color color, Vector starting_pos) : Piece(
        ROOK, 50, color, starting_pos, 
        {
            Vector(0, 1),
            Vector(1, 0),
            Vector(0, -1),
            Vector(-1, 0),
        },
        new int[64] {
            0,  0,  0,  0,  0,  0,  0,  0,
            5, 10, 10, 10, 10, 10, 10,  5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            -5,  0,  0,  0,  0,  0,  0, -5,
            0,  0,  0,  5,  5,  0,  0,  0
        },
        NULL
    ) {}
};

#endif
