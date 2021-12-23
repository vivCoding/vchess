#include "../Board/Board.h"
#include "Piece.h"

bool Piece::is_valid_move(Vector next_move, Board* board) {
    if (is_valid && next_move.x >= 0 && next_move.x < 8 && next_move.y >= 0 && next_move.y < 8) {
        for (int i = 0; i < this->num_moves; i++) {
            Vector v = position.add(moves[i]);
            Piece* p = board->get_piece(v);
            if (next_move.equal_to(v) && (p->is_valid || p->color != color)) {
                return true;
            }
        }
    }
    return false;
}

vector<Vector> Piece::get_valid_moves(Board* board) {
    vector<Vector> valid_moves;
    // NOTE: we don't run is_valid_move for every move since it has higher big-O
    for (int i = 0; i < this->num_moves; i++) {
        Vector v = position.add(moves[i]);
        Piece* p = board->get_piece(v);
        if (v.x >= 0 && v.x < 8 && v.y >= 0 && v.y < 8 && (!p->is_valid || (p->is_valid && p->color != color))) {
            valid_moves.push_back(position.add(moves[i]));
        }
    }
    return valid_moves;
}
