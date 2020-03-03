#ifndef CUSTOM_MINESWEEPER_MINESWEEPER_BOARDGENERATOR_HPP_
#define CUSTOM_MINESWEEPER_MINESWEEPER_BOARDGENERATOR_HPP_

class Gameboard;

#include "boarddata.hpp"

class BoardGenerator{

public:
	BoardGenerator();
	Gameboard GenerateBoard(const BoardData& board_data);
};

#endif /* CUSTOM_MINESWEEPER_MINESWEEPER_BOARDGENERATOR_HPP_ */
