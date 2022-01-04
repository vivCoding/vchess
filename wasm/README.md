# VChess with JS/WASM

Thanks to WebAssembly (WASM), the chess engine (originally written in C++) can ported for use on the web with JS.

### Compilation
An already compiled `.wasm` file can be found in [here](https://github.com/vivCoding/vchess/tree/main/docs/wasm). You can also compile it yourself using the following Emscripten command (update paths accordingly):

```bash
em++ wasm/Main.cpp engine/*.cpp engine/*/*.cpp -o path_to_output -s WASM=1 O3 -s EXPORTED_FUNCTIONS='["_malloc", "_free"]'
```

### Initialization, Resetting, and Destroying
```js
// initializes a chess game. Chessboard is already set up, ready for use
const game = new ChessGame()
// creates chess engine with chess difficulty level 0
const engine = new ChessEngine()
// you can also initialize with a specific difficulty level
const engine = new ChessEngine(3)

// resets the board pieces to starting position, sets the turn color to WHITE
game.reset()

// destroying the game and engine when finished (prevents memory leaks)
game.end()
engine.end()
```

### Game State and Moving Pieces
Turns are represented by colors:
```cpp
const Colors {
    WHITE: 119,
    BLACK: 98,
}
```
To get turn information about your chess game:
```js
// returns current turn color
game.getTurn();
// change turn color to the next color
// e.g. change to BLACK if it was turn was WHITE before, and vice versa
game.nextTurn();
// you can also manually set the color
game.setTurn(Colors.WHITE);
```
There is also a convenient function to get the alternative color as well:
```cpp
getOtherColor(Colors.WHITE); // returns 98 (BLACK)
```

### Moving Pieces
```js
// moving a piece located on (x, y) to (x2, y2)
const movedSuccess = game.movePiece(x, y, x2, y2);

// move_piece returns false if moving that piece goes against chess rules
if (!moveSuccess) {
    console.log("invalid move!")
}
```

### Game State and Valid Moves
```js
// checks if the current turn is in check
const inCheck = game.isCheck()
// alternatively, you can pass in specified color
const whiteCheck = game.isCheck(Colors.WHITE)

// stalemate
const inStalemate = game.isStalemate()
const whiteStalemate = game.isStalemate(Colors.WHITE)

// checkmate
const inCheckmate = game.isCheckmate()
const whiteCheckmate = game.isCheckmate(Colors.WHITE)
```
```js
// getting legal (valid) moves for a piece at (x, y)
// i.e. these moves take into account of checks/mates
// unlike the C++ variant, validMoves return an array of simple objects containing valid positions for the specific piece at (x, y)
// i.e. [ { x, y }, { x, y} ]
const validMoves = game.getValidMoves(x, y)
console.log(validMoves[0].x)
console.log(validMoves[0].y)
```

### Pawn Promotion
After moving a piece, you can check if it's available for promotion:
```js
// check if a piece at board position (x, y) can be promoted
const canPromote = game.pawn_promotion_available(x, y);
```
Once you confirm that it can be promoted, you can promote it to piece of choice:
```js
// promotes pawn at specific location to QUEEN (Q)
// piece types should only be KNIGHT (K), BISHOP (B), ROOK (R), and QUEEN (Q)
bool promotion_successful = game.promote_pawn(x, y, "Q");
```

###  Move History and Undo
```js
// array of last moves made in string format, ordered from oldest to newest
game.getMoveHistory()
// returns last move in string format
game.getLastMove()
// undoes one move
game.undoMove()
```

### Getting Pieces
```js
// getting a singular piece. Returns an object
const queen = game.getPiece(3, 0)
queen.type // "Q"
queen.color // 119, aka. WHITE
queen.value // 90
queen.x // board position.x, 3
queen.y // board position.y, 0

// getting multiple pieces for a certain color
const whitePieces = game.getPieces(Colors.WHITE)
``` 
### Engine Level
```js
// get engine level
engine.getLevel()
// set engine level
engine.setLevel(3)
```

### Generating Moves
```js
// generate the best calculated move in a chess game (for the game's current turn)
// based on difficulty level specified when engine was initialized or set
const move = engine.generateMove(game)
// alternatively, you can generate move for a specific color
const move = engine.generateMove(game, Colors.BLACK)
// generateMove() will return an object
// you can read the generated move like so
move.x // board position.x to move from
move.y // board position.y to move from
move.x2 // board position.x to move to
move.y2  // board position.y to move to
move.movesConsidered // number of moves it considered
move.promoteTo // if it's a pawn promotion, what piece it should promote to

// you can also separately retrieve the number of moves the engine considered during its last move generation
console.log(engine.getNumberOfMovesConsidered())
```