#include "Piece.h"
#include "../Board/Colors.h"

#ifndef PAWN_H
#define PAWN_H

class Pawn : public Piece {
private:
    Vector initMove = Vector(0, 2);
public:
    Pawn(Color color, Vector startPos) {
        this->color = color;
        this->position = Vector(startPos.x, startPos.y);
        this->symbol = 'P';
        this->num_moves = 3;
        Vector moves[3] = {
            Vector(0, 1),
            Vector(1, 1),
            Vector(-1, 1),
        };
        this->moves = moves;
    }

    int makeMove(Vector nextMove) {
        return 0;
    }
};

#endif