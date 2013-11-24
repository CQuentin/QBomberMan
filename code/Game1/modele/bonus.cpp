#include "bonus.h"

Bonus::Bonus(int x, int y){
    posX = x;
    posY = y;


    type = qrand()%6;

    QPixmap sprite = QPixmap("../Game1/ressource/sprites_bonus.png");
    QPixmap currentImage;

    // TODO sprite
    switch(type){
    case HP :
        currentImage = sprite.copy(40,46,20,20);
        break;
    case EXPLOSION :
        currentImage = sprite.copy(0,83,20,20);
        break;
    case BOMBE :
        currentImage = sprite.copy(82,81,20,20);
        break;
    case JUMP :
        currentImage = sprite.copy(42,123,20,20);
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
