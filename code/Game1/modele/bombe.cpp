#include "bombe.h"

Bombe::Bombe(int x, int y)
{
    posX = x;
    posY = y;
}

void Bombe::setX(int x)
{
    posX = x;
}

void Bombe::setY(int y)
{
    posY = y;
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
