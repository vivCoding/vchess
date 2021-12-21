#include "../Util/Vector.h"
#include "Colors.h"
#include "../Pieces/Piece.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/King.h"
#include "../Pieces/Queen.h"

#include <iostream>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    Piece board[8][8];
public:
    Board() {
        for (int i = 0; i < 8; i += 7) {
            Color color = i == 0 ? WHITE : BLACK;
            board[0][i] = Rook(color, Vector(0, i));
            board[1][i] = Knight(color, Vector(1, i));
            board[2][i] = Bishop(color, Vector(2, i));
            board[3][i] = Queen(color, Vector(3, i));
            board[4][i] = King(color, Vector(4, i));
            board[5][i] = Bishop(color, Vector(5, i));
            board[6][i] = Knight(color, Vector(6, i));
            board[7][i] = Rook(color, Vector(7, i));

            int y = i == 0 ? 1 : 6;
            for (int x = 0; x < 8; x++) {
                board[x][y] = Pawn(color, Vector(x, y));
            }
        }
    }

    void print_board() {
        int gap = 25;
        cout << "   ";
        for (int x = 0; x < gap; x++) {
            cout << "-";
        }
        cout << endl;
        for (int y = 7; y >= 0; y--) {
            cout << y + 1 << " | ";
            for (int x = 0; x < 8; x++) {
                cout << board[x][y].symbol;
                if (board[x][y].is_valid()) {
                    if (board[x][y].color == WHITE) {
                        cout << 'w';
                    } else cout << 'b';
                } else cout << " ";
                cout << " ";
            }
            cout << "|";
            cout << endl;
        }
        cout << "   ";
        for (int x = 0; x < gap; x++) {
            cout << "-";
        }
        cout << endl;
        cout << "    a  b  c  d  e  f  g  h" << endl;
    }

    bool move_piece(int px, int py, int nx, int ny) {
        Piece* piece = get_piece(px, py);
        Piece* other = get_piece(nx, ny);
        if (piece->is_valid_move(Vector(nx, ny)) && (piece->color != other->color || !other->is_valid())) {
            set_piece(nx, ny, piece);
            piece->set_invalid();
            return true;
        } else return false;
    }

    Piece* get_piece(int x, int y) {
        return &board[x][y];
    }

    void set_piece(int x, int y, Piece* piece) {
        board[x][y] = *piece;
        piece->position.x = x;
        piece->position.y = y;
    }
};

#endif