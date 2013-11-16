#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    largeur = 900;
    hauteur = 600;
    gravity = 1;
    grille.resize(45);

    for(int i = 0; i<45; i++)
        grille[i].resize(30);

    scene = new QGraphicsScene(0, 0, largeur, hauteur, this);
    view = new QGraphicsView(scene, this);

    /*  -------------- début niveau -------------------- */

    //TODO : gérer avec des classes niveau
    ajouterPersonnage(5,3);
    ajouterBrique(false,5,5);

    for (int i =0; i< 45; i++)
        ajouterBrique(false,i,29);

    for (int j =29; j>= 15; j--)
        ajouterBrique(false,30,j);

    for (int i =30; i< 37; i++)
        ajouterBrique(false,i,15);

    /*  -------------- fin niveau -------------------- */

    // background = new QPixmap("IMG_8708_blue_Sky2.jpg");
    // scene->setBackgroundBrush(*background);

    timer.start(5, this);

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

    int correctionX = 0, correctionY = 0;
    int hauteurP = 36, largeurP = 22;
    switch(event->key()){
    case Qt::Key_Z:
        tryJump();
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
        correctionX = largeurP;
        qDebug()<<"droite";
        caseD = 2;
        break;
    case Qt::Key_S:
        y += 6;
        qDebug()<<"bas";
        correctionY = hauteurP;
        caseD = 3;
        break;
    default : break;
    }
    tryMove(x,y);

}

//TODO partie modèle à placer dans Joueur (garder partie graphique)
void MainWindow::tryMove(int x, int y){
    int hauteurP = 36, largeurP = 22, tailleC = 20;
    bool colision = false;
    int newX = personnage->getX()+x;
    int newY = personnage->getY()+y;

    // nombre de points du personnage espacés de 20px
    int nbPointX =1 + largeurP / tailleC;
    if (largeurP % tailleC !=0)
        nbPointX++;
    int nbPointY =1 + hauteurP / tailleC;
    if (hauteurP % tailleC !=0)
        nbPointY++;

    int posGrilleI;
    int posGrilleJ;

    // on regarde dans quelle partie de la grille se trouve chaque points espacés de 20px du personnage
    for (int i = 0; i< nbPointX; i++){
        if(i * tailleC > largeurP)
            posGrilleI = getGrilleIFromPosition(newX + largeurP);
        else
            posGrilleI = getGrilleIFromPosition(newX + i * tailleC);

        for (int j = 0; j< nbPointY; j++){
            if(j * tailleC > hauteurP)
                posGrilleJ = getGrilleJFromPosition(newY + hauteurP);
            else
                posGrilleJ = getGrilleJFromPosition(newY + j * tailleC);

            if(personnage->isColliding(posGrilleI,posGrilleJ,grille)){
                colision  = true;
            }
        }
    }

    if(!colision){
        personnage->setX(newX);
        personnage->setY(newY);
        personnage->getPicture()->moveBy(x,y);
    }
    // TODO
    // en cas de collision,on rapproche le personnage du bloc pour qu'il y soit collé
    /* else{


        switch (caseD){
            case 2 :
            posGrilleI = getGrilleIFromPosition(newX+largeurP);
            posGrilleJ = getGrilleIFromPosition(newY);
            //cas -> droite
            x = getPositionXFromGrille(posGrilleI) - personnage->getX();
            //qDebug()<<"cXB = "<<getPositionXFromGrille( posGrilleI);
            if ( x>0){
                personnage->setX(personnage->getX()+x);
                personnage->setY(newY);
                personnage->getPicture()->moveBy(x,y);
            }
            break;

            case 1 :
            //cas -> gauche
            x = personnage->getX() - (getPositionXFromGrille( posGrilleI) + tailleC) ;
            if ( x>0){
                personnage->setX(personnage->getX() - x);
                personnage->setY(newY);
                personnage->getPicture()->moveBy(-x,y);
            }
            break;

            case 0 :
            //cas -> haut
            y = personnage->getY() - (getPositionYFromGrille( posGrilleJ) + tailleC) ;
            if ( y>0){
                personnage->setX(newX);
                personnage->setY(personnage->getY() - y);
                personnage->getPicture()->moveBy(x,-y);
            }
            break;

            case 3 :
            //cas -> bas
            y = getPositionYFromGrille( posGrilleJ) - (personnage->getY() + hauteurP) ;
            if ( y>0){
                personnage->setX(newX);
                personnage->setY(personnage->getY()+y);
                personnage->getPicture()->moveBy(x,y);
            }
            break;

        default : break;
        }

    }*/
}

void MainWindow::tryJump(){
    int posI = getGrilleIFromPosition(personnage->getX());
    int posJ = getGrilleJFromPosition(personnage->getY() + 36);

    if(personnage->isColliding(posI,posJ+1,grille)){
        qDebug()<<"jump!";
        toggleGravity();
    }
}

void MainWindow::timerEvent ( QTimerEvent * event ){
    if (gravity<0){
        int posI = getGrilleIFromPosition(personnage->getX());
        int posJ = getGrilleJFromPosition(personnage->getY()+20);
        personnage->setCurrentH(personnage->getCurrentH()+1);

        if(personnage->getCurrentH()>= personnage->getMaxH() || personnage->isColliding(posI,posJ-1,grille)){
            toggleGravity();
            personnage->setCurrentH(0);
        }
    }
    tryMove(0,gravity);
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

void MainWindow::toggleGravity(){
    gravity = - gravity;
}

int MainWindow::getGravity(){
    return gravity;
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
