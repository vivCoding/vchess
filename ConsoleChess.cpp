/*
 * A simple console program to demonstrate the capabilities of the chess engine
*/

#include <iostream>
#include "engine/Engine.h"
using namespace std;

int main() {
    int level = 4;
    Color player_color = WHITE;
    Color engine_color = BLACK;
    ChessEngine chess_engine(level);
    string input = "";
    string cols = "abcdefgh";
    // determines whether we should print the board on next iteration
    bool show_board = true;

    cout << "Game start with chess engine level " << chess_engine.get_level() << " and player is " << (char) player_color << "!\n";
    while (true) {
        // we only show the board when a new move has been made, a move has been undone, or user commands a re-print
        if (show_board) {
            // print board upside down or not
            chess_engine.print_board(player_color == BLACK);
        }
        // if it's enemy's turn, generate a move
        if (chess_engine.get_turn() == engine_color && !chess_engine.is_checkmate(engine_color)) {
            Move move = chess_engine.generate_move(engine_color, true);
            chess_engine.move_piece(move);
            cout << "BLACK MOVE: " << move.as_string() << endl;
            show_board = true;
            chess_engine.next_turn();
            continue;
        }
        
        cout << "Type next move or command (\"help\" for all commands): ";
        getline(cin, input);

        if (input == "exit") {
            cout << "Exited!\n";
            break;
        } else if (input == "help") {
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
            cout << "\t- \"level <n>\" to set the chess_engine engine level (0 inclusive). Default is 4\n";
            cout << "\t- \"color [w, b]\" to set the player starting color (either w or b). Default is w\n";
            cout << "\t- \"settings\" to show current game settings\n";
            show_board = false;
        } else if (input == "reset") {
            chess_engine.reset_game(level);
            engine_color = chess_engine.get_other_color(player_color);
            cout << "Game reset with chess engine level " << chess_engine.get_level() << " and player is " << (char) player_color << "!\n";
            show_board = true;
        } else if (input == "undo") {
            for (int i = 0; i < 2; i++) {
                Move* m = chess_engine.peek_history_back();
                if (m != NULL) {
                    cout << "Undo move " << m->as_string() << " success!" << endl;
                    chess_engine.undo_move();
                    chess_engine.next_turn();
                    cout << "size: " << chess_engine.move_history_size() << endl;
                } else {
                    cout << "No moves to undo!" << endl;
                    break;
                }
            }
            show_board = true;
        } else if(input == "print") {
            show_board = true;
        } else if (input == "history") {
            int history_size = chess_engine.move_history_size();
            if (history_size == 0) {
                cout << "No moves made yet!" << endl;
            } else {
                for (int i = 0; i < history_size; i++) {
                    Move* m = chess_engine.peek_history(i);
                    cout << i + 1 << ") " << (char) m->piece_moved->color << ": " << m->as_string() << endl;
                }
            }
            show_board = false;
        } else if (input == "settings") {
            cout << "Player color is set to " << (char) player_color << ", chess_engine level set to " << level << endl;
            show_board = false;
        } else if (input.length() >= 7 && input.substr(0, 6) == "level ") {
            level = stoi(input.substr(6));
            cout << "New chess_engine level is " << level << ". Reset game to apply chess_engine level." << endl;
            show_board = false;
        } else if (input.length() == 7 && input.substr(0, 6) == "color ") {
            if (input[6] == 'w') {
                player_color = WHITE;
                cout << "Player color set to w. Reset game to apply new player color" << endl;
            } else if (input[6] == 'b') {
                player_color  = BLACK;
                cout << "Player color set to b. Reset game to apply new player color" << endl;
            } else cout << "Invalid color! Type \"color w\" or \"color b\" to set player color." << endl;
            show_board = false;
        } else {
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
                    bool move_success = chess_engine.move_piece(x, y, x2, y2);
                    if (move_success) {
                        chess_engine.next_turn();
                        show_board = true;
                    } else cout << "Invalid move!" << endl;
                }
            }
        }
    }
    return 0;
}
