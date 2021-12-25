#ifndef ENGINE_H
#define ENGINE_h

#include "Board/Board.h"
#include "Util/Move.h"
#include <random>
#include <stack>
using namespace std;

/*
 * Represents a chess game, with functions to move chess pieces and uphold the rules of chess (e.g. check, checkmate, turns)
 * Can generate the "best" move for specific color
*/
class ChessEngine {
private:
    Board* board;
    Color turn;
    int level;

    // random stuff
    random_device rd;
    mt19937 rng;

    // Returns random integer from [n1, n2)
    int random_number(int n1, int n2) {
        uniform_int_distribution<int> uni(n1, n2 - 1);
        return uni(rng);
    }

    struct PossibleMove {
        Color color;
        Move root;
        Move move;
        int depth;
        bool maximizing;
        int score;
        bool visited = false;
    };

    /*
     * Checks if moving piece is valid (i.e, is valid piece move and does not result in check for given color or current turn color)
    */
    // TODO: perhaps do not have to check is_valid_move. Just check for check
    bool is_valid_move(Move move) { return is_valid_move(move, turn); }
    bool is_valid_move(Move move, Color color) { return is_valid_move(move.move_from, move.move_to, color); }
    bool is_valid_move(Vector from, Vector to) { return is_valid_move(from, to, turn); }
    bool is_valid_move(Vector from, Vector to, Color color) {
        Piece* p = board->get_piece(from);
        if (p != NULL && p->is_valid_move(to, board)) {
            // temporary move piece to new place and check if it results in check;
            Piece* old = board->replace_piece(to, p);
            board->clear_piece(from);
            bool in_check = is_check(color);
            // move piece back to original position
            board->replace_piece(to, old);
            board->replace_piece(from, p);
            return !in_check;
        }
        return false;
    }
    
    // TODO: use this function in other functions where applicable
    vector<Move> get_all_valid_moves() { return get_all_valid_moves(turn); }
    vector<Move> get_all_valid_moves(Color color) {
        vector<Move> possible_moves;
        for (int x = 0; x < BOARD_SIZE; x++) {
            for (int y = 0; y < BOARD_SIZE; y++) {
                Piece* p = board->get_piece(x, y);
                if (p != NULL && p->color == color) {
                    vector<Vector> valid_moves = p->get_valid_moves(board);
                    Vector from = p->position;
                    for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                        // temporary move piece to new place and check if it results in check;
                        Piece* old = board->replace_piece(*m, p);
                        board->clear_piece(from);
                        bool in_check = is_check(color);
                        // move piece back to original position
                        board->replace_piece(*m, old);
                        board->replace_piece(from, p);
                        if (!in_check) {
                            possible_moves.push_back(Move(from, *m, p, old));
                        }
                    }
                }
            }
        }
        return possible_moves;
    }

