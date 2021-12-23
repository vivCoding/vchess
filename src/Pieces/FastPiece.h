#ifndef FAST_PIECE_H
#define FAST_PIECE_H

#include "Piece.h"

// forward declare, avoid circular dependencies
class Board;

class FastPiece : public Piece {
public:
    FastPiece(Color color, PieceType type, int value, Vector starting_position)
        : Piece(color, type, value, starting_position)
    {}

    bool is_valid_move(Vector next_move, Board *board);
    vector<Vector> get_valid_moves(Board* board);
};

#endif
