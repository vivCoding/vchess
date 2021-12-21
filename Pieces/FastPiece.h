#include "Piece.h"

#ifndef FAST_PIECE_H
#define FAST_PIECE_H

// forward declare, avoid circular dependencies
class Board;

class FastPiece : public Piece {
public:
    int is_valid_move(Vector nextMove, Board* board) {
        return 0;
    }
};

#endif