Module.onRuntimeInitialized = function() {
    main()
}

let game
let engine

function main() {
    game = new ChessGame()
    engine = new ChessEngine(1)
    console.log("got it", HEAP8[engine._engineIdAddress])
    console.log(game.gameId)
    console.log(engine.engineId)
    console.log("move", game.movePiece(4, 1, 4, 3))
    console.log("nextTurn", game.nextTurn())
    console.log("getTurn", game.getTurn())
    console.log("undoMove", game.undoMove())
    console.log("setTurn", game.setTurn(Colors.WHITE))
    console.log("move", game.movePiece(4, 1, 4, 2))
    console.log("nextTurn", game.nextTurn())
    let move = engine.generateMove(game, game.getTurn())
    console.log("generated", move)
    console.log("move black", game.movePiece(move.x, move.y, move.x2, move.y2))
}