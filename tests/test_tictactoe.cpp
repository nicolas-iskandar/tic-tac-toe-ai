#include "tictactoe.hpp"
#include "gtest/gtest.h"

TEST(BoardTest, AllRowWinners)
{
    char board1[ROWS][COLS] = {{'O', 'O', 'O'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(get_winner(board1), 'O');

    char board2[ROWS][COLS] = {{0, 0, 0}, {'X', 'X', 'X'}, {0, 0, 0}};
    EXPECT_EQ(get_winner(board2), 'X');

    char board3[ROWS][COLS] = {{0, 0, 0}, {0, 0, 0}, {'O', 'O', 'O'}};
    EXPECT_EQ(get_winner(board3), 'O');
}

TEST(BoardTest, AllColWinners)
{
    char board1[ROWS][COLS] = {{'O', 0, 0}, {'O', 0, 0}, {'O', 0, 0}};
    EXPECT_EQ(get_winner(board1), 'O');

    char board2[ROWS][COLS] = {{0, 'X', 0}, {0, 'X', 0}, {0, 'X', 0}};
    EXPECT_EQ(get_winner(board2), 'X');

    char board3[ROWS][COLS] = {{0, 0, 'O'}, {0, 0, 'O'}, {0, 0, 'O'}};
    EXPECT_EQ(get_winner(board3), 'O');
}

TEST(BoardTest, BothDiagonalWinners)
{
    char board1[ROWS][COLS] = {{'O', 0, 0}, {0, 'O', 0}, {0, 0, 'O'}};
    EXPECT_EQ(get_winner(board1), 'O');

    char board2[ROWS][COLS] = {{0, 0, 'X'}, {0, 'X', 0}, {'X', 0, 0}};
    EXPECT_EQ(get_winner(board2), 'X');
}

TEST(BoardTest, Draw)
{
    char board[ROWS][COLS] = {
        {'X', 'O', 'X'}, {'X', 'O', 'O'}, {'O', 'X', 'X'}};
    EXPECT_TRUE(board_is_full(board));
    EXPECT_EQ(get_winner(board), 0);
}

TEST(BoardTest, EmptyBoard)
{
    char board[ROWS][COLS] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(get_winner(board), 0);
    EXPECT_FALSE(board_is_full(board));
    EXPECT_EQ(player_turn(board), 'X');
}

TEST(BoardTest, PartiallyFilledBoard)
{
    char board[ROWS][COLS] = {{'X', 0, 'O'}, {0, 'X', 0}, {0, 0, 0}};
    EXPECT_EQ(get_winner(board), 0);
    EXPECT_FALSE(board_is_full(board));
}

TEST(BoardTest, PlayerTurnLogic)
{
    char board2[ROWS][COLS] = {{'X', 'O', 0}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(player_turn(board2), 'X');

    char board3[ROWS][COLS] = {{'X', 'O', 'X'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(player_turn(board3), 'O');

    char board4[ROWS][COLS] = {{'O', 'O', 'X'}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(player_turn(board4), 'X');
}

TEST(BoardTest, ValidPlayer)
{
    EXPECT_TRUE(is_valid_player('X'));
    EXPECT_TRUE(is_valid_player('O'));
    EXPECT_FALSE(is_valid_player('A'));
    EXPECT_FALSE(is_valid_player('x'));
    EXPECT_FALSE(is_valid_player('o'));
    EXPECT_FALSE(is_valid_player(0));
    EXPECT_FALSE(is_valid_player(' '));
}

TEST(BoardTest, BoardFullScenarios)
{
    char empty[ROWS][COLS] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_FALSE(board_is_full(empty));

    char one_filled[ROWS][COLS] = {{'X', 0, 0}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_FALSE(board_is_full(one_filled));

    char almost_full[ROWS][COLS] = {
        {'X', 'O', 'X'}, {'O', 'X', 'O'}, {'O', 'X', 0}};
    EXPECT_FALSE(board_is_full(almost_full));

    char full[ROWS][COLS] = {{'X', 'O', 'X'}, {'O', 'X', 'O'}, {'O', 'X', 'O'}};
    EXPECT_TRUE(board_is_full(full));
}

TEST(BoardTest, RowContainsWinner)
{
    char winning_row[COLS] = {'X', 'X', 'X'};
    char mixed_row[COLS] = {'X', 'O', 'X'};
    char empty_row[COLS] = {0, 0, 0};
    char partial_row[COLS] = {'X', 'X', 0};

    EXPECT_TRUE(row_contains_winner(winning_row));
    EXPECT_FALSE(row_contains_winner(mixed_row));
    EXPECT_FALSE(row_contains_winner(empty_row));
    EXPECT_FALSE(row_contains_winner(partial_row));
}

TEST(BoardTest, ColContainsWinner)
{
    char board_col_win[ROWS][COLS] = {
        {'X', 'O', 0}, {'X', 'O', 0}, {'X', 'O', 0}};
    char board_no_win[ROWS][COLS] = {
        {'X', 'O', 0}, {'O', 'X', 0}, {'X', 'O', 0}};

    EXPECT_TRUE(col_contains_winner(board_col_win, 0));
    EXPECT_TRUE(col_contains_winner(board_col_win, 1));
    EXPECT_FALSE(col_contains_winner(board_col_win, 2));
    EXPECT_FALSE(col_contains_winner(board_no_win, 0));
}

TEST(BoardTest, DiagonalContainsWinner)
{
    char main_diag[ROWS][COLS] = {{'X', 0, 0}, {0, 'X', 0}, {0, 0, 'X'}};
    char anti_diag[ROWS][COLS] = {{0, 0, 'O'}, {0, 'O', 0}, {'O', 0, 0}};
    char no_diag[ROWS][COLS] = {{'X', 0, 'O'}, {0, 'O', 0}, {'X', 0, 'X'}};
    char empty_center[ROWS][COLS] = {{'X', 0, 0}, {0, 0, 0}, {0, 0, 'X'}};

    EXPECT_TRUE(diagonal_contains_winner(main_diag));
    EXPECT_TRUE(diagonal_contains_winner(anti_diag));
    EXPECT_FALSE(diagonal_contains_winner(no_diag));
    EXPECT_FALSE(diagonal_contains_winner(empty_center));
}
