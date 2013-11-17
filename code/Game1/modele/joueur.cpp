#include "joueur.h"


Joueur::Joueur(int x ,int y){
    setX(x);
    setY(y);
    sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");
    currentImage = sprite.copy(11,505,22,36);
    picture = new QGraphicsPixmapItem(currentImage);
    picture->setPos(x,y);
    hauteur = 35;
    largeur = 20;
    maxHigh = 50;
    currentHigh = 0;
    step = 0;
    pauseSprite = 15;
    state = STANDING;
}

void Joueur::detruireJoueur(){
    delete this;
}

void Joueur::setX(int x)
{
    this->posX = x;
}

void Joueur::setY(int y)
{
    this->posY = y;
}

int Joueur::getX()
{
    return posX;
}

int Joueur::getY()
{
    return posY;
}

void Joueur::newPosition(int x,int y){
    setX(x);
    setY(y);
}

void Joueur::setPicture(QGraphicsPixmapItem *picture){
    this->picture = picture;
}

QGraphicsPixmapItem* Joueur::getPicture(){
    return picture;
}

bool Joueur::isColliding(int i, int j, QVector<QVector<Brique *> > grille){

    Brique *test = grille[i][j];

    if (test == NULL)
        return false;
    return true;
}


int Joueur::getMaxH(){
    return maxHigh;
}

int Joueur::getCurrentH(){
    return currentHigh;
}

void Joueur::setMaxH(int h){
    maxHigh = h;
}

void Joueur::setCurrentH(int h){
    currentHigh = h;
}

int Joueur::getHauteur(){
    return hauteur;
}

void Joueur::setHauteur(int h){
    hauteur = h;
}

int Joueur::getLargeur(){
    return largeur;
}

void Joueur::setLargeur(int l){
    largeur = l;
}

void Joueur::courireD(){
    if (state == STANDING)
        step = 0;

    state = RUNNING_D;
    if(pauseSprite >= 15){
        switch(step){
        case 0:
            currentImage = sprite.copy(13,28,32,34);
            step = 1;
            break;
        case 1:
            currentImage = sprite.copy(57,28,20,34);
            step = 2;
            break;
        case 2:
            currentImage = sprite.copy(83,29,27,33);
            step = 3;
            break;
        case 3:
            currentImage = sprite.copy(116,28,20,34);
            step = 4;
            break;
        case 4:
            currentImage = sprite.copy(141,27,20,35);
            step = 5;
            break;
        case 5:
            currentImage = sprite.copy(167,28,20,34);
            step = 6;
            break;
        case 6:
            currentImage = sprite.copy(193,29,27,33);
            step = 7;
            break;
        case 7:
            currentImage = sprite.copy(226,28,20,34);
            step = 8;
            break;
        case 8:
            currentImage = sprite.copy(252,27,20,35);
            step = 1;
            break;
        }
        pauseSprite = 0;

        picture->setPixmap(currentImage);

        //dans les sprite 2 et 6, le point le plus à gauche n'est plus la tête
        //adoucit le mouvement (différence de 4px -> diff de 2px puis 2px)
        // ATTENTION : pendant un court moment, le joueur voit son personnage à 2 px de là
        // où il est rééllement
        if(step == 3 || step == 7)
            picture->moveBy(-2,0);
        else if(step == 4 || step == 8)
            picture->moveBy(2,0);

    }
    else pauseSprite ++;



}

void Joueur::immobile(){
    if(pauseSprite >= 30){
        switch(state){
        case STANDING :
            currentImage = sprite.copy(11,505,22,36);
            break;

        case RUNNING_D :
            currentImage = sprite.copy(294,28,25,34);
            state = STANDING;
            break;
        case RUNNING_G : //TODO pic
            state = STANDING;
            break;
            //    case FALLING :
            //        currentImage = sprite.copy(200,73,32,41);
            //        state
        case LANDING :
            currentImage = sprite.copy(238,85,27,31);
            state = GETTING_UP;
            break;
        case GETTING_UP :
            currentImage = sprite.copy(272,83,20,33);
            state = STANDING;
            break;
        }

        pauseSprite = 0;
        picture->setPixmap(currentImage);
    }
    else
        pauseSprite++;

}
