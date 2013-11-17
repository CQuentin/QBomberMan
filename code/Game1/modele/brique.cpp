#include "brique.h"


Brique::Brique(bool cassable,int x ,int y){
    setX(x);
    setY(y);
    setCassable(cassable);

    QPixmap sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");

    if(cassable)
         sprite = sprite.copy(48,560,20,20);
    else
         sprite = sprite.copy(18,560,20,20);

    picture = new QGraphicsPixmapItem(sprite);
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
