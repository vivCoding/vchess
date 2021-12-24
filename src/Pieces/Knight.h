#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

/*
 * Represents a knight chess piece. Derived from Piece class
*/
class Knight : public Piece {
public:
    Knight(Color color, Vector starting_pos) : Piece(color, KNIGHT, 3, starting_pos) {
        this->num_moves = 8;
        this->moves = new Vector[this->num_moves]{
            Vector(-2, 1),
            Vector(-2, -1),
            Vector(-1, 2),
            Vector(-1, -2),
            Vector(1, 2),
            Vector(1, -2),
            Vector(2, 1),
            Vector(2, -1),
        };
    }
};

#endif
