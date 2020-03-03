#ifndef CUSTOM_MINESWEEPER_GUI_GAME_AREA_MINE_BUTTON_HPP_
#define CUSTOM_MINESWEEPER_GUI_GAME_AREA_MINE_BUTTON_HPP_

class QSignalMapper;
class QMouseEvent;

#include <QPushButton>

class MinePushButton : public QPushButton {

	Q_OBJECT

private:
	int index;
	bool marked;
	bool mouseEventsEnabled;

public:
	explicit MinePushButton(QWidget* parent = 0);

	void setIndex(int index);
	int getIndex();

	void resetState();
	void setUsed();

	bool isOpened();
	void setOpened(bool isNumField = false);

	void setMine();
	void setNumber(int num);

	void setMark(bool value);
	bool isMarked();

	void setIcon2(const QString& path);

	void disableMouseEvent(bool value);

	void addMapping(QSignalMapper* left_mapper, QSignalMapper* middle_mapper, QSignalMapper* right_mapper, int index);
	void removeMapping(QSignalMapper* left_mapper, QSignalMapper* middle_mapper, QSignalMapper* right_mapper);

private slots:
    void mousePressEvent(QMouseEvent* e);

signals:
    void rightClicked();
    void middleClicked();

};

#endif /* CUSTOM_MINESWEEPER_GUI_GAME_AREA_MINE_BUTTON_HPP_ */
