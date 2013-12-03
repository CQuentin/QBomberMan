#ifndef QBOMBERMAN_H
#define QBOMBERMAN_H

#include <QMainWindow>
#include "ui_qbomberman.h"

/*! \class QBomberMan
 * \brief classe représentant la fenetre d'acceuil
 * \author Jérémy Vaz Borges
 */
class QBomberMan : public QMainWindow, public Ui::QBomberMan
{
    Q_OBJECT

public:
    /*!
     * \brief Constructeur
     * \author Jérémy Vaz Borges
     */
    explicit QBomberMan(QWidget *parent = 0);

    /*!
     * \brief Destructeur
     * \author Jérémy Vaz Borges
     */
    ~QBomberMan();

private slots:

    /*!
     * \brief Slot boutton creer partie
     * \author Sébastien Trousse
     */
    void on_creerPartie_clicked();

    /*!
     * \brief Slot boutton rejoindre partie
     * \author Sébastien Trousse
     */
    void on_rejoindreChannel_clicked();

    /*!
     * \brief Slot boutton Rejoindre de la fenetre rejoindre partie
     * \author Jérémy Vaz Borges
     */
    void on_rejoindreBtn_clicked();

    /*!
     * \brief Slot boutton OK de la fenetre creer partie
     * \author Jérémy Vaz Borges
     */
    void on_okButton_clicked();

private:
    Ui::QBomberMan *ui; /*! Graphisme de la fenetre */
};

#endif // QBOMBERMAN_H
