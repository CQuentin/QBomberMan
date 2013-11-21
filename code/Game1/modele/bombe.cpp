#include "bombe.h"

Bombe::Bombe(QObject *parent = 0, int x = 0, int y = 0, int bmId = 1) : QObject(parent)
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
    exploded = false;
    bomberManId = bmId;
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
    else{
        switch (countDown) {
        case 100 :
            timer.start(100,this);
            countDown -= 20;
            currentImage = sprite.copy(49,239,14,15);
            break;
        case 80 :
            countDown -=20;
            currentImage = sprite.copy(30,239,16,16);
            break;
        case 60 :
            countDown -= 20;
            currentImage = sprite.copy(80,213,16,16);
            break;
        case 40 :
            countDown -= 20;
            currentImage = sprite.copy(57,213,15,16);
            break;
        case 20 :
            countDown -= 20;
            currentImage = sprite.copy(37,212,12,18);
            break;
        case 0 :
            countDown -= 20;
            currentImage = sprite.copy(24,212,4,18);
            break;
        }
    }

    if (countDown < 0 && !exploding){
        currentImage = sprite.copy(13,209,1,24);
        exploding = true;
    }
    else if (exploding){
        exploded = true;
        timer.stop();
    }
    picture->setPixmap(currentImage);
}

void Bombe::addExplosions(QGraphicsPixmapItem *pExplosion){
    explosions.append(pExplosion);
}

QVector<QGraphicsPixmapItem*> Bombe::getExplosions(){
    return explosions;
}

void Bombe::trigger(){

    timer.start(100,this);
countDown = -1;

}

int Bombe::getBManId(){
    return bomberManId;
}

Bombe::~Bombe(){
    delete this;
}
