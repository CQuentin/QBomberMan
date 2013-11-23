#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>
#include <QRect>
#include <QTransform>
#include "brique.h"
#include "bombe.h"

class Joueur
{
private :

    enum states
    {
        STANDING =0,
        RUNNING_D =1,
        RUNNING_G = 2,
        FALLING = 3,
        LANDING = 4,
        GETTING_UP = 5,
        JUMPING = 6,
        DROPING = 7
    };
    int id;
    int posX;
    int posY;
    int hauteur;
    int largeur;
    int maxHigh;
    int state;
    int currentHigh;
    int step;
    int pauseSprite;
    bool orientG;
    QPixmap sprite;
    QPixmap currentImage;
    QGraphicsPixmapItem *picture;
    int xSprite;
    int ySprite;
    int hSprite;
    int lSprite;
    int nbMaxBombes;
    int nbBombes;
    int hp;
    QVector<Bombe*> bombes;


public:
    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe Joueur
     *
     * \param x La position à l'abscisse du personnage
     * \param y La position à l'ordonnée du personnage
     * \author Clément CARLES
     * \author Quentin CHEYNET
     */
    Joueur(int id,int x ,int y);
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
    bool isColliding(int i, int j, QVector<QVector<Brique *> > grille);

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
     * \brief assignation d'un entier h à currentHigh
     * \param h La hauteur courrante après un saut
     * \author Quentin CHEYNET
     */
    void setCurrentH(int h);

    /*!
     * \brief renvoie la hauteur du personnage
     * \return hauteur
     * \author Quentin CHEYNET
     */
    int getHauteur();

    /*!
     * \brief assignation d'un entier h à hauteur
     * \param h La hauteur du personnage
     * \author Quentin CHEYNET
     */
    void setHauteur(int h);

    /*!
     * \brief renvoie la largeur du personnage
     * \return largeur
     * \author Quentin CHEYNET
     */
    int getLargeur();

    /*!
     * \brief assignation d'un entier l à largeur
     * \param l La largeur du personnage
     * \author Quentin CHEYNET
     */
    void setLargeur(int l);

    /*!
     * \brief change picture pour faire courir le personnage vers la droite
     * \author Quentin CHEYNET
     */
    void courireD();

    /*!
     * \brief change picture pour faire courir le personnage vers la gauche
     * \author Quentin CHEYNET
     */
    void courireG();

    /*!
     * \brief change picture en cas d'immobilité, en fonction de state
     * \author Quentin CHEYNET
     */
    void immobile();

    /*!
     * \brief assignation d'un entier s à state
     * \param s L'état du personnage
     * \author Quentin CHEYNET
     */
    void setCurrentS(int s);

    /*!
     * \brief renvoie l'état du personnage
     * \return state
     * \author Quentin CHEYNET
     */
    int getCurrentS();

    /*!
     * \brief assignation d'un entier n à nbMaxBombes
     * \param n Le nombre maximum de bombes déposées
     * \author Quentin CHEYNET
     */
    void setMaxBombes(int n);

    /*!
     * \brief renvoie le nombre maximum de bombes déposées
     * \return nbMaxBombes
     * \author Quentin CHEYNET
     */
    int getMaxBombes();

    /*!
     * \brief incrémente nbBombes
     * \author Quentin CHEYNET
     */
    void incrNbBombe();

    /*!
     * \brief décremente nbBombes
     * \author Quentin CHEYNET
     */
    void decrNbBombe();

    /*!
     * \brief pose une bombe si c'est possible
     * \return Vrai si le joueur peut poser une bombe, faux sinon
     * \author Quentin CHEYNET
     */
    bool tryDropBombe();

    /*!
     * \brief enleve un pv au joueur
     * \author Quentin CHEYNET
     */
    void hit();

    /*!
     * \brief regarde si le joueur est en vie
     * \return Vrai si le joueur est en vie
     * \author Quentin CHEYNET
     */
    bool isAlive();

    /*!
     * \brief Fait exploser toutes les bombes du joueur
     * innutilisé pour le moment
     * \author Quentin CHEYNET
     */
    void trigger();


    /*!
     * \brief assignation d'un entier id à id
     * \param id L'identifiant du joueur
     * \author Quentin CHEYNET
     */
    void setId(int id);

    /*!
     * \brief renvoie l' identifiant du joueur
     * \return id
     * \author Quentin CHEYNET
     */
    int getId();

    /*!
     * \brief assignation des nouvelles coordonées du sprite
     * \param x Position x du sprite
     * \param y Position y du sprite
     * \param l Largeur du sprite
     * \param h Hauteur du sprite
     * \author Quentin CHEYNET
     */
    void setCoordSprite(int x, int y, int l, int h);

    /*!
     * \brief renvoie les coordonées du sprite
     * \return un QVector contenant xSprite, ySprite, lSprite, hSprite
     * \author Quentin CHEYNET
     */
    QVector<int> getCoordSprite();

    /*!
     * \brief ajoute une bombe au QVector bombes du Joueur
     * \param b La bombe ajouté
     * \author Quentin CHEYNET
     */
    void addBombe(Bombe *b);

    /*!
     * \brief supprime une bombe
     * \param i L'indice de la bombe supprimée
     * \author Quentin CHEYNET
     */
    void removeBombe(int i);

    /*!
     * \brief renvoie la vector de bombe
     * \return bombes Le QVector de bombes lachées par le joueur
     * \author Quentin CHEYNET
     */
    QVector<Bombe*> getVectorBombes();

    /*!
     * \brief renvoie la dernière bombe posée par le joueur, si elle existe
     * \return la dernière bombe posée par le joueur, si elle existe, NULL sinon
     * \author Quentin CHEYNET
     */
    Bombe *getLastBombe();

    /*!
     * \brief renvoie si le personnage est orienté vers la gauche o non
     * \return Vrai si orientG = true, faux sinon
     * \author Quentin CHEYNET
     */
    bool isOrientG();

    /*!
     * \brief assignation d'un bool à orientG
     * \param o Le bool qui décide si orientG = true ou false
     * \author Quentin CHEYNET
     */
    void setOrientG(bool o);

    /*!
     * \brief change l'image du personnage
     *
     * utilisé uniquement pour les autres personnages
     *
     * \author Quentin CHEYNET
     */
    void refreshPicture();
};
#endif // JOUEUR_H
