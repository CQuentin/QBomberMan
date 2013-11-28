#include "qbomberman.h"
#include "ui_qbomberman.h"
#include "mainwindow.h"
#include "vue/fenetreserveur.h"

QBomberMan::QBomberMan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QBomberMan)
{
    ui->setupUi(this);
    QPalette fond;
    fond.setBrush(backgroundRole(),QBrush(QImage("../Game1/ressource/Bomberman.jpg")));
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

void QBomberMan::on_rejoindreChannel_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->RejoindrePartie);
}

void QBomberMan::on_rejoindreBtn_clicked()
{
    hide();

    MainWindow *c = new MainWindow(ui->ipLineEdit->text());
    c->setWindowTitle(QString::fromUtf8("Game1"));
    c->resize(900, 600);
    c->show();
}
