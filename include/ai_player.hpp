#pragma once
#include "tictactoe.hpp"
#include <vector>

std::vector<std::pair<int, int>> actions(const char board[ROWS][COLS]);
bool terminal(const char board[ROWS][COLS]);
int utility(const char board[ROWS][COLS]);
std::pair<int, int> minimax(const char board[ROWS][COLS], char current_player);
int max_value(char board[ROWS][COLS]);
int min_value(char board[ROWS][COLS]);
