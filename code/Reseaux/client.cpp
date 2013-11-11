#include <QtWidgets>
#include <QtNetwork>
#include <QtGui>

#include "client.h"


Client::Client(QWidget *parent)
:   QDialog(parent)
{

    hoteLabel = new QLabel(tr("&IP:"));
    portLabel = new QLabel(tr("&Port:"));
    messageLabel = new QLabel(tr("&Message:"));

    hoteLigneEdit = new QLineEdit;
    portLigneEdit = new QLineEdit;
    portLigneEdit->setValidator(new QIntValidator(1, 65535, this));
    messageLigneEdit = new QLineEdit;

    hoteLabel->setBuddy(hoteLigneEdit);
    portLabel->setBuddy(portLigneEdit);
    messageLabel->setBuddy(messageLigneEdit);


    historique = new QTextEdit;

    connexionBouton = new QPushButton(tr("Connexion"));
    connexionBouton->setDefault(true);
    connexionBouton->setEnabled(false);

    envoiMessageBouton = new QPushButton(tr("Envoyer un message"));
    envoiMessageBouton->setEnabled(false);

    deconnexionBouton = new QPushButton(tr("Deconnexion"));
    deconnexionBouton->setEnabled(false);

    quitteBouton = new QPushButton(tr("Quitter"));

    boutonBox = new QDialogButtonBox;
    boutonBox->addButton(envoiMessageBouton, QDialogButtonBox::ActionRole);
    boutonBox->addButton(deconnexionBouton, QDialogButtonBox::ActionRole);
    boutonBox->addButton(connexionBouton, QDialogButtonBox::ActionRole);
    boutonBox->addButton(quitteBouton, QDialogButtonBox::RejectRole);

    tcpSocket = new QTcpSocket(this);

    connect(hoteLigneEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(activationConnexionBoutton()));
    connect(portLigneEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(activationConnexionBoutton()));
    connect(deconnexionBouton, SIGNAL(clicked()),
            this, SLOT(deconnexion()));
    connect(connexionBouton, SIGNAL(clicked()),
            this, SLOT(connexion()));

    connect(envoiMessageBouton, SIGNAL(clicked()),
            this, SLOT(envoiMessage()));

    connect(quitteBouton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(lireMessage()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(hoteLabel, 0, 0);
    mainLayout->addWidget(hoteLigneEdit, 0, 1);
    mainLayout->addWidget(portLabel, 1, 0);
    mainLayout->addWidget(portLigneEdit, 1, 1);
    mainLayout->addWidget(messageLabel, 2, 0);
    mainLayout->addWidget(messageLigneEdit, 2, 1);
    mainLayout->addWidget(historique, 5, 0, 4, 2);
    mainLayout->addWidget(boutonBox, 9, 0, 1, 2);
    setLayout(mainLayout);

    setWindowTitle(tr("Client"));
    portLigneEdit->setFocus();
}


void Client::connexion()
{
    connexionBouton->setEnabled(false);
    deconnexionBouton->setEnabled(true);
    envoiMessageBouton->setEnabled(true);
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(hoteLigneEdit->text(),
                             portLigneEdit->text().toInt());

}

void Client::deconnexion()
{
    connexionBouton->setEnabled(true);
    deconnexionBouton->setEnabled(false);
    envoiMessageBouton->setEnabled(false);
    tcpSocket->abort();
    historique->append(("Deconnexion"));

}

void Client::envoiMessage()
{
    blockSize = 0;

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << messageLigneEdit->text();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
    historique->append(tr("Envoie > %1").arg(messageLigneEdit->text()));

}

void Client::lireMessage()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if(blockSize == 0){
        if(tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if(tcpSocket->bytesAvailable() < blockSize)
        return;

    QString recu;
    in >> recu;
    qDebug() << recu;
    historique->append(tr("Recu > %1").arg(recu));
    envoiMessageBouton->setEnabled(true);
    blockSize = 0;

}

void Client::displayError(QAbstractSocket::SocketError socketError){
    switch(socketError)
    {
        case QAbstractSocket::HostNotFoundError:
            historique->append(tr("ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port."));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            historique->append(tr("ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port."));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            historique->append(tr("ERREUR : le serveur a coupé la connexion."));
            break;
        default:
            historique->append(tr("ERREUR : ") + tcpSocket->errorString());
    }

        connexionBouton->setEnabled(true);
}

void Client::activationConnexionBoutton()
{
    connexionBouton->setEnabled(!hoteLigneEdit->text().isEmpty()
                                 && !portLigneEdit->text().isEmpty());
}

