#ifndef SERVEUR_H
#define SERVEUR_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include <QStringList>
#include "modele/joueur.h"


class Serveur : public QTcpServer
{
    Q_OBJECT

public:
    Serveur(int,int,QObject *parent = 0);
    ~Serveur();
    int getSizeClients();
    int getNbUtilisateur();

private slots:
    void readyRead();
    void disconnected();
    void envoyerListeUtilisateur();

protected:
    void incomingConnection(int descripteurSocket);

private:
    QSet<QTcpSocket*>         m_clients;
    //QMap<QTcpSocket*,Joueur > m_utilisateurs;
    QMap<QTcpSocket*,int >    m_utilisateurs;
    quint16                   m_tailleBloc;
    int                       m_nbUtilisateur;
    static int                m_clientIdCourant;
    int                       m_niv;
};

#endif // SERVEUR_H
