# VChess
A basic C++ chess engine for playing chess games and generating optimal moves.

Designed to be paired with a GUI, and act as a backend for chess programs.

- [Features](#features)
- [How to Use](#how-to-use)
    - [Initialization and Resetting](#Initialization-and-Resetting)
    - [Game State and Moving Pieces](#Game-State-and-Moving-Pieces)
        - [Player Turns](#Player-Turns)
        - [Moving Pieces](#Moving-Pieces)
        - [Game State and Valid Moves](#Game-State-and-Valid-Moves)
        - [Generating Moves](#Generating-Moves)
        - [Move History and Undo](#Move-History-and-Undo)
    - [Board State and Pieces](#Board-State-and-Pieces)
        - [Getting Pieces](#Getting-Pieces)
        - [Getting Piece Information](#Getting-Piece-Information)
    - [Utility Classes](#Utility-Classes)
        - [Vector](#Vector)
        - [Move](#Move)
- [Basic Example](#Basic-Example)
- [Known Issues and TODOs](#Known-Issues-and-TODOs)
- [Contributing](#Contributing)

## Features
- Proper piece movement and game/board state
- Undo move and move history
- Move generation using negamax with alpha-beta pruning and moves sorting
- Move utility evaluation based on material score, center distance, mobility, and simple piece square tables

## How to Use
There are two main classes:
- `ChessGame` keeps state of the current game/board, as well as maintain chess rules.
- `ChessEngine` is used for move generation and evaluation. This class is optional for use if your chess program does not require move generation or evaluation

To use these classes, simply include required header files:
```cpp
// replace "engine" with the path to the engine folder
#include "engine/Game.h"
#include "engine/Engine.h"
```
Compile your program with the engine files:
```bash
g++ YourFile.cpp <path_to_engine>/*.cpp <path_to_engine>/*/*.cpp
```

### Initialization and Resetting
```cpp
// initializes a chess game. Chessboard is already set up, ready for use
ChessGame game;
// creates chess engine with chess difficulty level 0
ChessEngine engine();
// you can also initialize with a specific difficulty level
ChessEngine engine(4);

// resets the board pieces to starting position, sets the turn color to WHITE
engine.reset_game();
// resets with a specific difficulty level
engine.reset_game(4);
```

### Game State and Moving Pieces

#### Player Turns
Turns are represented by colors, whcih are represented by enums:
```cpp
enum Color {
    WHITE = 'w',
    BLACK = 'b',
};
```
To get turn information about your chess game:
```cpp
// returns current turn color
game.get_turn();
// change turn color to the next color
// e.g. change to BLACK if it was turn was WHITE before, and vice versa
game.next_turn();
// you can also manually set the color
game.set_turn(WHITE);
```
There is also a convenient function to get the alternative color as well:
```cpp
get_other_color(WHITE); // returns BLACK
```

#### Moving Pieces
```cpp
// moving a piece located on (x, y) to (x2, y2)
bool moved_success = game.move_piece(x, y, x2, y2);
// alternatively, you can use the custom Vector class
bool moved_success = game.move_piece(Vector(x, y), Vector(x2, y2));

// move_piece returns false if moving that piece goes against chess rules
if (!moved_success) {
    std::cout << "invalid move!";
}
```
See [Utility Classes](#Utility-Classes) for info about the `Vector` class

#### Game State and Valid Moves
```cpp
// checks if the current turn is in check
bool in_check = game.is_check()
// alternatively, you can pass in specified color
bool white_check = game.is_check(WHITE);

// stalemate
bool in_stalemate = game.is_stalemate();
bool white_stalemate = game.is_stalemate(WHITE);

// checkmate
bool in_checkmate = chess_engine.is_checkmate();
bool white_checkmate = chess_engine.is_checkmate(WHITE);
```
```cpp
// getting legal (valid) moves for a piece at <x, y>
// i.e. these moves take into account of checks/mates
vector<Move> valid_moves = get_valid_moves(x, y);
vector<Move> valid_moves = get_valid_moves(Vector(x, y));

// getting ALL legal moves for the current player's turn (or specified color)
vector<Move> player_valid_moves = get_all_valid_moves();
vector<Move> white_valid_moves = get_all_valid_moves(WHITE);
```

See [Utility Classes](#Utility-Classes) for usage of the `Move` class.


#### Generating Moves
```cpp
// generate the best calculated move for current turn
// based on difficulty level specified when engine was intialized or reset
Move move = engine.generate_move();
// alternatively, you can generate move for a specific color
Move black_move = engine.generate_move(BLACK);
// you can also retrieve the number of moves the engine considered during its last move generation
engine.get_moves_considered();
```
See [Utility Classes](#Utility-Classes) for usage of the `Move` class.

#### Move History and Undo
```cpp
// viewing total moves made
int total_moves_made = game.move_history_size();
// to view the most recent move made, use peek_history_back
Move* most_recent_move = game.peek_history_back();
// you can also traverse through the move history, where the 0th index is the oldest move
Move* oldest_move = game.peek_history(0);

// undo a move made
game.undo_move();
```

### Board State and Pieces
#### Getting Pieces
```c++
// getting all pieces from specific color
vector<Piece*> white_pieces = chess_engine.board->get_pieces(WHITE);
vector<Piece*> black_pieces = chess_engine.board->get_pieces(BLACK);

// getting specific pieces with coordinates (vectors)
// the board is 8x8, with indices from 0-7
// this gets the white queen piece (assuming it start from starting position)
Piece* p = chess_engine.board->get_piece(3, 0);
Piece* p = chess_engine.board->get_piece(Vector(3, 0));
```

#### Getting Piece Information
```cpp
Piece* p = chess_engine.board->get_piece(3, 0);
p->type; // QUEEN
p->color; // WHITE
p->get_material_value(); // 90
p->position; // Vector(3, 0)

// Returns the piece moveset (how a piece can move)
std::vector<Vector> moveset = p->get_moveset();
```

## Utility Classes

### Vector

This is not to be confused with `std::vector`.

`Vector` is a custom class used to conveniently store xy positions and movements.
```cpp
// default initializes to x = 0 and y = 0
Vector zero_vector = Vector();
// initializes to x = 2 and y = 8
Vector v = Vector(2, 8);

// set vector x to 5 and y = 3
v.set(5, 3);
v.set(Vector(5, 3));

// vector arithmetic. These do not modify the vectors. Instead, they return a new one
v.add(Vector(1, 2)); // returns Vector(6, 5)
v.subtract(Vector(4, 1)); // returns Vector(2, 4)
v.scale(2); // return Vector(4, 8)

// compare two vectors to see if they have same x and y values
Vector v2 = Vector(4, 8);
v.equal_to(v2); // true
v.equal_to(Vector(1, 0)) // false

// returns the Vector in a readable format
v.as_string() // returns "(4, 8)"
```

### Move
`Move` is a custom class to represent one move made by a player. It is what `engine.generate_move()` returns, and what the `game.move_history` stores.

A `Move` stores:
- What piece moved
- What piece was replaced/captured (can be `NULL`)
- Where the piece came from
- The final destination of the piece
- The move type
- Whether the move was the moved piece's first move
```cpp
// initialization
Move move = Move(vector_from, vector_to, Piece* piece_moving, Piece* piece_replaced);
Move move = Move(vector_from, vector_to, Piece* piece_moving, Piece* piece_replaced, MoveType move_type);
```
Moves can have the following types, represented as an enum:
```cpp
enum MoveType {
    MOVE,
    CAPTURE,
    CASTLE,
    QUEENSIDE_CASTLE
};
```
#### Example
```cpp
// a common scenario for using Move is thru generating moves with the engine
Move move = engine.generate_move();
// what piece is it moving
Piece* piece_moved = move.piece_moved;
// where was the piece at the startf the move
Vector from = move.move_from;
// where did the piece move to
Vector to = move.move_to;
// what piece did it replace (capture). Can be NULL
Piece* piece_replaced = move.piece_replaced;
// what type of move was this?
MoveType type = move.type;
// was it piece_moved's first move?
bool first_move = move.first_move;
```
You can also represent the move as a readable string (in chess long notation):
```cpp
// returns move as string
// example value: Ng8-f6 (move knight from g8 to f6)
move.as_string();
```

## Basic Example
Below is a very basic implementation of the chess engine. A simple but more developed chess program is available in the repo as `ConsoleChess.cpp`
```cpp
#include "engine/Engine.h"
#include <iostream>
using namespace std;

int main() {
    // initialize a chess game and chess engine with difficulty level 4
    ChessGame game;
    ChessEngine engine(4);
    // games always start with WHITE
    // move white pawn from e2 to e4
    game.move_piece(4, 1, 4, 3);
    // indicate the chess engine to change turn color
    // in this case, it will change to BLACK
    game.next_turn();
    // generate best move for color BLACK
    Move black_move = engine.generate_move(game.get_turn());
    game.move_piece(black_move);
    game.next_turn();
    return 0;
}
```
Final board (may vary on generated move):
```
   -------------------------
8 | Rb .  Bb Qb Kb Bb Nb Rb |
7 | Pb Pb Pb Pb Pb Pb Pb Pb |
6 | .  .  Nb .  .  .  .  .  |
5 | .  .  .  .  .  .  .  .  |
4 | .  .  .  .  Pw .  .  .  |
3 | .  .  .  .  .  .  .  .  |
2 | Pw Pw Pw Pw .  Pw Pw Pw |
1 | Rw Nw Bw Qw Kw Bw Nw Rw |
   -------------------------
    a  b  c  d  e  f  g  h
WHITE TURN TO MOVE
```

## Known Issues and TODOs
- No pawn promotion yet :(
- Chess move generation and evaluation improvements
    - Searching has been substantially improved with alpha-beta pruning and sorting moves. However, this may be improved with transposition tables and other techniques such as negascout
    - Piece evaluation can be further improved with better piece-squares tables, such as ones that further take into consideration of how close it is to endgame
- Checks/mates calculation runtime complexities could possibly be reduced

## Contributing

Feel free to contribute and/or report issues through GitHub.