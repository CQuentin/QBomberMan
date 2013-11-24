#ifndef BONUS_H
#define BONUS_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTime>
class Bonus
{

private :
    enum types
    {
        HP =0,
        EXPLOSION =1,
        BOMBE = 2,
        JUMP = 3,
        SPEED = 4,
        TRIGGER = 5
    };
    int posX;
    int posY;
    int type;
    QGraphicsPixmapItem *picture;


public:

    Bonus(int x ,int y);


    /*!
     * \brief renvoie le type de bonus
     * \return type
     * \author Quentin CHEYNET
     */
    int getBonusType();

    /*!
     * \brief renvoie l'attribut picture
     * \return picture
     * \author Quentin CHEYNET
     */
    QGraphicsPixmapItem *getPicture();

    ~Bonus();

};

#endif // BONUS_H
