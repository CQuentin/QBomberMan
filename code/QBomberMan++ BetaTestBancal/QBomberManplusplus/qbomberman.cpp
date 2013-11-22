#include "qbomberman.h"
#include "ui_qbomberman.h"
#include "MainWindow.h"
#include "FenetreServeur.h"

QBomberMan::QBomberMan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QBomberMan)
{
    ui->setupUi(this);
    QPalette fond;
    fond.setBrush(backgroundRole(),QBrush(QImage("../QBomberManplusplus/Bomberman.jpg")));
    this->setPalette(fond);
}

QBomberMan::~QBomberMan()
{
    delete ui;
}

void QBomberMan::on_creerPartie_clicked()
{
    hide();
    FenetreServeur *f = new FenetreServeur();
    f->show();    
}

void QBomberMan::on_rejoindrePartie_clicked()
{
    hide();
    MainWindow *c = new MainWindow();
    c->show();

}
