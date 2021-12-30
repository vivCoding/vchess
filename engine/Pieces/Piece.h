#ifndef PIECE_H
#define PIECE_H

#include "../Util/Vector.h"
#include "../Util/Colors.h"
#include "../Util/Move.h"
#include "PieceTypes.h"
#include <random>
#include <vector>
using std::vector;

class Move;
class Board;
/*
 * Class that represents the basic chess piece, with functions responsible for upholding the rules for each chess piece (e.g. get valid piece moves)
 * The base chess piece moves one space at a time (e.g. Knight, King)
 * All chess pieces derive from this class
*/
class Piece {
protected:
    int num_moves = 0;
    Vector* moves;
    string piece_id;
    // material value
    int value;
    // piece square tables reference: https://www.chessprogramming.org/Simplified_Evaluation_Function
    int *square_table;
    int *end_square_table;

    void generate_id();

public:
    Color color;
    PieceType type;
    Vector position;

    Piece() : num_moves(0), type(EMPTY) { generate_id(); }
    Piece(Color color, PieceType type, int value, Vector starting_pos)
        : value(value)
        , color(color)
        , type(type)
        , position(starting_pos.x , starting_pos.y)
    { generate_id(); }

    // Takes a Vector position and checks if it's a valid next position (move) for the piece
    virtual bool is_valid_move(Vector next_position, Board* board);
    // Gets all the valid moves possible, and returns it as a vector of Moves
    virtual vector<Move> get_valid_moves(Board* board);

    // Gets piece square function table for piece
    virtual int get_square_table_value();
    virtual int get_square_table_value(bool endgame);
    virtual int get_square_table_value(int x, int y, bool endgame);

    // get material value for piece
    int get_value() { return value; }
    string get_id() { return piece_id; }

    virtual ~Piece() {
        delete moves;
        delete square_table;
        delete end_square_table;
    }
};

#endif
