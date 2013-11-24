#include "bonus.h"

Bonus::Bonus(int x, int y){
    posX = x;
    posY = y;

    type = qrand()%6;

    // TODO sprite
    switch(type){
    case HP :
        break;
    case EXPLOSION :
        break;
    case BOMBE :
        break;
    case JUMP :
        break;
    case SPEED :
        break;
    case TRIGGER :
        break;
    }

}

int Bonus::getBonusType(){
    return type;
}

QGraphicsPixmapItem* Bonus::getPicture(){
    return picture;
}
