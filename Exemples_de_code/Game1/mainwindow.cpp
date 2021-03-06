#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
	scene = new QGraphicsScene(0, 0, 900, 600, this);
	view = new QGraphicsView(scene, this);
	background = new QPixmap("IMG_8708_blue_Sky2.jpg");

	scene->setBackgroundBrush(*background);

	// QPixmap img("128px-Feed-icon.png");
	// scene->addPixmap(img);

	/* Affiche un logo flux RSS aux coordonnées x=400, y=200 */
	QGraphicsPixmapItem * img = scene->addPixmap(QPixmap("128px-Feed-icon.png"));
	img->setPos(400, 200);

	/* Affiche un smiley aux coordonnées x=20, y=20, et de taille deux fois plus petite que la taille de l'image originale */
	QGraphicsPixmapItem * smiley = scene->addPixmap(QPixmap("face-smile-2.png"));
	smiley->setScale(0.5);
	smiley->setPos(20, 20);

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
	delete background;
}
