#include <QVBoxLayout>
#include <QSettings>

#include "game_area_widget.hpp"
#include "game_header_widget.hpp"
#include "game_board_widget.hpp"

GameAreaWidget::GameAreaWidget(QWidget* parent)
	:QWidget(parent) {

	QVBoxLayout* mainLayout = new QVBoxLayout;

	headerWidget = new GameHeaderWidget(this);
	boardWidget = new GameBoardWidget(this);

	mainLayout->addWidget(headerWidget);
	mainLayout->addWidget(boardWidget);

	mainLayout->setAlignment(headerWidget, Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignHCenter);
	mainLayout->setAlignment(boardWidget, Qt::AlignmentFlag::AlignCenter);

	connect(boardWidget, SIGNAL(gameStarted(int)), headerWidget, SLOT(setMineCount(int)));
	connect(boardWidget, SIGNAL(gameStarted(int)), headerWidget, SLOT(startTimer()));
	connect(boardWidget, SIGNAL(gameStarted(int)), headerWidget, SLOT(setHappyFace()));
	connect(boardWidget, SIGNAL(gameLost()), headerWidget, SLOT(stopTimer()));
	connect(boardWidget, SIGNAL(gameLost()), headerWidget, SLOT(setSadFace()));
	connect(boardWidget, SIGNAL(gameWon()), headerWidget, SLOT(stopTimer()));
	connect(boardWidget, SIGNAL(gameWon()), headerWidget, SLOT(setHappyFace()));
	connect(boardWidget, SIGNAL(gameMineMarked()), headerWidget, SLOT(decrementMineCount()));
	connect(boardWidget, SIGNAL(gameMineUnmarked()), headerWidget, SLOT(incrementMineCount()));

	connect(boardWidget, SIGNAL(gameStarted(int)), this, SIGNAL(gameStarted()));

	connect(headerWidget, SIGNAL(newGameRequested()), boardWidget, SLOT(createNewGame()));

	setLayout(mainLayout);
}

void GameAreaWidget::request_new_game() {
	boardWidget->createNewGame();
}
