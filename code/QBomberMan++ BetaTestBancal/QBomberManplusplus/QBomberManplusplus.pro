#-------------------------------------------------
#
# Project created by QtCreator 2013-11-17T18:02:00
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QBomberManplusplus
TEMPLATE = app


SOURCES += main.cpp\
        qbomberman.cpp \
    Serveur.cpp \
    FenetreServeur.cpp \
    MainWindow.cxx \
    client.cpp \
    controleur/toucheclavier.cpp \
    modele/bombe.cpp \
    modele/brique.cpp \
    modele/joueur.cpp \
    vue/mainwindow.cpp


HEADERS  += qbomberman.h \
    Serveur.h \
    FenetreServeur.h \
    MainWindow.h \
    client.h \
    controleur/toucheclavier.h \
    modele/bombe.h \
    modele/brique.h \
    modele/joueur.h \
    vue/mainwindow.h


FORMS    += qbomberman.ui \
    FenetreServeur.ui \
    MainWindow.ui

