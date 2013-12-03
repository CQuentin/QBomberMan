#ifndef BONUS_H
#define BONUS_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QTime>


/*! \class Bombe
 * \brief classe représentant les bonus
 * \author Quentin CHEYNET
 */
class Bonus
{

private :
    /*!
     * \brief ensemble des différents types d'un bonus
     * \author Quentin CHEYNET
     */
    enum types
    {
        HP =0,                          /*!< bonus augmentant la vie */
        EXPLOSION =1,                   /*!< bonus augmentant power (la portée des bombes) */
        BOMBE = 2,                      /*!< bonus augmentant le nombre de bombes pouvant être posées simultanément */
        JUMP = 3,                       /*!< bonus augmentant hauteur du saut, puis donnant la capactié de voler */
        SPEED = 4,                      /*!< bonus augmentant la vitesse de déplacement */
        TRIGGER = 5                     /*!< bonus donnant la possibilité de déclancher les bombes à distance, et supprimme leur timer */
    };
    int posX;                           /*!< position sur l'axe des abscisse */
    int posY;                           /*!< position sur l'axe des ordonnée */
    int type;                           /*!< type du bonus (choisi dans l'enum types */
    QGraphicsPixmapItem *picture;       /*!< image du bonus affichée */


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
