#ifndef WASM_EXPORTS_H
#define WASM_EXPORTS_H

#include <emscripten/emscripten.h>

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    int get_last_vector_length();
    EMSCRIPTEN_KEEPALIVE
    char get_other_color(char color);

    EMSCRIPTEN_KEEPALIVE
    char* create_chess_game();
    EMSCRIPTEN_KEEPALIVE
    bool is_valid_game(char* game_id);
    EMSCRIPTEN_KEEPALIVE
    char game_get_turn(char* game_id);
    EMSCRIPTEN_KEEPALIVE
    bool game_next_turn(char* game_id);
    EMSCRIPTEN_KEEPALIVE
    bool game_set_turn(char* game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool game_move_piece(char* game_id, int x, int y, int x2, int y2);
    EMSCRIPTEN_KEEPALIVE
    bool game_is_check(char* game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool game_is_stalemate(char* game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool game_is_checkmate(char* game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    int** game_get_valid_moves(char* game_id, int x, int y);
    EMSCRIPTEN_KEEPALIVE
    char** game_get_move_history(char* game_id);
    EMSCRIPTEN_KEEPALIVE
    const char* game_get_last_move(char* game_id);
    EMSCRIPTEN_KEEPALIVE
    bool game_undo_move(char* game_id);
    EMSCRIPTEN_KEEPALIVE
    int* game_get_piece(char* game_id, int x, int y);
    EMSCRIPTEN_KEEPALIVE
    int** game_get_pieces(char* game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    bool game_reset(char* game_id);
    EMSCRIPTEN_KEEPALIVE
    bool delete_chess_game(char* game_id);

    EMSCRIPTEN_KEEPALIVE
    char* create_chess_engine(int level);
    EMSCRIPTEN_KEEPALIVE
    bool is_valid_engine(char* engine_id);
    EMSCRIPTEN_KEEPALIVE
    int engine_get_level(char* engine_id);
    EMSCRIPTEN_KEEPALIVE
    bool engine_set_level(char* engine_id, int new_level);
    EMSCRIPTEN_KEEPALIVE
    int* engine_generate_move(char* engine_id, char* game_id, char color);
    EMSCRIPTEN_KEEPALIVE
    int engine_get_number_moves(char* engine_id);
    EMSCRIPTEN_KEEPALIVE
    bool delete_chess_engine(char* engine_id);
}

#endif