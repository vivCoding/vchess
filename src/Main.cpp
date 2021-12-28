#include <iostream>
#include "Engine.h"
using namespace std;


int main() {
    ChessEngine chess(4);
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
        cout << "Type next move or exit: ";
        getline(cin, input);
        if (input == "exit") {
            cout << "Exited!\n";
            break;
        } else if (input == "help") {
            cout << "-----\nHELP:\nType \"exit\" to exit program, or \"help\" to bring up this menu.\nType \"reset\" to reset the game.\n";
            cout << "\nMOVES:\nMoves should be in format [a-h][1-8] [a-h][1-8]\nExample: b1 c3 (move piece at b1 to c3)\n\n";
            show_board = false;
        } else if (input == "reset") {
            chess.reset_game();
            cout << "Game reset with chess level " << chess.get_level() << "!\n";
            show_board = true;
        } else {
            if (input.length() != 5 || input[2] != ' ') {
                cout << "Invalid input! Type \"help\" for more info!\n";
                show_board = false;
            } else {
                show_board = false;
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
