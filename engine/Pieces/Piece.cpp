#include "../Board/Board.h"
#include "Piece.h"

void Piece::generate_id() {
    string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, chars.size() - 1);
    piece_id = "";
    int id_length = 8;
    for (int i = 0; i < id_length; i++) {
        piece_id += chars[uni(rng)];
    }
}

Piece::Piece() { generate_id(); }
Piece::Piece(PieceType type, int value, Color color, Vector starting_pos, vector<Vector> moveset, int* square_table, int* end_square_table)
    : moveset(moveset)
    , value(value)
    , square_table(square_table)
    , end_square_table(end_square_table)
    , color(color)
    , type(type)
    , position(starting_pos.x, starting_pos.y)
    , has_moved(false) { generate_id(); }

vector<Vector> Piece::get_moveset() {
    return moveset;
}

int Piece::get_square_table_value() { return get_square_table_value(false); }
int Piece::get_square_table_value(bool endgame) {
    int x = position.x, y = position.y;
    return get_square_table_value(x, y, endgame);
}
int Piece::get_square_table_value(int x, int y, bool endgame) {
    if (endgame && end_square_table != NULL) {
        if (color == WHITE) return end_square_table[8 * (7 - y) + x];
        else return end_square_table[8 * y + x];
    } else {
        if (color == WHITE) return square_table[8 * (7 - y) + x];
        else return square_table[8 * y + x];
    }
}

int Piece::get_material_value() { return value; }
string Piece::get_id() { return piece_id; }

Piece::~Piece() {
    delete square_table;
    delete end_square_table;
}