#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    largeur = 900;
    hauteur = 600;

    grille.resize(45*30);

    scene = new QGraphicsScene(0, 0, largeur, hauteur, this);
    view = new QGraphicsView(scene, this);

    //TODO : gérer avec des classes niveau


    for (int i =0; i< 45; i++)
        ajouterBrique(false,i,29);



    // background = new QPixmap("IMG_8708_blue_Sky2.jpg");
    // scene->setBackgroundBrush(*background);




    personnage = new QGraphicsPixmapItem(QPixmap("../Game1/ressource/personnage.png"));
    personnage->setPos(0, 0);
    scene->addItem(personnage);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedWidth(900);
    view->setFixedHeight(600);
    view->show();
}



void MainWindow::ajouterBrique(bool cassable, int x, int y)
{
    int posX = getPositionXFromGrille(x);
    int posY = getPositionYFromGrille(y);
    int indice = getGrilleFromPosition(x,y);

    grille[indice] = new Brique(cassable,posX,posY);

    scene->addItem(grille[indice]->getPicture());
}


void MainWindow::keyPressEvent(QKeyEvent* event) {
    qreal x = 0,y = 0;
    switch(event->key()){
    case Qt::Key_Z:
        //personnage->moveBy(0,-5);
        y += -5;
        qDebug()<<"haut";
        break;
    case Qt::Key_Q:
       // personnage->moveBy(-5,0);
        x += -5;
        qDebug()<<"gauche";
        break;
    case Qt::Key_D:
        //personnage->moveBy(5,0);
        x += 5;
        qDebug()<<"droite";
        break;
    case Qt::Key_S:
       // personnage->moveBy(0,5);
        y += 5;
        qDebug()<<"droite";
        break;
       default : break;
    }
    personnage->moveBy(x,y);
}


QPoint MainWindow::getPositionFromGrille(int x,int y){
    // 20 car une case = 20p,
    // à modifier pour gérer les différentes tailles
    return QPoint(x * 20 , y * 20 );
}

int MainWindow::getPositionXFromGrille(int i){
    // 20 car une case = 20p,
    // à modifier pour gérer les différentes tailles
    return i * 20;
}

int MainWindow::getPositionYFromGrille(int i){
    // 20 car une case = 20p,
    // à modifier pour gérer les différentes tailles

    return (i * 20);
}

int MainWindow::getGrilleFromPosition(int x, int y){
    x = x/20;
    y = y/20;

    return 45*x + y;
}



/* Destructeur de la classe MainWindow */
MainWindow::~MainWindow()
{
    for(int i=0; i<(int) briques_incassables.size(); i++)
        delete briques_incassables[i];

    for(int i=0; i<(int) briques_cassables.size(); i++)
        delete briques_cassables[i];
    delete personnage;
    delete view;
    delete scene;
    // delete background;
}
