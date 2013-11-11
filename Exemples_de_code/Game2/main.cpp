#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char * argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowTitle(QString::fromUtf8("Game1"));
	w.resize(900, 600);
	w.show();

	return a.exec();
}
