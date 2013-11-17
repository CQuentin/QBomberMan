#include "bombe.h"

Bombe::Bombe(int x, int y)
{
    posX = x;
    posY = y;
    sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");
    currentImage = sprite.copy(66,238,13,15);
    picture = new QGraphicsPixmapItem(currentImage);
    picture->setPos(x,y);
    hauteur = 20;
    largeur = 20;
    pauseSprite = 15;
    power = 4;
}

void Bombe::setX(int x)
{
    posX = x;
    picture->setX(x);
}

void Bombe::setY(int y)
{
    posY = y;
    picture->setY(y);
}

int Bombe::getX()
{
    return posX;
}

int Bombe::getY()
{
    return posY;
}

int Bombe::getHauteur(){
    return hauteur;
}

void Bombe::setHauteur(int h){
    hauteur = h;
}

int Bombe::getLargeur(){
    return largeur;
}

void Bombe::setLargeur(int l){
    largeur = l;
}

void Bombe::setPicture(QGraphicsPixmapItem *picture){
    this->picture = picture;
}

QGraphicsPixmapItem* Bombe::getPicture(){
    return picture;
}

bool Bombe::isExploding(){
    return false;
}

int Bombe::getPower(){
    return power;
}

void Bombe::setPower(int p){
    power = p;
}

Bombe::~Bombe(){
    delete this;
}
