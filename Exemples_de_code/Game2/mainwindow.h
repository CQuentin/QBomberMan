#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <vector>

class MainWindow : public QMainWindow
{
	Q_OBJECT

	private:
		QGraphicsScene * scene;
		QGraphicsView * view;
		QPixmap * background;
		std::vector<QGraphicsPixmapItem *> briques_cassables;
		std::vector<QGraphicsPixmapItem *> briques_incassables;

	public:
    		explicit MainWindow(QWidget * parent = 0);
    		~MainWindow();
		void ajouter_brique(bool cassable, int x, int y);
		void afficher_mur();

	// public slots:
};

#endif MAINWINDOW_H
