#include "FastPiece.h"
#include "../Board/Colors.h"

#ifndef QUEEN_H
#define QUEEN_H

class Queen : public FastPiece {
public:
    Queen(Color color, Vector startPos) {
        this->color = color;
        this->position = Vector(startPos.x, startPos.y);
        this->symbol = 'Q';
        this->num_moves = 8;
        Vector moves[8] = {
            Vector(0, 1),
            Vector(1, 1),
            Vector(1, 0),
            Vector(1, -1),
            Vector(0, -1),
            Vector(-1, -1),
            Vector(-1, 0),
            Vector(-1, 1),
        };
        this->moves = moves;
    }
};

#endif