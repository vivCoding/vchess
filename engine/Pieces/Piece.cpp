#include "../Board/Board.h"
#include "Piece.h"

bool Piece::is_valid_move(Vector next_position, Board* board) {
    if (board->within_boundaries(next_position)) {
        for (int i = 0; i < this->num_moves; i++) {
            Vector v = position.add(moves[i]);
            Piece* p = board->get_piece(v);
            if (next_position.equal_to(v) && (p == NULL || p->color != color)) {
                return true;
            }
        }
    }
    return false;
}

vector<Move> Piece::get_valid_moves(Board* board) {
    vector<Move> valid_moves;
    for (int i = 0; i < this->num_moves; i++) {
        Vector v = position.add(moves[i]);
        Piece* p = board->get_piece(v);
        if (board->within_boundaries(v) && (p == NULL || p->color != color)) {
            valid_moves.push_back(Move(position, v, this, p));
        }
    }
    return valid_moves;
}

int Piece::get_square_table_value() { return get_square_table_value(false); }
int Piece::get_square_table_value(bool endgame) {
    int x = position.x, y = position.y;
    return get_square_table_value(x, y, endgame);
}
int Piece::get_square_table_value(int x, int y, bool endgame) {
    if (endgame && end_square_table != NULL) {
        if (color == WHITE) return end_square_table[8 * (7 - y) + x];
        else return end_square_table[8 * y + x];
    } else {
        if (color == WHITE) return square_table[8 * (7 - y) + x];
        else return square_table[8 * y + x];
    }
}
