#include "joueur.h"


Joueur::Joueur(int x ,int y){
    setX(x);
    setY(y);
    picture = new QGraphicsPixmapItem(QPixmap("../Game1/ressource/personnage.png"));
    picture->setPos(x,y);

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
//Q
int Joueur::getX()
{
    return posX;
}
//Q
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

bool Joueur::isColising(int i, int j, QVector<QVector<Brique *> > grille){

    //TODO
    Brique *test = grille[i][j];

    if (test == NULL)
        return false;
    return true;
}
