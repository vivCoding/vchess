#ifndef ENGINE_H
#define ENGINE_h

#include "Game.h"
#include "Util/Move.h"
#include <random>
#include <stack>
#include <algorithm>
using namespace std;
// using std::stack;
// using std::sort;
// using std::random_device;
// using std::mt19937;
// using std::uniform_int_distribution;
// using std::max;

class ChessGame;
/*
 * Represents a chess game, with functions to move chess pieces and uphold the rules of chess (e.g. check, checkmate, turns)
 * Can generate the "best" move for specific color
*/
class ChessEngine {
private:
    int level;
    int moves_considered;
    random_device rd;
    mt19937 rng;

    // Used for move evaluation. Values based on https://www.chessprogramming.org/Center_Manhattan-Distance, and inversed to appropriately show scores
    const int center_distance_scores[64] = {
        0, 1, 2, 3, 3, 2, 1, 0,
        1, 2, 3, 4, 4, 3, 2, 1,
        2, 3, 4, 5, 5, 4, 3, 2,
        3, 4, 5, 6, 6, 5, 4, 3,
        3, 4, 5, 6, 6, 5, 4, 3,
        2, 3, 4, 5, 5, 4, 3, 2,
        1, 2, 3, 4, 4, 3, 2, 1,
        0, 1, 2, 3, 3, 2, 1, 0
    };

    // Returns random integer from [n1, n2)
    int random_number(int n1, int n2);

    // Structure for storing next possible move. Used for move generation
    struct PossibleMove {
        Color color;
        Move root, move, predicted_move;
        int depth, score, best_score, children_count;
        bool visited = false;
        int alpha = INT16_MIN, beta = INT16_MAX;
        PossibleMove* parent;
    };

    // Creates a possible move
    PossibleMove* create_possible_move(Color color, Move root, Move move, int depth, int score, int best_score, PossibleMove* parent);

    // comparator used for sorting
    static bool compare_possible_move(PossibleMove* pm, PossibleMove* pm2) {
        return pm->score < pm2->score;
    }

public:
    ChessEngine();
    ChessEngine(int level);

    /*
     * Randomnly generates the next (valid) move for the given color (or current turn color if none is given)
    */
    Move generate_random_move(Color color, ChessGame* game);

    /*
     * Calculates and returns the next move for the given color (or current turn color if none is given)
     * Utilizes the chess engine level. If level is low, the function takes less time to complete, but may result in worse moves,
     * while higher levels take more time to calculate and may result in better moves
     * 
     * This function implements negamax with alpha-beta pruning. Note that one should check if in checkmate before generating move, as
     * the function will result in error if it's already in checkmate
    */
    Move generate_move(Color color, ChessGame* game);

    /*
     * Calculates utility (score) for a given move based several factors
     * - material value of captured (if any) piece
     * - mobility value (how many moves it can take afterwards)
     * - center value (how close it is to the center)
     * - position value (how good is it's position according to the piece)
    */
    int calculate_utility(Move m, ChessGame* game);

    /*
     * Tries to determine whether the current game is close to the end by checking the difference between the total piece values between
     * the two colors, as well as the total number of pieces on each side
    */
    bool is_end_game(ChessGame* game);

    // Set chess engine level
    void set_level(int new_level);
    // Returns current chess engine level
    int get_level();
    // Gets the number of moves considered from the last move generation
    int get_moves_considered();
};

#endif
