#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include "brique.h"
class Joueur
{
public:
    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe Joueur
     *
     * \param x,y La position du personnage
     * \author Clément CARLES,Quentin CHEYNET
     */
    Joueur(int x ,int y);
    void newPosition (int x , int y);
    void detruireJoueur();
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
    * \brief renvoie vrai si le la case[i][j] contient une brique
    * \param i Ligne de la grille à regarder
    * \param j Colonne de la grille à regarder
    * \author Quentin CHEYNET
    */
    bool isColising(int i, int j, QVector<QVector<Brique *> > grille);

    /*!
     * \brief renvoie la position x du personnage
     * \return posX
     * \author Quentin CHEYNET
     */
    int getX();

    /*!
     * \brief renvoie la position y du personnage
     * \return posY
     * \author Quentin CHEYNET
     */
    int getY();

    /*!
     * \brief assignation d'un entier x à posX
     * \param x La position x du personnage
     * \author Clément CARLES
     */
    void setX(int x);

    /*!
     * \brief assignation d'un entier y à posY
     * \param y La position y du personnage
     * \author Clément CARLES
     */
    void setY(int y);

    /*!
     * \brief renvoie la hauteur maximum à laquelle le personnage peut sauter
     * \return maxHigh
     * \author Quentin CHEYNET
     */
    int getMaxH();

    /*!
     * \brief renvoie la hauteur courrante après un saut
     * \return currentHigh
     * \author Quentin CHEYNET
     */
    int getCurrentH();

    /*!
     * \brief assignation d'un entier h à maxHigh
     * \param h La hauteur maximum à laquelle le personnage peut sauter
     * \author Quentin CHEYNET
     */
    void setMaxH(int h);

    /*!
     * \brief assignation d'un entier h à currantH
     * \param h La hauteur courrante après un saut
     * \author Quentin CHEYNET
     */
    void setCurrentH(int h);

private :
    int posX;
    int posY;
    int maxHigh;
    int currentHigh;
    QGraphicsPixmapItem *picture;


};
#endif // JOUEUR_H
