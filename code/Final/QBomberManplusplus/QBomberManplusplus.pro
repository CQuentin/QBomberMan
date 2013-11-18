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
    MainWindow.cxx

HEADERS  += qbomberman.h \
    Serveur.h \
    FenetreServeur.h \
    MainWindow.h


FORMS    += qbomberman.ui \
    FenetreServeur.ui \
    MainWindow.ui

