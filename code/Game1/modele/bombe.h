#ifndef BOMBE_H
#define BOMBE_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QRect>
#include <QTransform>
#include "brique.h"


class Bombe
{
private:
    int posX;
    int posY;
    int hauteur;
    int largeur;
    int pauseSprite;
    int power;
    QPixmap sprite;
    QPixmap currentImage;
    QGraphicsPixmapItem *picture;


public:
    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe Bombe
     *
     * \param x La position à l'abscisse de la bombe
     * \param y La position à l'ordonnée de la bombe
     * \author Quentin CHEYNET
     */
    Bombe(int x, int y);

    /*!
     * \brief renvoie la position x de la bombe
     * \return posX
     * \author Quentin CHEYNET
     */
    int getX();

    /*!
     * \brief renvoie la position y de la bombe
     * \return posY
     * \author Quentin CHEYNET
     */
    int getY();

    /*!
     * \brief assignation d'un entier x à posX
     * \param x La position x de la bombe
     * \author Quentin CHEYNET
     */
    void setX(int x);

    /*!
     * \brief assignation d'un entier y à posY
     * \param y La position y de la bombe
     * \author Quentin CHEYNET
     */
    void setY(int y);

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
     * \brief renvoie la hauteur de la bombe
     * \return hauteur
     * \author Quentin CHEYNET
     */
    int getHauteur();

    /*!
     * \brief assignation d'un entier h à hauteur
     * \param h La hauteur de la bombe
     * \author Quentin CHEYNET
     */
    void setHauteur(int h);

    /*!
     * \brief renvoie la largeur de la bombe
     * \return largeur
     * \author Quentin CHEYNET
     */
    int getLargeur();

    /*!
     * \brief assignation d'un entier l à largeur
     * \param l La largeur de la bombe
     * \author Quentin CHEYNET
     */
    void setLargeur(int l);

    /*!
     * \brief regarde si le timer de la bombe est à 0
     * \return Vrai si timer = 0, faux sinon
     * \author Quentin CHEYNET
     */
    bool isExploding();

    /*!
     * \brief renvoie la portée de la bombe
     * \return power
     * \author Quentin CHEYNET
     */
    int getPower();

    /*!
     * \brief assignation d'un entier p à powerr
     * \param p la portée de la bombe
     * \author Quentin CHEYNET
     */
    void setPower(int p);


    /*!
     * \brief Destructeur
     * Destructeur de la classe Bombe
     * \author Quentin CHEYNET
     */
    ~Bombe();
};

#endif // BOMBE_H
