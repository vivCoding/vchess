#ifndef MOVE_H
#define MOVE_H

#include "Vector.h"

/*
 * Represents a chess move
 * Stores the position of piece to move from, and the position to where the piece needs to move
*/
class Move {
private:
    string cols = "abcdefgh";
public:
    Vector move_from;
    Vector move_to;

    Move() {}
    Move(Vector move_from, Vector move_to) : move_from(move_from), move_to(move_to) {}
    Move(int fx, int fy, int tx, int ty) : move_from(Vector(fx, fy)), move_to(tx, ty) {}

    string as_string() {
        return cols[move_from.x] + to_string(move_from.y) + " " + cols[move_to.x] + to_string(move_to.y);
    }
};

#endif
