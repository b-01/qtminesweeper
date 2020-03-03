#ifndef CUSTOM_MINESWEEPER_GUI_PREFERENCES_DIALOG_HPP_
#define CUSTOM_MINESWEEPER_GUI_PREFERENCES_DIALOG_HPP_

class QPushButton;
class QSpinBox;

#include <QDialog>

class PreferencesDialog : public QDialog {

	Q_OBJECT

private:
	QSpinBox* textWidth;
	QSpinBox* textHeight;
	QSpinBox* textMinecount;
	QPushButton* buttonEasy;
	QPushButton* buttonMedium;
	QPushButton* buttonHard;
	QPushButton* buttonSave;
	QPushButton* buttonCancel;

	void loadPreferences();
	void savePreferences();
	void setValues(int h, int w, int count);

public:
	explicit PreferencesDialog(QWidget *parent = 0);

private slots:
	void accept();
	void easy();
	void medium();
	void hard();
};

#endif /* CUSTOM_MINESWEEPER_GUI_PREFERENCES_DIALOG_HPP_ */
