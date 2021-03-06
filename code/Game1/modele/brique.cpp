#include "brique.h"


Brique::Brique(bool cassable,int x ,int y){
    posX = x;
    posY = y;
    this->cassable = cassable;

    QPixmap sprite = QPixmap("../Game1/ressource/sprites_bomberman.png");

    if(cassable)
        sprite = sprite.copy(48,560,20,20);
    else
        sprite = sprite.copy(18,560,20,20);

    picture = new QGraphicsPixmapItem(sprite);
    picture->setPos(x,y);
}

void Brique::setPicture(QGraphicsPixmapItem *picture){
    this->picture = picture;
}

QGraphicsPixmapItem* Brique::getPicture(){
    return picture;
}

bool Brique::estCassable(){
    return cassable;
}

Brique::~Brique(){
    delete this;
}
