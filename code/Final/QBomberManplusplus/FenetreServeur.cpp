#include "FenetreServeur.h"
#include "Serveur.h"
#include "MainWindow.h"

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


void FenetreServeur::on_okButton_clicked()
{
    Serveur *serveur = new Serveur(ui->nbJSpinBox->value());
    bool reussi = serveur->listen(QHostAddress::Any, 4200);
    if(!reussi)
    {
        qFatal("Impossible d'écouter le port 4200");
    }
    qDebug() << "Pret!";
    qDebug() << ui->nbJSpinBox->value() ;

    ui->okButton->setEnabled(false);
    ui->nbJSpinBox->setEnabled(false);

    MainWindow *c = new MainWindow();
    c->show();

}
