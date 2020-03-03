#include <stdexcept>

#include "gameboard.hpp"
#include "minefield.hpp"

bool Gameboard::destroyMines() {
	for(const auto& field : fields) {
		delete field;
	}
	return true;
}

void Gameboard::copyMines(const std::vector<MineField*>& fields) {
	this->fields.clear();
	for(auto& field : fields) {
		this->fields.push_back(new MineField(*field));
	}
}

Gameboard::Gameboard() {
	BoardData tmp = {2, 1, 1};
	board_data = tmp;
}

Gameboard::Gameboard(const BoardData& board)
	: board_data(board) {
}

Gameboard::Gameboard(const Gameboard& board) {
	board_data = board.board_data;
	copyMines(board.fields);
}

Gameboard::~Gameboard() {
	destroyMines();
}

Gameboard& Gameboard::operator =(const Gameboard& rhs) {
	if(this != &rhs) {
		board_data = rhs.board_data;
		copyMines(rhs.fields);
	}
	return *this;
}

void Gameboard::set_board_height(int height) {
	if(height < 1) {
		throw std::logic_error("Board height should not be < 1!");
	}
	board_data.height = height;
}

void Gameboard::set_board_width(int width) {
	if(width < 1) {
			throw std::logic_error("Board width should not be < 1!");
	}
	board_data.width = width;
}

void Gameboard::set_mine_count(int count) {
	if(count < 0) {
			throw std::logic_error("Board width should not be < 0!");
	}
	board_data.mine_count = count;
}

int Gameboard::get_board_height() {
	return board_data.height;
}

int Gameboard::get_board_width() {
	return board_data.width;
}

int Gameboard::get_mine_count() {
	return board_data.mine_count;
}

bool Gameboard::SetNewMine(int x, int y) {
	if( IsMine(x, y) || !IsInRange(x, y)) {
		return false;
	}
	fields.push_back(new MineField(x, y));
	return true;
}

bool Gameboard::IsMine(int x, int y) {
	for(const auto& field : fields) {
		if(field->get_x() == x && field->get_y() == y) {
			return true;
		}
	}
	return false;
}

bool Gameboard::IsInRange(int x, int y) {
	if( x < 0 || y < 0 || y >= board_data.height || x >= board_data.width) {
		return false;
	}
	return true;
}

int Gameboard::GetNeighborMineCount(int x, int y) {
	int count = 0;
	for(int i=(x-1); i<=(x+1); i++) {
		for(int u=(y-1); u<=(y+1); u++) {
			if(IsMine(i, u)) {
				count++;
			}
		}
	}
	return count;
}
