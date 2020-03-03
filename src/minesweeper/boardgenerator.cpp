#include <chrono>
#include <functional>
#include <random>

#include "boardgenerator.hpp"
#include "gameboard.hpp"

BoardGenerator::BoardGenerator() { }

Gameboard BoardGenerator::GenerateBoard(const BoardData& board_data) {
	std::random_device randomDevice;
	std::mt19937 generator_h(randomDevice());
	std::mt19937 generator_w(randomDevice());
	std::uniform_int_distribution<int> distribution_height(1, board_data.height);
	std::uniform_int_distribution<int> distribution_width(1, board_data.width);

	auto rand_height = std::bind(distribution_height, generator_h);
	auto rand_width = std::bind(distribution_width, generator_w);

	Gameboard board (board_data);

	for(int i=0; i<board_data.mine_count; i++) {
		while(! board.SetNewMine(rand_width(), rand_height())) { }
	}

	return board;
}
