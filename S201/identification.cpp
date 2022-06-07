#include "identification.h"
#include "ui_identification.h"
#include <QDebug>

Identification::Identification(Presentation *presentation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Identification),
    _laPresentation(presentation)
{
    ui->setupUi(this);
    connect(ui->pushButtonEntrer, SIGNAL(clicked()), this, SLOT(userTentativeConnexion()));
    connect(this, SIGNAL(tentativeConnexion(QString, QString)), _laPresentation, SLOT(seConnecter(QString, QString)));
}

Identification::~Identification()
{
    delete ui;
}

void Identification::fermerFenetre()
{
    disconnect(this, SIGNAL(tentativeConnexion(QString, QString)), _laPresentation, SLOT(seConnecter(QString, QString)));
    this->close();
}

void Identification::userTentativeConnexion()
{
    //qDebug() << "Test connexion" << Qt::endl;
    bool nomUtilisateur = false;    // La variable vérifiant que l'utilisateur a saisi quelque chose pour son nom
    bool mdpUtilisateur = false;    // La variable vérifiant que l'utilisateur a saisi quelque chose pour son mot de passe

    // On vérifie que l'utilisateur a bien tout saisi
    // Vérification du nom d'utilisateur
    if(ui->lineEditUtilisateur->text() != QString("")){
        nomUtilisateur = true;
    }

    // Vérification du mot de passe
    if(ui->lineEditMDP->text() != QString("")){
        mdpUtilisateur = true;
    }

    // Si tout va bien on émet le signal qui sera reçu par la présentation
    if(nomUtilisateur && mdpUtilisateur){
        emit tentativeConnexion(ui->lineEditUtilisateur->text(), ui->lineEditMDP->text());
    }
}
