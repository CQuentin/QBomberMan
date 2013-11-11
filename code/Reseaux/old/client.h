#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QTextEdit;
QT_END_NAMESPACE

class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);

private slots:
    void connexion();
    void deconnexion();
    void envoiMessage();
    void lireMessage();
    void displayError(QAbstractSocket::SocketError socketError);
    void activationConnexionBoutton();
private:
    QLabel *hoteLabel;
    QLabel *portLabel;
    QLabel *messageLabel;
    QLineEdit *hoteLigneEdit;
    QLineEdit *portLigneEdit;
    QLineEdit *messageLigneEdit;
    QTextEdit *historique;
    QPushButton *deconnexionBouton;
    QPushButton *connexionBouton;
    QPushButton *envoiMessageBouton;
    QPushButton *quitteBouton;
    QDialogButtonBox *boutonBox;

    QTcpSocket *tcpSocket;
    quint16 blockSize;
};


#endif
