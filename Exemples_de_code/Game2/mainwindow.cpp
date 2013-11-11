#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
	scene = new QGraphicsScene(0, 0, 900, 600, this);
	view = new QGraphicsView(scene, this);
	// background = new QPixmap("IMG_8708_blue_Sky2.jpg");
	// scene->setBackgroundBrush(*background);

	// QPixmap img("128px-Feed-icon.png");
	// scene->addPixmap(img);

	ajouter_brique(true, 50, 50);
	ajouter_brique(true, 150, 50);
	ajouter_brique(true, 150, 250);
	ajouter_brique(false, 250, 350);
	afficher_mur();

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setFixedWidth(900);
	view->setFixedHeight(600);
	view->show();
}

/* Destructeur de la classe MainWindow */
MainWindow::~MainWindow()
{
	delete view;
	delete scene;
	// delete background;
}

void MainWindow::ajouter_brique(bool cassable, int x, int y)
{
	if(cassable)
	{
		QGraphicsPixmapItem * brique = new QGraphicsPixmapItem(QPixmap("brique_cassable.png"));
		brique->setPos(x, y);
		briques_cassables.push_back(brique);
	}
	else
	{
		QGraphicsPixmapItem * brique = new QGraphicsPixmapItem(QPixmap("brique_incassable.png"));
		brique->setPos(x, y);
		briques_incassables.push_back(brique);
	}
}

void MainWindow::afficher_mur()
{
	for(int i=0; i<briques_incassables.size(); i++)
		scene->addItem(briques_incassables[i]);

	for(int i=0; i<briques_cassables.size(); i++)
		scene->addItem(briques_cassables[i]);
}
