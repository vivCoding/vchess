#include "../Pieces/Piece.h"
#include "Move.h"

Move::Move() {}
Move::Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced)
    : move_from(move_from), move_to(move_to)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(piece_replaced == NULL ? MOVE : CAPTURE), first_move(piece_moved == NULL ? false : !piece_moved->has_moved) {}
Move::Move(int fx, int fy, int tx, int ty, Piece *piece_moved, Piece *piece_replaced)
    : move_from(Vector(fx, fy)), move_to(tx, ty)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(piece_replaced == NULL ? MOVE : CAPTURE), first_move(piece_moved == NULL ? false : !piece_moved->has_moved) {}
Move::Move(Vector move_from, Vector move_to, Piece* piece_moved, Piece* piece_replaced, MoveType type)
    : move_from(move_from), move_to(move_to)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(type), first_move(piece_moved == NULL ? false : !piece_moved->has_moved) {}
Move::Move(int fx, int fy, int tx, int ty, Piece *piece_moved, Piece *piece_replaced, MoveType type)
    : move_from(Vector(fx, fy)), move_to(tx, ty)
    , piece_moved(piece_moved), piece_replaced(piece_replaced)
    , type(type), first_move(piece_moved == NULL ? false : !piece_moved->has_moved) {}

string Move::as_string() {
    if (type == CASTLE) return "0-0";
    else if (type == QUEENSIDE_CASTLE) return "0-0-0";
    string s = "";
    if (piece_moved->type != PAWN) s += (char) piece_moved->type;
    s += cols[move_from.x] + to_string(move_from.y + 1);
    s += type == CAPTURE ? "x" : "-";
    s += cols[move_to.x] + to_string(move_to.y + 1);
    return s;
}