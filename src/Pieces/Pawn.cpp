#include "../Board/Board.h"
#include "Pawn.h"

bool Pawn::is_valid_move(Vector next_move, Board *board) {
    int sign = color == WHITE ? 1 : -1;
    // check capture moves
    for (int i = 2; i < 4; i++) {
        Vector v = position.add(moves[i].scale(sign));
        Piece* p = board->get_piece(v);
        if (next_move.equal_to(v) && p->is_valid && p->color != color) {
            return true;
        }
    }
    return (
        // check move forward 1
        (next_move.equal_to(position.add(moves[0].scale(sign))))
        && (!board->get_piece(next_move)->is_valid)
    ) || (
        // check move forward 2
        (next_move.equal_to(position.add(moves[1].scale(sign))))
        && ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
        && (!board->get_piece(position.x, color == WHITE ? 2 : 5)->is_valid)
        && (!board->get_piece(position.x, color == WHITE ? 3 : 4)->is_valid)
    );
}

vector<Vector> Pawn::get_valid_moves(Board* board) {
    vector<Vector> valid_moves;
    int sign = color == WHITE ? 1 : -1;
    // check capture moves
    for (int i = 2; i < 4; i++) {
        Vector v = position.add(moves[i].scale(sign));
        Piece* p = board->get_piece(v);
        if (p->is_valid && p->color != color) {
            valid_moves.push_back(v);
        }
    }
    // check move forward 1
    if ((!board->get_piece(position.add(moves[0].scale(sign)))->is_valid))
        valid_moves.push_back(moves[0]);
    // check move forward 2
    if (
        ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
        && (!board->get_piece(position.x, color == WHITE ? 2 : 5)->is_valid)
        && (!board->get_piece(position.x, color == WHITE ? 3 : 4)->is_valid)
    ) valid_moves.push_back(moves[1]);
    return valid_moves;
}
