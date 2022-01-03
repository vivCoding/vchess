#include "../engine/Engine.h"
#include "../engine/Game.h"
#include "Exports.h"

// TODO: break it up into different files ffs

static int last_vector_length = 0;

char* generate_id() {
    string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, chars.length() - 1);
    char* id = (char*) malloc(sizeof(char) * 9);
    for (int i = 0; i < 8; i++) {
        id[i] = chars[uni(rng)];
    }
    id[8] = '\0';
    return id;
}

char get_other_color(char color) {
    return color == 'w' ? 'b' : 'w';
}

Color color_from_char(char c) {
    return c == 'w' ? WHITE : BLACK;
}

bool is_valid_color(char c) {
    return c == 'w' || c == 'b';
}

int get_last_vector_length() {
    return last_vector_length;
}

#pragma region WASM_CHESS_GAME

static unordered_map<char*, ChessGame*> games;

// Returns game id string
char* create_chess_game() {
    char* game_id = generate_id();
    ChessGame* game = new ChessGame();
    games.insert(pair<char*, ChessGame*>(game_id, game));
    return game_id;
}

bool is_valid_game(char* game_id) {
    return games.find(game_id) != games.end();
}

// Returns char representing color ('w' or 'b'). If specified game doesn't exist, return 0
char game_get_turn(char* game_id) {
    if (is_valid_game(game_id)) {
        return games.at(game_id)->get_turn();
    }
    return 0;
}

// Returns true if game exists and success, false if fails
bool game_next_turn(char* game_id) {
    if (is_valid_game(game_id)) {
        games.at(game_id)->next_turn();
        return true;
    }
    return false;
}

// Returns true if game exists and success, false if fails
bool game_set_turn(char* game_id, char color) {
    if (is_valid_game(game_id) && is_valid_color(color)) {
        games.at(game_id)->set_turn(color_from_char(color));
        return true;
    }
    return false;
}

// Returns 1 if success, 0 if invalid move, -1 if game not found
bool game_move_piece(char* game_id, int x, int y, int x2, int y2) {
    if (is_valid_game(game_id)) {
        return games.at(game_id)->move_piece(x, y, x2, y2);
    }
    return false;
}

// Returns 1 if success, 0 if invalid move, -1 if game not found or invalid color
bool game_is_check(char* game_id, char color) {
    if (is_valid_game(game_id) && is_valid_color(color)) {
        return games.at(game_id)->is_check(color_from_char(color));
    }
    return false;
}

// Returns 1 if success, 0 if invalid move, -1 if game not found or invalid color
bool game_is_stalemate(char* game_id, char color) {
    if (is_valid_game(game_id) && is_valid_color(color)) {
        return games.at(game_id)->is_stalemate(color_from_char(color));
    }
    return false;
}

// Returns 1 if success, 0 if invalid move, -1 if game not found or invalid color
bool game_is_checkmate(char* game_id, char color) {
    if (is_valid_game(game_id) && is_valid_color(color)) {
        return games.at(game_id)->is_checkmate(color_from_char(color));
    }
    return false;
}

// Returns pointer to double array of final destination vectors: [[x, y], [x2, y2], [x3, y3]]
// If game doesn't exist, return 0
int** game_get_valid_moves(char* game_id, int x, int y) {
    if (is_valid_game(game_id)) {
        vector<Move> valid_moves = games.at(game_id)->get_valid_moves(x, y);
        int n = valid_moves.size();
        int** arr = (int**) malloc(sizeof(int*) * n);
        last_vector_length = n;
        for (int i = 0; i < n; i++) {
            arr[i] = (int*) malloc(sizeof(int) * 2);
            arr[i][0] = valid_moves.at(i).move_to.x;
            arr[i][1] = valid_moves.at(i).move_to.y;
        }
        return arr;
    }
    return 0;
}

// Return array of moves in string format. If game doesn't exist return 0
char** game_get_move_history(char* game_id) {
    if (is_valid_game(game_id)) {
        ChessGame* game = games.at(game_id);
        int n = game->move_history_size();
        char** arr = (char**) malloc(sizeof(char*) * n);
        last_vector_length = n;
        for (int i = 0; i < n; i++) {
            arr[i] = (char*) malloc(sizeof(char) * 6);
            string s = game->peek_history(i)->as_string();
            for (int j = 0; j < s.length(); j++) {
                arr[i][j] = s[j];
            }
        }
        return arr;
    }
    return 0;
}

