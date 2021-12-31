#ifndef MOVE_H
#define MOVE_H

#include "Vector.h"
#include "../Pieces/Piece.h"

/*
 * Constants for move types
*/
enum MoveType {
    MOVE,
    CAPTURE,
    CHECK,
    CHECKMATE,
    CASTLE,
    QUEENSIDE_CASTLE
};

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
    MoveType type;
    // determines if it's the piece_moved first time moving
    bool first_move;

    Move();
    // Creates a move. Move type is automatically set to CAPTURE if it sees piece_replaced is not NULL
    Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced);
    Move(int fx, int fy, int tx, int ty, Piece *piece_moved, Piece* piece_replaced);
    Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type);
    Move(int fx, int fy, int tx, int ty, Piece* piece_moved, Piece* piece_replaced, MoveType type);

    /*
     * Returns the move in a readable format with chess coordinates
    */
    string as_string();
};

#endif
