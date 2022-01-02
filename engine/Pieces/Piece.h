#ifndef PIECE_H
#define PIECE_H

#include "../Util/Vector.h"
#include "../Util/Colors.h"
#include "../Util/Move.h"
#include "PieceTypes.h"
#include <random>
#include <vector>
using std::vector;
using std::uniform_int_distribution;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

    class Move;
class Board;
/*
 * Represents a chess piece
*/
class Piece {
protected:
    vector<Vector> moveset;
    string piece_id;
    int value;
    // Piece square tables reference: https://www.chessprogramming.org/Simplified_Evaluation_Function
    int* square_table;
    int* end_square_table;

    void generate_id();

public:
    Color color;
    PieceType type;
    Vector position;
    bool has_moved;

    Piece();
    Piece(PieceType type, int value, Color color, Vector starting_pos, vector<Vector> moveset, int* square_table, int* end_square_table);

    vector<Vector> get_moveset();

    // Get piece square function table
    int get_square_table_value();
    int get_square_table_value(bool endgame);
    int get_square_table_value(int x, int y, bool endgame);

    string get_id();
    int get_material_value();

    ~Piece();
};

#endif
