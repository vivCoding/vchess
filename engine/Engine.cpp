#include "Game.h"
#include "Engine.h"

#pragma region CHESS_ENGINE_PRIVATE

int ChessEngine::random_number(int n1, int n2) {
    uniform_int_distribution<int> uni(n1, n2 - 1);
    return uni(rng);
}

ChessEngine::PossibleMove* ChessEngine::create_possible_move(
    Color color, Move root, Move move, int depth, int score, int best_score, PossibleMove *parent) {
    struct PossibleMove pm;
    pm.color = color; pm.root = root; pm.move = move; pm.depth = depth;
    pm.score = score; pm.best_score = best_score; pm.parent = parent;
    PossibleMove* pma = new PossibleMove(pm);
    return pma;
}

#pragma endregion CHESS_ENGINE_PRIVATE

#pragma region CHESS_ENGINE_PUBLIC

ChessEngine::ChessEngine() : level(0), rng(mt19937(rd())) {}
ChessEngine::ChessEngine(int level) : level(level), rng(mt19937(rd())) {}

Move ChessEngine::generate_random_move(Color color, ChessGame* game) {
    vector<Move> possible_moves = game->get_all_valid_moves(color);
    moves_considered = possible_moves.size();
    Move move = possible_moves.at(random_number(0, possible_moves.size()));
    if (move.type == PAWN_PROMOTION) {
        move.promote_to = promote_to_pieces[random_number(0, 4)];
    }
    return move;
}

Move ChessEngine::generate_move(Color color, ChessGame* game) {
    if (level <= 0) return generate_random_move(color, game);
    stack<PossibleMove*> pm_stack;
    vector<PossibleMove> best_moves;
    int best_score = INT32_MIN, worst_score = INT32_MAX;
    int root_alpha = -INT16_MAX, root_beta = INT16_MAX;
    Color other_color = get_other_color(color);
    // first add all the first moves
    vector<Move> first_moves = game->get_all_valid_moves(color);
    int root_children_count = first_moves.size();
    vector<PossibleMove*> first_pms;
    for (auto m = first_moves.begin(); m != first_moves.end(); m++) {
        if (m->type == PAWN_PROMOTION) {
            // consider all types of promotions
            for (PieceType pt : promote_to_pieces) {
                Move nm = Move(m->move_from, m->move_to, m->piece_moved, m->piece_replaced, m->type);
                nm.promote_to = pt;
                first_pms.push_back(create_possible_move(
                    other_color, nm, nm, 1,
                    calculate_utility(nm, game), INT32_MIN, NULL
                ));
            }
        } else {
            first_pms.push_back(create_possible_move(
                other_color, *m, *m, 1,
                calculate_utility(*m, game), INT32_MIN, NULL
            ));
        }
    }
    // sort for slightly better pruning
    sort(first_pms.begin(), first_pms.end(), compare_possible_move);
    for (auto pm = first_pms.begin(); pm != first_pms.end(); pm++) {
        pm_stack.push(*pm);
    }
    moves_considered = 0;
    while (!pm_stack.empty()) {
        PossibleMove *pm = pm_stack.top();
        Move move = pm->move;
        if (pm->visited) {
            pm_stack.pop();
            game->undo_move();
            PossibleMove* parent = pm->parent;
            int negated_score = -pm->best_score;
            // update best scores based on negamax
            if (parent != NULL) {
                parent->children_count--;
                if (negated_score > parent->best_score) {
                    parent->best_score = negated_score;
                    if (pm->color == color) parent->predicted_move = pm->move;
                }
                // alpha beta pruning
                parent->alpha = max(parent->alpha, parent->best_score);
                if (parent->alpha > parent->beta) {
                    while (parent->children_count) {
                        delete pm_stack.top();
                        pm_stack.pop();
                        parent->children_count--;
                    }
                }
            } else {
                root_children_count--;
                // update root best scores
                if (negated_score > best_score) {
                    best_score = negated_score;
                    best_moves.clear();
                    best_moves.push_back(*pm);
                } else if (negated_score == best_score) {
                    best_moves.push_back(*pm);
                }
                // alpha beta pruning, but on the root
                root_alpha = max(root_alpha, best_score);
                if (root_alpha > root_beta) {
                    while (root_children_count) {
                        delete pm_stack.top();
                        pm_stack.pop();
                        root_children_count--;
                    }
                }
                if (negated_score < worst_score) {
                    worst_score = negated_score;
                }
            }
            delete pm;
            moves_considered++;
        } else {
            // move piece to find new possible moves
            game->move_valid(move);
            if (move.type == PAWN_PROMOTION) {
                game->promote_pawn(move.move_to, move.promote_to);
            }
            // mark it visited so we revisit later and undo the move done
            pm->visited = true;
            // if we haven't reached all levels yet, then push all possible moves for next turn
            if (pm->depth != level) {
                // update to get the latest alphas and betas for pruning
                if (pm->parent != NULL) {
                    pm->alpha = -pm->parent->beta;
                    pm->beta = -pm->parent->alpha;
                } else {
                    pm->alpha = -root_beta;
                    pm->beta = -root_alpha;
                }
                vector<Move> possible_moves = game->get_all_valid_moves(pm->color);
                // used later to keep track of how many of the children are still left in stack and potentially remove them
                Color new_color = get_other_color(pm->color);
                int sign = pm->color == color ? 1 : -1;
                vector<PossibleMove*> pms;
                for (auto m = possible_moves.begin(); m != possible_moves.end(); m++) {
                    if (m->type == PAWN_PROMOTION) {
                        // consider all promotion types
                        for (PieceType pt : promote_to_pieces) {
                            Move nm = *m;
                            nm.promote_to = pt;
                            pms.push_back(create_possible_move(
                                new_color, pm->root, nm, pm->depth + 1, pm->score + sign * calculate_utility(nm, game), INT32_MIN, pm
                            ));
                        }
                        pm->children_count += 4;
                    } else {
                        pms.push_back(create_possible_move(
                            new_color, pm->root, *m, pm->depth + 1, pm->score + sign * calculate_utility(*m, game), INT32_MIN, pm
                        ));
                    }
                }
                pm->children_count = pms.size();
                // if we have no possible moves, that means we've reached the end of a branch early
                if (pm->children_count == 0) {
                    // set the best_score with current sign (for negamax) and set its level to the highest (essentially marking it the end of branch)
                    pm->best_score = (pm->color == color ? 1 : -1) * pm->score;
                    pm->depth = level;
                    continue;
                }
                // sorting them for slightly better pruning. Add to stack ascending or descending score based on color
                // If our color, add them ascending (consider large options first, as we're maximizing).
                // Vice versa, the other color is minimizing, so add them descending order to consider smaller options first
                sort(pms.begin(), pms.end(), compare_possible_move);
                auto start = pm->color == color ? pms.begin() : pms.end() - 1;
                auto end = pm->color == color ? pms.end() : pms.begin() - 1;
                int step = pm->color == color ? 1 : -1;
                for (auto pm = start; pm != end; pm += step) {
                    pm_stack.push(*pm);
                }
            } else {
                // we have reached all levels, simply set the best_score with current sign (for negamax)
                pm->best_score = (pm->color == color ? 1 : -1) * pm->score;
            }
        }
    }
    PossibleMove best_move = best_moves.at(random_number(0, best_moves.size()));
    return best_move.root;
}

