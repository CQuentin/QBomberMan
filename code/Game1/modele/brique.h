#ifndef BRIQUE_H
#define BRIQUE_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
class Brique
{

private :
    bool cassable;
    int posX;
    int posY;
    void setX(int x);
    void setY(int y);
    void setCassable(bool cassable);
    QGraphicsPixmapItem *picture;


public:
    Brique(bool cassable,int x ,int y);
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

    /*!
     * \brief Destructeur
     * Destructeur de la classe Brique
     * \author Quentin CHEYNET
     */
    ~Brique();

};
#endif // BRIQUE_H
