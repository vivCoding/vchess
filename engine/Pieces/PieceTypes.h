#ifndef PIECE_TYPES_H
#define PIECE_TYPES_H

/*
 * Constants for the different chess pieces
*/
enum PieceType {
    NONE = '.',
    PAWN = 'P',
    KNIGHT = 'N',
    BISHOP = 'B',
    ROOK = 'R',
    QUEEN = 'Q',
    KING = 'K'
};

static PieceType promote_to_pieces[] = { KNIGHT, BISHOP, ROOK, QUEEN };

#endif
