#ifndef QBOMBERMAN_H
#define QBOMBERMAN_H

#include <QMainWindow>
#include "ui_qbomberman.h"


class QBomberMan : public QMainWindow, public Ui::QBomberMan
{
    Q_OBJECT

public:
    explicit QBomberMan(QWidget *parent = 0);
    ~QBomberMan();

private slots:
    void on_creerPartie_clicked();

    void on_rejoindrePartie_clicked();

private:
    Ui::QBomberMan *ui;
};

#endif // QBOMBERMAN_H
