#ifndef JOUEUR_H
#define JOUEUR_H
#include <QGraphicsPixmapItem>
#include <QtMultimedia/QSound>
#include <QPixmap>
#include <QDebug>
#include <QRect>
#include <QTransform>
#include <QPainter>
#include "brique.h"
#include "bombe.h"


/*! \class Joueur
 * \brief classe représentant les joueurs
 * \author Quentin CHEYNET
 */
class Joueur
{
private :

    /*!
     * \brief ensemble des différents états du Joueur (utilisé surtout pour les sprites)
     * \author Quentin CHEYNET
     */
    enum states
    {
        STANDING =0,                        /*!< le personnage est debout, sur le sol, et ne fait rien */
        RUNNING_R =1,                       /*!< le personnage court vers la droite */
        RUNNING_L = 2,                      /*!< le personnage court vers la gauche */
        FALLING = 3,                        /*!< le personnage est en train de tomber */
        LANDING = 4,                        /*!< le personnage atterit sur le sol */
        GETTING_UP = 5,                     /*!< le personnage se relève après avoir atteri sur le sol */
        JUMPING = 6,                        /*!< le personnage est dans les air après un saut, avant d'avoir atteint sa hauteur maximal */
        DROPING = 7,                        /*!< le personnage lache une bombe */
        DYING = 8,                          /*!< le personnage est en train de mourrir */
        DEAD = 9,                           /*!< le personnage est mort */
        WINNING = 10                        /*!< le personnage a gagné et s'en réjouit */
    };

    int id;                                 /*!< id du personnage */
    int posX;                               /*!< position sur l'axe des abscisses */
    int posY;                               /*!< position sur l'axe des ordonnées */
    int hauteur;                            /*!< hauteur du personnage */
    int largeur;                            /*!< largeur du personnage */
    int maxHigh;                            /*!< la distance maximum sur y parcourue lors d'un saut */
    int state;                              /*!< type du bonus (choisi dans l'enum states) */
    int currentHigh;                        /*!< distance sur y actuellement parcouru après un saut */
    int step;                               /*!< indique quelle sprite utiliser lors de l'enchainement de plusieurs sprites */
    int pauseSprite;                        /*!< pause (en nombe de tic du timer) entre le changement de chaque image */
    bool orientG;                           /*!< vrai si le joueur est orienté vers la gauche, faux sinon (utilisé pour les sprites) */
    QPixmap sprite;                         /*!< le fichier des sprites */
    QPixmap currentImage;                   /*!< l'image utilisée actuellement */
    QGraphicsPixmapItem *picture;           /*!< l'image affiché */
    int xSprite;                            /*!< position x de l'image voulu dans le fichier des sprites */
    int ySprite;                            /*!< position y de l'image voulu dans le fichier des sprites */
    int hSprite;                            /*!< hauteur de l'image voulu dans le fichier des sprites */
    int lSprite;                            /*!< largeur de l'image voulu dans le fichier des sprites */
    int nbMaxBombes;                        /*!< nombre maximum de bombes que le Joueur peut poser simultanément */
    int nbBombes;                           /*!< nombre de bombes non explosée que le Joueur a actuellement posée */
    int hp;                                 /*!< nombre de point de vie du Joueur */
    QVector<Bombe*> bombes;                 /*!< listes des bombes posées par le Joueur */
    bool immortality;                       /*!< vrai si le joueur est immortel, faux sinon */
    int immortalityCD;                      /*!< durée actuelle de l'immortalité */
    int bonusPower;                         /*!< nombre de bonus de type EXPLOSION ramassé par le joueur */
    int bonusJump;                          /*!< nombre de bonus de type JUMP ramassé par le joueur */
    bool bonusTrigger;                      /*!< vrai si le joueur a ramassé le bonus de type TRIGGER, faux sinon */
    int tired;                              /*!< permet de savoir si le personnage peut se déplacer ou non (sert à ralentir la vitesse de déplacement) */
    int nbKills;                            /*!< nombre de joueurs que vous avez tués */
    int killBy;                             /*!< id du Joueur qui vous a tués */

public:

    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe Joueur
     *
     * \param id L'identifiant du Joueur
     * \param x La position à l'abscisse du personnage
     * \param y La position à l'ordonnée du personnage
     * \author Quentin CHEYNET
     */
    Joueur(int id,int x ,int y);

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
    * \param grille L'ensembles des briques
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

