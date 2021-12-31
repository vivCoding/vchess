#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

/*
 * Represents a knight chess piece. Derived from Piece class
*/
class Knight : public Piece {
public:
    Knight(Color color, Vector starting_pos) : Piece(
        KNIGHT, 30, color, starting_pos, 
        {
            Vector(-2, 1),
            Vector(-2, -1),
            Vector(-1, 2),
            Vector(-1, -2),
            Vector(1, 2),
            Vector(1, -2),
            Vector(2, 1),
            Vector(2, -1),
        },
        new int[64] {
            -50,-40,-30,-30,-30,-30,-40,-50,
            -40,-20,  0,  0,  0,  0,-20,-40,
            -30,  0, 10, 15, 15, 10,  0,-30,
            -30,  5, 15, 20, 20, 15,  5,-30,
            -30,  0, 15, 20, 20, 15,  0,-30,
            -30,  5, 10, 15, 15, 10,  5,-30,
            -40,-20,  0,  5,  5,  0,-20,-40,
            -50,-40,-30,-30,-30,-30,-40,-50, 
        },
        NULL
    ) {}
};

#endif
