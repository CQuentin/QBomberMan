#include "joueur.h"


Joueur::Joueur(int x ,int y){
    setX(x);
    setY(y);
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

void Joueur::newPosition(int x,int y){
    setX(x);
    setY(y);
}
