#include "../Board/Board.h"
#include "Pawn.h"

bool Pawn::is_valid_move(Vector next_move, Board *board) {
    cout << "pawn stuff" << endl;
    int sign = color == WHITE ? 1 : -1;
    // check capture moves
    for (int i = 2; i < 4; i++) {
        Vector v = position.add(moves[i].scale(sign));
        if (next_move.equal_to(v) && board->get_piece(v.x, v.y)->is_valid && board->get_piece(v.x, v.y)->color != color) {
            return true;
        }
    }
    return (
        // check move forward 2
        (next_move.equal_to(position.add(moves[1].scale(sign))))
        && ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
        && (!board->get_piece(position.x, color == WHITE ? 2 : 5)->is_valid)
        && (!board->get_piece(position.x, color == WHITE ? 3 : 4)->is_valid)
    ) || (
        // check move forward 1
        (next_move.equal_to(position.add(moves[0].scale(sign))))
        && (!board->get_piece(next_move.x, next_move.y)->is_valid)
    );
}