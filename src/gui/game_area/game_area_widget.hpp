#ifndef CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_AREA_WIDGET_HPP_
#define CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_AREA_WIDGET_HPP_

class GameBoardWidget;
class GameHeaderWidget;

#include <QWidget>

class GameAreaWidget : public QWidget {

	Q_OBJECT

private:
	GameHeaderWidget* headerWidget;
	GameBoardWidget* boardWidget;

public:
	explicit GameAreaWidget(QWidget *parent = 0);

public slots:
	void request_new_game();

signals:
	void gameStarted();
};

#endif /* CUSTOM_MINESWEEPER_GUI_GAME_AREA_GAME_AREA_WIDGET_HPP_ */
