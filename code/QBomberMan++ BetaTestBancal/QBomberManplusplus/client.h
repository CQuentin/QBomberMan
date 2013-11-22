#ifndef CLIENT_H
#define CLIENT_H
#include "modele/joueur.h"
#include "modele/bombe.h"
#include <QTcpSocket>
#include <QVector>
#include "vue/mainwindow.h"



class Client : public QTcpSocket
{
public:
    Q_OBJECT

    Client(QObject *parent = 0);
    ~Client();
public slots:
    void readyRead();
    void connected();

private:

    QVector<Joueur*> m_utilisateurs;
    QVector<Bombe*> m_bombes;
    MainWindow* scene ;


    // TODO void deplacerJoueur();
};

#endif // CLIENT_H
