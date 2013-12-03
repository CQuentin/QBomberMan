#ifndef BOMBE_H
#define BOMBE_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QtMultimedia/QSound>
#include <QPixmap>
#include <QDebug>
#include <QRect>
#include <QTransform>
#include <QBasicTimer>
#include <QVector>
#include "brique.h"


/*! \class Bombe
 * \brief classe représentant les bombes
 * \author Quentin CHEYNET
 */
class Bombe: public QObject
{
private:
    int posX;                                   /*!< position sur l'axe des abscisse */
    int posY;                                   /*!< position sur l'axe des ordonnées */
    int hauteur;                                /*!< hauteur de la bombe */
    int largeur;                                /*!< largeur de la bombe */
    int pauseSprite;                            /*!< pause (en nombe de tic du timer) entre le changement de chaque image */
    int power;                                  /*!< puissance de la bombe (portée des explosions) */
    int countDown;                              /*!< temps écoulé en ms avant l'explosion de la bombe */
    bool exploding;                             /*!< vrai si la bombe est en train d'exploser, faux sinon */
    bool exploded;                              /*!< vrai si la bombe a explosé, faux sinon */
    QVector <QGraphicsPixmapItem*> explosions;       /*!< QVector des explosions de la bombe (une explosion étant une image de 20x20) */
    QBasicTimer timer;                          /*!< timer gérant le countDown et le changement d'image */
    QPixmap sprite;                             /*!< le fichier des sprites */
    QPixmap currentImage;                       /*!< l'image utilisée actuellement */
    QGraphicsPixmapItem *picture;               /*!< l'image affiché */
    int bomberManId;                            /*!< l'id du Joueur qui a posé la bombe */


public:
    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe Bombe
     * \param parent : QObject parent
     * \param x La position à l'abscisse de la bombe
     * \param y La position à l'ordonnée de la bombe
     * \param bmId Identifiant du Joueur ayant posé la bombe
     * \author Quentin CHEYNET
     */
    Bombe(QObject *parent, int x, int y, int bmId);

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
     * \brief regarde si la bombe est en train d'exploser (timer = 0)
     * \return Vrai si exploding == true, faux sinon
     * \author Quentin CHEYNET
     */
    bool isExploding();

    /*!
     * \brief regarde la bombe a explosé
     * \return Vrai si exploded == 0, faux sinon
     * \author Quentin CHEYNET
     */
    bool hasExploded();

    /*!
     * \brief renvoie la portée de la bombe
     * \return power
     * \author Quentin CHEYNET
     */
    int getPower();

    /*!
     * \brief assignation d'un entier p à power
     * \param p la portée de la bombe
     * \author Quentin CHEYNET
     */
    void setPower(int p);

    /*!
     * \brief timer de la bombe
     * \param event
     * \author Quentin CHEYNET et Jean-Phillipe Huguet(gestion son)
     */
    void timerEvent ( QTimerEvent * event );

    /*!
     * \brief ajoute une explosion au QVector explosions
     * \param pExplosion
     * \author Quentin CHEYNET
     */
    void addExplosions(QGraphicsPixmapItem * pExplosion);

    /*!
     * \brief renvoie le QVector explosions
     * \return explosions
     * \author Quentin CHEYNET
     */
    QVector<QGraphicsPixmapItem*> getExplosions();

    /*!
     * \brief fait exploser une bombe
     * \author Quentin CHEYNET
     */
    void trigger();

    /*!
     * \brief renvoie l'identifiant du poseur de la bombe
     * \return bomberManId
     * \author Quentin CHEYNET
     */
    int getBManId();

    /*!
     * \brief stop le timer de la bombe
     * \author Quentin CHEYNET
     */
    void stopCountDown();

    /*!
     * \brief lance le timer de la bombe
     * \author Quentin CHEYNET
     */
    void startCountDown();

    /*!
     * \brief Destructeur
     * Destructeur de la classe Bombe
     * \author Quentin CHEYNET
     */
    ~Bombe();
};

#endif // BOMBE_H
