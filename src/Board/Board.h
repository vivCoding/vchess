#ifndef BOARD_H
#define BOARD_H

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

class Board {
private:
    Piece* board[8][8];
    string REG_PIECES = "NK";
    string FAST_PIECES = "RBQ";
public:
    Board() {
        for (int y = 0; y < 8; y++) {
            Color color = y < 4 ? WHITE : BLACK;
            if (y == 0 || y == 7) {
                board[0][y] = new Rook(color, Vector(0, y));
                board[1][y] = new Knight(color, Vector(1, y));
                board[2][y] = new Bishop(color, Vector(2, y));
                board[3][y] = new Queen(color, Vector(3, y));
                board[4][y] = new King(color, Vector(4, y));
                board[5][y] = new Bishop(color, Vector(5, y));
                board[6][y] = new Knight(color, Vector(6, y));
                board[7][y] = new Rook(color, Vector(7, y));
            } else if (y == 1 || y == 6) {
                for (int x = 0; x < 8; x++) {
                    board[x][y] = new Pawn(color, Vector(x, y));
                }
            } else {
                for (int x = 0; x < 8; x++) {
                    board[x][y] = new Piece();
                }
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
                if (board[x][y]->is_valid) {
                    cout << ((char) board[x][y]->type);
                    if (board[x][y]->color == WHITE) {
                        cout << 'w';
                    } else cout << 'b';
                } else cout << ". ";
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
        if (piece->is_valid && piece->is_valid_move(Vector(nx, ny), this)) {
            set_piece(nx, ny, piece);
            board[px][py] = new Piece();
            return true;
        } else return false;
    }

    Piece* get_piece(int x, int y) {
        return board[x][y];
    }

    Piece* get_piece(Vector v) {
        return board[v.x][v.y];
    }

    void set_piece(int x, int y, Piece* piece) {
        delete board[x][y];
        board[x][y] = piece;
        piece->position.x = x;
        piece->position.y = y;
    }

    ~Board() {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                delete board[x][y];
            }
        }
    }
};

#endif
