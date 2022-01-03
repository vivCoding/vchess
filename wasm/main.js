// TODO: documentation

const Colors = {
    WHITE: 119,
    BLACK: 98
}

const Pieces = {
    PAWN: 80,
    KNIGHT: 78,
    BISHOP: 66,
    ROOK: 82,
    QUEEN: 81,
    KING: 75
}

function colorToChar(color) {
    return color == Colors.WHITE ? "w" : color == Colors.BLACK ? "b" : null
}

function getOtherColor(color) {
    return Module._get_other_color(color)
}

function stringToMemory(str) {
    let strArr = new Uint8Array(str.length + 1)
    for (let i = 0; i < str.length; i++) {
        strArr[i] = str[i].charCodeAt(0)
    }
    strArr[strArr.length - 1] = 0
    const heapSpace = Module._malloc(strArr.length * strArr.BYTES_PER_ELEMENT)
    Module.HEAP8.set(strArr, heapSpace)
    return heapSpace;
}

function stringFromMemory(address, length) {
    let str = "";
    for (let i = 0; i < length; i++) {
        let n = HEAP8[address + i]
        if (n != 0) str += String.fromCharCode(n)
    }
    return str
}

function stringArrayFromMemory(address, length, length2) {
    let arr = []
    address = address >> 2
    for (let i = 0; i < length; i++) {
        let str = ""
        let address2 = Module.HEAP32[address + i]
        for (let j = 0; j < length2; j++) {
            const n = Module.HEAP8[address2 + j]
            if (n >= 32) str += String.fromCharCode(n);
        }
        arr.push(str)
        Module._free(address2)
    }
    Module._free(address)
    return arr
}

function intArrayFromMemory(address, length) {
    let arr = []
    address = address >> 2
    for (let i = 0; i < length; i++) {
        arr.push(Module.HEAP32[address + i])
    }
    Module._free(address)
    return arr
}

function doubleIntArrayFromMemory(address, length, length2) {
    let arr = []
    address = address >> 2
    for (let i = 0; i < length; i++) {
        let arr2 = []
        let address2 = Module.HEAP32[address + i] >> 2
        for (let j = 0; j < length2; j++) {
            arr2.push(Module.HEAP32[address2 + j])
        }
        arr.push(arr2)
        Module._free(address2)
    }
    Module._free(address)
    return arr
}


class ChessGame {
    constructor() {
        const idAddress = Module._create_chess_game()
        this.gameId = stringFromMemory(idAddress, 8)
        this._gameIdAddress = idAddress
    }

    getTurn() {
        const turn = Module._game_get_turn(this._gameIdAddress)
        return turn
    }

    nextTurn() {
        return Module._game_next_turn(this._gameIdAddress)
    }

    setTurn(color) {
        return Module._game_set_turn(this._gameIdAddress, color)
    }

    movePiece(x, y, x2, y2) {
        return Module._game_move_piece(this._gameIdAddress, x, y, x2, y2)
    }

    isCheck(color = null) {
        if (color == null) color = this.getTurn()
        return Module._game_is_check(this._gameIdAddress, color)
    }

    isStalemate(color = null) {
        if (color == null) color = this.getTurn()
        return Module._game_is_stalemate(this._gameIdAddress, color)
    }

    isCheckmate(color = null) {
        if (color == null) color = this.getTurn()
        return Module._game_is_checkmate(this._gameIdAddress, color)
    }

    getValidMoves(x, y) {
        const address = Module._game_get_valid_moves(this._gameIdAddress, x, y)
        if (address == 0) return []
        const totalValidMoves = Module._get_last_vector_length()
        const arr = doubleIntArrayFromMemory(address, totalValidMoves, 2)
        let moves = []
        arr.forEach(move => {
            moves.push({
                x: move[0],
                y: move[1]
            })
        })
        return moves
    }

    getMoveHistory() {
        const address = Module._game_get_move_history(this._gameIdAddress)
        if (address == 0) return []
        const totalMoves = Module._get_last_vector_length(this._gameIdAddress)
        let arr = stringArrayFromMemory(address, totalMoves, 6)
        for (let i = 0; i < arr.length; i++) {
            if (arr[i][2] == "-" || arr[i][2] == "x") {
                arr[i] = arr[i].substr(0, 5)
            }
        }
        return arr
    }

    getLastMove() {
        const address = Module._game_get_last_move(this._gameIdAddress)
        if (address == 0) return ""
        return stringFromMemory(address, 6)
    }

    undoMove() {
        return Module._game_undo_move(this._gameIdAddress)
    }

    getPiece(x, y) {
        const address = Module._game_get_piece(this._gameIdAddress, x, y)
        if (address == 0) return null
        const arr = intArrayFromMemory(address, 5)
        const piece = {
            type: String.fromCharCode(arr[0]),
            color: arr[1],
            value: arr[2],
            x: arr[3],
            y: arr[4]
        }
        return piece
    }

    getPieces(color) {
        const address = Module._game_get_pieces(this._gameIdAddress, color)
        if (address == 0) return null
        const totalPieces = Module._get_last_vector_length()
        const arr = doubleIntArrayFromMemory(address, totalPieces, 5)
        const pieces = []
        arr.forEach(piece => {
            pieces.push({
                type: String.fromCharCode(piece[0]),
                color: piece[1],
                value: piece[2],
                x: piece[3],
                y: piece[4]
            })
        })
        return pieces
    }

    reset() {
        return Module._game_reset(this._gameIdAddress)
    }

    end() {
        const success = Module._delete_chess_game(this._gameIdAddress)
        if (success) Module._free(this._gameIdAddress)
        return success
    }
}


class ChessEngine {
    constructor(level = 0) {
        const idAddress = Module._create_chess_engine(level)
        this.engineId = stringFromMemory(idAddress, 8)
        this._engineIdAddress = idAddress
    }

    getLevel() {
        return Module._engine_get_level(this._engineIdAddress)
    }

    setLevel(newLevel) {
        return Module._engine_set_level(this._engineIdAddress, newLevel)
    }

    generateMove(game, color) {
        const address = Module._engine_generate_move(this._engineIdAddress, game._gameIdAddress, color)
        if (address == 0) return null
        const arr = intArrayFromMemory(address, 5)
        let move = {
            x: arr[0],
            y: arr[1],
            x2: arr[2],
            y2: arr[3],
            movesConsidered: arr[4]
        }
        return move
    }

    getNumberOfMovesConsidered() {
        return Module._engine_get_number_moves(this._engineIdAddress)
    }

    end() {
        const success = Module._delete_chess_engine(this._engineIdAddress)
        if (success) Module._free(this._engineIdAddress)
        return success
    }
}