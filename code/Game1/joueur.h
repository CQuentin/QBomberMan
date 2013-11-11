#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur
{
public:
    Joueur(int x ,int y);
    void newPosition (int x , int y);
    void detruireJoueur();

private :
    int posX;
    int posY;
    void setX(int x);
    void setY(int y);
};
#endif // JOUEUR_H
