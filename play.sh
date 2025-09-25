#!/bin/bash

if [ ! -d "build" ]; then
  mkdir build
fi

cd build

if [ ! -f "CMakeCache.txt" ]; then
  cmake ..
fi

cmake --build .

./tictactoe
