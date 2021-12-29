
#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

/*
 * Represents a pawn chess piece. Derived from Piece class
 * 
 * The pawn is a special chess piece, with many conditional properties.
 * Thus the need to override many methods for this pieces is necessary
*/
class Pawn : public Piece {
public:
    Pawn(Color color, Vector starting_pos) : Piece(color, PAWN, 10, starting_pos) {
        this->num_moves = 4;
        this->moves = new Vector[4] {
            Vector(0, 1),
            Vector(0, 2),
            Vector(-1, 1),
            Vector(1, 1)
        };
        this->square_table = new int[64] {
            0, 0, 0, 0, 0, 0, 0, 0,
            50, 50, 50, 50, 50, 50, 50, 50,
            10, 10, 20, 30, 30, 20, 10, 10,
            5, 5, 10, 25, 25, 10, 5, 5,
            0, 0, 0, 20, 20, 0, 0, 0,
            5, -5, -10, 0, 0, -10, -5, 5,
            5, 10, 10, -20, -20, 10, 10, 5,
            0, 0, 0, 0, 0, 0, 0, 0
        };
        this->end_square_table = NULL;
    }

    bool is_valid_move(Vector next_position, Board *board);
    vector<Move> get_valid_moves(Board* board);
};

#endif
