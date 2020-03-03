#include <QtWidgets>

#include "mainwindow.hpp"
#include "game_area/game_area_widget.hpp"
#include "preferences_dialog.hpp"
#include "global_constants.hpp"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent) {
	setWindowIcon(QIcon(QPixmap(":/images/bomb.png")));

	mainContent = new GameAreaWidget(this);
	setCentralWidget(mainContent);

	createActions();
	createMenu();
	connect(mainContent, SIGNAL(gameStarted()), this, SLOT(gameStarted()));

    setWindowTitle(tr("QTMinesweeper"));
    loadPreferences();

    statusBar()->show();
}

void MainWindow::createActions() {
	newGameAction = new QAction(tr("&New Game"), this);
	newGameAction->setShortcut(QKeySequence::StandardKey::New);
	newGameAction->setStatusTip(tr("Start a new game"));
    connect(newGameAction, SIGNAL(triggered()), mainContent, SLOT(request_new_game()));

	preferencesAction = new QAction(tr("&Preferences..."), this);
	preferencesAction->setShortcut(QKeySequence::StandardKey::Preferences);
	preferencesAction->setStatusTip(tr("Change game settings"));
    connect(preferencesAction, SIGNAL(triggered()), this, SLOT(preferences()));

	exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence::StandardKey::Quit);
    exitAction->setStatusTip(tr("Quit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show some information about this application"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenu() {
	minesweeperMenu = menuBar()->addMenu(tr("&File"));
	minesweeperMenu->addAction(newGameAction);
	minesweeperMenu->addAction(preferencesAction);
	minesweeperMenu->addAction(exitAction);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
}

void MainWindow::loadPreferences() {
	QSettings settings(GlobalConstants::Settings::FILE_NAME, QSettings::IniFormat);

	this->resize(settings.value(GlobalConstants::Settings::WINDOW_SIZE, QSize(500,500)).toSize());
	this->move(settings.value(GlobalConstants::Settings::WINDOW_POS, QPoint(0,0)).toPoint());
}

void MainWindow::writePreferences() {
	QSettings settings(GlobalConstants::Settings::FILE_NAME, QSettings::IniFormat);

	settings.setValue(GlobalConstants::Settings::WINDOW_SIZE, this->size());
	settings.setValue(GlobalConstants::Settings::WINDOW_POS, this->pos());
	settings.sync();
}

void MainWindow::closeEvent(QCloseEvent* event) {
	writePreferences();
	QMainWindow::closeEvent(event);
}

void MainWindow::preferences() {
	PreferencesDialog* widget = new PreferencesDialog(this);
	widget->exec();
}

void MainWindow::about() {
	QMessageBox::about(this, tr("About QTMinesweeper"),
	            tr("<p>QTMinesweeper v1.0</p><p>by <i>b-01</i></p>"));
}

void MainWindow::gameStarted() {
	this->resize(this->minimumSizeHint());
}
