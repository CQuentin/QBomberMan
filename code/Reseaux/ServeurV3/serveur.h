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
    ~Serveur();

private slots:
    void retransmettreDonnees();
    void seConnecterAuClient();

private:
    QTextEdit   *m_historique;
    QLabel      *m_statutServeurLabel;
    QPushButton *m_quitterBouton;
    QLabel      *m_dernierMessageLabel;
    QLabel      *m_dernierPortClientLabel;
    QTcpServer  *m_tcpServeur;
    QTcpSocket  *m_clientConnection;
    QDataStream  m_fluxEntree;
    quint16      m_tailleBloc;

    void initialiserLabels();
    void initialiserBoutons();
    void initialiserTextEdit();
    void initialiserLayouts();
    void initialiserServeur();
    void initialiserFenetre(QString nomFenetre);
    void liaisonSignauxSlots();
};
#endif // SERVEUR_H
