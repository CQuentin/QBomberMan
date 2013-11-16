#include "joueur.h"


Joueur::Joueur(int x ,int y){
    setX(x);
    setY(y);
    picture = new QGraphicsPixmapItem(QPixmap("../Game1/ressource/personnage.png"));
    picture->setPos(x,y);
    maxHigh = 50;
    currentHigh = 0;
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
