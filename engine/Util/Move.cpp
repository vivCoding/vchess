#include "../Pieces/Piece.h"
#include "Move.h"

Move::Move() : type(MOVE), promote_to(NONE), old_pawn(NULL) {}
Move::Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced)
    : move_from(move_from), move_to(move_to)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(piece_replaced == NULL ? MOVE : CAPTURE), first_move(piece_moved == NULL ? false : !piece_moved->has_moved)
    , promote_to(NONE), old_pawn(NULL) {}

Move::Move(int fx, int fy, int tx, int ty, Piece *piece_moved, Piece *piece_replaced)
    : move_from(Vector(fx, fy)), move_to(tx, ty)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(piece_replaced == NULL ? MOVE : CAPTURE), first_move(piece_moved == NULL ? false : !piece_moved->has_moved)
    , promote_to(NONE), old_pawn(NULL) {}

// specify move type
Move::Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type)
    : move_from(move_from), move_to(move_to)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(type), first_move(piece_moved == NULL ? false : !piece_moved->has_moved)
    , promote_to(NONE), old_pawn(type == PAWN_PROMOTION ? piece_moved : NULL) {}

Move::Move(int fx, int fy, int tx, int ty, Piece *piece_moved, Piece *piece_replaced, MoveType type)
    : move_from(Vector(fx, fy)), move_to(tx, ty)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(type), first_move(piece_moved == NULL ? false : !piece_moved->has_moved)
    , promote_to(NONE), old_pawn(type == PAWN_PROMOTION ? piece_moved : NULL) {}

// specify piece to promote to
Move::Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type, PieceType promote_to)
    : move_from(move_from), move_to(move_to)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(type), first_move(piece_moved == NULL ? false : !piece_moved->has_moved)
    , promote_to(promote_to), old_pawn(type == PAWN_PROMOTION ? piece_moved : NULL) {}

Move::Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type, PieceType promote_to, Piece* old_pawn)
    : move_from(move_from), move_to(move_to)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(type), first_move(piece_moved == NULL ? false : !piece_moved->has_moved)
    , promote_to(promote_to), old_pawn(old_pawn) {}

string Move::as_string() {
    if (type == CASTLE) return "0-0";
    else if (type == QUEENSIDE_CASTLE) return "0-0-0";
    string s = "";
    if (piece_moved->type != PAWN && type != PAWN_PROMOTION) s += (char) piece_moved->type;
    s += cols[move_from.x] + to_string(move_from.y + 1);
    s += type == CAPTURE || (type == PAWN_PROMOTION && piece_replaced != NULL) ? "x" : "-";
    s += cols[move_to.x] + to_string(move_to.y + 1);
    if (type == PAWN_PROMOTION) s += (char) promote_to;
    return s;
}