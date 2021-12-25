#ifndef PIECE_H
#define PIECE_H

#include "../Util/Vector.h"
#include "../Board/Colors.h"
#include "../Board/PieceTypes.h"
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
public:
    Color color;
    PieceType type;
    int value;
    Vector position;

    Piece() : num_moves(0), type(EMPTY) {}
    Piece(Color color, PieceType type, int value, Vector starting_pos)
        : color(color)
        , type(type)
        , value(value)
        , position(starting_pos.x , starting_pos.y)
    {}

    virtual bool is_valid_move(Vector next_move, Board* board);
    // TODO: convert this to vector<Move>
    // Maybe convert is_valid_move too
    virtual vector<Vector> get_valid_moves(Board* board);

    virtual ~Piece() {
        delete moves;
    }
};

#endif
