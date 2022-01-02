#ifndef WASM_EXPORTS_H
#define WASM_EXPORTS_H

#include <emscripten/emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    int get_last_vector_length();
    EMSCRIPTEN_KEEPALIVE
    char get_other_color(char color);

    EMSCRIPTEN_KEEPALIVE
    const char* create_chess_game();
    EMSCRIPTEN_KEEPALIVE
    bool is_valid_game(string game_id);
    EMSCRIPTEN_KEEPALIVE
    char game_get_turn(string game_id);
    EMSCRIPTEN_KEEPALIVE
    bool game_next_turn(string game_id);
    EMSCRIPTEN_KEEPALIVE
    bool game_set_turn(string game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool game_move_piece(string game_id, int x, int y, int x2, int y2);
    EMSCRIPTEN_KEEPALIVE
    bool game_is_check(string game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool game_is_stalemate(string game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool game_is_checkmate(string game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    int** game_get_valid_moves(string game_id, int x, int y);
    EMSCRIPTEN_KEEPALIVE
    const char** game_get_move_history(string game_id);
    EMSCRIPTEN_KEEPALIVE
    const char* game_get_last_move(string game_id);
    EMSCRIPTEN_KEEPALIVE
    bool game_undo_move(string game_id);
    EMSCRIPTEN_KEEPALIVE
    int* game_get_piece(string game_id, int x, int y);
    EMSCRIPTEN_KEEPALIVE
    int** game_get_pieces(string game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool delete_chess_game(string game_id);

    EMSCRIPTEN_KEEPALIVE
    const char* create_chess_engine(int level);
    EMSCRIPTEN_KEEPALIVE
    bool is_valid_engine(string engine_id);
    EMSCRIPTEN_KEEPALIVE
    int engine_get_level(string engine_id);
    EMSCRIPTEN_KEEPALIVE
    bool engine_set_level(string engine_id, int new_level);
    EMSCRIPTEN_KEEPALIVE
    int* engine_generate_move(char* engine_id, string game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool delete_chess_engine(string engine_id);
}

#endif