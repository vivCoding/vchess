#include "../Util/Vector.h"
#include "../Board/Colors.h"
#include <iostream>
using namespace std;

#ifndef PIECE_H
#define PIECE_H

class Piece {
protected:
    int num_moves = 0;
    Vector* moves;
public:
    char symbol = '.';
    Color color;
    Vector position;

    Piece() {};

    bool is_valid() {
        return symbol != '.';
    }

    bool is_valid_move(Vector next_move) {
        if (is_valid() && next_move.x >= 0 && next_move.x < 8 && next_move.y >= 0 && next_move.y < 8) {
            for (int i = 0; i < this->num_moves; i++) {

                cout << (moves + i)->x << ", " << (moves + i)->y << endl;
                
                if (next_move.equal_to(position.add(moves[i]))) {
                    return true;
                }
            }
        }
        return false;
    }

    void set_invalid() {
        symbol = '.';
    }
};

#endif