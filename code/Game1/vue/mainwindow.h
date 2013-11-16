#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QWidget>
#include <QKeyEvent>
#include <QTimerEvent>
#include <QDebug>
#include <QVector>
#include<QBasicTimer>
#include "../modele/brique.h"
#include "../modele/joueur.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QGraphicsScene * scene;
        QGraphicsView * view;
        QPixmap * background;
        Joueur * personnage;
        int largeur;
        int hauteur;
        QBasicTimer timer;
        int gravity;

        // vector :  45 * 30 cases pour du 900*600. Une case = 20*20px
        // Brique : remplacer plus tard par élément
       QVector<QVector<Brique*> > grille;

    public:
       /*!
        * \brief Constructeur
        *
        * Constructeur de la classe MainWindow
        *
        * \param parent : QMainWindow parent
        * \author Quentin CHEYNET
        */
            explicit MainWindow(QWidget * parent = 0);

       /*!
        * \brief détéction des évènement clavier (touches enfoncées)
        * \param event
        * \author Quentin CHEYNET
        */
        void keyPressEvent(QKeyEvent* event);

        /*!
         * \brief détéction des évènement clavier (touches relachées)
         * \param event
         * \author Quentin CHEYNET
         */
        void keyReleaseEvent(QKeyEvent* event);

        /*!
         * \brief timerEvent pour faire tomber un personnage
         *
         * \param event
         * \author Quentin CHEYNET
         */
        void timerEvent ( QTimerEvent * event );

        /*!
         * \brief ajoute une brique dans la vue
         *
         * Une instance de Brique est créée. Elle est ajoutée dans
         * l'attribut grille, puis elle est affiché dans la scène
         *
         * \param cassable Décide si la nouvelle brique est cassable ou non
         * \param i Colonne de la grille
         * \param j Ligne de la grille
         * \author Quentin CHEYNET
         */
        void ajouterBrique(bool cassable, int i, int j);

        /*!
         * \brief ajoute un personnage dans la vue
         *
         * Une instance de Joueur est créée, puis elle est affiché dans la scène
         *
         * \param i Colonne de la grille
         * \param j Ligne de la grille
         * \author Quentin CHEYNET
         */
        void ajouterPersonnage(int i, int j);

        /*!
         * \brief renvoie la position en pixel d'un objet dans la scene
         *
         * Un objet (Joueur, Brique, Bombe, Explosion) est représenté
         * dans grille (QVector deux dimmensions), mais son image (attribut picture )
         * doit s'afficher dans la scene, avec une position exprimé en pixel.
         * La fonction calcule x et y à partir des indices i et j, et renvoie
         * un QPoint (x,y).
         *
         * \param i Colonne de la grille
         * \param j Ligne de la grille
         * \return Un QPoint, correspondant à la position dans la scène
         * \author Quentin CHEYNET
         */
        QPoint getPositionFromGrille(int i, int j);

        /*!
         * \brief renvoie l'abscisse en pixel d'un objet dans la scene
         *
         * Un objet (Joueur, Brique, Bombe, Explosion) est représenté
         * dans grille (QVector deux dimmensions), mais son image (attribut picture )
         * doit s'afficher dans la scene, avec une position exprimé en pixel.
         * La fonction calcule x à partir de l' indice i et renvoie x
         *
         * \param i Colonne de la grille
         * \return x, correspondant à l'abscisse dans la scène
         * \author Quentin CHEYNET
         */
        int getPositionXFromGrille(int i);

        /*!
         * \brief renvoie l'ordonnée en pixel d'un objet dans la scene
         *
         * Un objet (Joueur, Brique, Bombe, Explosion) est représenté
         * dans grille (QVector deux dimmensions), mais son image (attribut picture )
         * doit s'afficher dans la scene, avec une position exprimé en pixel.
         * La fonction calcule y à partir de l' indice j et renvoie y
         *
         * \param j Ligne de la grille
         * \return y, correspondant à l'ordonnée dans la scène
         * \author Quentin CHEYNET
         */
        int getPositionYFromGrille(int j);

        /*!
         * \brief renvoie la colonne i d'un objet dans la grille
         *
         * Un objet (Joueur, Brique, Bombe, Explosion) est représenté
         * dans grille (QVector deux dimmensions), mais son image (attribut picture )
         * s'affiche dans la scene, avec une position exprimé en pixel.
         * La fonction calcule l'indice i de la grille à partire de l'abscisse x
         *
         * \param x Abscisse de l'image dans scene
         * \return i,colonne de la grille
         * \author Quentin CHEYNET
         */
        int getGrilleIFromPosition(int x);

        /*!
         * \brief renvoie la ligne j d'un objet dans la grille
         *
         * Un objet (Joueur, Brique, Bombe, Explosion) est représenté
         * dans grille (QVector deux dimmensions), mais son image (attribut picture )
         * s'affiche dans la scene, avec une position exprimé en pixel.
         * La fonction calcule l'indice j de la grille à partire de l'ordonnée y
         *
         * \param x Ordonnée de l'image dans scene
         * \return j,ligne de la grille
         * \author Quentin CHEYNET
         */
        int getGrilleJFromPosition(int y);

        /*!
         * \brief fait bouger un personnage en prenant en compte les collisions
         *  TODO : placer une partie dans Joueur
         * \param x Abscisse de l'image dans scene
         * \param Y Ordonnée de l'image dans scene
         * \author Quentin CHEYNET
         */
        void tryMove(int x, int y);
        /*!
         * \brief fait sauter un personnage en prenant en compte les collisions
         *  TODO : placer une partie dans Joueur
         * \author Quentin CHEYNET
         */
        void tryJump();

        /*!
         * \brief inverse le signe de la gravité
         * \author Quentin CHEYNET
         */
        void toggleGravity();

        /*!
         * \brief renvoie la valeur de la gravité
         * \return gravity
         * \author Quentin CHEYNET
         */
        int getGravity();

         ~MainWindow();
    // public slots:
};
#endif
