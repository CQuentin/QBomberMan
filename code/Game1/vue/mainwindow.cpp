#include "mainwindow.h"

/* Constructeur de la classe MainWindow */
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
{
    baseGravity = 1;
    largeur = 900;
    hauteur = 600;
    tailleC = 20;
    largeurG = largeur/tailleC;
    hauteurG = hauteur/tailleC;
    gravity = 0;
    grille.resize(largeurG);
    controleur = new ToucheClavier();

    for(int i = 0; i<largeurG; i++)
        grille[i].resize(hauteurG);

    scene = new QGraphicsScene(0, 0, largeur, hauteur, this);
    view = new QGraphicsView(scene, this);

    /*  -------------- début niveau -------------------- */

    //TODO : gérer avec des classes niveau
    ajouterPersonnage(5,3);
    ajouterBrique(false,5,5);

    for (int i =0; i< largeurG; i++)
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
        if(dec >=largeurG)
            dec = 44;
    }
    /*  -------------- fin niveau -------------------- */

    // background = new QPixmap("IMG_8708_blue_Sky2.jpg");
    // scene->setBackgroundBrush(*background);

    timer.start(5, this);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedWidth(largeur);
    view->setFixedHeight(hauteur);
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
    int hauteurP = personnage->getHauteur(), largeurP = personnage->getLargeur();
    bool colision = false;
    int newX = personnage->getX()+x;
    int newY = personnage->getY()+y;

    // nombre de points du personnage espacés de tailleCpx
    int nbPointX =1 + largeurP / tailleC;
    if (largeurP % tailleC !=0)
        nbPointX++;
    int nbPointY =1 + hauteurP / tailleC;
    if (hauteurP % tailleC !=0)
        nbPointY++;

    int posGrilleI;
    int posGrilleJ;

    // on regarde dans quelle partie de la grille se trouve chaque points espacés de tailleCpx du personnage
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
        gravity = -baseGravity;
}

void MainWindow::timerEvent ( QTimerEvent * event ){
    if (gravity<0){
        personnage->setCurrentH(personnage->getCurrentH()+1);
        if(personnage->getCurrentH()>= personnage->getMaxH() || collisionTest(0,-1)){
            gravity = baseGravity;
            personnage->setCurrentH(0);
        }
    }
    else if(collisionTest(0,1))
        gravity = 0;
    else gravity = baseGravity;

    int x = 0;
    if(gravity == 0 && controleur->getStateKeys(0))
        tryJump();

    //    if(controleur->getStateKeys(2))
    //        y += 1;
    if(controleur->getStateKeys(1)){
        x +=- 1;
    }
    else if(controleur->getStateKeys(3)){
        x += 1;
        personnage->courireD();
    }

   if(x == 0 && gravity == 0)
       personnage->immobile();

    tryMove(0,gravity);
    tryMove(x,0);
}

QPoint MainWindow::getPositionFromGrille(int i, int j){
    // tailleC car une case = tailleCp,
    // à modifier pour gérer les différentes tailles
    return QPoint(i * tailleC , j * tailleC );
}

int MainWindow::getPositionXFromGrille(int i){
    // tailleC car une case = tailleCp,
    // à modifier pour gérer les différentes tailles
    return i * tailleC;
}

int MainWindow::getPositionYFromGrille( int j){
    // tailleC car une case = tailleCp,
    // à modifier pour gérer les différentes tailles

    return j*tailleC;
}

int MainWindow::getGrilleIFromPosition(int x){
    return x/tailleC;
}

int MainWindow::getGrilleJFromPosition(int y){
    return  y/tailleC;
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
