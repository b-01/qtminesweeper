#include <QSignalMapper>
#include <QMouseEvent>
#include <QIcon>

#include "../global_constants.hpp"
#include "mine_pushbutton.hpp"

MinePushButton::MinePushButton(QWidget* parent)
	: QPushButton(parent) {

	index = 0;
	marked = false;
	mouseEventsEnabled = true;

	setText("");
	setMaximumSize(22,22);
}

void MinePushButton::setIndex(int index) {
	this->index = index;
}

int MinePushButton::getIndex() {
	return index;
}

void MinePushButton::resetState() {
	index = 0;
	marked = false;
	mouseEventsEnabled = true;
	setStyleSheet("");
	setVisible(false);
	setEnabled(true);
	setFlat(false);
	setIcon(QIcon());
	setText("");
}

void MinePushButton::setUsed() {
	setVisible(true);
}

bool MinePushButton::isOpened() {
	return isFlat();
}

void MinePushButton::setOpened(bool isNumField) {
	setFlat(true);
	setEnabled(isNumField);
}

void MinePushButton::setMine() {
	setIcon2(GlobalConstants::Icons::MINE);
}

void MinePushButton::setNumber(int num) {
	setOpened(true);
	QString fontStyle;

	switch (num) {
		case 1:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_1;
			break;
		case 2:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_2;
			break;
		case 3:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_3;
			break;
		case 4:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_4;
			break;
		case 5:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_5;
			break;
		case 6:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_6;
			break;
		case 7:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_7;
			break;
		case 8:
			fontStyle = GlobalConstants::NumberStyles::NUMBER_8;
			break;
		default:
			fontStyle = GlobalConstants::NumberStyles::DEFAULT;
			break;
	}

	setStyleSheet(fontStyle);
	setText(QString().setNum(num));
}

void MinePushButton::setMark(bool value) {
	if(value) {
		setIcon2(GlobalConstants::Icons::FLAG);
		setIconSize(QSize(GlobalConstants::Icons::SIZE,GlobalConstants::Icons::SIZE));
	} else {
		setIcon(QIcon());
	}
	marked = value;
}

bool MinePushButton::isMarked() {
	return marked;
}

void MinePushButton::setIcon2(const QString& path) {
	setIcon(QIcon(QPixmap(path)));
	setIconSize(QSize(GlobalConstants::Icons::SIZE,GlobalConstants::Icons::SIZE));
}

void MinePushButton::addMapping(QSignalMapper* left_mapper, QSignalMapper* middle_mapper, QSignalMapper* right_mapper, int index) {
	setIndex(index);

	if(left_mapper != nullptr) {
		connect(this, SIGNAL(clicked()), left_mapper, SLOT(map()));
		left_mapper->setMapping(this, index);
	}

	if(middle_mapper != nullptr) {
		connect(this, SIGNAL(middleClicked()), middle_mapper, SLOT(map()));
		middle_mapper->setMapping(this, index);
	}

	if(right_mapper != nullptr) {
		connect(this, SIGNAL(rightClicked()), right_mapper, SLOT(map()));
		right_mapper->setMapping(this, index);
	}
}

void MinePushButton::removeMapping(QSignalMapper* left_mapper, QSignalMapper* middle_mapper, QSignalMapper* right_mapper) {
	if(left_mapper != nullptr) {
		disconnect(this, SIGNAL(clicked()), left_mapper, SLOT(map()));
		left_mapper->removeMappings(this);
	}

	if(middle_mapper != nullptr) {
		disconnect(this, SIGNAL(middleClicked()), middle_mapper, SLOT(map()));
		middle_mapper->removeMappings(this);
	}

	if(right_mapper != nullptr) {
		disconnect(this, SIGNAL(rightClicked()), right_mapper, SLOT(map()));
		right_mapper->removeMappings(this);
	}
}

void MinePushButton::disableMouseEvent(bool value) {
	mouseEventsEnabled = !value;
}

void MinePushButton::mousePressEvent(QMouseEvent* e) {
	if(!mouseEventsEnabled) {
		e->ignore();
		return;
	}

	if(e->button() == Qt::RightButton) {
		emit rightClicked();
	}

	if(e->button() == Qt::MiddleButton) {
		emit middleClicked();
	}

	QPushButton::mousePressEvent(e);
}
