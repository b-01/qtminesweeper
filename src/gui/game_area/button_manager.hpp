#ifndef CUSTOM_MINESWEEPER_GUI_GAME_AREA_BUTTON_MANAGER_HPP_
#define CUSTOM_MINESWEEPER_GUI_GAME_AREA_BUTTON_MANAGER_HPP_

class MinePushButton;
class QSignalMapper;

#include <QList>

class ButtonManager {

private:
	QList<MinePushButton*> listAvailableButtons;
	QList<MinePushButton*> listUsedButtons;
	int markedCount;

public:
	ButtonManager();

	MinePushButton*& operator[] (const int nIndex);

	void prepareButtons(int count, QSignalMapper* lMapper, QSignalMapper* mMapper, QSignalMapper* rMapper);
	void resetButtons(QSignalMapper* lMapper, QSignalMapper* mMapper, QSignalMapper* rMapper);
	void setMarkedCount(int num);
	int getMarkedCount();
	int getSize();
	void disableAll();
};

#endif /* CUSTOM_MINESWEEPER_GUI_GAME_AREA_BUTTON_MANAGER_HPP_ */
