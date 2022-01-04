/*
 * A simple console program to demonstrate the capabilities of the chess engine
 * To compile, follow the README.md instructions, using ConsoleChess.cpp as the main file
*/

#include "engine/Game.h"
#include "engine/Engine.h"
#include <iostream>
using namespace std;

void print_board(ChessGame* game, bool upsidedown);
void print_help_menu();

int main() {
    int level = 1;
    Color player_color = WHITE;
    Color engine_color = BLACK;
    ChessGame game;
    ChessEngine engine(level);
    // used for parsing input
    string cols = "abcdefgh";
    // determines whether we should print the board on next iteration
    bool show_board = true;

    cout << "Game start with chess engine level " << engine.get_level() << " and player is " << (char) player_color << "!\n";
    string input = "";
    while (true) {
        // we only show the board when a new move has been made, a move has been undone, or user commands a re-print
        if (show_board) {
            // print board upside down or not
            print_board(&game, player_color == BLACK);
        }

        if (game.get_turn() == engine_color && !game.is_checkmate(engine_color)) {
            Move move = engine.generate_move(engine_color, &game);
            // Move move = engine.generate_random_move(engine_color, &game);
            game.move_piece(move);
            if (move.type == PAWN_PROMOTION) {
                game.promote_pawn(move.move_to, move.promote_to);
            }
            cout << "Moves considered: " << engine.get_moves_considered() << endl;
            cout << "BLACK MOVE: " << move.as_string() << endl;
            game.next_turn();
            show_board = true;
            continue;
        }

        cout << "Type next move or command (\"help\" for all commands): ";
        getline(cin, input);

        if (input == "exit") {
            cout << "Exited!\n";
            break;
        } else if (input == "help") {
            print_help_menu();
            show_board = false;
        } else if (input == "reset") {
            game.reset_game();
            engine.set_level(level);
            engine_color = get_other_color(player_color);
            cout << "Game reset with chess engine level " << engine.get_level() << " and player is " << (char) player_color << "!\n";
            show_board = true;
        } else if (input == "undo") {
            for (int i = 0; i < 2; i++) {
                Move* m = game.peek_history_back();
                if (m != NULL) {
                    cout << "Undo move " << m->as_string() << " success!\n";
                    game.undo_move();
                    game.next_turn();
                } else {
                    cout << "No moves to undo!\n";
                    break;
                }
            }
            show_board = true;
        } else if (input == "print") {
            show_board = true;
        } else if (input == "history") {
            int history_size = game.move_history_size();
            if (history_size == 0) {
                cout << "No moves made yet!\n";
            } else {
                for (int i = 0; i < history_size; i++) {
                    Move* m = game.peek_history(i);
                    cout << i + 1 << ") " << (char) m->piece_moved->color << ": " << m->as_string() << endl;
                }
            }
            show_board = false;
        } else if (input == "settings") {
            cout << "- Player color is: " << (char) player_color << "\n- Chess engine level: " << level << endl;
            show_board = false;
        } else if (input.length() >= 7 && input.substr(0, 6) == "level ") {
            level = stoi(input.substr(6));
            cout << "New chess engine level is " << level << ". Reset game to apply chess engine level.\n";
            show_board = false;
        } else if (input.length() == 7 && input.substr(0, 6) == "color ") {
            if (input[6] == 'w') {
                player_color = WHITE;
                cout << "Player color set to w. Reset game to apply new player color.\n";
            } else if (input[6] == 'b') {
                player_color  = BLACK;
                cout << "Player color set to b. Reset game to apply new player color.\n";
            } else cout << "Invalid color! Type \"color w\" or \"color b\" to set player color.\n";
            show_board = false;
        } else {
            // parse input for move
            show_board = false;
            if (input.length() != 5 || input[2] != ' ') {
                cout << "Invalid input! Type \"help\" for more info!\n";
            } else {
                int x = cols.find(input[0]);
                int y = atoi(&input[1]) - 1;
                int x2 = cols.find(input[3]);
                int y2 = atoi(&input[4]) - 1;
                // Even though chess_engine.move_piece() will return false if we have invalid input,
                // we'll still make sure we have good input so we can let user know
                if (x == -1 || y < 0 || y > 7 || x2 == -1 || y2 < 0 || y2 > 7) {
                    cout << "Invalid input! Type \"help\" for more info!\n";
                    continue;
                } else {
                    bool move_success = game.move_piece(x, y, x2, y2);
                    if (move_success) {
                        if (game.pawn_promotion_available(x2, y2)) {
                            while (true) {
                                cout << "Promote to (enter N, B, R, Q): ";
                                getline(cin, input);
                                bool found = false;
                                for (PieceType pt : promote_to_pieces) {
                                    if (input[0] == (char) pt) {
                                        game.promote_pawn(x2, y2, pt);
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found) cout << "Invalid promotion piece!\n";
                                else break;
                            }
                        }
                        game.next_turn();
                        show_board = true;
                    } else cout << "Invalid move! Type \"help\" for more info!" << endl;
                }
            }
        }
    }
}

void print_board(ChessGame* game, bool upsidedown) {
    int gap = 25;
    cout << "   ";
    for (int x = 0; x < gap; x++) {
        cout << "-";
    }
    cout << endl;
    int start = upsidedown ? 0 : 7;
    int end = upsidedown ? 8 : -1;
    int step = upsidedown ? 1 : -1;
    for (int y = start; y != end; y += step) {
        cout << y + 1 << " | ";
        for (int x = start; x != end; x += step) {
            Piece* p = game->board->get_piece(upsidedown ? x : 7 - x, upsidedown ? 7 - y : y);
            if (p != NULL) {
                cout << ((char) p->type);
                if (p->color == WHITE) {
                    cout << 'w';
                } else cout << 'b';
            } else cout << ". ";
            cout << " ";
        }
        cout << "|";
        cout << endl;
    }
    cout << "   ";
    for (int x = 0; x < gap; x++) {
        cout << "-";
    }
    cout << endl;
    cout << "    a  b  c  d  e  f  g  h" << endl;
    if (game->get_turn() == WHITE) cout << "WHITE TURN";
    else cout << "BLACK TURN";
    if (game->is_checkmate()) cout << ": CHECKMATE. GAME OVER!";
    else if (game->is_stalemate()) cout << ": CHECKMATE. GAME OVER!";
    else if (game->is_check()) cout << ": CHECK!";
    cout << endl;
}

void print_help_menu() {
    cout << "-----\nCOMMANDS:\n";
    cout << "\t- \"undo\" to undo the last move.\n";
    cout << "\t- \"history\" to view move history.\n";
    cout << "\t- \"reset\" to reset the game.\n";
    cout << "\t- \"print\" to re-print the board.\n";
    cout << "\t- \"exit\" to exit program.\n";
    cout << "\t- \"help\" to bring up this menu.\n";
    cout << "MOVES:\n";
    cout << "\tYou can move a piece by directly typing in the move\n";
    cout << "\tMoves should be in format \"[a-h][1-8] [a-h][1-8]\"\n";
    cout << "\tExample: b1 c3 (move piece at b1 to c3)\n";
    cout << "SETTINGS:\n";
    cout << "\tSettings are applied upon game reset\n";
    cout << "\t- \"level <n>\" to set the chess_engine engine level (0 inclusive). Default is 3\n";
    cout << "\t- \"color [w, b]\" to set the player starting color (either w or b). Default is w\n";
    cout << "\t- \"settings\" to show current game settings\n";
}