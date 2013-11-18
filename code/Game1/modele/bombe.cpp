#include "bombe.h"

Bombe::Bombe(QObject *parent = 0, int x = 0, int y = 0) : QObject(parent)
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
    countDown = 3100;
    timer.start(1000,this);
    exploding = false;
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
    return exploding;
}
bool Bombe::hasExploded(){
    return exploded;
}

int Bombe::getPower(){
    return power;
}

void Bombe::setPower(int p){
    power = p;
}

void Bombe::timerEvent ( QTimerEvent * event ){

    if (countDown > 100)
        countDown -=1000;
    else if (countDown == 100){
        timer.start(100,this);
        countDown -= 20;
        //image
    }
    else if (countDown <100){
        countDown -=20;
        //image
    }
    if (countDown < 0 && !exploding){
        timer.start(300,this);
        exploding = true;
    }
    else if (exploding){
        exploded = true;
        timer.stop();
    }
}

void Bombe::addExplosions(QGraphicsPixmapItem *pExplosion){
    explosions.append(pExplosion);
}

QVector<QGraphicsPixmapItem*> Bombe::getExplosions(){
    return explosions;
}

Bombe::~Bombe(){
    delete this;
}
