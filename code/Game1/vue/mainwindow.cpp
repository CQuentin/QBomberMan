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
    bombes.resize(0);

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

void MainWindow::ajouterBombe(int x, int y)
{
    Bombe *bombe = new Bombe(x,y);
    bombe->setY(bombe->getY() - bombe->getHauteur()+1);
    bombes.append(bombe);
    scene->addItem(bombe->getPicture());
}

void MainWindow::ajouterExplosion(int i, int j, int dx, int dy,bool end){
    QPixmap sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");
    QTransform transform;

    if(end)
        sprite = sprite.copy(48,591,20,20);
    else
        sprite = sprite.copy(18,591,20,20);


    if (dx == -1)
        sprite = sprite.transformed(transform.rotate( -180,Qt::YAxis ), Qt::FastTransformation);
    else if (dy != 0){
        sprite = sprite.transformed(transform.rotate( dy *90 ), Qt::FastTransformation);
    }


    QGraphicsPixmapItem *picture = new QGraphicsPixmapItem(sprite);
    picture->setPos(getPositionXFromGrille(i),getPositionYFromGrille(j));
    scene->addItem(picture);

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
//TODO partie modèle à placer dans Joueur (garder partie graphique)
void MainWindow::tryJump(){
    if(collisionTest(0,1)){
        gravity = -baseGravity;
        //        personnage->setCurrentS(6);
    }
}

void MainWindow::timerEvent ( QTimerEvent * event ){

    // ----------- partie personnage
    if (gravity<0){
        personnage->setCurrentH(personnage->getCurrentH()+1);
        if(personnage->getCurrentH()>= personnage->getMaxH() || collisionTest(0,-1)){
            gravity = baseGravity;
            personnage->setCurrentH(0);
        }
        else{
            personnage->setCurrentS(6);
            personnage->immobile();
        }

    }
    else if(collisionTest(0,1)){
        if(gravity == 1)
            personnage->setCurrentS(4); //LANDING
        gravity = 0;
    }
    else {
        gravity = baseGravity;
        personnage->setCurrentS(3); // FALLING
        personnage->immobile();
    }

    int x = 0;
    if(gravity == 0 && controleur->getStateKeys(0))
        tryJump();

    if(controleur->getStateKeys(2)){
        if (personnage->tryDropBombe()){
            // ajouter un truc du style personnage->getBonusBombe()
            ajouterBombe(personnage->getX(),personnage->getY()+ personnage->getHauteur());
            controleur->setPressed(Qt::Key_S,false);
        }
    }

    if(controleur->getStateKeys(1)){
        x +=- 1;
        personnage->courireG();
    }
    else if(controleur->getStateKeys(3)){
        x += 1;
        personnage->courireD();
    }

    if(x == 0 && gravity == 0 /*&& personnage->getCurrentS() != 3*/)
        personnage->immobile();

    tryMove(0,gravity);
    tryMove(x,0);

    // ----------- partie bombes
    int tmpSize = bombes.size();
    for(int i = 0; i<tmpSize; i++){
        if(bombes[i]->isExploding()){
            explosion(bombes[i],0,0);
            explosion(bombes[i],0,1);
            explosion(bombes[i],0,-1);
            explosion(bombes[i],1,0);
            explosion(bombes[i],-1,0);
            scene->removeItem((bombes[i])->getPicture());
            bombes.remove(i);
            tmpSize--;
        }
    }
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

void MainWindow::explosion(Bombe *bombe, int dx, int dy){

    int pI = getGrilleIFromPosition(personnage->getX());
    int pJ = getGrilleJFromPosition(personnage->getY());

    int posGrilleI = getGrilleIFromPosition(bombe->getX());
    int posGrilleJ = getGrilleJFromPosition(bombe->getY());
    int range = bombe->getPower();
    int i = posGrilleI, j= posGrilleJ;

    if(dx == 0 && dy == 0){
        if(pI == i && pJ == j  && personnage->isAlive() )
            personnage->hit();
        ajouterExplosion(i,j,dx,dy,false);
    }
    else{


        bool end = false;

        i = i +dx;
        j = j +dy;



        while((grille[i][j] == NULL || grille[i][j]->estCassable()) && range >0){
            if (range -1 <= 0)
                end = true;
            if(grille[i][j] != NULL){
                scene->removeItem(grille[i][j]->getPicture());
                grille[i][j]->detruireBrique();
                // = NULL ?
            }
            if(pI == i && pJ == j  && personnage->isAlive() )
                personnage->hit();
            ajouterExplosion(i,j,dx,dy,end);
            i = i + dx;
            j = j + dy;

            if (j < 0)
                j = 0;
            if (i < 0)
                i = 0;
            if (j > hauteurG)
                j = hauteurG;
            if (i > largeurG)
                i = largeurG;

            range --;
        }
    }

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
