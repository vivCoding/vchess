#ifndef ENGINE_H
#define ENGINE_h

#include "Board/Board.h"
#include "Util/Move.h"
#include <random>
using namespace std;

class ChessEngine {
private:
    Board* board;
    Color turn;
    Color starting_turn;
    random_device rd;
public:
    ChessEngine() : board(new Board()), turn(WHITE), starting_turn(WHITE) {};
    ChessEngine(Color starting_color) : board(new Board()), turn(starting_color), starting_turn(starting_color) {};

    /*
     * Resets chess game and board state 
    */
    void reset_game() { reset_game(starting_turn); }
    void reset_game(Color starting_color) {
        // perhaps there's a better way to do this, but im lazy rn lol
        delete board;
        board = new Board();
        turn = WHITE;
    }

    // Swap turn to play next move
    void next_turn() { turn = turn == WHITE ? BLACK : WHITE; }
    // Get the current turn's color
    Color get_turn() { return turn; }
    // Get the current enemy's color
    Color other_color() { return turn == WHITE ? BLACK : WHITE; }

    /*
     * Move piece from (px, py) to (nx, y)
     * Returns true if it's a valid move, or false if the move is invalid or the move would result in a check for the current turn
    */
    bool move_piece(Move move) {
        return move_piece(move.move_from.x, move.move_from.y, move.move_to.x, move.move_to.y);
    }
    bool move_piece(int px, int py, int nx, int ny) {
        if (board->within_boundaries(px, py) && board->within_boundaries(nx, ny)) {
            Piece* p = board->get_piece(px, py);
            if (p != NULL && p->is_valid_move(Vector(nx, ny), board)) {
                Piece* old = board->replace_piece(nx, ny, p);
                board->clear_piece(px, py);
                if (is_check()) {
                    board->replace_piece(px, py, p);
                    board->replace_piece(nx, ny, old);
                    return false;
                }
                next_turn();
                delete old;
                return true;
            }
        }
        return false;
    }

    /*
     * Returns true if the given color (or current turn color if none is given) is in check
    */
    bool is_check() { return is_check(turn); }
    bool is_check(Color color) {
        Vector king_position = board->get_king(color)->position;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                Piece* p = board->get_piece(x, y);
                if (p != NULL && p->color != color) {
                    vector<Vector> valid_moves = p->get_valid_moves(board);
                    for (auto p = valid_moves.begin(); p != valid_moves.end(); p++) {
                        if (p->equal_to(king_position)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    /*
     * Returns true if the given color (or current turn color if none is given) is in checkmate
    */
    bool is_checkmate() { return is_checkmate(turn); }
    bool is_checkmate(Color color) {
        // RIP runtime complexity = 64 * color_piece_valid_moves * 64 * enemy_piece_valid_moves
        if (is_check(color)) {
            // check if there's a piece out there that can prevent check
            for (int x = 0; x < BOARD_SIZE; x++) {
                for (int y = 0; y < BOARD_SIZE; y++) {
                    Piece* p = board->get_piece(x, y);
                    if (p != NULL && p->color == color && p->type) {
                        Vector p_position = p->position;
                        vector<Vector> valid_moves = p->get_valid_moves(board);
                        for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                            // temporary move piece to location, and check if it still results in "check"
                            Piece* old = board->replace_piece(m->x, m->y, p);
                            board->clear_piece(p_position.x, p_position.y);
                            bool still_check = is_check(color);
                            // move piece back to original position
                            board->replace_piece(m->x, m->y, old);
                            board->replace_piece(p_position.x, p_position.y, p);
                            // if there wasn't a check, that means checkmate can be prevented
                            if (!still_check) {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        }
        return false;
    }

    /*
     * Calculates and generates the next move for the given color (or current turn color if none is given)
    */
    Move generate_move() { return generate_move(turn); }
    Move generate_move(Color color) {
        vector<Move> possible_moves;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                Piece* p = board->get_piece(x, y);
                if (p != NULL && p->color == color) {
                    Vector p_position = p->position;
                    vector<Vector> valid_moves = p->get_valid_moves(board);
                    for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                        // temporary move piece to location, and check if it still results in "check"
                        Piece* old = board->replace_piece(m->x, m->y, p);
                        board->clear_piece(p_position.x, p_position.y);
                        bool still_check = is_check(color);
                        // move piece back to original position
                        board->replace_piece(m->x, m->y, old);
                        board->replace_piece(p_position.x, p_position.y, p);
                        // if there wasn't a check, that means checkmate can be prevented
                        if (!still_check) {
                            possible_moves.push_back(Move(p_position, *m));
                        }
                    }
                }
            }
        }
        mt19937 rng(rd());
        uniform_int_distribution<int> uni(0, possible_moves.size());
        return possible_moves.at(uni(rng));
    }

    /*
     * Prints board state and the current turn
    */
    void print_board() {
        cout << endl;
        board->print_board();
        if (turn == WHITE) cout << "WHITE TURN";
        else cout << "BLACK TURN";
        if (is_checkmate()) cout << ": CHECKMATE. GAME OVER!";
        else if (is_check()) cout << ": CHECK!";
        cout << endl;
    }

    ~ChessEngine() {
        delete &board;
    }
};

#endif
