#include <QLCDNumber>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QPixmap>

#include "../global_constants.hpp"
#include "game_header_widget.hpp"

GameHeaderWidget::GameHeaderWidget(QWidget* parent)
	: QWidget(parent) {

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

	QHBoxLayout* mainLayout = new QHBoxLayout;
	QLabel* spacerLabel = new QLabel;

	lcdRemainingMines = new QLCDNumber;
	lcdTime = new QLCDNumber;
	buttonNewGame = new QPushButton(tr(""));

	spacerLabel->setMaximumWidth(200);

	setHappyFace();
	buttonNewGame->setToolTip(tr("Start a new game!"));
	buttonNewGame->setStatusTip(tr("Start a new game!"));
	buttonNewGame->setMaximumSize(30,25);
	connect(buttonNewGame, SIGNAL(clicked()), this, SIGNAL(newGameRequested()));

	lcdRemainingMines->setFixedSize(75,25);
	lcdTime->setFixedSize(75,25);

	lcdTime->setToolTip(tr("Elapsed time (in seconds)"));
	lcdTime->setStatusTip(tr("Elapsed time (in seconds)"));
	lcdRemainingMines->setToolTip(tr("Remaining mines"));
	lcdRemainingMines->setStatusTip(tr("Remaining mines"));

	mainLayout->addWidget(lcdRemainingMines, Qt::AlignmentFlag::AlignLeft);
	mainLayout->addWidget(spacerLabel);
	mainLayout->addWidget(buttonNewGame, Qt::AlignmentFlag::AlignCenter);
	mainLayout->addWidget(spacerLabel);
	mainLayout->addWidget(lcdTime, Qt::AlignmentFlag::AlignRight);

	mainLayout->setAlignment(Qt::AlignmentFlag::AlignTop | Qt::AlignmentFlag::AlignHCenter);

	setLayout(mainLayout);
}

void GameHeaderWidget::setMineCount(int count) {
	lcdRemainingMines->display(count);
}

void GameHeaderWidget::incrementMineCount() {
	lcdRemainingMines->display(lcdRemainingMines->intValue() + 1);
}

void GameHeaderWidget::decrementMineCount() {
	lcdRemainingMines->display(lcdRemainingMines->intValue() - 1);
}

void GameHeaderWidget::startTimer() {
	lcdTime->display(0);
	timer->start(1000);
}

void GameHeaderWidget::stopTimer() {
	timer->stop();
}

void GameHeaderWidget::updateTime() {
	if(lcdTime->intValue() == 999) {
		timer->stop();
		return;
	}
	lcdTime->display(lcdTime->intValue() + 1);
}

void GameHeaderWidget::setHappyFace() {
	buttonNewGame->setIcon(QIcon(QPixmap(GlobalConstants::Icons::SMILEY_HAPPY)));
	buttonNewGame->setIconSize(QSize(GlobalConstants::Icons::SIZE, GlobalConstants::Icons::SIZE));
}

void GameHeaderWidget::setSadFace() {
	buttonNewGame->setIcon(QIcon(QPixmap(GlobalConstants::Icons::SMILEY_SAD)));
	buttonNewGame->setIconSize(QSize(GlobalConstants::Icons::SIZE, GlobalConstants::Icons::SIZE));
}