    /*!
     * \brief active l'animation de la mort, puis met state à DEAD
     * \author Quentin CHEYNET et Jean-Phillipe Huguet(gestion son)
     */
    void die();

    /*!
     * \brief gère l'imortalité (sprite, bool immortality)
     * \author Quentin CHEYNET
     */
    void checkImmortality();


    /*!
     * \brief reçoit un bonus et modifie les caratéristiques du Joueur
     * \param t Le type de bonus
     * \author Quentin CHEYNET et Jean-Phillipe Huguet(gestion son)
     */
    void receiveBonus(int t);


    /*!
     * \brief regarde si le personnage a le bonus pour faire exploser une bombe
     * \return vrai si bonusTrigger est vrai, faux sinon
     * \author Quentin CHEYNET
     */
    bool hasBonusTrigger();

    /*!
     * \brief renvoie la valeur de bonusJump
     *
     * bonusJump est le nombre de fois que le joueur a ramassé un bonus pour sauter (max 2)
     *
     * \return bonusJump
     * \author Quentin CHEYNET
     */
    int getBonusJump();

    /*!
     * \brief renvoie la valeur tired
     * \return tired, pour savoir si le personnage fait une pause avance
     * \author Quentin CHEYNET
     */
    int getTired();

    /*!
     * \brief assignation d'un entier à tired
     * \param t La nouvelle valeur de tired
     * \author Quentin CHEYNET
     */
    void setTired(int t);

    /*!
     * \brief regarde si le personnage est immortel
     * \return vrai si immortality = vrai, faux sinon
     * \author Quentin CHEYNET
     */
    bool isImmortal();

    /*!
     * \brief assignation d'un bool à immortality
     * \param i vrai si le personnage doit être immortel, faux sinon
     * \author Quentin CHEYNET
     */
    void setImmortality(bool i);


    /*!
     * \brief retourne la valeur de bonusPower
     * \return La valeur de l'explosion des bombes du Joueur
     * \author Quentin CHEYNET
     */
    int getPowerBomb();

    /*!
     * \brief assignation d'un entier à bonusPower
     * \param p La valeur de l'explosion des bombes du Joueur
     * \author Quentin CHEYNET
     */
    void setPowerBomb(int p);

    /*!
     * \brief assignation d'un bool à bonusTrigger
     * \param t vrai si le personnage doit avoir le bonus pour déclencher les bombes
     * \author Quentin CHEYNET
     */
    void setTriggerBomb(bool t);

    /*!
     * \brief met les sprites de la victoire
     * \author Quentin CHEYNET
     */
    void cheer();

    /*!
     * \brief assignation d'un entier à killBy
     * \param idJ L'identifiant du joueur qui vous a tué
     * \author Quentin CHEYNET
     */
    void setKillBy(int idJ);


    /*!
     * \brief retourne la valeur de killBy
     * \return killBy l'identifiant du joueur qui vous a tué
     * \author Quentin CHEYNET
     */
    int getKillBy();

    /*!
     * \brief retourne la valeur de nbKills
     * \return nbKills Le nombre de joueur que vous avez tué
     * \author Quentin CHEYNET
     */
    int getNbKills();

    /*!
     * \brief augmente le nombre de personnage tué de 1
     * \author Quentin CHEYNET
     */
    void incrNbKills();

    /*!
     * \brief Destructeur
     * Destructeur de la classe Joueur
     * \author Quentin CHEYNET
     */
    ~Joueur();
};
#endif // JOUEUR_H
