#ifndef SERVEUR_H
#define SERVEUR_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include <QStringList>


class Serveur : public QTcpServer
{
    Q_OBJECT

public:
    Serveur(QObject *parent = 0);
    ~Serveur();

private slots:
    void readyRead();
    void disconnected();
    void envoyerListeUtilisateur();

protected:
    void incomingConnection(int descripteurSocket);

private:
    QSet<QTcpSocket*>         m_clients;
    QMap<QTcpSocket*,QString> m_utilisateurs;
    quint16                   m_tailleBloc;

};

#endif // SERVEUR_H
