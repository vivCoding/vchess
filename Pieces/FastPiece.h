#include "Piece.h"

#ifndef FAST_PIECE_H
#define FAST_PIECE_H

class FastPiece : public Piece {
public:
    int is_valid_move(Vector nextMove) {
        return 0;
    }
};

#endif