#ifndef PIECE_H
#define PIECE_H

#include "../Util/Vector.h"
#include "../Board/Colors.h"
#include "../Board/PieceTypes.h"
#include <vector>
using std::vector;

class Board;

class Piece {
protected:
    int num_moves = 0;
    Vector* moves;
public:
    Color color;
    PieceType type;
    int value;
    Vector position;
    bool is_valid;

    Piece() : type(EMPTY), is_valid(false) {}
    Piece(Color color, PieceType type, int value, Vector starting_pos)
        : color(color)
        , type(type)
        , value(value)
        , position(starting_pos.x , starting_pos.y)
        , is_valid(true)
    {}

    virtual bool is_valid_move(Vector next_move, Board* board);
    virtual vector<Vector> get_valid_moves(Board* board);

    virtual ~Piece() {
        delete moves;
    }
};

#endif
