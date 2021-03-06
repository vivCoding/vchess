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

vector<Move> ChessGame::get_moves(Vector v) { return get_moves(board->get_piece(v)); }
vector<Move> ChessGame::get_moves(int x, int y) { return get_moves(board->get_piece(x, y)); }
vector<Move> ChessGame::get_moves(Piece* piece) {
    vector<Move> moves;
    if (piece != NULL) {
        vector<Vector> moveset = piece->get_moveset();
        int moveset_size = moveset.size();
        Color color = piece->color;
        PieceType type = piece->type;
        Vector position = piece->position;

        if (type == KNIGHT) {
            for (int i = 0; i < moveset_size; i++) {
                Vector v = position.add(moveset.at(i));
                Piece* p = board->get_piece(v);
                if (board->within_boundaries(v) && (p == NULL || p->color != color)) {
                    moves.push_back(Move(position, v, piece, p));
                }
            }
        } else if (type == BISHOP || type == ROOK || type == QUEEN) {
            for (int i = 0; i < moveset_size; i++) {
                for (int j = 1; j < BOARD_SIZE; j++) {
                    Vector v = position.add(moveset.at(i).scale(j));
                    Piece* p = board->get_piece(v);
                    if (!board->within_boundaries(v) || (p != NULL && p->color == color)) {
                        break;
                    } else {
                        moves.push_back(Move(position, v, piece, p));
                        if (p != NULL) break;
                    }
                }
            }
        } else if (type == PAWN) {
            int sign = color == WHITE ? 1 : -1;
            // check capture moves
            for (int i = 2; i < 4; i++) {
                Vector v = position.add(moveset.at(i).scale(sign));
                if (board->within_boundaries(v)) {
                    Piece* p = board->get_piece(v);
                    if (p != NULL && p->color != color) {
                        moves.push_back(Move(position, v, piece, p, v.y == 7 || v.y == 0 ? PAWN_PROMOTION : CAPTURE));
                    }
                }
            }
            // check move forward 1
            Vector forward1 = position.add(moveset.at(0).scale(sign));
            if (board->within_boundaries(forward1) && board->get_piece(forward1) == NULL) {
                moves.push_back(Move(position, forward1, piece, NULL, forward1.y == 7 || forward1.y == 0 ? PAWN_PROMOTION : MOVE));
            }
            // check move forward 2
            Vector forward2 = Vector(position.x, color == WHITE ? 3 : 4);
            if (
                ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
                && (board->get_piece(forward1) == NULL)
                && (board->get_piece(forward2) == NULL)
            ) {
                moves.push_back(Move(position, forward2, piece, NULL));
            }
        } else if (type == KING) {
            for (int i = 0; i < moveset_size; i++) {
                Vector v = position.add(moveset.at(i));
                Piece* p = board->get_piece(v);
                if (board->within_boundaries(v) && (p == NULL || p->color != color)) {
                    moves.push_back(Move(position, v, piece, p));
                }
            }

            // castling
            if (!piece->has_moved) {
                int row = color == WHITE ? 0 : 7;
                for (int x = 0; x <= 7; x += 7) {
                    Piece* rook = board->get_piece(x, row);
                    if (rook != NULL && !rook->has_moved) {
                        bool bad = false;
                        int step = x == 7 ? 1 : -1;
                        for (int i = position.x + step; i != x; i += step) {
                            // make sure there are no pieces between
                            if (board->get_piece(i, row) != NULL) {
                                bad = true;
                                break;
                            }
                        }
                        if (!bad) {
                            for (int i = position.x + step; i != x; i += step) {
                                // make sure there are no spaces are interfered with an enemy piece
                                // do a separate loop because calling will_check() can be expensive
                                if (will_check(Move(position, Vector(i, row), piece, NULL), color)) {
                                    bad = true;
                                    break;
                                }
                            }
                        }
                        if (!bad) {
                            moves.push_back(Move(position, Vector(x == 0 ? 2 : 6, row), piece, NULL, x == 0 ? QUEENSIDE_CASTLE : CASTLE));
                        }
                    }
                }
            }
        }
    }
    return moves;
}

ChessGame::ChessGame() : turn(WHITE), pieces_to_promote({}), board(new Board()) {}

bool ChessGame::move_piece(int fx, int fy, int tx, int ty) { return move_piece(Vector(fx, fy), Vector(tx, ty)); }
bool ChessGame::move_piece(Vector from, Vector to) { return move_piece(Move(from, to, board->get_piece(from), board->get_piece(to))); }
bool ChessGame::move_piece(Move m) {
    if (is_valid_move(m)) {
        // correctly update move type
        if (m.piece_replaced != NULL) m.type = CAPTURE;
        else if (m.piece_moved->type == KING && m.move_from.x == 4) {
            if (m.move_to.x == 6) {
                m.type = CASTLE;
            } else if (m.move_to.x == 2) {
                m.type = QUEENSIDE_CASTLE;
            }
        }
        if (m.piece_moved->type == PAWN && (m.move_to.y == 0 || m.move_to.y == 7)) {
            m.type = PAWN_PROMOTION;
        }
        move_valid(m);
        return true;
    }
    return false;
}

