#include <QGridLayout>
#include <QSettings>
#include <QSignalMapper>

#ifndef NDEBUG
	#include <QDebug>
#endif

#include "../global_constants.hpp"
#include "game_board_widget.hpp"
#include "mine_pushbutton.hpp"
#include "../../minesweeper/boardgenerator.hpp"

GameBoardWidget::GameBoardWidget(QWidget* parent)
	: QWidget(parent) {

	signalMapperLeftClick = new QSignalMapper(this);
	signalMapperMiddleClick = new QSignalMapper(this);
	signalMapperRightClick = new QSignalMapper(this);
	mainLayout = new QGridLayout;
	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);

	connect(signalMapperLeftClick, SIGNAL(mapped(int)), this, SLOT(clickMineField(int)));
	connect(signalMapperRightClick, SIGNAL(mapped(int)), this, SLOT(rightClickMineField(int)));
	connect(signalMapperMiddleClick, SIGNAL(mapped(int)), this, SLOT(middleClickMineField(int)));

	setLayout(mainLayout);
}

void GameBoardWidget::initGameBoard(const BoardData& data) {
	int needed = data.width * data.height;

	buttonManager.prepareButtons(needed, signalMapperLeftClick, signalMapperMiddleClick, signalMapperRightClick);
	for(int i=0; i<data.height; i++) {
		for(int u=0; u<data.width; u++) {
			int index = i*data.width+u;
			mainLayout->addWidget(buttonManager[index], i, u);
			buttonManager[index]->setUsed();
		}
	}
}

void GameBoardWidget::destroyGameBoard() {
	for (int i = 0; i < buttonManager.getSize(); i++) {
		mainLayout->removeWidget(buttonManager[i]);
	}
	buttonManager.resetButtons(signalMapperLeftClick, signalMapperMiddleClick, signalMapperRightClick);
}

BoardData GameBoardWidget::loadPreferences() {
	QSettings settings(GlobalConstants::Settings::FILE_NAME, QSettings::IniFormat);

	BoardData retVal = {
		settings.value(GlobalConstants::Settings::BOARD_HEIGHT, 16).toInt(),
		settings.value(GlobalConstants::Settings::BOARD_WIDTH, 16).toInt(),
		settings.value(GlobalConstants::Settings::BOARD_MINECOUNT, 40).toInt()
	};

	return retVal;
}

void GameBoardWidget::createNewGame(const BoardData& data) {
	gameBoard = BoardGenerator().GenerateBoard(data);

#ifndef NDEBUG
	//print board in debug mode
	for(int i=0; i<gameBoard.get_board_height(); i++) {
		QString s;
		for(int u=0; u<gameBoard.get_board_width(); u++) {
			if(gameBoard.IsMine(u,i)) {
				s.append(" X ");
			} else {
				s.append(" ").append(QString().setNum(gameBoard.GetNeighborMineCount(u, i))).append(" ");
			}
		}
		qDebug() << s;
	}
	qDebug() << " ";
#endif

	// if there are buttons in the main layout
	if(! mainLayout->isEmpty()) {
		destroyGameBoard();
	}
	// create a new gameboard
	initGameBoard(data);
	// tell everyone that a new game has started and how many mines it contains
	emit gameStarted(data.mine_count);
}

void GameBoardWidget::createNewGame() {
	// interface for public use

	// create a new game
	createNewGame(loadPreferences());
}

void GameBoardWidget::clickMineField(int index) {
	int row = index / gameBoard.get_board_width();
	int col = index - (row * gameBoard.get_board_width());

	openField(row, col);
}

void GameBoardWidget::middleClickMineField(int index) {
	int row = index / gameBoard.get_board_width();
	int col = index - (row * gameBoard.get_board_width());

	openSurroundingFields(row, col);
}

void GameBoardWidget::rightClickMineField(int index) {
	// if the field is already opened, we cant mark and thus stop here
	if(buttonManager[index]->isOpened()) {
		return;
	}

	// if marked, remove the mark
	if(buttonManager[index]->isMarked()) {
		buttonManager[index]->setMark(false);
		buttonManager.setMarkedCount(buttonManager.getMarkedCount() - 1);
		emit gameMineUnmarked();
		return;
	}

	// mark the field
	buttonManager[index]->setMark(true);
	buttonManager.setMarkedCount(buttonManager.getMarkedCount() + 1);
	emit gameMineMarked();

	// check if every mine is marked
	if(playerWin()) {
		// tell everyone that the game is over
		emit gameWon();
		// show the user all fields
		showWholeField();
	}
}

void GameBoardWidget::openField(int row, int column) {
	// index out of range
	if(!gameBoard.IsInRange(column, row)) {
		return;
	}
	// field already opened or marked ( we cant open a marked field )
	int index = row * gameBoard.get_board_width() + column;
	if(buttonManager[index]->isOpened() || buttonManager[index]->isMarked()) {
		return;
	}
	// open the field (do not allow clicks)
	buttonManager[index]->setOpened();
	// is there a mine at this index?
	if(gameBoard.IsMine(column, row)) {
		// you lose, tell it everyone
		emit gameLost();
		// show the mines
		showMines();
		// disable all fields
		buttonManager.disableAll();
		return;
	}

	// how many mines are around?
	int count = gameBoard.GetNeighborMineCount(column, row);
	if(count == 0) {
		// no mines around => open all surrounding fields
		openSurroundingFields(row, column);
	} else {
		buttonManager[index]->setNumber(count);
	}
}

void GameBoardWidget::openSurroundingFields(int row, int column) {
	for(int i=(row-1); i<=(row+1); i++) {
		for(int u=(column-1); u<=(column+1); u++) {
			openField(i, u);
		}
	}
}

bool GameBoardWidget::playerWin() {
	int foundCount = 0;

	for(int row=0; row<gameBoard.get_board_height(); row++) {
		for (int col=0; col<gameBoard.get_board_width(); col++) {
			int index = (row * gameBoard.get_board_width()) + col;

			if(buttonManager[index]->isMarked() && gameBoard.IsMine(col, row)) {
				foundCount++;
			}
		}
	}

	return ((foundCount == buttonManager.getMarkedCount()) && (foundCount == gameBoard.get_mine_count()));
}

void GameBoardWidget::showMines() {
	for(int row=0; row<gameBoard.get_board_height(); row++) {
		for (int col = 0; col<gameBoard.get_board_width(); col++) {
			int index = (row * gameBoard.get_board_width()) + col;

			if(gameBoard.IsMine(col, row)) {
				if(buttonManager[index]->isMarked()) {
					buttonManager[index]->setIcon2(GlobalConstants::Icons::FLAG_OK);
				} else {
					buttonManager[index]->setMine();
				}
			} else {
				if(buttonManager[index]->isMarked()) {
					buttonManager[index]->setIcon2(GlobalConstants::Icons::FLAG_ERROR);
				}
			}
		}
	}
}

void GameBoardWidget::showWholeField() {
	showMines();

	for(int row=0; row<gameBoard.get_board_height(); row++) {
		for (int col = 0; col<gameBoard.get_board_width(); col++) {
			int index = (row * gameBoard.get_board_width()) + col;
			// Every normal field gets revealed - Mines were revealed at the
			// beginning
			if(! gameBoard.IsMine(col, row)) {
				int count = gameBoard.GetNeighborMineCount(col, row);
				if(count == 0) {
					buttonManager[index]->setOpened();
				} else {
					buttonManager[index]->setNumber(count);
				}
			}
		}
	}
}
