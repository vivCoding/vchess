#ifndef MOVE_H
#define MOVE_H

#include "Vector.h"
#include "../Pieces/PieceTypes.h"
#include "../Pieces/Piece.h"

/*
 * Constants for move types
*/
enum MoveType {
    MOVE = 'm',
    CAPTURE = 'c',
    CASTLE = 't',
    QUEENSIDE_CASTLE = 'q',
    PAWN_PROMOTION = 'p'
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
    // used for pawn promotion
    PieceType promote_to;
    // when pawn is promoted, this is used to store the pawn for reuse
    Piece* old_pawn;

    Move();
    // Creates a move. Move type is automatically set to CAPTURE if it sees piece_replaced is not NULL
    Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced);
    Move(int fx, int fy, int tx, int ty, Piece *piece_moved, Piece* piece_replaced);
    // Specify move type
    Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type);
    Move(int fx, int fy, int tx, int ty, Piece* piece_moved, Piece* piece_replaced, MoveType type);
    // Specify piece to promote to. When it gets promoted, 
    Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type, PieceType promote_to);
    Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type, PieceType promote_to, Piece* old_pawn);

    /*
     * Returns the move in a readable format with chess coordinates
    */
    string as_string();
};

#endif
