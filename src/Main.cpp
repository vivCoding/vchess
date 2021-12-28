#include <iostream>
#include "Engine.h"
using namespace std;


int main() {
    ChessEngine chess(5);
    string input = "";
    string cols = "abcdefgh";
    bool show_board = true;

    while (input != "exit") {
        if (show_board) {
            chess.print_board();
        }
        if (chess.get_turn() == BLACK && !chess.is_checkmate(BLACK)) {
            Move move = chess.generate_move(BLACK);
            chess.move_piece(move);
            cout << "BLACK MOVE: " << move.as_string() << endl;
            show_board = true;
            continue;
        }
        cout << "Type next move or command (\"help\" for all commands): ";
        getline(cin, input);
        if (input == "exit") {
            cout << "Exited!\n";
            break;
        } else if (input == "help") {
            cout << "-----" << endl << "COMMANDS:" << endl;
            cout << "\tType \"undo\" to undo the last move." << endl;
            cout << "\tType \"history\" to view move history." << endl;
            cout << "\tType \"reset\" to reset the game.\n";
            cout << "\tType \"print\" to re-print the board.\n";
            cout << "\tType \"exit\" to exit program." << endl;
            cout << "\tType \"help\" to bring up this menu.\n";
            cout << "MOVES" << endl;
            cout << "\tMoves should be in format [a-h][1-8] [a-h][1-8]" << endl;
            cout << "\tExample: b1 c3 (move piece at b1 to c3)\n\n";
            show_board = false;
        } else if (input == "reset") {
            chess.reset_game();
            cout << "Game reset with chess level " << chess.get_level() << "!\n";
            show_board = true;
        } else if (input == "undo") {
            for (int i = 0; i < 2; i++) {
                Move* m = chess.peek_history_back();
                if (m != NULL) {
                    cout << "Undo move " << m->as_string() << " success!" << endl;
                    chess.undo_move();
                    chess.next_turn();
                    cout << "size: " << chess.move_history_size() << endl;
                } else {
                    cout << "No moves to undo!" << endl;
                }
            }
            show_board = true;
        } else if(input == "print") {
            show_board = true;
        } else if (input == "history") {
            int history_size = chess.move_history_size();
            if (history_size == 0) {
                cout << "No moves made yet!" << endl;
            } else {
                for (int i = 0; i < history_size; i++) {
                    Move* m = chess.peek_history(i);
                    cout << i + 1 << ") " << (char) m->piece_moved->color << ": " << m->as_string() << endl;
                }
            }
            show_board = false;
        } else {
            show_board = false;
            if (input.length() != 5 || input[2] != ' ') {
                cout << "Invalid input! Type \"help\" for more info!\n";
            } else {
                int px = cols.find(input[0]);
                int py = atoi(&input[1]);
                int nx = cols.find(input[3]);
                int ny = atoi(&input[4]);
                if (px == -1 || py == 0 || nx == -1 || ny == 0) {
                    cout << "Invalid input! Type \"help\" for more info!\n";
                    continue;
                } else {
                    if (chess.move_piece(px, py - 1, nx, ny - 1)) {
                        show_board = true;
                    } else cout << "Invalid move!" << endl;
                }
            }
        }
    }
    return 0;
}
