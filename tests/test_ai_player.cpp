#include "ai_player.hpp"
#include "tictactoe.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <vector>

using namespace std;

TEST(AIPlayerTest, ActionsEmptyBoard)
{
    char board[ROWS][COLS] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    vector<pair<int, int>> moves = actions(board);

    EXPECT_EQ(moves.size(), 9);
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            EXPECT_TRUE(find(moves.begin(), moves.end(), make_pair(r, c)) !=
                        moves.end());
}

TEST(AIPlayerTest, ActionsPartialBoard)
{
    char board[ROWS][COLS] = {{'X', 0, 'O'}, {0, 'X', 0}, {0, 0, 0}};
    vector<pair<int, int>> moves = actions(board);

    EXPECT_EQ(moves.size(), 6);

    vector<pair<int, int>> expected = {{0, 1}, {1, 0}, {1, 2},
                                       {2, 0}, {2, 1}, {2, 2}};
    for (const auto &move : expected)
        EXPECT_TRUE(find(moves.begin(), moves.end(), move) != moves.end());

    EXPECT_TRUE(find(moves.begin(), moves.end(), make_pair(0, 0)) ==
                moves.end());
    EXPECT_TRUE(find(moves.begin(), moves.end(), make_pair(0, 2)) ==
                moves.end());
    EXPECT_TRUE(find(moves.begin(), moves.end(), make_pair(1, 1)) ==
                moves.end());
}

TEST(AIPlayerTest, ActionsFullBoard)
{
    char board[ROWS][COLS] = {
        {'X', 'O', 'X'}, {'O', 'X', 'O'}, {'O', 'X', 'O'}};
    vector<pair<int, int>> moves = actions(board);

    EXPECT_EQ(moves.size(), 0);
}

TEST(AIPlayerTest, ActionsOneMove)
{
    char board[ROWS][COLS] = {{'X', 'O', 'X'}, {'O', 'X', 'O'}, {'O', 'X', 0}};
    vector<pair<int, int>> moves = actions(board);

    EXPECT_EQ(moves.size(), 1);
    EXPECT_EQ(moves[0], make_pair(2, 2));
}

TEST(AIPlayerTest, TerminalEmptyBoard)
{
    char board[ROWS][COLS] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_FALSE(terminal(board));
}

TEST(AIPlayerTest, TerminalWinningBoard)
{
    char board[ROWS][COLS] = {{'X', 'X', 'X'}, {0, 'O', 0}, {'O', 0, 0}};
    EXPECT_TRUE(terminal(board));
}

TEST(AIPlayerTest, TerminalFullBoard)
{
    char board[ROWS][COLS] = {
        {'X', 'O', 'X'}, {'X', 'O', 'O'}, {'O', 'X', 'X'}};
    EXPECT_TRUE(terminal(board));
}

TEST(AIPlayerTest, TerminalGameInProgress)
{
    char board[ROWS][COLS] = {{'X', 'O', 0}, {0, 'X', 0}, {0, 0, 'O'}};
    EXPECT_FALSE(terminal(board));
}

TEST(AIPlayerTest, UtilityXWins)
{
    char board[ROWS][COLS] = {{'X', 'X', 'X'}, {'O', 'O', 0}, {0, 0, 0}};
    EXPECT_EQ(utility(board), 1);
}

TEST(AIPlayerTest, UtilityOWins)
{
    char board[ROWS][COLS] = {{'O', 'O', 'O'}, {'X', 'X', 0}, {0, 0, 0}};
    EXPECT_EQ(utility(board), -1);
}

TEST(AIPlayerTest, UtilityDraw)
{
    char board[ROWS][COLS] = {
        {'X', 'O', 'X'}, {'X', 'O', 'O'}, {'O', 'X', 'X'}};
    EXPECT_EQ(utility(board), 0);
}

TEST(AIPlayerTest, UtilityNoWinner)
{
    char board[ROWS][COLS] = {{'X', 'O', 0}, {0, 'X', 0}, {0, 0, 0}};
    EXPECT_EQ(utility(board), 0);
}

TEST(AIPlayerTest, MaxValueTerminalWin)
{
    char board[ROWS][COLS] = {{'X', 'X', 'X'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(max_value(board), 1);
}

TEST(AIPlayerTest, MaxValueTerminalLoss)
{
    char board[ROWS][COLS] = {{'O', 'O', 'O'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(max_value(board), -1);
}

TEST(AIPlayerTest, MinValueTerminalWin)
{
    char board[ROWS][COLS] = {{'O', 'O', 'O'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(min_value(board), -1);
}

TEST(AIPlayerTest, MinValueTerminalLoss)
{
    char board[ROWS][COLS] = {{'X', 'X', 'X'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(min_value(board), 1);
}

TEST(AIPlayerTest, MinimaxWinningMoveX)
{
    char board[ROWS][COLS] = {{'X', 'X', 0}, {'O', 'O', 0}, {0, 0, 0}};
    pair<int, int> move = minimax(board, 'X');
    EXPECT_EQ(move, make_pair(0, 2));
}

TEST(AIPlayerTest, MinimaxWinningMoveO)
{
    char board[ROWS][COLS] = {{'X', 'X', 'O'}, {'X', 'O', 0}, {0, 0, 0}};
    pair<int, int> move = minimax(board, 'O');
    EXPECT_EQ(move, make_pair(2, 0));
}

TEST(AIPlayerTest, MinimaxBlockingMoveX)
{
    char board[ROWS][COLS] = {{'X', 'X', 0}, {'O', 0, 0}, {0, 0, 0}};
    pair<int, int> move = minimax(board, 'O');
    EXPECT_EQ(move, make_pair(0, 2));
}

TEST(AIPlayerTest, MinimaxTerminalBoard)
{
    char board[ROWS][COLS] = {{'X', 'X', 'X'}, {'O', 'O', 0}, {0, 0, 0}};
    pair<int, int> move = minimax(board, 'X');
    EXPECT_EQ(move, make_pair(-1, -1));
}
