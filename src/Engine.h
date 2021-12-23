#ifndef ENGINE_H
#define ENGINE_h

#include "Board/Board.h"

class ChessEngine {
private:
    Board board;
    Color turn;
    Color starting_turn;
    Vector white_king;
    Vector black_king;
public:
    ChessEngine() : turn(WHITE), starting_turn(WHITE) {};
    ChessEngine(Color starting_color) : turn(starting_color), starting_turn(starting_color) {};

    void reset_game() {
        reset_game(starting_turn);
    }

    void reset_game(Color starting_color) {
        delete &board;
        board = Board();
        turn = WHITE;
    }

    void next_turn() { turn = turn == WHITE ? BLACK : WHITE; }
    Color other_color() { return turn == WHITE ? BLACK : WHITE; }

    bool move_piece(int px, int py, int nx, int ny) {
        if (board.within_boundaries(px, py) && board.within_boundaries(nx, ny)) {
            Piece* p = board.get_piece(px, py);
            if (p != NULL && p->is_valid_move(Vector(nx, ny), &board)) {
                Piece* old = board.replace_piece(nx, ny, p);
                board.clear_piece(px, py);
                if (is_check()) {
                    board.replace_piece(px, py, p);
                    board.replace_piece(nx, ny, old);
                    return false;
                }
                next_turn();
                delete old;
                return true;
            }
        }
        return false;
    }

    bool is_check() {
        return is_check(turn);
    }
    bool is_check(Color color) {
        Vector king_position = board.get_king(color)->position;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                Piece* p = board.get_piece(x, y);
                if (p != NULL && p->color != color) {
                    vector<Vector> valid_moves = p->get_valid_moves(&board);
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

    bool is_checkmate() { return is_checkmate(turn); }
    bool is_checkmate(Color color) {
        // RIP runtime complexity = 64 * color_piece_valid_moves * 64 * enemy_piece_valid_moves
        if (is_check(color)) {
            // check if there's a piece out there that can prevent check
            for (int x = 0; x < BOARD_SIZE; x++) {
                for (int y = 0; y < BOARD_SIZE; y++) {
                    Piece* p = board.get_piece(x, y);
                    if (p != NULL && p->color == color && p->type) {
                        Vector p_position = p->position;
                        vector<Vector> valid_moves = p->get_valid_moves(&board);
                        for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                            // temp move piece to location, and check if it still results in "check"
                            Piece* old = board.replace_piece(m->x, m->y, p);
                            board.clear_piece(p_position.x, p_position.y);
                            bool still_check = is_check(color);
                            // move piece back to original position
                            board.replace_piece(m->x, m->y, old);
                            board.replace_piece(p_position.x, p_position.y, p);
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

    bool generate_move() { return generate_move(turn); }
    bool generate_move(Color color) {
        return false;
    }

    void print_board() {
        cout << endl;
        board.print_board();
        if (turn == WHITE) {
            cout << "WHITE TURN";
        } else cout << "BLACK TURN";
        if (is_checkmate()) {
            cout << ": CHECKMATE. GAME OVER!";
        } else if (is_check()) {
            cout << ": CHECK!";
        }
        cout << endl;
    }

    ~ChessEngine() {
        delete &board;
    }
};

#endif
