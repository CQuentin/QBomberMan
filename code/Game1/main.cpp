#include "qbomberman.h"
#include <QApplication>
#include "./vue/mainwindow.h"

int main(int argc, char *argv[])
{
    qsrand(QTime::currentTime().msec());
    QApplication a(argc, argv);
    QBomberMan w;
    w.show();
    return a.exec();
}
