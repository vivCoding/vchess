#include "../Util/Vector.h"
#include "../Board/Colors.h"

#ifndef PIECE_H
#define PIECE_H

class Piece {
protected:
    int num_moves = 0;
    Vector* moves;
public:
    char symbol = '.';
    Color color;
    Vector position;

    Piece() {};

    bool is_valid() {
        return symbol != '.';
    }

    int is_valid_move(Vector nextMove) {
        return 0;
    }
};

#endif