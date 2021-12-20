#include "../Util/Vector.h"
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
public:
    Piece board[8][8];

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
            cout << 7 - y + 1 << " | ";
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
};

#endif