#include <QtWidgets>
#include "client.h"


Client::Client(QObject *parent) : QTcpSocket(parent)
{
    //Creer la scene
    scene = new MainWindow() ;



    connect(this, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(this, SIGNAL(connected()), this, SLOT(connected()));
}

/**
 * Destructeur par défaut
 * @brief Serveur::~Serveur
 */
Client::~Client()
{

}

/**
  Le client arrive sur le serveur et lui dit faut me rajouter à la liste
 * @brief Client::connected
 */
void Client::connected()
{
     this->write(QString("/me:\n").toUtf8());
}

void Client::readyRead()
{

    while(this->canReadLine())
    {

        QString line = QString::fromUtf8(this->readLine()).trimmed();

        // TODO: REGEX a créer pour l
        QRegExp messageRegex("^([^:]+):(.*)$");
        QRegExp usersRegex("^/users:(.*)$");
        QRegExp deplacementRegex("^/dep:(.*)$");
        QRegExp bombeRegex("^/bom:(.*)$");

        // Is this a users message:
        if(usersRegex.indexIn(line) != -1)
        {
            // If so, update our users list on the right:
            QStringList users = usersRegex.cap(1).split(",");
            //userListWidget->clear();
            foreach(QString user, users){
                QStringList J = user.split(" ");
                /*
                 *Exemple de code quand ça fonctionnera !
                // J[0] id joueur
                // J[1] pos x
                // J[2] pos y
                //foreach(Joueur j ,m_utilisateurs){
                if(j.getid){  Si l'id du joueur est déjà dans la liste passer à l'itération suivante
                    continue;
                }
                else{
                    Joueur* j = new Joueur(J[1],J[2]);
                    m_utilisateurs.append(j);
                    scene->ajouterPersonnage(j);
                }

            }*/

            }
        }

        else if(deplacementRegex.indexIn(line) != -1)
        {
            QStringList bombe = usersRegex.cap(1).split(" ");

            foreach (Bombe b, m_bombes) {
                if(b.getid == bombe[0] && b.getidJ == bombe[1]){
                    continue;
                }
                else{ // bombe[0] id bombe
                    // bombe[1] id joueur
                    // bombe[2] pos X
                    // bombe[3] pos Y
                    Bombe* bo = new Bombe(bombe[0], bombe[1], bombe[2], bombe[3]);
                    scene->ajouterBombe(bo);

                }

            }


       //     roomTextEdit->append(user + " : " + message);
        }
    }
}
