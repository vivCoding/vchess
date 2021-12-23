/*
 * Board
 * 
 * Keeps track of a chessboard state
*/

#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 8

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
    Piece* board[BOARD_SIZE][BOARD_SIZE];
    string REG_PIECES = "NK";
    string FAST_PIECES = "RBQ";
    Piece* white_king;
    Piece* black_king;
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
                    // board[x][y] = new Piece();
                    board[x][y] = NULL;
                }
            }
        }
        white_king = board[4][0];
        black_king = board[4][7];
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
                if (board[x][y] != NULL) {
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

    Piece* get_piece(int x, int y) {
        if (within_boundaries(x, y)) {
            return board[x][y];
        } else return NULL;
    }

    Piece* get_piece(Vector v) {
        return board[v.x][v.y];
    }

    /*
     * Replaces piece at board position with the given piece
     * Returns &piece that was replaced, or NULL if no piece exists at 
    */
    Piece* replace_piece(int x, int y, Piece* piece) {
        if (within_boundaries(x, y)) {
            Piece* replaced = board[x][y];
            board[x][y] = piece;
            if (piece != NULL) {
                piece->position.set(x, y);
                if (piece->type == KING) {
                    if (piece->color == WHITE) {
                        white_king = piece;
                    } else black_king = piece;
                }
            }
            return replaced;
        } else return NULL;
    }
    Piece* replace_piece(Vector v, Piece* piece) {
        return replace_piece(v.x, v.y, piece);
    }

    /*
     * Clears the board space at given position (i.e. setting it to NULL)
     * Returns the piece that previously occupied the space, or NULL if no such piece existed
    */
    Piece* clear_piece(int x, int y) {
        if (!within_boundaries(x, y)) return NULL;
        Piece* cleared = board[x][y];
        board[x][y] = NULL;
        return cleared;
    }
    Piece* clear_piece(Vector v) {
        return clear_piece(v.x, v.y);
    }

    Piece* get_king(Color color) {
        return color == WHITE ? white_king : black_king;
    }

    bool within_boundaries(int x, int y) {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
    }

    bool within_boundaries(Vector v) {
        return within_boundaries(v.x, v.y);
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
