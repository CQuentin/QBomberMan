#ifndef SERVEUR_H
#define SERVEUR_H

/*!
 * \file serveur.h
 * \brief Gestion de la partie réseau coté serveur
 * \author Jérémy VAZ BORGES et Sébastien TROUSSE
 */


#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include <QStringList>
#include "modele/joueur.h"

/*! \class Serveur
 * \brief classe gérant le serveur
 * \author Jérémy VAZ BORGES et Sébastien TROUSSE
 */
class Serveur : public QTcpServer
{
    Q_OBJECT

public:
    /*!
     * \brief Constructeur
     * \author Jérémy VAZ BORGES
     */
    Serveur(int,int,QObject *parent = 0);

    /*!
     * \brief Destructeur
     * Destructeur de la classe Serveur
     * \author Sébastien TROUSSE
     */
    ~Serveur();    

private slots:
    /*!
     * \brief Slots de lecture
     * Lit le message reçu et le traite
     * \author Jérémy VAZ BORGES et Sébastien TROUSSE
     */
    void readyRead();

    /*!
     * \brief Slots de déconnection
     * Gestion de la déconnection d'un client
     * \author Sébastien TROUSSE
     */
    void disconnected();

    /*!
     * \brief Slots de synchronisation des joueurs presents
     * \author Sébastien TROUSSE
     */
    void envoyerListeUtilisateur();

protected:
    /*!
     * \brief Slots de gestion de connection
     * Gestion de la connection d'un client
     * \author Jérémy VAZ BORGES et Sébastien TROUSSE
     */
    void incomingConnection(int descripteurSocket);

private:
    QSet<QTcpSocket*>         m_clients;            /*!< Liste des sockets clients */
    QMap<QTcpSocket*,int >    m_utilisateurs;       /*! Liste des sockets et identifiants clients */
    int                       m_nbUtilisateur;      /*! Nombre maximum de client sur la partie */
    static int                m_clientIdCourant;    /*! Identifiant du client courant */
    int                       m_niv;                /*! Numéro du niveau */
};

#endif // SERVEUR_H
