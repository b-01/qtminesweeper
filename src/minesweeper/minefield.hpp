#ifndef CUSTOM_MINESWEEPER_MINESWEEPER_MINEFIELD_HPP_
#define CUSTOM_MINESWEEPER_MINESWEEPER_MINEFIELD_HPP_

class MineField {

private:
	int x;
	int y;
public:
	MineField();
	MineField(int x, int y);

	void set_x(int x);
	void set_y(int y);

	int get_x();
	int get_y();
};

#endif /* CUSTOM_MINESWEEPER_MINESWEEPER_MINEFIELD_HPP_ */
