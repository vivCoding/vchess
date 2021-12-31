# VChess
A basic C++ chess engine for playing chess games and generating optimal moves.

Designed to be paired with a GUI, and act as a backend for chess programs.

- [Features](#features)
- [How to Use](#how-to-use)
    - [Initialization and Resetting](#Initialization-and-Resetting)
    - [Game State and Moving Pieces](#Game-State-and-Moving-Pieces)
    - [Board State and Piece State](#Board-State-and-Piece-State)
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

#### Color/turn to play:
Colors are represented by enums:
```cpp
enum Color {
    WHITE = 'w',
    BLACK = 'b',
};
```
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

#### Moving Pieces:
```cpp
// moving a piece located on (x, y) to (x2, y2)
bool moved_success = game.move_piece(x, y, x2, y2);
// alternatively, you can use the custom Vector class (not to be confused with std::vector)
// the Vector class conveniently stores x and y values
bool moved_success = game.move_piece(Vector(x, y), Vector(x2, y2));

// move_piece returns false if moving that piece goes against chess rules
if (!moved_success) {
    std::cout << "invalid move!";
}
```
#### Basic Chess Game State:
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

#### Generating Moves:
```cpp
// generate the best calculated move for current turn
// based on difficulty level specified when engine was intialized or reset
Move move = engine.generate_move();
// alternatively, you can generate move for a specific color
Move black_move = engine.generate_move(BLACK);
```
#### Getting Move Information:
```cpp
Move move = chess_engine.generate_move();
// what piece is it moving
Piece* piece_moved = move.piece_moved;
// where was the piece at the startf the move
Vector from = move.move_from;
// where did the piece move to
Vector to = move.move_to;
// what piece did it replace (capture). Can be NULL
Piece* piece_replaced = move.piece_replaced;
```

#### Move History and Undo:
```cpp
// viewing total moves made
int total_moves_made = chess_engine.move_history_size();
// to view the most recent move made, use peek_history_back
Move* most_recent_move = chess_engine.peek_history_back();
// you can also traverse through the move history, where the 0th index is the oldest move
Move* oldest_move = chess_engine.peek_history(0);

// undo a move made
chess_engine.undo_move()
```

#### Printing Game
`Engine.h` provides a handy `print_board()` function to print the chess game to the console.
```
chess_engine.print_board();
Output:
   -------------------------
8 | Rb Nb Bb Qb Kb Bb Nb Rb |
7 | Pb Pb Pb Pb Pb Pb Pb Pb |
6 | .  .  .  .  .  .  .  .  |
5 | .  .  .  .  .  .  .  .  |
4 | .  .  .  .  .  .  .  .  |
3 | .  .  .  .  .  .  .  .  |
2 | Pw Pw Pw Pw Pw Pw Pw Pw |
1 | Rw Nw Bw Qw Kw Bw Nw Rw |
   -------------------------
    a  b  c  d  e  f  g  h
WHITE TURN
```

### Board State and Piece State
#### Getting Pieces:
```c++
// getting all pieces from specific color
vector<Piece*> white_pieces = chess_engine.board->get_pieces(WHITE);
vector<Piece*> black_pieces = chess_engine.board->get_pieces(BLACK);

// getting specific pieces with coordinates (vectors)
// The board is 8x8, with indices from 0-7
// getting the white queen piece
Piece* p = chess_engine.board->get_piece(3, 0);
// alternatively, you can use the custom Vector class (not to be confused with std::vector)
// the Vector class conveniently stores x and y values
Piece* p = chess_engine.board->get_piece(Vector(0, 0));
```
#### Getting Piece Information:
```cpp
// if we get piece when the board is in its starting position, it will return white rook
Piece* p = chess_engine.board->get_piece(3, 0);
p->type; // QUEEN
p->color; // WHITE
p->get_value(); // 90
p->position; // Vector(3, 0)

// checking if a move is valid or not
// pass in a vector as its next position, as well as the chess engine board
bool valid_move = p->is_valid_position(Vector(0, 1), chess_engine->board);
// get all the valid moves for a piece
std::vector<Move> = p->get_valid_moves(chess_engine->board);
```

## Basic Example
Below is a very basic implementation of the chess engine. A simple but more developed chess program is available in the repo as `ConsoleChess.cpp`
```cpp
#include "engine/Engine.h"
#include <iostream>
using namespace std;

int main() {
    // initialize a chess engine with difficulty level 4
    ChessEngine chess_engine(4);
    // games always start with WHITE
    // move white pawn from e2 to e4
    chess_engine.move_piece(4, 1, 4, 3);
    // indicate the chess engine to change turn color
    // in this case, it will change to BLACK
    chess_engine.next_turn();
    // generate best move for color BLACK
    Move m = chess_engine.generate_move();
    chess_engine.next_turn();
    chess_engine.print_board();
    return 0;
}
```
Output (may vary on generated move):
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
WHITE TURN
```

## Known Issues and TODOs
- No castling or pawn promotion yet :(
- Chess move generation and evaluation improvements
    - Searching has been substantially improved with alpha-beta pruning and sorting moves. However, this may be improved with transposition tables and other techniques such as negascout
    - Piece evaluation can be further improved with better piece-squares tables, such as ones that further take into consideration of how close it is to endgame

## Contributing

Feel free to contribute and/or report issues through GitHub.