void ChessGame::move_valid(Move m) {
    board->replace_piece(m.move_to, m.piece_moved);
    board->clear_piece(m.move_from);
    if (m.type == CASTLE || m.type == QUEENSIDE_CASTLE) {
        Vector rook_pos = Vector(m.move_to.x == 6 ? 7 : 0, m.move_from.y);
        Piece* rook = board->get_piece(rook_pos);
        board->replace_piece(rook_pos.x == 7 ? 5 : 3, rook_pos.y, rook);
        board->clear_piece(rook_pos);
        rook->has_moved = true;
    }
    Move* to_store = new Move(m.move_from, m.move_to, m.piece_moved, m.piece_replaced, m.type);
    if (m.type == PAWN_PROMOTION) {
        pieces_to_promote.insert(pair<string, Move*>(m.piece_moved->get_id(), to_store));
    }
    move_history.push_back(to_store);
    m.piece_moved->has_moved = true;
}

bool ChessGame::is_valid_move(Move m) { return is_valid_move(m, turn); }
bool ChessGame::is_valid_move(Move m, Color color) {
    if (
        board->within_boundaries(m.move_from) && board->within_boundaries(m.move_to) &&
        m.piece_moved != NULL && m.piece_moved->color == color && m.move_from.equal_to(m.piece_moved->position)
    ) {
        PieceType type = m.piece_moved->type;
        vector<Vector> moveset = m.piece_moved->get_moveset();
        int moveset_size = moveset.size();
        Vector position = m.move_from;
        Vector next_position = m.move_to;

        if (type == KNIGHT) {
            for (int i = 0; i < moveset_size; i++) {
                Vector v = position.add(moveset.at(i));
                Piece* p = board->get_piece(v);
                if (m.move_to.equal_to(v) && (p == NULL || p->color != color)) {
                    return !will_check(m, color);
                }
            }
        } else if (type == BISHOP || type == ROOK || type == QUEEN) {
            for (int i = 0; i < moveset_size; i++) {
                for (int j = 1; j < BOARD_SIZE; j++) {
                    Vector v = position.add(moveset.at(i).scale(j));
                    Piece* p = board->get_piece(v);
                    if (!board->within_boundaries(v) || (p != NULL && (!next_position.equal_to(v) || p->color == color))) {
                        break;
                    } else if (next_position.equal_to(v) && (p == NULL || (p != NULL && p->color != color))) {
                        return !will_check(m, color);
                    }
                }
            }
        } else if (type == PAWN) {
            int sign = color == WHITE ? 1 : -1;
            // check capture moves
            for (int i = 2; i < 4; i++) {
                Vector v = position.add(moveset.at(i).scale(sign));
                Piece* p = board->get_piece(v);
                if (next_position.equal_to(v) && p != NULL && p->color != color) {
                    return !will_check(m, color);
                }
            }
            return (
                // check move forward 1
                (next_position.equal_to(position.add(moveset.at(0).scale(sign))))
                && (board->get_piece(next_position) == NULL)
                && !will_check(m, color)
            ) || (
                // check move forward 2
                (next_position.equal_to(position.add(moveset.at(1).scale(sign))))
                && ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
                && (board->get_piece(position.x, color == WHITE ? 2 : 5) == NULL)
                && (board->get_piece(position.x, color == WHITE ? 3 : 4) == NULL)
                && !will_check(m, color)
            );
        } else if (type == KING) {
            for (int i = 0; i < moveset_size; i++) {
                Vector v = position.add(moveset.at(i));
                Piece* p = board->get_piece(v);
                if (m.move_to.equal_to(v) && (p == NULL || p->color != color)) {
                    return !will_check(m, color);
                }
            }
            // castling
            int row = color == WHITE ? 0 : 7;
            int next_x = next_position.x;
            if (!m.piece_moved->has_moved && (next_x == 6 || next_x == 2)) {
                int rook_x = next_x == 6 ? 7 : 0;
                Piece* rook = board->get_piece(rook_x, row);
                // if it hasn't moved, then it's guaranteed to be a rook
                if (rook != NULL && !rook->has_moved && !is_check(color)) {
                    int step = rook_x == 7 ? 1 : -1;
                    // make sure there are no pieces between
                    for (int i = position.x + step; i != rook_x; i += step) {
                        if (board->get_piece(i, row) != NULL) return false;
                    }
                    // make sure there are no spaces are interfered with an enemy piece
                    // in a separate loop because will_check can be expensive
                    for (int i = position.x + step; i != rook_x; i += step) {
                        if (will_check(Move(position, Vector(i, row), m.piece_moved, NULL), color)) return false;
                    }
                    return true;
                } else return false;
            } else return false;
        }
    }
    return false;
}

