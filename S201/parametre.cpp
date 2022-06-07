#include "parametre.h"
#include "ui_parametre.h"

Parametre::Parametre(Presentation *presentation, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametre),
    _laPresentation(presentation)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(modifierParametres()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(this, SIGNAL(modification(QString, int, int)), _laPresentation, SLOT(modifierParametres(QString, int, int)));
}

Parametre::~Parametre()
{
    delete ui;
}

void Parametre::modifierParametres()
{
    // Variables
    QString nomJoueur;
    QString strScore;
    QString strTps;

    // Traitements
    nomJoueur = ui->lineEditNom->text();
    strScore = ui->spinBoxScore->text();
    strTps = ui->spinBoxTps->text();
    emit modification(nomJoueur, strScore.toInt(), strTps.toInt());
    disconnect(this, SIGNAL(modification(QString, int, int)), _laPresentation, SLOT(modifierParametres(QString, int, int)));
    this->close();
}
