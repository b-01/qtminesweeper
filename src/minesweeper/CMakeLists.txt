SET(minesweeper_srcs boardgenerator.cpp gameboard.cpp minefield.cpp)

ADD_LIBRARY(minesweeper ${minesweeper_srcs})
