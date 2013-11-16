#include <QApplication>
#include <QtCore>

#include <stdlib.h>
#include "serveur.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Serveur serveur;
    serveur.show();
    return app.exec();
}
