#ifndef FENETRESERVEUR_H
#define FENETRESERVEUR_H

#include <QMainWindow>

#include "ui_FenetreServeur.h"

#include "modele/reseau/serveur.h"
#include "mainwindow.h"

namespace Ui {
class FenetreServeur;
}

/*! \class FenetreServeur
 * \brief classe représentant la fenetre de création d'une partie
 * \author Sébastien Trousse
 */
class FenetreServeur : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Constructeur
     * \author Sébastien Trousse
     */
    explicit FenetreServeur(QWidget *parent = 0);

    /*!
     * \brief Destructeur
     * \author Sébastien Trousse
     */
    ~FenetreServeur();


private slots:

    /*!
     * \brief Slot boutton OK
     * \author Sébastien Trousse
     */
    void on_okButton_clicked();

private:
    Ui::FenetreServeur *ui; /*! Graphisme de la fenetre */
};

#endif // FENETRESERVEUR_H
