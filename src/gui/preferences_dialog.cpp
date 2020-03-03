#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QSettings>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

#include "preferences_dialog.hpp"
#include "global_constants.hpp"

PreferencesDialog::PreferencesDialog(QWidget* parent)
	: QDialog(parent) {

	textWidth = new QSpinBox;
	textHeight = new QSpinBox;
	textMinecount = new QSpinBox;

	textWidth->setFixedWidth(70);
	textHeight->setFixedWidth(70);
	textMinecount->setFixedWidth(70);

	textWidth->setMinimum(4);
	textHeight->setMinimum(4);
	textMinecount->setMinimum(1);

	textWidth->setMaximum(100);
	textHeight->setMaximum(100);
	textMinecount->setMaximum(100);

	buttonSave = new QPushButton(tr("&Save"));
	buttonCancel = new QPushButton(tr("&Cancel"));
	buttonEasy = new QPushButton(tr("Easy"));
	buttonMedium = new QPushButton(tr("Medium"));
	buttonHard = new QPushButton(tr("Hard"));

	buttonEasy->setFixedWidth(70);
	buttonMedium->setFixedWidth(70);
	buttonHard->setFixedWidth(70);

	QLabel* labelDifficulty = new QLabel(tr("Difficulty:"));
	QLabel* labelCustom = new QLabel(tr("Custom:"));

	connect(buttonSave, SIGNAL(clicked()), this, SLOT(accept()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

	connect(buttonEasy, SIGNAL(clicked()), this, SLOT(easy()));
	connect(buttonMedium, SIGNAL(clicked()), this, SLOT(medium()));
	connect(buttonHard, SIGNAL(clicked()), this, SLOT(hard()));

	QHBoxLayout* layoutDifficulty = new QHBoxLayout;
	layoutDifficulty->addWidget(buttonEasy);
	layoutDifficulty->addWidget(buttonMedium);
	layoutDifficulty->addWidget(buttonHard);
	layoutDifficulty->setSpacing(5);

	QHBoxLayout* layoutButton = new QHBoxLayout;
	layoutButton->setSpacing(5);
	layoutButton->addWidget(buttonSave);
	layoutButton->addWidget(buttonCancel);

	QFormLayout* layoutForm = new QFormLayout;
	layoutForm->setSpacing(4);
	layoutForm->addRow(tr("Width: "), textWidth);
	layoutForm->addRow(tr("Height: "), textHeight);
	layoutForm->addRow(tr("Mines: "), textMinecount);
	layoutForm->setFormAlignment(Qt::AlignmentFlag::AlignCenter);

	QVBoxLayout* layoutTop = new QVBoxLayout;
	layoutTop->addWidget(labelDifficulty);
	layoutTop->addItem(layoutDifficulty);
	layoutTop->addWidget(labelCustom);
	layoutTop->addItem(layoutForm);
	layoutTop->setSpacing(7);
	layoutTop->setAlignment(Qt::AlignmentFlag::AlignCenter);

	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addItem(layoutTop);
	layoutMain->addItem(layoutButton);
	layoutMain->setAlignment(Qt::AlignmentFlag::AlignCenter);

	setLayout(layoutMain);
	setModal(true);

	loadPreferences();
}

void PreferencesDialog::loadPreferences() {
	QSettings settings(GlobalConstants::Settings::FILE_NAME, QSettings::IniFormat);

	setValues(settings.value(GlobalConstants::Settings::BOARD_HEIGHT, 16).toInt(),
		settings.value(GlobalConstants::Settings::BOARD_WIDTH, 16).toInt(),
		settings.value(GlobalConstants::Settings::BOARD_MINECOUNT, 40).toInt());
}

void PreferencesDialog::savePreferences() {
	QSettings settings(GlobalConstants::Settings::FILE_NAME, QSettings::IniFormat);

	settings.setValue(GlobalConstants::Settings::BOARD_HEIGHT, textHeight->value());
	settings.setValue(GlobalConstants::Settings::BOARD_WIDTH, textWidth->value());
	settings.setValue(GlobalConstants::Settings::BOARD_MINECOUNT, textMinecount->value());

	settings.sync();
}

void PreferencesDialog::setValues(int h, int w, int count) {
	textHeight->setValue(h);
	textWidth->setValue(w);
	textMinecount->setValue(count);
}

void PreferencesDialog::easy() {
	setValues(9,9,10);
}

void PreferencesDialog::medium() {
	setValues(16,16,40);
}

void PreferencesDialog::hard() {
	setValues(16,30,99);
}

void PreferencesDialog::accept() {
	int height = textHeight->value();
	int width = textWidth->value();
	int mines = textMinecount->value();

	if(height < 0
			|| width < 0
			|| mines < 0) {
		QMessageBox::warning(this, tr("Invalid value"), tr("A field has a valid smaller than 0!"));
		return;
	}

	if((height*width) <= mines) {
		QMessageBox::warning(this, tr("Invalid value"), tr("More mines than available fields!"));
		return;
	}

	savePreferences();
	QDialog::accept();
}