int ChessEngine::calculate_utility(Move m, ChessGame* game) {
    Piece* moved = m.piece_moved;
    Piece* captured = m.piece_replaced;
    Color other = get_other_color(moved->color);
    int old_mobility = game->get_moves(m.piece_replaced).size();
    int old_position_value = moved->get_square_table_value(is_end_game(game));
    int score = 0;
    int material = 0;
    // temporary move piece to check mobility and other factors
    game->move_valid(m);
    // also promote pawn if needed
    if (m.type == PAWN_PROMOTION) {
        // we score the material value for promoting
        // typically, the queen is the best piece to promote to
        game->promote_pawn(m.move_to, m.promote_to);
        switch (m.promote_to) {
            case KNIGHT: material += 15; break;
            case BISHOP: material += 17; break;
            case ROOK: material += 25; break;
            case QUEEN: material += 45; break;
            default: break;
        }
    }
    // if checkmate or stalemate, set flat value
    if (game->is_checkmate(other)) score = INT16_MAX;
    else if (game->is_stalemate(other)) score = 100;
    else {
        material += captured == NULL ? 0 : captured->get_material_value();
        int mobility = game->get_moves(m.piece_replaced).size() - old_mobility;
        int center_value = center_distance_scores[8 * m.move_to.y + m.move_to.x] - center_distance_scores[8 * m.move_from.y + m.move_from.x];
        int position_value = moved->get_square_table_value(is_end_game(game)) - old_position_value;
        score = 6 * material + 2 * center_value + mobility * 2 * position_value;
    }
    game->undo_move();
    return score;
}

bool ChessEngine::is_end_game(ChessGame* game) {
    vector<Piece*> white_pieces = game->board->get_pieces(WHITE);
    vector<Piece*> black_pieces = game->board->get_pieces(BLACK);
    int white_values = 0, black_values = 0;
    for (auto pa = white_pieces.begin(); pa != white_pieces.end(); pa++) {
        Piece* p = *pa;
        if (p->type != KING) white_values += p->get_material_value();
    }
    for (auto pa = black_pieces.begin(); pa != black_pieces.end(); pa++) {
        Piece* p = *pa;
        if (p->type != KING) black_values += p->get_material_value();
    }
    int count_diff = white_pieces.size() - black_pieces.size();
    return abs(white_values - black_values) >= 10 || abs(count_diff) > 10;
}

void ChessEngine::set_level(int new_level) { level = new_level < 0 ? 0 : new_level; }
int ChessEngine::get_level() { return level; }
int ChessEngine::get_moves_considered() { return moves_considered; }

#pragma endregion CHESS_ENGINE_PUBLIC
