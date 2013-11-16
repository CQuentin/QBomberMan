#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    largeur = 900;
    hauteur = 600;
    gravity = 0;
    grille.resize(45);
    controleur = new ToucheClavier();

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

    int dec = 0;
    for(int j = 23; j>=15; j-=2){
        for (int i =6; i< 16; i++)
            ajouterBrique(false,i+dec,j);
        dec+= 4;
        if(dec >=45)
            dec = 44;
    }
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

void MainWindow::keyReleaseEvent(QKeyEvent* event) {

    if(!event->isAutoRepeat()){
        controleur->setPressed(event->key(),false);
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {

    if(!event->isAutoRepeat())
        controleur->setPressed(event->key(),true);
}

bool MainWindow::collisionTest(int x, int y){
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

    return colision;
}

//TODO partie modèle à placer dans Joueur (garder partie graphique)
void MainWindow::tryMove(int x, int y){
    int newX = personnage->getX()+x;
    int newY = personnage->getY()+y;

    if(!collisionTest(x,y)){
        personnage->setX(newX);
        personnage->setY(newY);
        personnage->getPicture()->moveBy(x,y);
    }


}

void MainWindow::tryJump(){
    if(collisionTest(0,1))
        gravity = -1;
}

void MainWindow::timerEvent ( QTimerEvent * event ){
    if (gravity<0){
        personnage->setCurrentH(personnage->getCurrentH()+1);
        if(personnage->getCurrentH()>= personnage->getMaxH() || collisionTest(0,-1)){
            gravity = 1;
            personnage->setCurrentH(0);
        }
    }
    else if(collisionTest(0,1))
        gravity = 0;
    else gravity = 1;

    int x = 0,y = 0;
    if(gravity == 0 && controleur->getStateKeys(0))
        tryJump();
    if(controleur->getStateKeys(1))
        x +=- 1;
    //    if(controleur->getStateKeys(2))
    //        y += 1;
    if(controleur->getStateKeys(3)){
        x += 1;
    }
    tryMove(0,gravity);
    tryMove(x,y);
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
        for(int j=0; j<(int) grille[i].size(); j++)
            delete grille[i][j];
    delete personnage;
    delete view;
    delete scene;
    // delete background;
}
