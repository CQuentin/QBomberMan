#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>

#include "serveur.h"

/**
 * Constructeur par défaut
 * @brief Serveur::Serveur
 * @param parent
 */
Serveur::Serveur(QWidget *parent)
    :   QDialog(parent)
{
    initialiserServeur();
    initialiserLabels();
    initialiserBoutons();
    initialiserTextEdit();
    liaisonSignauxSlots();
    initialiserLayouts();
    initialiserFenetre("Serveur QBomberman ++");
}
/**
 * Destructeur par défaut
 * @brief Serveur::~Serveur
 */
Serveur::~Serveur()
{

}

/**
 * Slot
 * @brief Serveur::seConnecterAuClient
 */
void Serveur::seConnecterAuClient()
{
    // Etablir connexion
    m_statutServeurLabel->setText(tr("Connecté..."));
    m_clientConnection = m_tcpServeur->nextPendingConnection();
    connect(m_clientConnection, SIGNAL(disconnected()), m_clientConnection, SLOT(deleteLater()));
    connect(m_clientConnection, SIGNAL(readyRead()), this, SLOT(retransmettreDonnees()));
}

/**
 * Slot
 * @brief Serveur::retransmettreDonnees
 */
void Serveur::retransmettreDonnees()
{
    // Mettre en place les flux de donnees
    QDataStream fluxEntree (m_clientConnection);
    fluxEntree.setVersion(QDataStream::Qt_4_0);

    if (m_tailleBloc == 0) {
        if (m_clientConnection->bytesAvailable() < (int)sizeof(quint16)){ return; }
        fluxEntree >> m_tailleBloc;
    }

    if (m_clientConnection->bytesAvailable() < m_tailleBloc)
        return;

    QString message;
    fluxEntree >> message;

    m_dernierMessageLabel->setText(tr("Dernier message : %1").arg(message));
    m_dernierPortClientLabel->setText(tr("Port du dernier client : %1").arg(m_clientConnection->peerPort()));
    m_historique->append(message);
    m_historique->append(tr("Envoi de message à %1").arg(m_clientConnection->peerPort()));

    QByteArray buffer;
    QDataStream fluxSortie(&buffer, QIODevice::WriteOnly);
    fluxSortie.setVersion(QDataStream::Qt_4_0);
    fluxSortie << (quint16)0;
    fluxSortie << message;
    fluxSortie.device()->seek(0);
    fluxSortie << (quint16)(buffer.size() - sizeof(quint16));

    m_clientConnection->write(buffer);
    m_tailleBloc = 0;

}
/**
 * Sert à initialiser les différents labels de l'interface graphique
 * @brief Serveur::initialiserLabels
 */
void Serveur::initialiserLabels()
{
    m_statutServeurLabel     = new QLabel(
                tr("Le serveur est lancé sur le port %1.\n"
                   "En attente de clients...").arg(m_tcpServeur->serverPort()));
    m_dernierMessageLabel    = new QLabel(tr(""));
    m_dernierPortClientLabel = new QLabel(tr(""));
}

void Serveur::initialiserBoutons()
{
    m_quitterBouton = new QPushButton(tr("Quitter"));
    m_quitterBouton->setAutoDefault(false);
}

void Serveur::initialiserTextEdit()
{
    m_historique = new QTextEdit;
    m_historique->setReadOnly(true);
}

/**
 * Sert à initialiser les différents layouts de l'interface graphique
 * @brief Serveur::initialiserLayouts
 */
void Serveur::initialiserLayouts()
{
    QHBoxLayout *boutonsLayout   = new QHBoxLayout;
    QVBoxLayout *principalLayout = new QVBoxLayout;

    boutonsLayout->addStretch(1); // permet de centrer le bouton (il faut les deux)
    boutonsLayout->addWidget(m_quitterBouton);
    boutonsLayout->addStretch(1); // permet de centrer le bouton
    principalLayout->addWidget(m_statutServeurLabel);
    principalLayout->addWidget(m_dernierMessageLabel);
    principalLayout->addWidget(m_dernierPortClientLabel);
    principalLayout->addLayout(boutonsLayout); // intègre le layout des boutons au principal
    principalLayout->addWidget(m_historique);

    setLayout(principalLayout);
}

/**
 * Sert à initialiser le socket du serveur
 * @brief Serveur::initialiserLayouts
 */
void Serveur::initialiserServeur()
{
    m_tailleBloc = 0;
    m_tcpServeur = new QTcpServer(this);

    if (!m_tcpServeur->listen()) {
        QMessageBox::critical(this, tr("Serveur QBomberman ++"),
                              tr("Impossible de démarrer le serveur: %1.")
                              .arg(m_tcpServeur->errorString()));
        close(); // ferme la fenêtre
        return;
    }
}

/**
 *
 * @brief Serveur::liaisonSignauxSlots
 */
void Serveur::liaisonSignauxSlots()
{
    connect(m_quitterBouton, SIGNAL(clicked()),       this, SLOT(close()));
    connect(m_tcpServeur,    SIGNAL(newConnection()), this, SLOT(seConnecterAuClient()));
    connect(m_statutServeurLabel, SIGNAL(closeConnection(), this, SLOT(seConnecterAuClient());
}

void Serveur::initialiserFenetre(QString nomFenetre)
{
    setWindowTitle(tr(nomFenetre.toStdString().c_str()));
}
