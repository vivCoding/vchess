#include "../Board/Board.h"
#include "FastPiece.h"

bool FastPiece::is_valid_move(Vector next_move, Board* board) {
    if (board->within_boundaries(next_move)) {
        for (int i = 0; i < this->num_moves; i++) {
            for (int j = 1; j < BOARD_SIZE; j++) {
                Vector v = position.add(moves[i].scale(j));
                Piece* p = board->get_piece(v);
                if (!board->within_boundaries(v) || (p != NULL && (!next_move.equal_to(v) || p->color == color))) {
                    break;
                } else if (next_move.equal_to(v) && (p == NULL || (p != NULL && p->color != color))) {
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
        for (int j = 1; j < BOARD_SIZE; j++) {
            Vector v = position.add(moves[i].scale(j));
            Piece* p = board->get_piece(v);
            if (!board->within_boundaries(v) || (p != NULL && p->color == color)) {
                break;
            } else {
                valid_moves.push_back(v);
                if (p != NULL) break;
            }
        }
    }
    return valid_moves;
}
