#include "../Board/Board.h"
#include "Piece.h"

bool Piece::is_valid_move(Vector next_move, Board* board) {
    if (board->within_boundaries(next_move)) {
        for (int i = 0; i < this->num_moves; i++) {
            Vector v = position.add(moves[i]);
            Piece* p = board->get_piece(v);
            if (next_move.equal_to(v) && (p == NULL || p->color != color)) {
                return true;
            }
        }
    }
    return false;
}

vector<Vector> Piece::get_valid_moves(Board* board) {
    vector<Vector> valid_moves;
    for (int i = 0; i < this->num_moves; i++) {
        Vector v = position.add(moves[i]);
        Piece* p = board->get_piece(v);
        if (board->within_boundaries(v) && (p == NULL || p->color != color)) {
            valid_moves.push_back(position.add(moves[i]));
        }
    }
    return valid_moves;
}
