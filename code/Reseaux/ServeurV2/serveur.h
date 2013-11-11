#ifndef SERVEUR_H
#define SERVEUR_H


#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTcpServer;
class QTcpSocket;
class QTextEdit;
QT_END_NAMESPACE

class Serveur : public QDialog
{
    Q_OBJECT

public:
    Serveur(QWidget *parent = 0);

private slots:
    void retransmettreDonnees();
    void seConnecterAuClient();

private:
    QTextEdit *historique;
    QLabel *statutServeurLabel;
    QPushButton *quitterBouton;
    QLabel *dernierMessageLabel;
    QLabel *dernierPortClientLabel;
    QTcpServer *tcpServeur;
    QTcpSocket *clientConnection;
    QDataStream fluxEntree;
    quint16 tailleBloc;

};
#endif // SERVEUR_H
