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

    public:
            explicit MainWindow(QWidget * parent = 0);
            ~MainWindow();
        void keyPressEvent(QKeyEvent* event);
        void ajouter_brique(bool cassable, int x, int y);
        void afficher_mur();

    // public slots:
};

