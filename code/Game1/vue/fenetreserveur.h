#ifndef FENETRESERVEUR_H
#define FENETRESERVEUR_H

#include <QMainWindow>

#include "ui_FenetreServeur.h"

#include "modele/reseau/serveur.h"
#include "mainwindow.h"

namespace Ui {
class FenetreServeur;
}

class FenetreServeur : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetreServeur(QWidget *parent = 0);
    ~FenetreServeur();


private slots:
    void on_okButton_clicked();

private:
    Ui::FenetreServeur *ui;
};

#endif // FENETRESERVEUR_H
