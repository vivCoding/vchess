#include "../Board/Board.h"
#include "Piece.h"
#include <iostream>
using namespace std;

bool Piece::is_valid_move(Vector next_move, Board* board) {
    if (is_valid && next_move.x >= 0 && next_move.x < 8 && next_move.y >= 0 && next_move.y < 8) {
        for (int i = 0; i < this->num_moves; i++) {
            Vector v = position.add(moves[i]);
            Piece* p = board->get_piece(v.x, v.y);
            if (next_move.equal_to(v) && (!p->is_valid || p->color != color)) {
                return true;
            }
        }
    }
    return false;
}