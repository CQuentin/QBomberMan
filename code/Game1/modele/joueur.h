#ifndef JOUEUR_H
#define JOUEUR_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "brique.h"
#include <QDebug>
class Joueur
{
public:
    Joueur(int x ,int y);
    void newPosition (int x , int y);
    void detruireJoueur();
    QGraphicsPixmapItem *getPicture();
    void setPicture(QGraphicsPixmapItem *);
    bool isColising(int i, int j, QVector<QVector<Brique *> > grille);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

private :
    int posX;
    int posY;

    QGraphicsPixmapItem *picture;
};
#endif // JOUEUR_H
