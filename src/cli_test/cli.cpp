#include <iostream>

#include "../minesweeper/boardgenerator.hpp"
#include "../minesweeper/gameboard.hpp"

void PrintBoard(Gameboard& board) {
	for(int i=0; i<board.get_board_width(); i++) {
		for(int u=0; u<board.get_board_height(); u++) {
			if(board.IsMine(i,u)) {
				std::cout << " X ";
			} else {
				std::cout << " " << board.GetNeighborMineCount(i, u) << " ";
			}
		}
		std::cout << std::endl;
	}
}

int main() {
	BoardData data = {4,4,4};
	BoardGenerator generator;

	std::cout << "[MINESWEEPER]" << std::endl;

	Gameboard board = generator.GenerateBoard(data);
	PrintBoard(board);
	std::cout << "--" << std::endl;
	for(int i=0; i<5; i++) {
		board = generator.GenerateBoard(data);
		PrintBoard(board);
		std::cout << "--" << std::endl;
	}
	return 0;
}