vector<Move> ChessGame::get_valid_moves(Vector v) { return get_valid_moves(v.x, v.y); }
vector<Move> ChessGame::get_valid_moves(int x, int y) {
    Piece* piece = board->get_piece(x, y);
    vector<Move> valid_moves;
    if (piece != NULL) {
        vector<Vector> moveset = piece->get_moveset();
        int moveset_size = moveset.size();
        Color color = piece->color;
        PieceType type = piece->type;
        Vector position = piece->position;

        if (type == KNIGHT) {
            for (int i = 0; i < moveset_size; i++) {
                Vector v = position.add(moveset.at(i));
                Piece* p = board->get_piece(v);
                if (board->within_boundaries(v) && (p == NULL || p->color != color)) {
                    Move m = Move(position, v, piece, p);
                    if (!will_check(m, color)) {
                        valid_moves.push_back(m);
                    }
                }
            }
        } else if (type == BISHOP || type == ROOK || type == QUEEN) {
            for (int i = 0; i < moveset_size; i++) {
                for (int j = 1; j < BOARD_SIZE; j++) {
                    Vector v = position.add(moveset.at(i).scale(j));
                    Piece* p = board->get_piece(v);
                    if (!board->within_boundaries(v) || (p != NULL && p->color == color)) {
                        break;
                    } else {
                        Move m = Move(position, v, piece, p);
                        if (!will_check(m, color)) valid_moves.push_back(m);
                        if (p != NULL) break;
                    }
                }
            }
        } else if (type == PAWN) {
            int sign = color == WHITE ? 1 : -1;
            // check capture moves
            for (int i = 2; i < 4; i++) {
                Vector v = position.add(moveset.at(i).scale(sign));
                if (board->within_boundaries(v)) {
                    Piece* p = board->get_piece(v);
                    if (p != NULL && p->color != color) {
                        Move m = Move(position, v, piece, p, v.y == 7 || v.y == 0 ? PAWN_PROMOTION : CAPTURE);
                        if (!will_check(m, color)) valid_moves.push_back(m);
                    }
                }
            }
            // check move forward 1
            Vector forward1 = position.add(moveset.at(0).scale(sign));
            Move forward1_move = Move(position, forward1, piece, NULL, forward1.y == 7 || forward1.y == 0 ? PAWN_PROMOTION : MOVE);
            if (board->within_boundaries(forward1) && board->get_piece(forward1) == NULL && !will_check(forward1_move, color)) {
                valid_moves.push_back(forward1_move);
            }
            // check move forward 2
            Vector forward2 = Vector(position.x, color == WHITE ? 3 : 4);
            Move forward2_move = Move(position, forward2, piece, NULL);
            if (
                ((color == WHITE && position.y == 1) || (color == BLACK && position.y == 6))
                && (board->get_piece(forward1) == NULL)
                && (board->get_piece(forward2) == NULL)
                && !will_check(forward2_move, color)
            ) {
                valid_moves.push_back(forward2_move);
            }
        } else if (type == KING) {
            for (int i = 0; i < moveset_size; i++) {
                Vector v = position.add(moveset.at(i));
                Piece* p = board->get_piece(v);
                if (board->within_boundaries(v) && (p == NULL || p->color != color)) {
                    Move m = Move(position, v, piece, p);
                    if (!will_check(m, color)) {
                        valid_moves.push_back(m);
                    }
                }
            }

            // castling
            if (!piece->has_moved) {
                int row = color == WHITE ? 0 : 7;
                for (int x = 0; x <= 7; x += 7) {
                    Piece* rook = board->get_piece(x, row);
                    if (rook != NULL && !rook->has_moved && !is_check(color)) {
                        bool bad = false;
                        int step = x == 7 ? 1 : -1;
                        for (int i = position.x + step; i != x; i += step) {
                            Vector v = Vector(i, row);
                            Move m = Move(position, v, piece, NULL);
                            // make sure there are no pieces between
                            if (board->get_piece(v) != NULL || will_check(m, color)) {
                                bad = true;
                                break;
                            }
                        }
                        if (!bad) {
                            // now check if there are spaces where enemy pieces interfere
                            // we do a separate loop because calling will_check is a bit expensive
                            for (int i = position.x + step; i != x; i+= step) {
                                Vector v = Vector(i, row);
                                Move m = Move(position, v, piece, NULL);
                                if (will_check(m, color)) {
                                    bad = true;
                                    break;
                                }
                            }
                        }
                        if (!bad) {
                            valid_moves.push_back(Move(position, Vector(x == 0 ? 2 : 6, row), piece, NULL, x == 0 ? QUEENSIDE_CASTLE : CASTLE));
                        }
                    }
                }
            }
        }
    }
    return valid_moves;
}

