#include "chifoumivue.h"
#include "ui_chifoumivue.h"
#include <QDebug>

// Déclaration des sous-programmes utilisées dans les sous-programmes de la classe
int randMinMax(int min, int max);
// Renvoie un nombre entier entre min inclus et max exclus

// Définition des sous-programmes de la classe
ChifoumiVue::ChifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{
    ui->setupUi(this);
    this->setFixedSize(this->minimumSize());

    // Création des QPixmap pour l'affichage des figures choisies
    rienPixmap = QPixmap(":images/images/rien_115.png");
    ciseauPixmap = QPixmap(":images/images/ciseau_115.png");
    papierPixmap = QPixmap(":images/images/papier_115.png");
    pierrePixmap = QPixmap(":images/images/pierre_115.png");

    // On connecte les boutons
    QObject::connect(ui->pushButtonNouvellePartie, SIGNAL(clicked()), this, SLOT(nouvellePartie()));
    QObject::connect(ui->pushButtonPapier, SIGNAL(clicked()), this, SLOT(jouerPapier()));
    QObject::connect(ui->pushButtonCiseau, SIGNAL(clicked()), this, SLOT(jouerCiseau()));
    QObject::connect(ui->pushButtonPierre, SIGNAL(clicked()), this, SLOT(jouerPierre()));

    // On désactive l'accès aux boutons
    ui->pushButtonCiseau->setEnabled(false);
    ui->pushButtonPapier->setEnabled(false);
    ui->pushButtonPierre->setEnabled(false);
}

ChifoumiVue::~ChifoumiVue()
{
    //dtor
}

void ChifoumiVue::nouvellePartie()
{
    // Réinitialisation des scores à 0
    QString s;  // Variable QString qui va nous servir à basculer le texte à 0
    // On repasse le score joueur à 0 et on l'affiche comme tel puis de même pour la machine
    (*this).scoreJoueur = 0;
    ui->labelScoreJoueur->setText(s.setNum(scoreJoueur));
    (*this).scoreMachine = 0;
    ui->labelScoreMachine->setText(s.setNum(scoreMachine));

    // On repasse la figure joueur à rien et on l'affiche comme tel puis de même pour la machine
    (*this).figureJoueur = rien;
    ui->labelFigureJoueur->setPixmap(rienPixmap);
    (*this).figureMachine = rien;
    ui->labelFigureMachine->setPixmap(rienPixmap);

    // On réactive l'accès aux boutons
    ui->pushButtonCiseau->setEnabled(true);
    ui->pushButtonPapier->setEnabled(true);
    ui->pushButtonPierre->setEnabled(true);
}

void ChifoumiVue::jouerPapier()
{
    // On modifie dans le système et sur l'affichage le fait que le joueur a désormé comme figure papier
    setCoupJoueur(papier);
    ui->labelFigureJoueur->setPixmap(papierPixmap);

    // On calcule la figure de la machine
    definirFigureMachine();

    // On cherche le gagnant
    char gagnant = determinerGagnant();

    // On modifie les scores tant dans l'affichage que dans le système
    majScore(gagnant);
}

void ChifoumiVue::jouerCiseau()
{
    // On modifie dans le système et sur l'affichage le fait que le joueur a désormé comme figure ciseau
    setCoupJoueur(ciseau);
    ui->labelFigureJoueur->setPixmap(ciseauPixmap);

    // On calcule la figure de la machine
    definirFigureMachine();

    // On cherche le gagnant
    char gagnant = determinerGagnant();

    // On modifie les scores tant dans l'affichage que dans le système
    majScore(gagnant);
}

void ChifoumiVue::jouerPierre()
{
    // On modifie dans le système et sur l'affichage le fait que le joueur a désormé comme figure pierre
    setCoupJoueur(pierre);
    ui->labelFigureJoueur->setPixmap(pierrePixmap);

    // On calcule la figure de la machine
    definirFigureMachine();

    // On cherche le gagnant
    char gagnant = determinerGagnant();

    // On modifie les scores tant dans l'affichage que dans le système
    majScore(gagnant);
}

ChifoumiVue::UnCoup ChifoumiVue::getCoupJoueur()
{
    return (*this).figureJoueur;
}

ChifoumiVue::UnCoup ChifoumiVue::getCoupMachine()
{
    return (*this).figureMachine;
}

int ChifoumiVue::getScoreJoueur()
{
    return (*this).scoreJoueur;
}

int ChifoumiVue::getScoreMachine()
{
    return (*this).scoreMachine;
}

void ChifoumiVue::setCoupJoueur(ChifoumiVue::UnCoup p_figure)
{
    (*this).figureJoueur = p_figure;
}

void ChifoumiVue::setCoupMachine(ChifoumiVue::UnCoup p_figure)
{
    (*this).figureMachine = p_figure;
    switch (p_figure){
        case pierre:
            ui->labelFigureMachine->setPixmap(pierrePixmap);
            break;
        case papier:
            ui->labelFigureMachine->setPixmap(papierPixmap);
            break;
        case ciseau:
            ui->labelFigureMachine->setPixmap(ciseauPixmap);
            break;
     }
}

void ChifoumiVue::setScoreJoueur(int p_score)
{
    (*this).scoreJoueur = p_score;
}

void ChifoumiVue::setScoreMachine(int p_score)
{
    (*this).scoreMachine = p_score;
}

void ChifoumiVue::definirFigureMachine()
{
    int nombre = randMinMax(0,3);
    setCoupMachine(UnCoup(nombre));
}

char ChifoumiVue::determinerGagnant()
{
    char gagnantARetourner = 'M';     // On créé le gagnant à retourner comme un caractère qui correspond par défaut à la machine

    // Il sera modifié dans l'un des cas suivants
    //qDebug() << getCoupJoueur() << " " << getCoupMachine() << Qt::endl;
    if(getCoupJoueur()==pierre && getCoupMachine()==ciseau){
            gagnantARetourner = 'J';
        }
        else if(getCoupJoueur()==ciseau && getCoupMachine()==papier){
            gagnantARetourner = 'J';
        }
        else if(getCoupJoueur()==papier && getCoupMachine()==pierre){
            gagnantARetourner = 'J';
        }
        else if (getCoupJoueur()==getCoupMachine())
        {
            gagnantARetourner = 'N';
        }

    return gagnantARetourner;
}

void ChifoumiVue::majScore(char p_gagnant)
{
    int scoreAModifier; // Cela va nous servir pour modifier correctement les scores
    QString s;          // Cela va nous servir pour la modification de l'affichage des scores
        switch (p_gagnant) {
            case 'J':
                scoreAModifier = getScoreJoueur();
                scoreAModifier +=1 ;
                setScoreJoueur(scoreAModifier);
                ui->labelScoreJoueur->setText(s.setNum(getScoreJoueur()));
                break;
            case 'M':
                scoreAModifier = getScoreMachine();
                scoreAModifier +=1 ;
                setScoreMachine(scoreAModifier);
                ui->labelScoreMachine->setText(s.setNum(getScoreMachine()));
                break;
        }
}

// Définition des sous-programmes utilisés dans ceux de la classe
int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

