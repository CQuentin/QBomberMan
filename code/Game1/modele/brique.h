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

    /*!
     * \brief regarde si la brique est cassable
     * \return Vrai si la brique est cassable, faux sinon
     * \author Quentin CHEYNET
     */
    bool estCassable();


private :
    bool cassable;
    int posX;
    int posY;
    void setX(int x);
    void setY(int y);
    void setCassable(bool cassable);
    QGraphicsPixmapItem *picture;
};
#endif // BRIQUE_H
