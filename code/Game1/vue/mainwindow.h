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
class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QGraphicsScene * scene;
        QGraphicsView * view;
        QPixmap * background;
        std::vector<QGraphicsPixmapItem *> briques_cassables;
        std::vector<QGraphicsPixmapItem *> briques_incassables;
        QGraphicsPixmapItem * personnage;
        int largeur;
        int hauteur;

        // vector :  45 * 30 cases pour du 900*600. Une case = 20*20px
        // imaginer qu'on a un vector 2d de 45*30 pour utiliser x et y
        // Brique : remplacer plus tard par élément
        QVector<Brique*> grille;

    public:
            explicit MainWindow(QWidget * parent = 0);

        void keyPressEvent(QKeyEvent* event);
        void ajouterBrique(bool cassable, int x, int y);

        QPoint getPositionFromGrille(int x, int y);
        int getPositionXFromGrille(int i);
        int getPositionYFromGrille(int i);
        int getGrilleFromPosition(int x, int y);


         ~MainWindow();
    // public slots:
};