public:
    ChessEngine() : board(new Board()), turn(WHITE), level(0), rng(mt19937(rd())) {}
    ChessEngine(int level) : board(new Board()), turn(WHITE), level(level), rng(mt19937(rd())) {}

    /*
     * Move piece from (px, py) to (nx, y)
     * Returns true if it's a valid move, or false if the move is invalid or the move would result in a check for the current turn
    */
    bool move_piece(Move move) { return move_piece(move.move_from, move.move_to); }
    bool move_piece(int fx, int fy, int tx, int ty) { return move_piece(Vector(fx, fy), Vector(tx, ty)); }
    bool move_piece(Vector from, Vector to) {
        if (is_valid_move(from, to)) {
            Piece* old = board->replace_piece(to, board->get_piece(from));
            board->clear_piece(from);
            delete old;
            next_turn();
            return true;
        }
        return false;
    }

    /*
     * Checks if the given color (or current turn color if none is given) is in check
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
     * Checks if the given color (or current turn color if none is given) is in checkmate
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
                        vector<Vector> valid_moves = p->get_valid_moves(board);
                        for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                            // if we have at least one valid move, that means we can still prevent check
                            if (is_valid_move(p->position, *m)) {
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
     * Checks if the given color (or current turn color if none is given) is in stalement
    */
    bool is_stalemate() { return is_stalemate(turn); }
    bool is_stalemate(Color color) {
        // exact same logic as checkmate, except we're not in check
        if (!is_check(color)) {
            for (int x = 0; x < BOARD_SIZE; x++) {
                for (int y = 0; y < BOARD_SIZE; y++) {
                    Piece* p = board->get_piece(x, y);
                    if (p != NULL && p->color == color) {
                        vector<Vector> valid_moves = p->get_valid_moves(board);
                        for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                            // if we have at least one move, then it's not stalement.
                            if (is_valid_move(p->position, *m)) {
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
     * Randomnly generates the next (valid) move for the given color (or current turn color if none is given)
    */
    Move generate_random_move() { return generate_random_move(turn); }
    Move generate_random_move(Color color) {
        vector<Move> possible_moves = get_all_valid_moves(color);
        return possible_moves.at(random_number(0, possible_moves.size()));
    }

    /*
     * Calculates and returns the next move for the given color (or current turn color if none is given)
     * Utilizes the chess engine level. If level is low, the function takes less time to complete, but may result in worse moves,
     * while higher levels take more time to calculate and may result in better moves
    */

    Move generate_move() { return generate_move(turn); }
    Move generate_move(Color color) {
        // TODO: holy crap fix the runtime complexity
        if (level == 0) return generate_random_move(color);
        stack<PossibleMove> pm_stack;
        vector<PossibleMove> best_moves;
        int best_score = INT32_MIN;
        // first add all the first moves
        vector<Move> first_moves = get_all_valid_moves(color);
        for (auto m = first_moves.begin(); m != first_moves.end(); m++) {
            struct PossibleMove pm;
            pm.color = color;
            pm.root = *m;
            pm.move = *m;
            pm.depth = 1;
            pm.maximizing = true;
            pm.score = m->piece_replaced == NULL ? 0 : m->piece_replaced->value;
            pm_stack.push(pm);
        }
        // now do DFS
        int count = 0;
        while (pm_stack.size() != 0) {
            struct PossibleMove pm = pm_stack.top();
            Move move = pm.move;
            pm_stack.pop();
            if (pm.visited) {
                // undo move
                board->replace_piece(move.move_to, move.piece_replaced);
                board->replace_piece(move.move_from, move.piece_moved);
                count++;
            } else {
                // move piece to find new possible moves
                board->replace_piece(move.move_to, move.piece_moved);
                board->clear_piece(move.move_from);
                // mark it visited, and revisit later so we can undo the move done
                pm.visited = true;
                pm_stack.push(pm);
                if (pm.depth != level) {
                    // if we haven't reached all levels yet, then find all possible moves for next turn
                    Color other = other_color(pm.color);
                    vector<Move> possible_moves = get_all_valid_moves(other);
                    // get the next best moves that will maximize score (or minimize if enemy's color)
                    // getting only the next best moves considerably reduces the number of moves we check
                    vector<PossibleMove> next_best_moves;
                    int next_best_score = pm.score;
                    int sign = pm.maximizing ? -1 : 1;
                    for (auto m = possible_moves.begin(); m != possible_moves.end(); m++) {
                        int updated_score = pm.score + sign * (m->piece_replaced == NULL ? 0 : m->piece_replaced->value);
                        // temporary move piece to see if it leads to stalemate/checkmate
                        board->replace_piece(m->move_to, m->piece_moved);
                        board->clear_piece(m->move_from);
                        if (is_stalemate(other_color())) {
                            updated_score -= INT16_MAX / 64;
                        } else if (is_stalemate(color)) {
                            updated_score += INT16_MAX / 64;
                        } else if (is_checkmate(color)) {
                            updated_score -= INT16_MAX;
                        } else if (is_checkmate(other_color())) {
                            updated_score += INT16_MAX;
                        }
                        // move piece back
                        board->replace_piece(m->move_to, m->piece_replaced);
                        board->replace_piece(m->move_from, m->piece_moved);
                        // check if this can be considered as a next best move
                        if (abs(updated_score) >= abs(next_best_score)) {
                            struct PossibleMove best_move;
                            best_move.color = other;
                            best_move.root = pm.root;
                            best_move.depth = pm.depth + 1;
                            best_move.maximizing = !pm.maximizing;
                            best_move.score = pm.score;
                            best_move.move = *m;
                            best_move.score = updated_score;
                            if (abs(updated_score) > abs(next_best_score)) {
                                next_best_moves.clear();
                            }
                            next_best_moves.push_back(best_move);
                            next_best_score = updated_score;
                        }
                    }
                    // all the next best moves have the same score, and thus must be checked. Add to stack
                    for (auto nm = next_best_moves.begin(); nm != next_best_moves.end(); nm++) {
                        pm_stack.push(*nm);
                    }
                } else {
                    // we've reached the max depth. Update best move accordingly
                    if (pm.score > best_score) {
                        best_moves.clear();
                        best_moves.push_back(pm);
                        best_score = pm.score;
                    } else if (pm.score == best_score) {
                        best_moves.push_back(pm);
                    }
                }
            }
        }
        struct PossibleMove best_move = best_moves.at(random_number(0, best_moves.size()));
        // cout << "total visited: " << count << endl;
        // cout << "best move: " << best_move.root.as_string() << endl;
        // cout << "score: " << best_score << endl;
        // cout << "predicted move: " << best_move.move.as_string() << endl;
        return best_move.root;
    }

    // Swap turn to play next move
    void next_turn() { turn = turn == WHITE ? BLACK : WHITE; }
    // Get the current turn's color
    Color get_turn() { return turn; }
    // Get the current enemy's color
    Color other_color() { return turn == WHITE ? BLACK : WHITE; }
    // Get the current enemy's color
    Color other_color(Color color) { return color == WHITE ? BLACK : WHITE; }

    /*
     * Resets chess game and board state 
    */
    void reset_game() { reset_game(level); }
    void reset_game(int level) {
        // perhaps there's a better way to do this, but im lazy rn lol
        delete board;
        board = new Board();
        turn = WHITE;
        this->level = level;
    }

    // Returns current chess engine level
    int get_level() { return level; }

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
