#ifndef PIECE_H
#define PIECE_H

#include "../Util/Vector.h"
#include "../Board/Colors.h"
#include "../Board/PieceTypes.h"
#include <random>
#include <vector>
using std::vector;

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
    int value;
    Vector position;

    Piece() : num_moves(0), type(EMPTY) { generate_id(); }
    Piece(Color color, PieceType type, int value, Vector starting_pos)
        : color(color)
        , type(type)
        , value(value)
        , position(starting_pos.x , starting_pos.y)
    { generate_id(); }

    virtual bool is_valid_move(Vector next_move, Board* board);
    // TODO: convert this to vector<Move>
    // Maybe convert is_valid_move too
    virtual vector<Vector> get_valid_moves(Board* board);

    string get_id() {
        return piece_id;
    }

    virtual ~Piece() {
        delete moves;
    }
};

#endif
