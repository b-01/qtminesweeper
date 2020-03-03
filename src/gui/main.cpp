#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
	QApplication application(argc, argv);
	MainWindow w;
	w.show();
    return application.exec();
}
