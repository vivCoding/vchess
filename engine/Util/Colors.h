#ifndef COLORS_H
#define COLORS_H

/*
 * Constants for chessboard colors
*/
enum Color {
    WHITE = 'w',
    BLACK = 'b',
};

// Convenient function to return the inverse color
inline Color get_other_color(Color color) {
    return color == WHITE ? BLACK : WHITE;
}

#endif
