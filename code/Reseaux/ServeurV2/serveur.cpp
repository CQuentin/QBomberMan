#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>

#include "serveur.h"

Serveur::Serveur(QWidget *parent)
    :   QDialog(parent)
{

    statutServeurLabel = new QLabel;
    dernierMessageLabel = new QLabel;
    dernierPortClientLabel = new QLabel;
    quitterBouton = new QPushButton(tr("Quitter"));
    quitterBouton->setAutoDefault(false);

    historique = new QTextEdit;
    historique->setReadOnly(true);

    tcpServeur = new QTcpServer(this);
    if (!tcpServeur->listen()) {
        QMessageBox::critical(this, tr("Serveur QBomberman ++"),
                               tr("Impossible de démarrer le serveur: %1.")
                               .arg(tcpServeur->errorString()));
        close();
        return;
    }
    statutServeurLabel->setText(tr("Le serveur est lancé sur le port %1.\n"
                            "En attente de clients...")
                         .arg(tcpServeur->serverPort()));

    dernierMessageLabel->setText(tr(""));
    dernierPortClientLabel->setText(tr(""));

    connect(quitterBouton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpServeur, SIGNAL(newConnection()), this, SLOT(seConnecterAuClient()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitterBouton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statutServeurLabel);
    mainLayout->addWidget(dernierMessageLabel);
    mainLayout->addWidget(dernierPortClientLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(historique);
    setLayout(mainLayout);

    setWindowTitle(tr("Serveur QBomberman ++"));
}

void Serveur::seConnecterAuClient()
{
    // Etablir connexion
    clientConnection = tcpServeur->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(retransmettreDonnees()));

    tailleBloc = 0;


}

void Serveur::retransmettreDonnees()
{
    // Mettre en place les flux de donnees
    QDataStream fluxEntree (clientConnection);
    fluxEntree.setVersion(QDataStream::Qt_4_0);

   /* historique->append(tr("debut fonction retransmettreDonnees, tailleBloc %1, BitDisponible %2")
                    .arg(tailleBloc).arg(clientConnection->bytesAvailable()));*/

    if (tailleBloc == 0) {
        if (clientConnection->bytesAvailable() < (int)sizeof(quint16))
            return;

        fluxEntree >> tailleBloc;
    }

    if (clientConnection->bytesAvailable() < tailleBloc)
        return;

    QString message;
    fluxEntree >> message;

    dernierMessageLabel->setText(tr("Dernier message : %1").arg(message));
    dernierPortClientLabel->setText(tr("Port Local du Dernier Client : %1").arg(clientConnection->peerPort()));
    historique->append(message);

    historique->append(tr("Envoi de message à %1").arg(clientConnection->peerPort()));

    QByteArray block;
    QDataStream fluxSortie(&block, QIODevice::WriteOnly);
    fluxSortie.setVersion(QDataStream::Qt_4_0);
    fluxSortie << (quint16)0;
    fluxSortie << message;
    fluxSortie.device()->seek(0);
    fluxSortie << (quint16)(block.size() - sizeof(quint16));

    clientConnection->write(block);

   /* historique->append(tr("fin fonction retransmettreDonnees, tailleBloc %1, BitDisponible %2")
                    .arg(tailleBloc).arg(clientConnection->bytesAvailable()));*/

    tailleBloc=0;

}
