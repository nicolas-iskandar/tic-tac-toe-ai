#include "tictactoe.hpp"
#include "gtest/gtest.h"

TEST(BoardTest, RowWinner)
{
    char board[ROWS][COLS] = {{'X', 'X', 'X'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(get_winner(board), 'X');
}

TEST(BoardTest, ColWinner)
{
    char board[ROWS][COLS] = {{'O', 0, 0}, {'O', 0, 0}, {'O', 0, 0}};
    EXPECT_EQ(get_winner(board), 'O');
}

TEST(BoardTest, DiagonalWinner)
{
    char board[ROWS][COLS] = {{'X', 0, 0}, {0, 'X', 0}, {0, 0, 'X'}};
    EXPECT_EQ(get_winner(board), 'X');
}

TEST(BoardTest, Draw)
{
    char board[ROWS][COLS] = {
        {'X', 'O', 'X'}, {'X', 'O', 'O'}, {'O', 'X', 'X'}};
    EXPECT_TRUE(board_is_full(board));
    EXPECT_EQ(get_winner(board), 0);
}

TEST(BoardTest, PlayerTurn)
{
    char board[ROWS][COLS] = {{'X', 'O', 'X'}, {0, 'O', 0}, {0, 0, 0}};
    EXPECT_EQ(player_turn(board), 'X');
}

TEST(AITest, OShouldWin)
{
    char board[ROWS][COLS] = {{'O', 'X', 'O'}, {'X', 'O', 0}, {'X', 'X', 0}};
    auto move = minimax(board, 'O');
    EXPECT_EQ(move.first, 2);
    EXPECT_EQ(move.second, 2);
}

TEST(AITest, OShouldBlockX)
{
    char board[ROWS][COLS] = {{'X', 'X', 0}, {'O', 0, 0}, {0, 0, 0}};
    auto move = minimax(board, 'O');
    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 2);
}

TEST(AITest, TerminalDetection)
{
    char board[ROWS][COLS] = {
        {'X', 'O', 'X'}, {'O', 'X', 'O'}, {'O', 'X', 'X'}};
    EXPECT_TRUE(terminal(board));
    EXPECT_EQ(utility(board), 1);
}