// Return last move made in string format. If game doesn't exist return 0
const char* game_get_last_move(char* game_id) {
    if (is_valid_game(game_id)) {
        string last_move = games.at(game_id)->peek_history_back()->as_string();
        const char* c = last_move.c_str();
        return c;
    }
    return 0;
}

// Return true if game exists and successful. false if game doesn't exist
bool game_undo_move(char* game_id) {
    if (is_valid_game(game_id)) {
        games.at(game_id)->undo_move();
        return true;
    }
    return false;
}

// Return piece information at (x, y) in array format: [(int) type, (int) color, materialValue, position.x, position.y]
int* game_get_piece(char* game_id, int x, int y) {
    if (is_valid_game(game_id)) {
        Piece* p = games.at(game_id)->board->get_piece(x, y);
        if (p == NULL) return 0;
        int* arr = (int*) malloc(sizeof(int) * 5);
        arr[0] = (int) p->type;
        arr[1] = (int) p->color;
        arr[2] = p->get_material_value();
        arr[3] = p->position.x;
        arr[4] = p->position.y;
        return arr;
    }
    return 0;
}

// Return array of pieces information at (x, y) in array format:
// [ [(int) type, (int) color, materialValue, position.x, position.y], ... ]
int** game_get_pieces(char* game_id, char color) {
    if (is_valid_game(game_id) && is_valid_color(color)) {
        vector<Piece*> pieces = games.at(game_id)->board->get_pieces(color_from_char(color));
        int n = pieces.size();
        int** arr = (int**) malloc(sizeof(int*) * n);
        last_vector_length = n;
        for (int i = 0; i < n; i++) {
            arr[i] = (int*) malloc(sizeof(int) * 5);
            Piece* p = pieces.at(i);
            arr[i][0] = (int) p->type;
            arr[i][1] = (int) p->color;
            arr[i][2] = p->get_material_value();
            arr[i][3] = p->position.x;
            arr[i][4] = p->position.y;
        }
        return arr;
    }
    return 0;
}

// Returns true if game exists, false if it doesn't
bool game_reset(char* game_id) {
    if (is_valid_game(game_id)) {
        games.at(game_id)->reset_game();
        return true;
    }
    return false;
}

// Returns true if game exists, false if it doesn't
bool delete_chess_game(char* game_id) {
    if (is_valid_game(game_id)) {
        delete games.at(game_id);
        games.erase(game_id);
        return true;
    }
    return false;
}

#pragma endregion WASM_CHESS_GAME

#pragma region WASM_CHESS_ENGINE

static unordered_map<char*, ChessEngine*> engines;

// Returns created engine id
char* create_chess_engine(int level = 0) {
    char* engine_id = generate_id();
    ChessEngine* engine = new ChessEngine(level);
    engines.insert(pair<char*, ChessEngine*>(engine_id, engine));
    return engine_id;
}

bool is_valid_engine(char* engine_id) {
    return engines.find(engine_id) != engines.end();
}

// If specified engine exists, return that engine level. If it doesn't return -1
int engine_get_level(char* engine_id) {
    if (is_valid_engine(engine_id)) {
        return engines.at(engine_id)->get_level();
    }
    return -1;
}

// Returns true if engine exists and success, false if engine doesn't exists
bool engine_set_level(char* engine_id, int new_level) {
    if (is_valid_engine(engine_id)) {
        engines.at(engine_id)->set_level(new_level);
        return true;
    }
    return false;
}

// Returns generated move in array format: [moveFromX, moveFromY, moveToX, moveToY, movesConsidered]
int* engine_generate_move(char* engine_id, char* game_id, char color) {
    if (is_valid_engine(engine_id) && is_valid_game(game_id) && is_valid_color(color)) {
        ChessEngine* engine = engines.at(engine_id);
        Move move = engine->generate_move(color_from_char(color), games.at(game_id));
        int* arr = (int*) malloc(sizeof(int) * 5);
        arr[0] = move.move_from.x;
        arr[1] = move.move_from.y;
        arr[2] = move.move_to.x;
        arr[3] = move.move_to.y;
        arr[4] = engine->get_moves_considered();
        return arr;
    }
    return 0;
}

// Returns -1 if engine doesn't exist
int engine_get_number_moves(char* engine_id) {
    if (is_valid_engine(engine_id)) {
        return engines.at(engine_id)->get_moves_considered();
    }
    return -1;
}

// Returns true if engine exists, false if it doesn't
bool delete_chess_engine(char* engine_id) {
    if (is_valid_engine(engine_id)) {
        delete engines.at(engine_id);
        engines.erase(engine_id);
        return true;
    }
    return false;
}

#pragma endregion WASM_CHESS_ENGINE