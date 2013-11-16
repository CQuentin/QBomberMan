QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Serveur
TEMPLATE = app


SOURCES += main.cpp \
    FenetrePrincipale.cpp \
    Serveur.cpp

HEADERS  += \
    FenetrePrincipale.h \
    Serveur.h

FORMS    += \
    FenetrePrincipale.ui
