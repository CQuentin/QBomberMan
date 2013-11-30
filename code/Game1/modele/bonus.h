#ifndef BONUS_H
#define BONUS_H

#include <QGraphicsPixmapItem>
#include <QtMultimedia/QSound>
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

    /*!
     * \brief constructeur de la classe Bonus
     * \param x La position x du bonus
     * \param y La position y du bonus
     * \param t Le type du bonus (-1 si il doit être défini)
     * \author Quentin CHEYNET
     */
    Bonus(int x , int y, int t);


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

    /*!
     * \brief destructeur de la classe Bonus
     * \author Quentin CHEYNET
     */
    ~Bonus();

};

#endif // BONUS_H
