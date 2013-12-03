#include "bonus.h"

Bonus::Bonus(int x, int y, int t){
    posX = x;
    posY = y;

    if(t < 0)
        type = qrand()%6;
    else
        type = t;

    QPixmap sprite = QPixmap("../Game1/ressource/sprites_bonus.png");
    QPixmap currentImage;

    switch(type){
    case HP :
        currentImage = sprite.copy(2,43,20,20);
        break;
    case EXPLOSION :
        currentImage = sprite.copy(0,83,20,20);
        break;
    case BOMBE :
        currentImage = sprite.copy(82,81,20,20);
        break;
    case JUMP :
        currentImage = sprite.copy(81,0,20,20);
        break;
    case SPEED :
        currentImage = sprite.copy(0,0,20,20);
        break;
    case TRIGGER :
        currentImage = sprite.copy(0,123,20,20);
        break;
    }

    picture = new QGraphicsPixmapItem(currentImage);
    picture->setPos(x,y);

}

int Bonus::getBonusType(){
    return type;
}

QGraphicsPixmapItem* Bonus::getPicture(){
    return picture;
}
