#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class MainWindow : public QMainWindow
{
	Q_OBJECT

	private:
		QGraphicsScene * scene;
		QGraphicsView * view;
		QPixmap * background;

	public:
    		explicit MainWindow(QWidget * parent = 0);
    		~MainWindow();

	// public slots:
};

#endif MAINWINDOW_H
