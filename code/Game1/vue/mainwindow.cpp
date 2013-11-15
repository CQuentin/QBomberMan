#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    largeur = 900;
    hauteur = 600;

    grille.resize(45);

    for(int i = 0; i<45; i++)
        grille[i].resize(30);

    scene = new QGraphicsScene(0, 0, largeur, hauteur, this);
    view = new QGraphicsView(scene, this);

    /*  -------------- début niveau -------------------- */

    //TODO : gérer avec des classes niveau
    ajouterPersonnage(0,0);
    for (int i =0; i< 45; i++)
        ajouterBrique(false,i,29);

    for (int j =29; j>= 15; j--)
        ajouterBrique(false,30,j);

    /*  -------------- fin niveau -------------------- */

    // background = new QPixmap("IMG_8708_blue_Sky2.jpg");
    // scene->setBackgroundBrush(*background);




    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedWidth(900);
    view->setFixedHeight(600);
    view->show();
}

void MainWindow::ajouterPersonnage(int i, int j){
    int posX = getPositionXFromGrille(i);
    int posY = getPositionYFromGrille(j);
    personnage = new Joueur(posX,posY);
    scene->addItem(personnage->getPicture());
}

void MainWindow::ajouterBrique(bool cassable, int i, int j)
{
    int posX = getPositionXFromGrille(i);
    int posY = getPositionYFromGrille(j);

    grille[i][j] = new Brique(cassable,posX,posY);

    scene->addItem(grille[i][j]->getPicture());
}


void MainWindow::keyPressEvent(QKeyEvent* event) {
    qreal x = 0,y =0 ;
    int correctionX =0, correctionY = 0;
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
        correctionX = 22;
        qDebug()<<"droite";
        break;
    case Qt::Key_S:
       // personnage->moveBy(0,5);
        y += 5;
        qDebug()<<"bas";
        correctionY = 36;
        break;
       default : break;
    }
    int newX = personnage->getX()+x;
    int newY = personnage->getY()+y;

    if(!personnage->isColising(getGrilleIFromPosition(newX + correctionX),getGrilleJFromPosition(newY + correctionY),grille)){
        personnage->setX(newX);
        personnage->setY(newY);
        personnage->getPicture()->moveBy(x,y);
    }



}


QPoint MainWindow::getPositionFromGrille(int i, int j){
    // 20 car une case = 20p,
    // à modifier pour gérer les différentes tailles
    return QPoint(i * 20 , j * 20 );
}

int MainWindow::getPositionXFromGrille(int i){
    // 20 car une case = 20p,
    // à modifier pour gérer les différentes tailles
    return i * 20;
}

int MainWindow::getPositionYFromGrille( int j){
    // 20 car une case = 20p,
    // à modifier pour gérer les différentes tailles

    return j*20;
}

int MainWindow::getGrilleIFromPosition(int x){
    return x/20;

}

int MainWindow::getGrilleJFromPosition(int y){
    return  y/20;

}



/* Destructeur de la classe MainWindow */
MainWindow::~MainWindow()
{
    for(int i=0; i<(int) grille.size(); i++)
        for(int j=0; j<(int) grille.size(); j++)
            delete grille[i][j];
    delete personnage;
    delete view;
    delete scene;
    // delete background;
}
