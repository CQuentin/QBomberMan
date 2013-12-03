#ifndef BRIQUE_H
#define BRIQUE_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

/*! \class Brique
 * \brief classe représentant les briques
 * \author Quentin CHEYNET
 */

class Brique
{

private :
    bool cassable;                      /*!< vrai si la brique est cassable, faux sinon */
    int posX;                           /*!< position sur l'axe des abscisses */
    int posY;                           /*!< position sur l'axe des ordonnées */
    QGraphicsPixmapItem *picture;       /*!< image de la brique affichée */


public:
    /*!
     * \brief Constructeur
     *
     * Constructeur de la classe Brique
     * \param cassable Vrai si la brique est cassable, faux sinon
     * \param x La position à l'abscisse
     * \param y La position à l'ordonnée
     * \author Quentin CHEYNET
     */
    Brique(bool cassable, int x , int y);

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
