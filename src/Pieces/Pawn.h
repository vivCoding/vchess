/*
 * Pawn
 * 
 * The pawn is a special chess piece, with many conditional properties.
 * Thus the need to override many methods for this pieces is necessary
*/

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Board;

class Pawn : public Piece {
public:
    Pawn(Color color, Vector starting_pos) : Piece(color, PAWN, 1, starting_pos) {
        this->num_moves = 4;
        this->moves = new Vector[4] {
            Vector(0, 1),
            Vector(0, 2),
            Vector(-1, 1),
            Vector(1, 1)
        };
    }

    bool is_valid_move(Vector next_move, Board* board);
    vector<Vector> get_valid_moves(Board* board);
};

#endif
