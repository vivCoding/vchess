#include "../Board/Board.h"
#include "Pawn.h"

bool Pawn::is_valid_move(Vector next_move, Board *board) {
    if (board->within_boundaries(next_move)) {
        int sign = color == WHITE ? 1 : -1;
        // check capture moves
        for (int i = 2; i < 4; i++) {
            Vector v = position.add(moves[i].scale(sign));
            Piece* p = board->get_piece(v);
            if (next_move.equal_to(v) && p != NULL && p->color != color) {
                return true;
            }
        }
        return (
            // check move forward 1
            (next_move.equal_to(position.add(moves[0].scale(sign))))
            && (board->get_piece(next_move) == NULL)
        ) || (
            // check move forward 2
            (next_move.equal_to(position.add(moves[1].scale(sign))))
            && ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
            && (board->get_piece(position.x, color == WHITE ? 2 : 5) == NULL)
            && (board->get_piece(position.x, color == WHITE ? 3 : 4) == NULL)
        );
    }
    return false;
}

vector<Vector> Pawn::get_valid_moves(Board* board) {
    vector<Vector> valid_moves;
    int sign = color == WHITE ? 1 : -1;
    // check capture moves
    for (int i = 2; i < 4; i++) {
        Vector v = position.add(moves[i].scale(sign));
        if (board->within_boundaries(v)) {
            Piece* p = board->get_piece(v);
            if (p != NULL && p->color != color) {
                valid_moves.push_back(v);
            }
        }
    }
    // check move forward 1
    Vector v = position.add(moves[0].scale(sign));
    if (board->within_boundaries(v) && board->get_piece(v) == NULL)
        valid_moves.push_back(v);
    // check move forward 2
    if (
        ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
        && (board->get_piece(position.x, color == WHITE ? 2 : 5) == NULL)
        && (board->get_piece(position.x, color == WHITE ? 3 : 4) == NULL)
    ) valid_moves.push_back(position.add(moves[1].scale(sign)));
    return valid_moves;
}
