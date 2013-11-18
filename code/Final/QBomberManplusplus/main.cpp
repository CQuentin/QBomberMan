#include "qbomberman.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QBomberMan w;
    w.show();

    return a.exec();
}
