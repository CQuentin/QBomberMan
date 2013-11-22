#include "Serveur.h"

Serveur::Serveur(int t, QObject *parent) : QTcpServer(parent)
{
    m_nbUtilisateur = t;
    m_clientIdCourant = 1;
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
       QRegExp depRegex("^/dep:(.*)$");
       Q
       //   QRegExp meRegex("^/me:$");


        if(meRegex.indexIn(ligne) != -1){
            Joueur j = new Joueur(5,10);
            //QString utilisateur = "J" + QString::number(m_clientIdCourant);
            //m_utilisateurs[client] = utilisateur;
            m_utilisateurs[client] = j;
           // qDebug() << utilisateur;
            qDebug() << m_utilisateurs[client];
            /*
             foreach(QTcpSocket *client, m_clients)
                client->write(QString("Serveur:" + utilisateur + " a rejoint le serveur.\n").toUtf8());
            */
            envoyerListeUtilisateur();
            ++m_clientIdCourant;
        }
        else if(m_utilisateurs.contains(client))
        {
             if(depRegex.indexIn(ligne) != -1){
                QString message = ligne;
                // QString utilisateur = m_utilisateurs[client];
             /*   qDebug() << "Utilisateur:" << utilisateur;
                qDebug() << "Message:" << message;*/

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
    foreach(Joueur utilisateur, m_utilisateurs.values())
        listeUtilisateur << utilisateur.id << " " << utilisateur.getX() << " " << utilisateur.getY();

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
