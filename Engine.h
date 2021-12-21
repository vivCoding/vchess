#include "Board/Board.h"
#include "Pieces/Piece.h"

#ifndef ENGINE_H
#define ENGINE_h

class ChessEngine {
private:
    Board board;
public:
    ChessEngine() {};

    bool move_piece(int px, int py, int nx, int ny) {
        return board.move_piece(px, py, nx, ny);
    }

    void print_board() {
        board.print_board();
    }
};

#endif