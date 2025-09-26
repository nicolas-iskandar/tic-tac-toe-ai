cmake_minimum_required(VERSION 3.10)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(tictactoe main.cpp src/tictactoe.cpp src/ai_player.cpp)

enable_testing()
add_subdirectory(tests)
