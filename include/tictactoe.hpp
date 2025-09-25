#pragma once
#include <limits>
#include <string>
#include <vector>

const int ROWS = 3;
const int COLS = 3;

void print_board(const char board[ROWS][COLS]);
int read(const std::string &prompt);
void fill(char board[ROWS][COLS], const int &row, const int &col,
          char &current_player_turn);
bool board_is_full(const char board[ROWS][COLS]);
bool is_valid_player(const char &player);
char get_winner(const char board[ROWS][COLS]);
bool row_contains_winner(const char row[COLS]);
bool col_contains_winner(const char board[ROWS][COLS], const int &c);
bool diagonal_contains_winner(const char board[ROWS][COLS]);

char player_turn(const char board[ROWS][COLS]);
std::vector<std::pair<int, int>> actions(const char board[ROWS][COLS]);
bool terminal(const char board[ROWS][COLS]);
int utility(const char board[ROWS][COLS]);
std::pair<int, int> minimax(const char board[ROWS][COLS], char current_player);
int max_value(char board[ROWS][COLS]);
int min_value(char board[ROWS][COLS]);
