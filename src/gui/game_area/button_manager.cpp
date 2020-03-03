#include <QSignalMapper>

#include "button_manager.hpp"
#include "mine_pushbutton.hpp"

ButtonManager::ButtonManager() {

	markedCount = 0;
}

MinePushButton*& ButtonManager::operator [](const int nIndex) {
	return listUsedButtons[nIndex];
}

void ButtonManager::prepareButtons(int count, QSignalMapper* lMapper, QSignalMapper* mMapper, QSignalMapper* rMapper) {
	// check if we need more buttons, create them if needed!
	if(listAvailableButtons.size() < count) {
		int toCreate = (count - listAvailableButtons.size());
		for(int i=0; i<toCreate; i++) {
			listAvailableButtons << new MinePushButton();
		}
	}
	// add the buttons to our display list
	for(int i=0; i<count; i++) {
		listUsedButtons << listAvailableButtons[i];
		listUsedButtons[i]->addMapping(lMapper, mMapper, rMapper, i);
	}
}

void ButtonManager::resetButtons(QSignalMapper* lMapper, QSignalMapper* mMapper, QSignalMapper* rMapper) {
	for(const auto& button : listUsedButtons) {
		button->resetState();
		button->removeMapping(lMapper, mMapper, rMapper);
	}
	listUsedButtons.clear();
	setMarkedCount(0);
}

void ButtonManager::setMarkedCount(int num) {
	if(num < 0) {
		num = 0;
	}
	markedCount = num;
}

int ButtonManager::getMarkedCount() {
	return markedCount;
}

int ButtonManager::getSize() {
	return listUsedButtons.size();
}

void ButtonManager::disableAll() {
	for(const auto& button : listUsedButtons) {
		button->disableMouseEvent(true);
	}
}
