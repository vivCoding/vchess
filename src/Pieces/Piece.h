#include "../Util/Vector.h"
#include "../Board/Colors.h"

#ifndef PIECE_H
#define PIECE_H

class Board;

class Piece {
protected:
    int num_moves = 0;
    Vector* moves;
public:
    bool is_valid = true;
    char symbol;
    Color color;
    Vector position;

    Piece() : is_valid(false) {}

    bool is_valid_move(Vector next_move, Board* board);
};

#endif