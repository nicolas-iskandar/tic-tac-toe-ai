#include "ai_player.hpp"
#include <cstring>
#include <vector>

using namespace std;

vector<pair<int, int>> actions(const char board[ROWS][COLS])
{
    vector<pair<int, int>> moves;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            if (board[r][c] != 'X' && board[r][c] != 'O')
                moves.push_back({r, c});
    return moves;
}

bool terminal(const char board[ROWS][COLS])
{
    return get_winner(board) || board_is_full(board);
}

int utility(const char board[ROWS][COLS])
{
    char win = get_winner(board);
    if (win == 'X')
        return 1;
    else if (win == 'O')
        return -1;
    return 0;
}

pair<int, int> minimax(const char board[ROWS][COLS], char current_player)
{
    if (terminal(board))
        return {-1, -1};

    pair<int, int> best_move = {-1, -1};

    if (current_player == 'X')
    {
        int best_val = numeric_limits<int>::min();
        for (auto move : actions(board))
        {
            char new_board[ROWS][COLS];
            memcpy(new_board, board, sizeof(new_board));
            new_board[move.first][move.second] = current_player;
            int val = min_value(new_board);
            if (val > best_val)
            {
                best_val = val;
                best_move = move;
            }
        }
    }
    else
    {
        int best_val = numeric_limits<int>::max();
        for (auto move : actions(board))
        {
            char new_board[ROWS][COLS];
            memcpy(new_board, board, sizeof(new_board));
            new_board[move.first][move.second] = current_player;
            int val = max_value(new_board);
            if (val < best_val)
            {
                best_val = val;
                best_move = move;
            }
        }
    }

    return best_move;
}

int max_value(char board[ROWS][COLS])
{
    if (terminal(board))
        return utility(board);
    int v = numeric_limits<int>::min();
    for (auto move : actions(board))
    {
        char new_board[ROWS][COLS];
        memcpy(new_board, board, sizeof(new_board));
        new_board[move.first][move.second] = 'X';
        v = max(v, min_value(new_board));
    }
    return v;
}

int min_value(char board[ROWS][COLS])
{
    if (terminal(board))
        return utility(board);
    int v = numeric_limits<int>::max();
    for (auto move : actions(board))
    {
        char new_board[ROWS][COLS];
        memcpy(new_board, board, sizeof(new_board));
        new_board[move.first][move.second] = 'O';
        v = min(v, max_value(new_board));
    }
    return v;
}