vector<Move> ChessGame::get_all_valid_moves() { return get_all_valid_moves(turn); }
vector<Move> ChessGame::get_all_valid_moves(Color color) {
    vector<Move> valid_moves;
    vector<Piece*> pieces = board->get_pieces(color);
    for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
        vector<Move> moves = get_valid_moves((*pa)->position);
        for (auto m = moves.begin(); m != moves.end(); m++) {
            valid_moves.push_back(*m);
        }
    }
    return valid_moves;
}

bool ChessGame::is_check() { return is_check(turn); }
bool ChessGame::is_check(Color color) {
    Vector king_position = board->get_king(color)->position;
    vector<Piece*> pieces = board->get_pieces(get_other_color(color));
    // TODO: maybe consider sorting moves beforehand?
    for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
        vector<Move> valid_moves = get_moves(*pa);
        for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
            if (m->type == CASTLE || m->type == QUEENSIDE_CASTLE) continue;
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
        // check if we have a piece that can prevent check, i.e. at least one valid move
        // this is faster than finding all possible moves first, since here we could return right away
        vector<Piece*> pieces = board->get_pieces(color);
        for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
            vector<Move> valid_moves = get_moves(*pa);
            for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                if (m->type == CASTLE || m->type == QUEENSIDE_CASTLE) continue;
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
    // exact same logic is checkmate, except we're not in check
    if (!is_check(color)) {
        vector<Piece*> pieces = board->get_pieces(color);
        for (auto pa = pieces.begin(); pa != pieces.end(); pa++) {
            vector<Move> valid_moves = get_moves(*pa);
            // if we have at least one valid move, then we're not in stalemate
            for (auto m = valid_moves.begin(); m != valid_moves.end(); m++) {
                if (!will_check(*m, color)) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool ChessGame::pawn_promotion_available(int x, int y) { return pawn_promotion_available(board->get_piece(x, y)->get_id()); }
bool ChessGame::pawn_promotion_available(Vector v) { return pawn_promotion_available(board->get_piece(v)->get_id()); }
bool ChessGame::pawn_promotion_available(string piece_id) {
    return pieces_to_promote.find(piece_id) != pieces_to_promote.end();
}

bool ChessGame::promote_pawn(int x, int y, PieceType promo_to) { return promote_pawn(board->get_piece(x, y)->get_id(), promo_to); }
bool ChessGame::promote_pawn(Vector v, PieceType promo_to) { return promote_pawn(board->get_piece(v)->get_id(), promo_to); }
bool ChessGame::promote_pawn(string piece_id, PieceType promote_to) {
    auto pf = pieces_to_promote.find(piece_id);
    if (pf != pieces_to_promote.end()) {
        Move* m = pf->second;
        Piece* pawn = m->piece_moved;
        Color color = pawn->color;
        Vector pos = pawn->position;
        Piece* new_piece;
        switch (promote_to) {
            case KNIGHT: new_piece = new Knight(color, pos); break;
            case BISHOP: new_piece = new Bishop(color, pos); break;
            case ROOK: new_piece = new Rook(color, pos); break;
            case QUEEN: new_piece = new Queen(color, pos); break;
            default: return false;
        }
        new_piece->has_moved = true;
        m->piece_moved = new_piece;
        m->old_pawn = board->replace_piece(pos, new_piece);
        m->promote_to = promote_to;
        pieces_to_promote.erase(piece_id);
        return true;
    }
    return false;
}

void ChessGame::undo_move() {
    if (move_history.empty()) return;
    Move* m = move_history.back();
    board->replace_piece(m->move_to, m->piece_replaced);
    board->replace_piece(m->move_from, m->piece_moved);
    if (m->type == CASTLE || m->type == QUEENSIDE_CASTLE) {
        Vector rook_pos = Vector(m->move_to.x == 6 ? 5 : 3, m->move_from.y);
        Piece* rook = board->get_piece(rook_pos);
        board->replace_piece(rook_pos.x == 5 ? 7 : 0, rook_pos.y, rook);
        board->clear_piece(rook_pos);
        rook->has_moved = !m->first_move;
    }
    if (m->type == PAWN_PROMOTION) {
        board->replace_piece(m->move_from, m->old_pawn);
        pieces_to_promote.erase(m->old_pawn->get_id());
    }
    m->piece_moved->has_moved = !m->first_move;
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
void ChessGame::set_turn(Color color) { turn = color; }

ChessGame::~ChessGame() {
    delete board;
    while (!move_history.empty()) {
        delete move_history.back();
        move_history.pop_back();
    }
}
