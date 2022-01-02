// finish loading all WASM before calling chess functions
Module.onRuntimeInitialized = main


function main() {
    const canvas = document.getElementById("canvas")
    const ctx = canvas.getContext("2d")
    const width = canvas.width, height = canvas.height
    const spaceWidth = canvas.width / 8, spaceHeight = canvas.height / 8
    
    const game = new ChessGame()
    const engine = new ChessEngine(3)
    drawBoard()

    function drawBoard(upsidedown = false) {
        ctx.beginPath()
        const brown = "rgb(180, 136, 102)"
        const yellow = "rgb(239, 216, 183)"
        const letters = "abcdefgh"
        ctx.fillStyle = brown
        ctx.fillRect(0, 0, width, height)
        ctx.font = "16px Arial"
        for (let x = 0; x < 8; x++) {
            const start = upsidedown ? 0 : 7
            const end = upsidedown ? 8 : -1
            const step = upsidedown ? 1 : -1
            for (let y = start; y != end; y += step) {
                ctx.fillStyle = yellow
                if ((x + y) % 2 == 0) ctx.fillRect(x * spaceWidth, y * spaceHeight, spaceWidth, spaceHeight)
                if (x == 0) {
                    ctx.fillStyle = "#4a3300"
                    ctx.fillText(y + 1, x + 2, y * spaceHeight + 18)
                }
                const piece = game.getPiece(x, 7 - y)
                if (piece != null) {
                    let sprite = new Image()
                    sprite.src = `pieces/${piece.color == Colors.WHITE ? "white" : "black"}/${piece.type}.png`
                    sprite.onload = function() {
                        let scale = 0.18
                        let sw = sprite.width * scale
                        let sh = sprite.height * scale
                        ctx.drawImage(sprite,
                            x * spaceWidth + spaceWidth / 2 - sw / 2,
                            y * spaceHeight + spaceHeight / 2 - sh / 2,
                            sw, sh
                        )
                    }
                }
            }
            ctx.fillStyle = "#4a3300"
            ctx.fillText(letters[x], (x + 1) * width / 8 - 12, height - 5)
        }
        ctx.closePath()
    }

    var mousePosition = {x: 0, y: 0}
    var pieceSelected = null
    var pieceValidMoves = []

    canvas.onmouseup = function(e) {
        let rect = canvas.getBoundingClientRect()
        mousePosition.x = e.clientX - rect.left
        mousePosition.y = e.clientY - rect.top
        const realPos = mouseToBoardPosition()
        if (pieceSelected == null) {
            pieceSelected = game.getPiece(realPos.x, realPos.y)
            if (pieceSelected.color == game.getTurn()) {
                pieceValidMoves = game.getValidMoves(pieceSelected.x, pieceSelected.y)
                showValidMoves()
            }
        } else {
            let found = pieceValidMoves.find(validMove => validMove.x == realPos.x && validMove.y == realPos.y)
            if (found != undefined) {
                game.movePiece(pieceSelected.x, pieceSelected.y, realPos.x, realPos.y)
                game.nextTurn()
                if (game.isCheckmate()) {
                    console.log("checkmate!")
                } else if (game.isStalemate()) {
                    console.log("stalemate!")
                } else if (game.isCheck()) {
                    console.log("check!")
                } else {
                    setTimeout(makeEnemyTurn, 250)
                }
            }
            pieceSelected = null
            drawBoard()
        }
    }

    function makeEnemyTurn() {
        if (!game.isCheckmate() && !game.isStalemate()) {
            console.log("making move for:", colorToChar(game.getTurn()))
            const move = engine.generateMove(game, game.getTurn())
            game.movePiece(move.x, move.y, move.x2, move.y2)
            console.log("moves considered:", move.movesConsidered)
            game.nextTurn()
            if (game.isCheckmate()) {
                console.log("checkmate!")
            } else if (game.isStalemate()) {
                console.log("stalemate!")
            } else if (game.isCheck()) {
                console.log("check!")
            }
            drawBoard()
        }
    }

    function showValidMoves() {
        ctx.fillStyle = "green"
        pieceValidMoves.forEach(validMove => {
            ctx.beginPath()
            ctx.arc(validMove.x * spaceWidth + spaceWidth / 2,  (7 - validMove.y) * spaceHeight + spaceHeight / 2, 10, 0, 2 * Math.PI)
            ctx.fill()
            ctx.closePath()
        })
        ctx.beginPath()
        ctx.lineWidth = 5
        ctx.strokeStyle = "blue"
        ctx.strokeRect(pieceSelected.x * spaceWidth, (7 - pieceSelected.y) * spaceHeight, spaceWidth, spaceHeight)
        ctx.closePath()
    }

    function mouseToBoardPosition() {
        return {
            x: Math.floor(mousePosition.x / spaceWidth),
            y: 7 - Math.floor(mousePosition.y / spaceHeight)
        }
    }
}
