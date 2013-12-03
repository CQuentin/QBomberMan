#include "serveur.h"

int Serveur::m_clientIdCourant = -1;

Serveur::Serveur(int t,int niv, QObject *parent) : QTcpServer(parent)
{
    m_nbUtilisateur = t;
    m_niv = niv;
}


Serveur::~Serveur(){}

void Serveur::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString ligne = QString::fromUtf8(client->readLine()).trimmed();

        QRegExp meRegex("^/me:(.*)$");
        QRegExp deplacementRegex("^/p:(.*)$");
        QRegExp bombeRegex("^/bom:(.*)$");
        QRegExp addBonusRegex("^/abon:(.*)$");
        QRegExp removeBonusRegex("^/rbon:(.*)$");
        QRegExp declenchementRegex("^/t:(.*)$");
        QRegExp killsRegex("^/k:(.*)$");

        if(meRegex.indexIn(ligne) != -1){
            int utilisateur = m_clientIdCourant;
            m_utilisateurs[client] = utilisateur;            

            client->write(QString("/i:%1 %2 %3 $\n").arg(utilisateur).arg(m_nbUtilisateur).arg(m_niv).toUtf8());

            envoyerListeUtilisateur();
        }
        else if(m_utilisateurs.contains(client))
        {
            if(deplacementRegex.indexIn(ligne) != -1 || bombeRegex.indexIn(ligne) != -1 || declenchementRegex.indexIn(ligne) != -1 || addBonusRegex.indexIn(ligne) != -1 || removeBonusRegex.indexIn(ligne) != -1 || killsRegex.indexIn(ligne) != -1 ){
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


void Serveur::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    m_clients.remove(client);
    m_utilisateurs.remove(client);
}


void Serveur::envoyerListeUtilisateur()
{
    QStringList listeUtilisateur;
    foreach(int utilisateur, m_utilisateurs.values())
        listeUtilisateur << QString::number(utilisateur);

    foreach(QTcpSocket *client, m_clients)
        client->write(QString("/users:" + listeUtilisateur.join(",") + "\n").toUtf8());
}


void Serveur::incomingConnection(int descripteurSocket)
{
    if(m_clients.size() < m_nbUtilisateur){

        QTcpSocket *client = new QTcpSocket(this);
        m_clientIdCourant++;
        client->setSocketDescriptor(descripteurSocket);
        m_clients.insert(client);        

        connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
        connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
    }
}
