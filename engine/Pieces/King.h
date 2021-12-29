#ifndef KING_H
#define KING_H

#include "Piece.h"

/*
 * Represents a king chess piece. Derived from Piece class
*/
class King : public Piece {
public:
    int* end_square_table;

    King(Color color, Vector starting_pos) : Piece(color, KING, INT16_MAX, starting_pos) {
        this->num_moves = 8;
        this->moves = new Vector[this->num_moves] {
            Vector(0, 1),
            Vector(1, 1),
            Vector(1, 0),
            Vector(1, -1),
            Vector(0, -1),
            Vector(-1, -1),
            Vector(-1, 0),
            Vector(-1, 1),
        };
        this->square_table = new int[64] {
            -30,-40,-40,-50,-50,-40,-40,-30,
            -30,-40,-40,-50,-50,-40,-40,-30,
            -30,-40,-40,-50,-50,-40,-40,-30,
            -30,-40,-40,-50,-50,-40,-40,-30,
            -20,-30,-30,-40,-40,-30,-30,-20,
            -10,-20,-20,-20,-20,-20,-20,-10,
            20, 20,  0,  0,  0,  0, 20, 20,
            20, 30, 10,  0,  0, 10, 30, 20
        };
        this->end_square_table = new int[64] {
            -50, -40, -30, -20, -20, -30, -40, -50,
            -30, -20, -10, 0, 0, -10, -20, -30,
            -30, -10, 20, 30, 30, 20, -10, -30,
            -30, -10, 30, 40, 40, 30, -10, -30,
            -30, -10, 30, 40, 40, 30, -10, -30,
            -30, -10, 20, 30, 30, 20, -10, -30,
            -30, -30, 0, 0, 0, 0, -30, -30,
            -50, -30, -30, -30, -30, -30, -30, -50
        };
    }

    // TODO: figure out why we can't get end_square_table from Piece.cpp
    int get_square_table_value(int x, int y, bool endgame) {
        if (endgame && end_square_table != NULL) {
            if (color == WHITE) return end_square_table[8 * (7 - y) + x];
            else return end_square_table[8 * y + x];
        } else {
            if (color == WHITE) return square_table[8 * (7 - y) + x];
            else return square_table[8 * y + x];
        }
    }
};

#endif
