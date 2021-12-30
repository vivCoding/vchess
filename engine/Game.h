#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "Util/Move.h"
#include "Board/Board.h"

class ChessGame {
private:
    Color turn;
    vector<Move*> move_history;

    /*
     * Checks if a move will result in check
    */
    bool will_check(Move m, Color color);

public:
    Board* board;
    
    ChessGame();

    /*
     * Move piece from (fx, fy) to (tx, ty)
     * Returns true if it's a valid move, or false if the move is invalid or the move would result in a check for the current turn
     * If it's a valid move, it performs the move and adds to move history
    */
    bool move_piece(int fx, int fy, int tx, int ty);
    bool move_piece(Vector from, Vector to);
    bool move_piece(Move m);

    // TODO
    bool is_valid_move(Move m);

    /*
     * Assumes the move passed is valid (to avoid additional function calls/loops), performs move, and adds to move history
     * For general use, it is highly recommended to use move_piece instead. Only call this function if you are absolutely sure the move is valid.
    */
    void move_valid(Move m);

    // TODO
    /*
     * Returns all possible (valid) moves for the current turn (or specified color)
    */
    vector<Move> get_all_valid_moves();
    vector<Move> get_all_valid_moves(Color color);

    /*
     * Checks if the given color (or current turn color if none is given) is in check
    */
    bool is_check();
    bool is_check(Color color);

    /*
     * Checks if the given color (or current turn color if none is given) is in checkmate
    */
    bool is_checkmate();
    bool is_checkmate(Color color);

    /*
     * Checks if the given color (or current turn color if none is given) is in stalement
    */
    bool is_stalemate();
    bool is_stalemate(Color color);

    /*
     * Undo the last move added to the moves history. Note that this does not return any data, and it destroys the last move (deallocate memory).
     * Thus if the data for the last move is needed, it should be retrieved and dealt with before calling undo_move()
    */
    void undo_move();

    /*
     * Returns the move in history given index, where index is 0th index starting from the oldest move added to it
    */
    Move* peek_history(int index);
    /*
     * Return the most recent move in history
    */
    Move* peek_history_back();

    // Returns move history size
    int move_history_size();

    /*
     * Resets the board pieces to starting position and the current turn to WHITE
    */
    void reset_game();

    // Swap turn to play next move
    void next_turn();
    // Get the current turn's color
    Color get_turn();

    ~ChessGame();
};

#endif