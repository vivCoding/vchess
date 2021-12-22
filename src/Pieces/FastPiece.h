#include "Piece.h"

#ifndef FAST_PIECE_H
#define FAST_PIECE_H

// forward declare, avoid circular dependencies
class Board;

class FastPiece : public Piece {
public:

    bool is_valid_move(Vector next_move, Board *board);
};

#endif