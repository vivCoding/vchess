#ifndef FAST_PIECE_H
#define FAST_PIECE_H

#include "Piece.h"

/*
 * Represents chess pieces that move more than one space at a time
 * All fast pieces derive from this class (e.g. Bishop, Rook, Queen)
 * Derived from class Piece
*/
class FastPiece : public Piece {
public:
    FastPiece(Color color, PieceType type, int value, Vector starting_position)
        : Piece(color, type, value, starting_position)
    {}

    bool is_valid_move(Vector next_position, Board *board);
    vector<Move> get_valid_moves(Board* board);
};

#endif
