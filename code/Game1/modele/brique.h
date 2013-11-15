#ifndef BRIQUE_H
#define BRIQUE_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
class Brique
{
public:
    Brique();
    Brique(bool cassable,int x ,int y);
    void detruireBrique();
    QGraphicsPixmapItem *getPicture();
    void setPicture(QGraphicsPixmapItem *);

private :
    bool estCassable;
    int posX;
    int posY;
    void setX(int x);
    void setY(int y);
    void setCassable(bool cassable);
    QGraphicsPixmapItem *picture;
};
#endif // BRIQUE_H
