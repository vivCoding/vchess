#include "../Board/Board.h"
#include "FastPiece.h"

bool FastPiece::is_valid_move(Vector next_move, Board* board) {
    if (is_valid && next_move.x >= 0 && next_move.x < 8 && next_move.y >= 0 && next_move.y < 8) {
        for (int i = 0; i < this->num_moves; i++) {
            for (int j = 1; j < 8; j++) {
                Vector v = position.add(moves[i].scale(j));
                Piece* p = board->get_piece(v);
                if (v.x < 0 || v.x >= 8 || v.y < 0 || v.y >= 8 || (p->is_valid && (!next_move.equal_to(v) || p->color == color))) {
                    break;
                } else if (next_move.equal_to(v) && (p->is_valid || (!p->is_valid && p->color != color))) {
                    return true;
                }
            }
        }
    }
    return false;
}

vector<Vector> FastPiece::get_valid_moves(Board* board) {
    vector<Vector> valid_moves;
    for (int i = 0; i < this->num_moves; i++) {
        for (int j = 1; j < 8; j++) {
            Vector v = position.add(moves[i].scale(j));
            Piece* p = board->get_piece(v);
            if (v.x < 0 || v.x >= 8 || v.y < 0 || v.y >= 8 || (p->is_valid && p->color != color)) {
                break;
            } else {
                valid_moves.push_back(position.add(moves[i]));
                if (p->is_valid) break;
            }
        }
    }
    return valid_moves;
}
