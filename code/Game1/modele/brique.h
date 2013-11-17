#ifndef BRIQUE_H
#define BRIQUE_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
class Brique
{
public:
    Brique(bool cassable,int x ,int y);
    void detruireBrique();
    /*!
     * \brief renvoie l'attribut picture
     * \return picture
     * \author Quentin CHEYNET
     */
    QGraphicsPixmapItem *getPicture();
    /*!
     * \brief assignation d'un QGraphicsPixmapItem à l'attribut picture
     * \param parent : QGraphicsPixmapItem *
     * \author Quentin CHEYNET
     */
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
