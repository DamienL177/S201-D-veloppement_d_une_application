#include "chifoumivue.h"
#include "ui_chifoumivue.h"
#include <QDebug>

ChifoumiVue::ChifoumiVue(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);
}

ChifoumiVue::~ChifoumiVue()
{
    delete ui;
}

void ChifoumiVue::nvlleConnexion(QObject *c)
{
    // Connection des boutons aux fonctions de la présentation
    QObject::connect(ui->pushButtonNouvellePartie, SIGNAL(clicked()), c, SLOT(nouvellePartie()));
    QObject::connect(ui->pushButtonCiseau, SIGNAL(clicked()), c, SLOT(jouerCiseau()));
    QObject::connect(ui->pushButtonPapier, SIGNAL(clicked()), c, SLOT(jouerPapier()));
    QObject::connect(ui->pushButtonPierre, SIGNAL(clicked()), c, SLOT(jouerPierre()));
    QObject::connect(ui->pushButtonPause, SIGNAL(clicked()), c, SLOT(demandePause()));
    // Connection des actions
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionAProposDe, SIGNAL(triggered()), c, SLOT(aProposDe()));
}

void ChifoumiVue::supprConnexion(QObject *c)
{
    // Déconnection des boutons aux fonctions de la présentation
    QObject::disconnect(ui->pushButtonNouvellePartie, SIGNAL(clicked()), c, SLOT(nouvellePartie()));
    QObject::disconnect(ui->pushButtonCiseau, SIGNAL(clicked()), c, SLOT(jouerCiseau()));
    QObject::disconnect(ui->pushButtonPapier, SIGNAL(clicked()), c, SLOT(jouerPapier()));
    QObject::disconnect(ui->pushButtonPierre, SIGNAL(clicked()), c, SLOT(jouerPierre()));
    QObject::disconnect(ui->pushButtonPause, SIGNAL(clicked()), c, SLOT(demandePause()));
    // Déconnection des actions
    QObject::disconnect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));
    QObject::disconnect(ui->actionAProposDe, SIGNAL(triggered()), c, SLOT(aProposDe()));
}

void ChifoumiVue::pauseConnextion(QObject *c)
{
    QObject::disconnect(ui->pushButtonPause, SIGNAL(clicked()), c, SLOT(demandeReprise()));
    QObject::connect(ui->pushButtonPause, SIGNAL(clicked()), c, SLOT(demandePause()));
}

void ChifoumiVue::repriseConnexion(QObject *c)
{
    QObject::disconnect(ui->pushButtonPause, SIGNAL(clicked()), c, SLOT(demandePause()));
    QObject::connect(ui->pushButtonPause, SIGNAL(clicked()), c, SLOT(demandeReprise()));
}

void ChifoumiVue::majInterface(Chifoumi *c)
{
    QString s;      // Cette variable nous sert afin de parvenir à afficher les scores des joueurs
    // On récupère les variables nécessaires à la mise à jour de l'interface
    Chifoumi::UnEtat e = c->getEtat();
    Chifoumi::UnCoup coupJoueur = c->getCoupJoueur();
    Chifoumi::UnCoup coupMachine = c->getCoupMachine();
    unsigned int scoreJoueur = c->getScoreJoueur();
    unsigned int scoreMachine = c->getScoreMachine();
    switch (e) {
        case Chifoumi::initial :        // Dans le cas où le jeu est dans l'état initial
            ui->labelFigureJoueur->setPixmap(QPixmap(":images/images/rien_115.png"));       // Les figures reçoivent la pixmap rien
            ui->labelFigureMachine->setPixmap(QPixmap(":images/images/rien_115.png"));
            ui->labelScoreJoueur->setText(s.setNum(0));         // Les scores sont affichés à 0
            ui->labelScoreMachine->setText(s.setNum(0));
            // On désactive l'accès aux boutons
            ui->pushButtonCiseau->setEnabled(false);
            ui->pushButtonPapier->setEnabled(false);
            ui->pushButtonPierre->setEnabled(false);
            ui->pushButtonPause->setEnabled(false);
            break;

        case Chifoumi::enCours :        // Dans le cas où le jeu est en cours
            switch (coupJoueur){        // On modifie la pixmap de la figure du joueur selon son coup
                case Chifoumi::rien :
                    ui->labelFigureJoueur->setPixmap(QPixmap(":images/images/rien_115.png"));
                    break;
                case Chifoumi::ciseau :
                    ui->labelFigureJoueur->setPixmap(QPixmap(":images/images/ciseau_115.png"));
                    break;
                case Chifoumi::pierre :
                    ui->labelFigureJoueur->setPixmap(QPixmap(":images/images/pierre_115.png"));
                    break;
                case Chifoumi::papier :
                    ui->labelFigureJoueur->setPixmap(QPixmap(":images/images/papier_115.png"));
                    break;
            }
            switch (coupMachine){       // On modifie la pixmap de la figure de la machine selon son coup
                case Chifoumi::rien :
                    ui->labelFigureMachine->setPixmap(QPixmap(":images/images/rien_115.png"));
                    break;
                case Chifoumi::ciseau :
                    ui->labelFigureMachine->setPixmap(QPixmap(":images/images/ciseau_115.png"));
                    break;
                case Chifoumi::pierre :
                    ui->labelFigureMachine->setPixmap(QPixmap(":images/images/pierre_115.png"));
                    break;
                case Chifoumi::papier :
                    ui->labelFigureMachine->setPixmap(QPixmap(":images/images/papier_115.png"));
                    break;
            }
            ui->pushButtonPause->setText(QString("Pause"));    // On met le bon texte dans le bouton Pause/Reprise
            ui->labelScoreJoueur->setText(s.number(scoreJoueur));       // On modifie l'affichage des scores
            ui->labelScoreMachine->setText(s.number(scoreMachine));
            ui->pushButtonCiseau->setEnabled(true);             // On active les boutons de figures
            ui->pushButtonPapier->setEnabled(true);
            ui->pushButtonPierre->setEnabled(true);
            ui->pushButtonNouvellePartie->setEnabled(true);
            ui->pushButtonPause->setEnabled(true);
            break;

        case Chifoumi::partieFinie :
            ui->pushButtonCiseau->setEnabled(false);             // On désactive les boutons de figures
            ui->pushButtonPapier->setEnabled(false);
            ui->pushButtonPierre->setEnabled(false);
            ui->pushButtonPause->setEnabled(false);
            break;
        case Chifoumi::enPause :
            ui->pushButtonPause->setText(QString("Reprise"));    // On met le bon texte dans le bouton Pause/Reprise
            ui->pushButtonCiseau->setEnabled(false);             // On désactive les boutons de figures
            ui->pushButtonPapier->setEnabled(false);
            ui->pushButtonPierre->setEnabled(false);
            ui->pushButtonNouvellePartie->setEnabled(false);
            break;
    }
}

void ChifoumiVue::majInterface(int tpsRestant)
{
    QString s;
    ui->labelNbTpsRestant->setText(s.number(tpsRestant));
}
