#include "tictactoe.hpp"
#include <iostream>

using namespace std;

int main()
{
    char board[ROWS][COLS]{};
    char current_player = player_turn(board);

    cout << "Welcome to Tic Tac Toe!\n";

    while (!terminal(board))
    {

        print_board(board);

        pair<int, int> move;
        if (current_player == 'O')
        {
            move = minimax(board, current_player);
            cout << "AI chooses: " << move.first + 1 << "," << move.second + 1
                 << "\n";
        }
        else
        {
            int r = read("Enter row (1-3): ");
            int c = read("Enter col (1-3): ");
            move = {r - 1, c - 1};
        }

        fill(board, move.first, move.second, current_player);
        current_player = player_turn(board);
    }

    print_board(board);
    char win = get_winner(board);
    if (win)
        cout << "Winner: " << win << "\n";
    else
        cout << "Draw!\n";

    return 0;
}
