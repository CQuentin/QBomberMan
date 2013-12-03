#include "fenetreserveur.h"

FenetreServeur::FenetreServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetreServeur)
{
    ui->setupUi(this);
    ui->portLigneEdit->setText("4200");

}

FenetreServeur::~FenetreServeur()
{
    delete ui;
}


void FenetreServeur::on_okButton_clicked(){}
