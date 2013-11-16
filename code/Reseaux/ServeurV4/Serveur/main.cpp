#include "fenetreprincipale.h"
#include "Serveur.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FenetrePrincipale fenetrePrincipale;
    fenetrePrincipale.show();

    Serveur *serveur = new Serveur();
    bool reussi = serveur->listen(QHostAddress::Any, 4200);
    if(!reussi)
    {
        qFatal("Impossible d'écouter le port 4200");
    }

    qDebug() << "Pret!";

    return app.exec();
}
