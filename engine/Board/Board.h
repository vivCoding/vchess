#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 8

#include "../Util/Vector.h"
#include "../Util/Colors.h"
#include "../Pieces/Piece.h"
#include "../Pieces/Pawn.h"
#include "../Pieces/Rook.h"
#include "../Pieces/Knight.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/King.h"
#include "../Pieces/Queen.h"

#include <unordered_map>
using std::unordered_map;
using std::pair;

/*
 * Class that keeps track of a chessboard state
 * 
 * Initializes as a standard 8x8 chessboard with all pieces at standard positions
*/
class Board {
private:
    Piece* board[BOARD_SIZE][BOARD_SIZE];
    string REG_PIECES = "NK";
    string FAST_PIECES = "RBQ";

    // allow for quicker querying
    unordered_map<string, Piece*> white_pieces;
    unordered_map<string, Piece*> black_pieces;
    Piece* white_king;
    Piece* black_king;

    // used for memory management
    unordered_map<string, Piece*> deleted_pieces;

public:
    Board() {
        white_pieces.reserve(16);
        black_pieces.reserve(16);
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                board[x][y] = NULL;
            }
        }
        for (int y = 0; y < 8; y += 7) {
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
                for (int x = 0; x < 8; x++) {
                    if (color == WHITE) {
                        white_pieces.insert(pair<string, Piece*>(board[x][y]->get_id(), board[x][y]));
                    } else {
                        black_pieces.insert(pair<string, Piece*>(board[x][y]->get_id(), board[x][y]));
                    }
                }
                int i = y == 0 ? 1 : 6;
                for (int x = 0; x < 8; x++) {
                    board[x][i] = new Pawn(color, Vector(x, i));
                    if (color == WHITE) {
                        white_pieces.insert(pair<string, Piece*>(board[x][i]->get_id(), board[x][i]));
                    } else {
                        black_pieces.insert(pair<string, Piece*>(board[x][i]->get_id(), board[x][i]));
                    }
                }
            }
        }
        white_king = board[4][0];
        black_king = board[4][7];
    }

    /*
     * Returns &piece at given board position, or NULL if no piece exists at given position
    */
    Piece* get_piece(Vector v) { return get_piece(v.x, v.y); }
    Piece* get_piece(int x, int y) { return within_boundaries(x, y) ? board[x][y] : NULL; }

    /*
     * Replaces piece at board position with the given piece
     * Returns pointer to piece that was replaced, or NULL if no piece exists at given position
     * Note that even if pieces are overrided on board, you do not have to worry about managing memory for them, as the class handles it automatically
    */
    Piece* replace_piece(Vector v, Piece* piece) { return replace_piece(v.x, v.y, piece); }
    Piece* replace_piece(int x, int y, Piece* piece) {
        if (within_boundaries(x, y)) {
            Piece* replaced = board[x][y];
            board[x][y] = piece;
            if (piece != NULL) {
                piece->position.set(x, y);
                if (piece->color == WHITE) {
                    white_pieces.insert(pair<string, Piece*>(piece->get_id(), piece));
                    if (piece->type == KING) {
                        white_king = piece;
                    }
                } else {
                    black_pieces.insert(pair<string, Piece*>(piece->get_id(), piece));
                    if (piece->type == KING) {
                        black_king = piece;
                    }
                }
                deleted_pieces.erase(piece->get_id());
                if (replaced != NULL) {
                    if (replaced->color == WHITE) {
                        white_pieces.erase(replaced->get_id());
                    } else {
                        black_pieces.erase(replaced->get_id());
                    }
                    deleted_pieces.insert(pair<string, Piece*>(replaced->get_id(), replaced));
                }
            }
            return replaced;
        } else return NULL;
    }

    /*
     * Clears the board space at given position (i.e. setting it to NULL)
     * Returns the piece that previously occupied the space, or NULL if no such piece existed
     * Note that even if pieces are cleared on board, you do not have to worry about managing memory for them, as the class handles it automatically
    */
    Piece* clear_piece(Vector v) { return clear_piece(v.x, v.y); }
    Piece* clear_piece(int x, int y) {
        if (!within_boundaries(x, y)) return NULL;
        Piece* cleared = board[x][y];
        board[x][y] = NULL;
        return cleared;
    }

    Piece* get_king(Color color) {
        return color == WHITE ? white_king : black_king;
    }

    vector<Piece*> get_pieces(Color color) {
        vector<Piece*> pieces;
        auto start = color == WHITE ? white_pieces.begin() : black_pieces.begin();
        auto end = color == WHITE ? white_pieces.end() : black_pieces.end();
        for (auto p = start; p != end; p++) {
            pieces.push_back(p->second);
        }
        return pieces;
    }

    /*
     * Checks whether given position is a valid board position
    */
    bool within_boundaries(Vector v) { return within_boundaries(v.x, v.y); }
    bool within_boundaries(int x, int y) {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
    }

    ~Board() {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                delete board[x][y];
            }
        }
        for (auto p = deleted_pieces.begin(); p != deleted_pieces.end(); p++) {
            delete p->second;
        }
    }
};

#endif
