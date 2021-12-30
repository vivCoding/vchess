#include "Game.h"

bool ChessGame::will_check(Move m, Color color) {
    if (board->within_boundaries(m.move_from) && board->within_boundaries(m.move_to)) {
        move_valid(m);
        bool in_check = is_check(color);
        undo_move();
        return in_check;
    }
    return false;
}

ChessGame::ChessGame() : turn(WHITE), board(new Board()) {}

bool ChessGame::move_piece(int fx, int fy, int tx, int ty) { return move_piece(Vector(fx, fy), Vector(tx, ty)); }
bool ChessGame::move_piece(Vector from, Vector to) { return move_piece(Move(from, to, board->get_piece(from), board->get_piece(to))); }
bool ChessGame::move_piece(Move m) {
    if (is_valid_move(m)) {
        move_valid(m);
        return true;
    }
    return false;
}

bool ChessGame::is_valid_move(Move m) {
    if (
        m.piece_moved != NULL &&
        m.piece_moved->color == turn &&
        m.piece_moved->is_valid_move(m.move_to, board) &&
        !will_check(m, turn)
    ) {
        return true;
    }
    return false;
}

void ChessGame::move_valid(Move m) {
    Move* to_store = new Move(m.move_from, m.move_to, m.piece_moved, m.piece_replaced);
    board->replace_piece(m.move_to, m.piece_moved);
    board->clear_piece(m.move_from);
    move_history.push_back(to_store);
}

vector<Move> ChessGame::get_all_valid_moves() { return get_all_valid_moves(turn); }
vector<Move> ChessGame::get_all_valid_moves(Color color) {
    vector<Move> possible_moves;
    vector<Piece*> pieces = board->get_pieces(color);
    for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
        Piece* p = *pa;
        vector<Move> valid_moves = p->get_valid_moves(board);
        for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
            if (!will_check(*m, color)) {
                possible_moves.push_back(*m);
            }
        }
    }
    return possible_moves;
}

bool ChessGame::is_check() { return is_check(turn); }
bool ChessGame::is_check(Color color) {
    Vector king_position = board->get_king(color)->position;
    vector<Piece*> pieces = board->get_pieces(get_other_color(color));
    for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
        vector<Move> valid_moves = (*pa)->get_valid_moves(board);
        for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
            if (m->move_to.equal_to(king_position)) {
                return true;
            }
        }
    }
    return false;
}

bool ChessGame::is_checkmate() { return is_checkmate(turn); }
bool ChessGame::is_checkmate(Color color) {
    if (is_check(color)) {
        // check if we have a piece that can prevent check
        // this is faster than finding all possible moves first, since here we could return right away
        vector<Piece*> pieces = board->get_pieces(color);
        for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
            vector<Move> valid_moves = (*pa)->get_valid_moves(board);
            for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                // if we have at least one valid move, that means we can still prevent check
                if (!will_check(*m, color)) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool ChessGame::is_stalemate() { return is_stalemate(turn); }
bool ChessGame::is_stalemate(Color color) {
    if (!is_check(color)) {
        vector<Piece*> pieces = board->get_pieces(color);
        for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
            vector<Move> valid_moves = (*pa)->get_valid_moves(board);
            // if we have at least one valid move, then we're not in stalemate
            if (valid_moves.size() != 0) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void ChessGame::undo_move() {
    if (move_history.empty()) return;
    Move* m = move_history.back();
    board->replace_piece(m->move_to, m->piece_replaced);
    board->replace_piece(m->move_from, m->piece_moved);
    delete m;
    move_history.pop_back();
}

Move* ChessGame::peek_history(int index) {
    if (index < 0 || index >= (int) move_history.size()) return NULL;
    return move_history.at(index);
}

Move* ChessGame::peek_history_back() { return peek_history(move_history.size() - 1); }

int ChessGame::move_history_size() { return move_history.size(); }

void ChessGame::reset_game() {
    // perhaps there's a better way to do this, but im lazy rn lol
    delete board;
    board = new Board();
    turn = WHITE;
    while (move_history.size()) {
        delete move_history.back();
        move_history.pop_back();
    }
}

void ChessGame::next_turn() { turn = turn == WHITE ? BLACK : WHITE; }
Color ChessGame::get_turn() { return turn; }

ChessGame::~ChessGame() {
    delete board;
}
