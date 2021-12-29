#ifndef MOVE_H
#define MOVE_H

#include "Vector.h"
#include "../Pieces/Piece.h"

class Piece;
/*
 * Represents a chess move
 * Stores the position of piece to move from, and the position to where the piece needs to move, as well as pointers to the pieces moved/replaced
 * Does not handle Piece memory
*/
class Move {
private:
    string cols = "abcdefgh";
public:
    Vector move_from;
    Vector move_to;
    Piece* piece_moved;
    Piece* piece_replaced;

    Move() {}
    Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced)
        : move_from(move_from), move_to(move_to)
        , piece_moved(piece_moved), piece_replaced(piece_replaced)
    {}
    Move(int fx, int fy, int tx, int ty, Piece *piece_moved, Piece *piece_replaced)
        : move_from(Vector(fx, fy)), move_to(tx, ty)
        , piece_moved(piece_moved), piece_replaced(piece_replaced)
    {}

    /*
     * Returns the move in a readable format with chess coordinates
    */
    string as_string() {
        return cols[move_from.x] + to_string(move_from.y + 1) + " " + cols[move_to.x] + to_string(move_to.y + 1);
    }
};

#endif
