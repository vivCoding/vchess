var Module=typeof Module!=="undefined"?Module:{};var moduleOverrides={};var key;for(key in Module){if(Module.hasOwnProperty(key)){moduleOverrides[key]=Module[key]}}var arguments_=[];var thisProgram="./this.program";var quit_=function(status,toThrow){throw toThrow};var ENVIRONMENT_IS_WEB=typeof window==="object";var ENVIRONMENT_IS_WORKER=typeof importScripts==="function";var ENVIRONMENT_IS_NODE=typeof process==="object"&&typeof process.versions==="object"&&typeof process.versions.node==="string";var scriptDirectory="";function locateFile(path){if(Module["locateFile"]){return Module["locateFile"](path,scriptDirectory)}return scriptDirectory+path}var read_,readAsync,readBinary,setWindowTitle;function logExceptionOnExit(e){if(e instanceof ExitStatus)return;var toLog=e;err("exiting due to exception: "+toLog)}var nodeFS;var nodePath;if(ENVIRONMENT_IS_NODE){if(ENVIRONMENT_IS_WORKER){scriptDirectory=require("path").dirname(scriptDirectory)+"/"}else{scriptDirectory=__dirname+"/"}read_=function shell_read(filename,binary){if(!nodeFS)nodeFS=require("fs");if(!nodePath)nodePath=require("path");filename=nodePath["normalize"](filename);return nodeFS["readFileSync"](filename,binary?null:"utf8")};readBinary=function readBinary(filename){var ret=read_(filename,true);if(!ret.buffer){ret=new Uint8Array(ret)}assert(ret.buffer);return ret};readAsync=function readAsync(filename,onload,onerror){if(!nodeFS)nodeFS=require("fs");if(!nodePath)nodePath=require("path");filename=nodePath["normalize"](filename);nodeFS["readFile"](filename,function(err,data){if(err)onerror(err);else onload(data.buffer)})};if(process["argv"].length>1){thisProgram=process["argv"][1].replace(/\\/g,"/")}arguments_=process["argv"].slice(2);if(typeof module!=="undefined"){module["exports"]=Module}process["on"]("uncaughtException",function(ex){if(!(ex instanceof ExitStatus)){throw ex}});process["on"]("unhandledRejection",function(reason){throw reason});quit_=function(status,toThrow){if(keepRuntimeAlive()){process["exitCode"]=status;throw toThrow}logExceptionOnExit(toThrow);process["exit"](status)};Module["inspect"]=function(){return"[Emscripten Module object]"}}else if(ENVIRONMENT_IS_WEB||ENVIRONMENT_IS_WORKER){if(ENVIRONMENT_IS_WORKER){scriptDirectory=self.location.href}else if(typeof document!=="undefined"&&document.currentScript){scriptDirectory=document.currentScript.src}if(scriptDirectory.indexOf("blob:")!==0){scriptDirectory=scriptDirectory.substr(0,scriptDirectory.replace(/[?#].*/,"").lastIndexOf("/")+1)}else{scriptDirectory=""}{read_=function(url){var xhr=new XMLHttpRequest;xhr.open("GET",url,false);xhr.send(null);return xhr.responseText};if(ENVIRONMENT_IS_WORKER){readBinary=function(url){var xhr=new XMLHttpRequest;xhr.open("GET",url,false);xhr.responseType="arraybuffer";xhr.send(null);return new Uint8Array(xhr.response)}}readAsync=function(url,onload,onerror){var xhr=new XMLHttpRequest;xhr.open("GET",url,true);xhr.responseType="arraybuffer";xhr.onload=function(){if(xhr.status==200||xhr.status==0&&xhr.response){onload(xhr.response);return}onerror()};xhr.onerror=onerror;xhr.send(null)}}setWindowTitle=function(title){document.title=title}}else{}var out=Module["print"]||console.log.bind(console);var err=Module["printErr"]||console.warn.bind(console);for(key in moduleOverrides){if(moduleOverrides.hasOwnProperty(key)){Module[key]=moduleOverrides[key]}}moduleOverrides=null;if(Module["arguments"])arguments_=Module["arguments"];if(Module["thisProgram"])thisProgram=Module["thisProgram"];if(Module["quit"])quit_=Module["quit"];var wasmBinary;if(Module["wasmBinary"])wasmBinary=Module["wasmBinary"];var noExitRuntime=Module["noExitRuntime"]||true;if(typeof WebAssembly!=="object"){abort("no native wasm support detected")}var wasmMemory;var ABORT=false;var EXITSTATUS;function assert(condition,text){if(!condition){abort("Assertion failed: "+text)}}var buffer,HEAP8,HEAPU8,HEAP16,HEAPU16,HEAP32,HEAPU32,HEAPF32,HEAPF64;function updateGlobalBufferAndViews(buf){buffer=buf;Module["HEAP8"]=HEAP8=new Int8Array(buf);Module["HEAP16"]=HEAP16=new Int16Array(buf);Module["HEAP32"]=HEAP32=new Int32Array(buf);Module["HEAPU8"]=HEAPU8=new Uint8Array(buf);Module["HEAPU16"]=HEAPU16=new Uint16Array(buf);Module["HEAPU32"]=HEAPU32=new Uint32Array(buf);Module["HEAPF32"]=HEAPF32=new Float32Array(buf);Module["HEAPF64"]=HEAPF64=new Float64Array(buf)}var INITIAL_MEMORY=Module["INITIAL_MEMORY"]||16777216;var wasmTable;var __ATPRERUN__=[];var __ATINIT__=[];var __ATPOSTRUN__=[];var runtimeInitialized=false;var runtimeKeepaliveCounter=0;function keepRuntimeAlive(){return noExitRuntime||runtimeKeepaliveCounter>0}function preRun(){if(Module["preRun"]){if(typeof Module["preRun"]=="function")Module["preRun"]=[Module["preRun"]];while(Module["preRun"].length){addOnPreRun(Module["preRun"].shift())}}callRuntimeCallbacks(__ATPRERUN__)}function initRuntime(){runtimeInitialized=true;callRuntimeCallbacks(__ATINIT__)}function postRun(){if(Module["postRun"]){if(typeof Module["postRun"]=="function")Module["postRun"]=[Module["postRun"]];while(Module["postRun"].length){addOnPostRun(Module["postRun"].shift())}}callRuntimeCallbacks(__ATPOSTRUN__)}function addOnPreRun(cb){__ATPRERUN__.unshift(cb)}function addOnInit(cb){__ATINIT__.unshift(cb)}function addOnPostRun(cb){__ATPOSTRUN__.unshift(cb)}var runDependencies=0;var runDependencyWatcher=null;var dependenciesFulfilled=null;function addRunDependency(id){runDependencies++;if(Module["monitorRunDependencies"]){Module["monitorRunDependencies"](runDependencies)}}function removeRunDependency(id){runDependencies--;if(Module["monitorRunDependencies"]){Module["monitorRunDependencies"](runDependencies)}if(runDependencies==0){if(runDependencyWatcher!==null){clearInterval(runDependencyWatcher);runDependencyWatcher=null}if(dependenciesFulfilled){var callback=dependenciesFulfilled;dependenciesFulfilled=null;callback()}}}Module["preloadedImages"]={};Module["preloadedAudios"]={};function abort(what){{if(Module["onAbort"]){Module["onAbort"](what)}}what="Aborted("+what+")";err(what);ABORT=true;EXITSTATUS=1;what+=". Build with -s ASSERTIONS=1 for more info.";var e=new WebAssembly.RuntimeError(what);throw e}var dataURIPrefix="data:application/octet-stream;base64,";function isDataURI(filename){return filename.startsWith(dataURIPrefix)}function isFileURI(filename){return filename.startsWith("file://")}var wasmBinaryFile;wasmBinaryFile="chess.wasm";if(!isDataURI(wasmBinaryFile)){wasmBinaryFile=locateFile(wasmBinaryFile)}function getBinary(file){try{if(file==wasmBinaryFile&&wasmBinary){return new Uint8Array(wasmBinary)}if(readBinary){return readBinary(file)}else{throw"both async and sync fetching of the wasm failed"}}catch(err){abort(err)}}function getBinaryPromise(){if(!wasmBinary&&(ENVIRONMENT_IS_WEB||ENVIRONMENT_IS_WORKER)){if(typeof fetch==="function"&&!isFileURI(wasmBinaryFile)){return fetch(wasmBinaryFile,{credentials:"same-origin"}).then(function(response){if(!response["ok"]){throw"failed to load wasm binary file at '"+wasmBinaryFile+"'"}return response["arrayBuffer"]()}).catch(function(){return getBinary(wasmBinaryFile)})}else{if(readAsync){return new Promise(function(resolve,reject){readAsync(wasmBinaryFile,function(response){resolve(new Uint8Array(response))},reject)})}}}return Promise.resolve().then(function(){return getBinary(wasmBinaryFile)})}function createWasm(){var info={"a":asmLibraryArg};function receiveInstance(instance,module){var exports=instance.exports;Module["asm"]=exports;wasmMemory=Module["asm"]["g"];updateGlobalBufferAndViews(wasmMemory.buffer);wasmTable=Module["asm"]["L"];addOnInit(Module["asm"]["h"]);removeRunDependency("wasm-instantiate")}addRunDependency("wasm-instantiate");function receiveInstantiationResult(result){receiveInstance(result["instance"])}function instantiateArrayBuffer(receiver){return getBinaryPromise().then(function(binary){return WebAssembly.instantiate(binary,info)}).then(function(instance){return instance}).then(receiver,function(reason){err("failed to asynchronously prepare wasm: "+reason);abort(reason)})}function instantiateAsync(){if(!wasmBinary&&typeof WebAssembly.instantiateStreaming==="function"&&!isDataURI(wasmBinaryFile)&&!isFileURI(wasmBinaryFile)&&typeof fetch==="function"){return fetch(wasmBinaryFile,{credentials:"same-origin"}).then(function(response){var result=WebAssembly.instantiateStreaming(response,info);return result.then(receiveInstantiationResult,function(reason){err("wasm streaming compile failed: "+reason);err("falling back to ArrayBuffer instantiation");return instantiateArrayBuffer(receiveInstantiationResult)})})}else{return instantiateArrayBuffer(receiveInstantiationResult)}}if(Module["instantiateWasm"]){try{var exports=Module["instantiateWasm"](info,receiveInstance);return exports}catch(e){err("Module.instantiateWasm callback failed with error: "+e);return false}}instantiateAsync();return{}}function callRuntimeCallbacks(callbacks){while(callbacks.length>0){var callback=callbacks.shift();if(typeof callback=="function"){callback(Module);continue}var func=callback.func;if(typeof func==="number"){if(callback.arg===undefined){getWasmTableEntry(func)()}else{getWasmTableEntry(func)(callback.arg)}}else{func(callback.arg===undefined?null:callback.arg)}}}var wasmTableMirror=[];function getWasmTableEntry(funcPtr){var func=wasmTableMirror[funcPtr];if(!func){if(funcPtr>=wasmTableMirror.length)wasmTableMirror.length=funcPtr+1;wasmTableMirror[funcPtr]=func=wasmTable.get(funcPtr)}return func}function ___cxa_allocate_exception(size){return _malloc(size+16)+16}function ExceptionInfo(excPtr){this.excPtr=excPtr;this.ptr=excPtr-16;this.set_type=function(type){HEAP32[this.ptr+4>>2]=type};this.get_type=function(){return HEAP32[this.ptr+4>>2]};this.set_destructor=function(destructor){HEAP32[this.ptr+8>>2]=destructor};this.get_destructor=function(){return HEAP32[this.ptr+8>>2]};this.set_refcount=function(refcount){HEAP32[this.ptr>>2]=refcount};this.set_caught=function(caught){caught=caught?1:0;HEAP8[this.ptr+12>>0]=caught};this.get_caught=function(){return HEAP8[this.ptr+12>>0]!=0};this.set_rethrown=function(rethrown){rethrown=rethrown?1:0;HEAP8[this.ptr+13>>0]=rethrown};this.get_rethrown=function(){return HEAP8[this.ptr+13>>0]!=0};this.init=function(type,destructor){this.set_type(type);this.set_destructor(destructor);this.set_refcount(0);this.set_caught(false);this.set_rethrown(false)};this.add_ref=function(){var value=HEAP32[this.ptr>>2];HEAP32[this.ptr>>2]=value+1};this.release_ref=function(){var prev=HEAP32[this.ptr>>2];HEAP32[this.ptr>>2]=prev-1;return prev===1}}var exceptionLast=0;var uncaughtExceptionCount=0;function ___cxa_throw(ptr,type,destructor){var info=new ExceptionInfo(ptr);info.init(type,destructor);exceptionLast=ptr;uncaughtExceptionCount++;throw ptr}function _abort(){abort("")}function _emscripten_memcpy_big(dest,src,num){HEAPU8.copyWithin(dest,src,src+num)}function abortOnCannotGrowMemory(requestedSize){abort("OOM")}function _emscripten_resize_heap(requestedSize){var oldSize=HEAPU8.length;requestedSize=requestedSize>>>0;abortOnCannotGrowMemory(requestedSize)}function getRandomDevice(){if(typeof crypto==="object"&&typeof crypto["getRandomValues"]==="function"){var randomBuffer=new Uint8Array(1);return function(){crypto.getRandomValues(randomBuffer);return randomBuffer[0]}}else if(ENVIRONMENT_IS_NODE){try{var crypto_module=require("crypto");return function(){return crypto_module["randomBytes"](1)[0]}}catch(e){}}return function(){abort("randomDevice")}}function _getentropy(buffer,size){if(!_getentropy.randomDevice){_getentropy.randomDevice=getRandomDevice()}for(var i=0;i<size;i++){HEAP8[buffer+i>>0]=_getentropy.randomDevice()}return 0}var asmLibraryArg={"c":___cxa_allocate_exception,"b":___cxa_throw,"a":_abort,"d":_emscripten_memcpy_big,"e":_emscripten_resize_heap,"f":_getentropy};var asm=createWasm();var ___wasm_call_ctors=Module["___wasm_call_ctors"]=function(){return(___wasm_call_ctors=Module["___wasm_call_ctors"]=Module["asm"]["h"]).apply(null,arguments)};var _malloc=Module["_malloc"]=function(){return(_malloc=Module["_malloc"]=Module["asm"]["i"]).apply(null,arguments)};var _get_other_color=Module["_get_other_color"]=function(){return(_get_other_color=Module["_get_other_color"]=Module["asm"]["j"]).apply(null,arguments)};var _get_last_vector_length=Module["_get_last_vector_length"]=function(){return(_get_last_vector_length=Module["_get_last_vector_length"]=Module["asm"]["k"]).apply(null,arguments)};var _create_chess_game=Module["_create_chess_game"]=function(){return(_create_chess_game=Module["_create_chess_game"]=Module["asm"]["l"]).apply(null,arguments)};var _is_valid_game=Module["_is_valid_game"]=function(){return(_is_valid_game=Module["_is_valid_game"]=Module["asm"]["m"]).apply(null,arguments)};var _game_get_turn=Module["_game_get_turn"]=function(){return(_game_get_turn=Module["_game_get_turn"]=Module["asm"]["n"]).apply(null,arguments)};var _game_next_turn=Module["_game_next_turn"]=function(){return(_game_next_turn=Module["_game_next_turn"]=Module["asm"]["o"]).apply(null,arguments)};var _game_set_turn=Module["_game_set_turn"]=function(){return(_game_set_turn=Module["_game_set_turn"]=Module["asm"]["p"]).apply(null,arguments)};var _game_move_piece=Module["_game_move_piece"]=function(){return(_game_move_piece=Module["_game_move_piece"]=Module["asm"]["q"]).apply(null,arguments)};var _game_is_check=Module["_game_is_check"]=function(){return(_game_is_check=Module["_game_is_check"]=Module["asm"]["r"]).apply(null,arguments)};var _game_is_stalemate=Module["_game_is_stalemate"]=function(){return(_game_is_stalemate=Module["_game_is_stalemate"]=Module["asm"]["s"]).apply(null,arguments)};var _game_is_checkmate=Module["_game_is_checkmate"]=function(){return(_game_is_checkmate=Module["_game_is_checkmate"]=Module["asm"]["t"]).apply(null,arguments)};var _game_get_valid_moves=Module["_game_get_valid_moves"]=function(){return(_game_get_valid_moves=Module["_game_get_valid_moves"]=Module["asm"]["u"]).apply(null,arguments)};var _game_pawn_promotion_available=Module["_game_pawn_promotion_available"]=function(){return(_game_pawn_promotion_available=Module["_game_pawn_promotion_available"]=Module["asm"]["v"]).apply(null,arguments)};var _game_promote_pawn=Module["_game_promote_pawn"]=function(){return(_game_promote_pawn=Module["_game_promote_pawn"]=Module["asm"]["w"]).apply(null,arguments)};var _game_get_move_history=Module["_game_get_move_history"]=function(){return(_game_get_move_history=Module["_game_get_move_history"]=Module["asm"]["x"]).apply(null,arguments)};var _game_get_last_move=Module["_game_get_last_move"]=function(){return(_game_get_last_move=Module["_game_get_last_move"]=Module["asm"]["y"]).apply(null,arguments)};var _game_undo_move=Module["_game_undo_move"]=function(){return(_game_undo_move=Module["_game_undo_move"]=Module["asm"]["z"]).apply(null,arguments)};var _game_get_piece=Module["_game_get_piece"]=function(){return(_game_get_piece=Module["_game_get_piece"]=Module["asm"]["A"]).apply(null,arguments)};var _game_get_pieces=Module["_game_get_pieces"]=function(){return(_game_get_pieces=Module["_game_get_pieces"]=Module["asm"]["B"]).apply(null,arguments)};var _game_reset=Module["_game_reset"]=function(){return(_game_reset=Module["_game_reset"]=Module["asm"]["C"]).apply(null,arguments)};var _delete_chess_game=Module["_delete_chess_game"]=function(){return(_delete_chess_game=Module["_delete_chess_game"]=Module["asm"]["D"]).apply(null,arguments)};var _create_chess_engine=Module["_create_chess_engine"]=function(){return(_create_chess_engine=Module["_create_chess_engine"]=Module["asm"]["E"]).apply(null,arguments)};var _is_valid_engine=Module["_is_valid_engine"]=function(){return(_is_valid_engine=Module["_is_valid_engine"]=Module["asm"]["F"]).apply(null,arguments)};var _engine_get_level=Module["_engine_get_level"]=function(){return(_engine_get_level=Module["_engine_get_level"]=Module["asm"]["G"]).apply(null,arguments)};var _engine_set_level=Module["_engine_set_level"]=function(){return(_engine_set_level=Module["_engine_set_level"]=Module["asm"]["H"]).apply(null,arguments)};var _engine_generate_move=Module["_engine_generate_move"]=function(){return(_engine_generate_move=Module["_engine_generate_move"]=Module["asm"]["I"]).apply(null,arguments)};var _engine_get_number_moves=Module["_engine_get_number_moves"]=function(){return(_engine_get_number_moves=Module["_engine_get_number_moves"]=Module["asm"]["J"]).apply(null,arguments)};var _delete_chess_engine=Module["_delete_chess_engine"]=function(){return(_delete_chess_engine=Module["_delete_chess_engine"]=Module["asm"]["K"]).apply(null,arguments)};var _free=Module["_free"]=function(){return(_free=Module["_free"]=Module["asm"]["M"]).apply(null,arguments)};var calledRun;function ExitStatus(status){this.name="ExitStatus";this.message="Program terminated with exit("+status+")";this.status=status}dependenciesFulfilled=function runCaller(){if(!calledRun)run();if(!calledRun)dependenciesFulfilled=runCaller};function run(args){args=args||arguments_;if(runDependencies>0){return}preRun();if(runDependencies>0){return}function doRun(){if(calledRun)return;calledRun=true;Module["calledRun"]=true;if(ABORT)return;initRuntime();if(Module["onRuntimeInitialized"])Module["onRuntimeInitialized"]();postRun()}if(Module["setStatus"]){Module["setStatus"]("Running...");setTimeout(function(){setTimeout(function(){Module["setStatus"]("")},1);doRun()},1)}else{doRun()}}Module["run"]=run;if(Module["preInit"]){if(typeof Module["preInit"]=="function")Module["preInit"]=[Module["preInit"]];while(Module["preInit"].length>0){Module["preInit"].pop()()}}run();
// TODO: documentation

// TODO: prob should convert to chars
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

    pawnPromotionAvailable(x, y) {
        return Module._game_pawn_promotion_available(this._gameIdAddress, x, y)
    }

    promotePawn(x, y, type) {
        return Module._game_promote_pawn(this._gameIdAddress, x, y, type.charCodeAt(0))
    }

    getMoveHistory() {
        const address = Module._game_get_move_history(this._gameIdAddress)
        if (address == 0) return []
        const totalMoves = Module._get_last_vector_length(this._gameIdAddress)
        let arr = stringArrayFromMemory(address, totalMoves, 6)
        for (let i = 0; i < arr.length; i++) {
            if ((arr[i][2] == "-" || arr[i][2] == "x") && ("RNBQ".indexOf(arr[i][6])) != -1) {
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
        const arr = intArrayFromMemory(address, 6)
        let move = {
            x: arr[0],
            y: arr[1],
            x2: arr[2],
            y2: arr[3],
            movesConsidered: arr[4],
            promoteTo: String.fromCharCode(arr[5])
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