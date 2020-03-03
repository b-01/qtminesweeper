#ifndef CUSTOM_MINESWEEPER_MINESWEEPER_GAMEBOARD_HPP_
#define CUSTOM_MINESWEEPER_MINESWEEPER_GAMEBOARD_HPP_

class MineField;

#include <vector>
#include "boarddata.hpp"

class Gameboard {

private:
	BoardData board_data;
	std::vector<MineField*> fields;

	bool destroyMines();
	void copyMines(const std::vector<MineField*>& fields);

public:
	Gameboard();
	explicit Gameboard(const BoardData& data);
	Gameboard(const Gameboard& board);
	~Gameboard();

	Gameboard& operator=(const Gameboard& rhs);

	void set_board_height(int height);
	void set_board_width(int width);
	void set_mine_count(int count);

	int get_board_height();
	int get_board_width();
	int get_mine_count();

	bool SetNewMine(int x, int y);
	bool IsMine(int x, int y);
	bool IsInRange(int x, int y);
	int GetNeighborMineCount(int x, int y);
};

#endif /* CUSTOM_MINESWEEPER_MINESWEEPER_GAMEBOARD_HPP_ */
