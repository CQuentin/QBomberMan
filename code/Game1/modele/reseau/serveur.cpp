#include "serveur.h"

Serveur::Serveur(int t, QObject *parent) : QTcpServer(parent)
{
    m_nbUtilisateur = t;
   m_clientIdCourant = -1;
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
        //qDebug() << "Read line:" << ligne;

       QRegExp meRegex("^/me:(.*)$");
       QRegExp deplacementRegex("^/p:(.*)$");
       QRegExp bombeRegex("^/bom:(.*)$");
       QRegExp declenchementRegex("^/t:([0-9]+)$");


        if(meRegex.indexIn(ligne) != -1){

            int utilisateur = m_clientIdCourant;
            m_utilisateurs[client] = utilisateur;
            //m_utilisateurs[client] = j;
            qDebug() << utilisateur;
           // qDebug() << m_utilisateurs[client];

             client->write(QString("/i: %1 $\n").arg(utilisateur).toUtf8());

            envoyerListeUtilisateur();


        }
        else if(m_utilisateurs.contains(client))
        {
             if(deplacementRegex.indexIn(ligne) != -1 || bombeRegex.indexIn(ligne) != -1 || declenchementRegex.indexIn(ligne) != -1){
                QString message = ligne;
                foreach(QTcpSocket *otherClient, m_clients)
                    otherClient->write(QString(message + "\n").toUtf8());
             }
        }
        else
        {
            qWarning() << "Erreur du client:" << client->peerAddress().toString() << ligne;
        }
    }
}



/**
 * Slot
 * @brief Serveur::disconnected
 */
void Serveur::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client deconnecte:" << client->peerAddress().toString();

    m_clients.remove(client);

    //QString user = m_utilisateurs[client];
    m_utilisateurs.remove(client);

    /*envoyerListeUtilisateur();
    foreach(QTcpSocket *client, m_clients)
        client->write(QString("Serveur:" + user + " est parti.\n").toUtf8());*/
}

/**
 * Slot
 * @brief Serveur::envoyerListeUtilisateur
 */
void Serveur::envoyerListeUtilisateur()
{
    QStringList listeUtilisateur;
    foreach(int utilisateur, m_utilisateurs.values())
        listeUtilisateur << QString::number(utilisateur);

    foreach(QTcpSocket *client, m_clients)
        client->write(QString("/users:" + listeUtilisateur.join(",") + "\n").toUtf8());
}

/**
 * @brief Serveur::incomingConnection
 * @param descripteurSocket
 */
void Serveur::incomingConnection(int descripteurSocket)
{
    if(m_clients.size() < m_nbUtilisateur){

        QTcpSocket *client = new QTcpSocket(this);
        m_clientIdCourant++;
        client->setSocketDescriptor(descripteurSocket);
        m_clients.insert(client);

        qDebug() << "Nouveau client :" << client->peerAddress().toString();

        connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
    }
    // TODO: Gerer erreur serveur plein
}

int Serveur::getSizem_clients(){
    return m_clients.size();
}

int Serveur::getm_nbUtilisateur(){
    return m_nbUtilisateur;
}
