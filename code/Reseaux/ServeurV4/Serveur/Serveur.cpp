#include "serveur.h"

Serveur::Serveur(QObject *parent) : QTcpServer(parent)
{

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
 * @brief Serveur::pretALire
 */
void Serveur::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString ligne = QString::fromUtf8(client->readLine()).trimmed();
        qDebug() << "Read line:" << ligne;

        QRegExp meRegex("^/me:(.*)$");

        if(meRegex.indexIn(ligne) != -1)
        {
            QString utilisateur = meRegex.cap(1);
            m_utilisateurs[client] = utilisateur;
            foreach(QTcpSocket *client, m_clients)
                client->write(QString("Serveur:" + utilisateur + " a rejoint le serveur.\n").toUtf8());
            envoyerListeUtilisateur();
        }
        else if(m_utilisateurs.contains(client))
        {
            QString message = ligne;
            QString utilisateur = m_utilisateurs[client];
            qDebug() << "Utilisateur:" << utilisateur;
            qDebug() << "Message:" << message;

            foreach(QTcpSocket *otherClient, m_clients)
                otherClient->write(QString(utilisateur + ":" + message + "\n").toUtf8());
        }
        else
        {
            qWarning() << "Erreur du client:" << client->peerAddress().toString() << ligne;
        }
    }
}



/**
 * Slot
 * @brief Serveur::clientDeconnecte
 */
void Serveur::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client deconnecte:" << client->peerAddress().toString();

    m_clients.remove(client);

    QString user = m_utilisateurs[client];
    m_utilisateurs.remove(client);

    envoyerListeUtilisateur();
    foreach(QTcpSocket *client, m_clients)
        client->write(QString("Serveur:" + user + " est parti.\n").toUtf8());
}

/**
 * Slot
 * @brief Serveur::envoyerListeUtilisateur
 */
void Serveur::envoyerListeUtilisateur()
{
    QStringList listeUtilisateur;
    foreach(QString utilisateur, m_utilisateurs.values())
        listeUtilisateur << utilisateur;

    foreach(QTcpSocket *client, m_clients)
        client->write(QString("/users:" + listeUtilisateur.join(",") + "\n").toUtf8());
}

/**
 * @brief Serveur::incomingConnection
 * @param descripteurSocket
 */
void Serveur::incomingConnection(int descripteurSocket)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(descripteurSocket);
    m_clients.insert(client);

    qDebug() << "Nouveau client :" << client->peerAddress().toString();

    connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}
