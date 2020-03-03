#ifndef CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_BOARD_WIDGET_HPP_
#define CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_BOARD_WIDGET_HPP_

class MinePushButton;
class QGridLayout;
class QSignalMapper;

#include <QWidget>
#include "button_manager.hpp"
#include "../../minesweeper/boarddata.hpp"
#include "../../minesweeper/gameboard.hpp"

class GameBoardWidget: public QWidget {

	Q_OBJECT

private:
	ButtonManager buttonManager;
	QSignalMapper* signalMapperLeftClick;
	QSignalMapper* signalMapperRightClick;
	QSignalMapper* signalMapperMiddleClick;
	QGridLayout* mainLayout;
	Gameboard gameBoard;

	void initGameBoard(const BoardData& data);
	void destroyGameBoard();
	BoardData loadPreferences();

	void openField(int row, int column);
	void openSurroundingFields(int row, int column);
	bool playerWin();
	void showMines();
	void showWholeField();


public:
	explicit GameBoardWidget(QWidget *parent = 0);

	void createNewGame(const BoardData& data);

private slots:
	void clickMineField(int index);
	void rightClickMineField(int index);
	void middleClickMineField(int index);

public slots:
	void createNewGame();

signals:
	void gameStarted(int mine_count);
	void gameLost();
	void gameWon();
	void gameMineMarked();
	void gameMineUnmarked();

};

#endif /* CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_BOARD_WIDGET_HPP_ */
