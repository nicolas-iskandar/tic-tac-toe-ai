#include "tictactoe.hpp"
#include <iostream>

using namespace std;

void print_board(const char board[ROWS][COLS])
{
    cout << '\n';
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (board[r][c] == 'X' || board[r][c] == 'O')
                cout << board[r][c];
            else
                cout << ' ';
            if (c < COLS - 1)
                cout << '|';
        }
        cout << "\n";
        if (r < ROWS - 1)
            cout << "-+-+-\n";
    }
    cout << "\n";
}

int read(const string &prompt)
{
    int number{};
    while (true)
    {
        cout << prompt;
        cin >> number;
        if (cin.fail() || number < 1 || number > 3)
        {
            cout << "Invalid\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return number;
    }
}

void fill(char board[ROWS][COLS], const int &row, const int &col,
          char &current_player_turn)
{
    const char current_cell = board[row][col];
    if (current_cell == 'X' || current_cell == 'O')
    {
        cout << "Invalid! Please enter an empty cell\n";
        return;
    }
    board[row][col] = current_player_turn;
}

bool board_is_full(const char board[ROWS][COLS])
{
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            if (!is_valid_player(board[r][c]))
                return false;
    return true;
}

bool is_valid_player(const char &player)
{
    return player == 'X' || player == 'O';
}

char get_winner(const char board[ROWS][COLS])
{
    for (int r = 0; r < ROWS; r++)
        if (row_contains_winner(board[r]))
            return board[r][0];

    for (int c = 0; c < COLS; c++)
        if (col_contains_winner(board, c))
            return board[0][c];

    if (diagonal_contains_winner(board))
        return board[1][1];

    return 0;
}

bool row_contains_winner(const char row[COLS])
{
    return row[0] != 0 && row[0] == row[1] && row[1] == row[2];
}

bool col_contains_winner(const char board[ROWS][COLS], const int &c)
{
    return board[0][c] != 0 && board[0][c] == board[1][c] &&
           board[1][c] == board[2][c];
}

bool diagonal_contains_winner(const char board[ROWS][COLS])
{
    return (board[0][0] != 0 && board[0][0] == board[1][1] &&
            board[1][1] == board[2][2]) ||
           (board[0][2] != 0 && board[0][2] == board[1][1] &&
            board[1][1] == board[2][0]);
}

char player_turn(const char board[ROWS][COLS])
{
    int X_count = 0, O_count = 0;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
        {
            if (board[r][c] == 'X')
                X_count++;
            else if (board[r][c] == 'O')
                O_count++;
        }
    return X_count > O_count ? 'O' : 'X';
}
