#ifndef CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_HEADER_WIDGET_HPP_
#define CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_HEADER_WIDGET_HPP_

class QLCDNumber;
class QPushButton;
class QTimer;

#include <QWidget>

class GameHeaderWidget: public QWidget {

	Q_OBJECT

private:
	QTimer* timer;
	QLCDNumber* lcdRemainingMines;
	QLCDNumber* lcdTime;
	QPushButton* buttonNewGame;

public:
	explicit GameHeaderWidget(QWidget *parent = 0);

private slots:
	void setMineCount(int count);
	void incrementMineCount();
	void decrementMineCount();
	void startTimer();
	void stopTimer();
	void updateTime();
	void setHappyFace();
	void setSadFace();

signals:
	void newGameRequested();
};

#endif /* CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_HEADER_WIDGET_HPP_ */
