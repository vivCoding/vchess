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
 * Class that represents the basic chess piece that moves one space at a time (e.g. Knight, King)
 * Can also represent an empty piece (space) on the chessboard (not used)
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
    virtual vector<Vector> get_valid_moves(Board* board);

    virtual ~Piece() {
        delete moves;
    }
};

#endif
