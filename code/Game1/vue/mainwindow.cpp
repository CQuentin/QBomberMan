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
    int caseD = 10;

    //taille personnage : 36 * 22
    // TODO : mettre dans attribut joueur, ou faire un gets size de l'image (attention si on prend l'image entière)

    int correctionX =0, correctionY = 0;
    switch(event->key()){
    case Qt::Key_Z:
        y += -5;
        qDebug()<<"haut";
        caseD = 0;
        break;
    case Qt::Key_Q:
        x += -5;
        qDebug()<<"gauche";
        caseD = 1;
        break;
    case Qt::Key_D:
        x += 5;
        correctionX = 20;
        qDebug()<<"droite";
        caseD = 2;
        break;
    case Qt::Key_S:
        y += 5;
        qDebug()<<"bas";
        correctionY = 36;
        caseD = 3;
        break;
       default : break;
    }
    int newX = personnage->getX()+x;
    int newY = personnage->getY()+y;

    int posGrilleI = getGrilleIFromPosition(newX + correctionX);
    int posGrilleJ = getGrilleJFromPosition(newY + correctionY);

    if(!personnage->isColliding(posGrilleI,posGrilleJ,grille)){
        personnage->setX(newX);
        personnage->setY(newY);
        personnage->getPicture()->moveBy(x,y);
    }
    else{
        switch (caseD){
            case 2 :
            //cas -> droite
            x = getPositionXFromGrille( posGrilleI) - personnage->getX();
            if ( x>0){
                personnage->setX(personnage->getX()+x-20);
                personnage->setY(newY);
                personnage->getPicture()->moveBy(x-20,y);
            }
            break;

            case 1 :
            //cas -> gauche
            x = personnage->getX() -getPositionXFromGrille( posGrilleI) ;
            if ( x>0){
                personnage->setX(personnage->getX()+x-20);
                personnage->setY(newY);
                personnage->getPicture()->moveBy(x-20,y);
            }
            break;

            case 0 :
            //cas -> haut
            y = personnage->getY() -getPositionYFromGrille( posGrilleJ) ;
            if ( y>0){
                personnage->setX(newX);
                personnage->setY(personnage->getY()+y-36);
                personnage->getPicture()->moveBy(x,y-36);
            }
            break;

            case 3 :
            //cas -> bas
            y = getPositionYFromGrille( posGrilleJ) - personnage->getY() ;
            if ( y>0){
                personnage->setX(newX);
                personnage->setY(personnage->getY()+y-36);
                personnage->getPicture()->moveBy(x,y-36);
            }
            break;

        default : break;
        }

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
