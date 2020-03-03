#include <stdexcept>

#include "minefield.hpp"

MineField::MineField(): x(0), y(0) {
}

MineField::MineField(int x, int y) : x(x), y(y) {
}

void MineField::set_x(int x) {
	if(x < 0) {
		throw std::logic_error("x must not be < 0 !");
	}
	this->x = x;
}

void MineField::set_y(int y) {
	if(y < 0) {
		throw std::logic_error("y must not be < 0 !");
	}
	this->y = y;
}

int MineField::get_x() {
	return x;
}

int MineField::get_y() {
	return y;
}
