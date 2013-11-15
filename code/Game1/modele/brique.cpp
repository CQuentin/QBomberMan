#include "brique.h"


Brique::Brique(bool cassable,int x ,int y){
    setX(x);
    setY(y);
    setCassable(cassable);

    if(cassable)
        picture = new QGraphicsPixmapItem(QPixmap("../Game1/ressource/brique_cassable.png"));
    else
        picture = new QGraphicsPixmapItem(QPixmap("../Game1/ressource/brique_incassable.png"));
     picture->setPos(x,y);
}

void Brique::detruireBrique(){
    delete this;
}

void Brique::setX(int x)
{
    this->posX = x;
}

void Brique::setY(int y)
{
    this->posY = y;
}

void Brique::setPicture(QGraphicsPixmapItem *picture){
    this->picture = picture;
}

QGraphicsPixmapItem* Brique::getPicture(){
    return picture;
}

void Brique::setCassable(bool cassable){
    this->estCassable = cassable   ;
}
