#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    ui->portLigneEdit->setText("4200");

}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

