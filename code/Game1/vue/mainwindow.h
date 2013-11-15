#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#endif MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <vector>
#include <QWidget>
    #include <QKeyEvent>
#include <QDebug>
#include <QVector>
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

        // vector :  45 * 30 cases pour du 900*600. Une case = 20*20px
        // imaginer qu'on a un vector 2d de 45*30 pour utiliser x et y
        // Brique : remplacer plus tard par élément
       QVector<QVector<Brique*> > grille;

    public:
            explicit MainWindow(QWidget * parent = 0);

        void keyPressEvent(QKeyEvent* event);
        void ajouterBrique(bool cassable, int i, int j);
        void ajouterPersonnage(int i, int j);

        QPoint getPositionFromGrille(int i, int j);
        int getPositionXFromGrille(int i);
        int getPositionYFromGrille(int j);
        int getGrilleIFromPosition(int x);
        int getGrilleJFromPosition(int y);


         ~MainWindow();
    // public slots:
};

