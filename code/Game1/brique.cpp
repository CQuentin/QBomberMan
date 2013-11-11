#include "brique.h"


Brique::Brique(bool cassable,int x ,int y){
    setX(x);
    setY(y);
    setCassable(cassable);
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

void Brique::setCassable(bool cassable){
    this->estCassable = cassable   ;
}
