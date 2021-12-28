#ifndef PIECE_H
#define PIECE_H

#include "../Util/Vector.h"
#include "../Util/Move.h"
#include "../Board/Colors.h"
#include "../Board/PieceTypes.h"
#include <random>
#include <vector>
using std::vector;
#include <iostream>
using namespace std;

// forward declare, avoid circular dependencies
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
    // material values are standard 10, 30, 50, 90, INTMAX
    int value;
    // piece square tables reference: https://www.chessprogramming.org/Simplified_Evaluation_Function
    int *square_table;
    int *end_square_table;

    void generate_id() {
        string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::random_device rd;
        std::mt19937 rng(rd());
        piece_id = "";
        std::uniform_int_distribution<int> uni(0, chars.size() - 1);
        int id_length = 8;
        for (int i = 0; i < id_length; i++) {
            piece_id += chars[uni(rng)];
        }
    }

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

    /*
     * Takes a Vector position and checks if it's a valid next position (move) for the piece
    */
    virtual bool is_valid_move(Vector next_position, Board* board);
    /*
     * Gets all the valid moves possible, and returns it as a vector of Moves
    */
    virtual vector<Move> get_valid_moves(Board* board);

    virtual int get_square_table_value();
    virtual int get_square_table_value(bool endgame);
    virtual int get_square_table_value(int x, int y, bool endgame);

    int get_value() { return value; }
    string get_id() { return piece_id; }

    virtual ~Piece() {
        delete moves;
        delete square_table;
        delete end_square_table;
    }
};

#endif
