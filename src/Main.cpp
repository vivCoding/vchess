#include <iostream>
#include "Engine.h"
using namespace std;


int main() {
    ChessEngine chess;
    string input = "";
    string cols = "abcdefgh";
    bool show_board = true;

    while (input != "exit") {
        if (show_board)
            chess.print_board();
        cout << "Type next move or exit: ";
        getline(cin, input);
        if (input == "exit") {
            cout << "Exited\n";
            return 0;
        } else if (input == "help") {
            cout << "-----\nHELP:\nType \"exit\" to exit program, or \"help\" to bring up this menu.\n";
            cout << "\nMOVES:\nMoves should be in format [a-h][1-8] [a-h][1-8]\nExample: b1 c3 (move piece at b1 to c3)\n\n";
            show_board = false;
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
}