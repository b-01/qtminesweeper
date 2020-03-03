#ifndef CUSTOM_MINESWEEPER_GUI_MAINWINDOW_HPP_
#define CUSTOM_MINESWEEPER_GUI_MAINWINDOW_HPP_

class QMenu;
class QAction;
class QCloseEvent;
class GameAreaWidget;

#include <QMainWindow>

class MainWindow : public QMainWindow {

	Q_OBJECT

private:
	QMenu* minesweeperMenu;
	QMenu* helpMenu;
	QAction* newGameAction;
	QAction* preferencesAction;
	QAction* exitAction;
	QAction* aboutAction;
	GameAreaWidget* mainContent;

    void createActions();
    void createMenu();
    void loadPreferences();
    void writePreferences();

protected:
    void closeEvent(QCloseEvent* event);

public:
	explicit MainWindow(QWidget* parent = 0);

private slots:
	void preferences();
	void about();
	void gameStarted();
};

#endif //CUSTOM_MINESWEEPER_GUI_MAINWINDOW_HPP_
