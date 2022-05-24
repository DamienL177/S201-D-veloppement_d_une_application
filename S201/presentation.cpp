#include "presentation.h"
#include "chifoumivue.h"
#include <QMessageBox>
#include <QDebug>

Presentation::Presentation(Chifoumi *c, QObject *parent)
    : QObject{parent}, _leModele(c)
{
    _leModele->initCoups();     // On initialise les coups à rien
    _leModele->initScores();    // On initialise les scores à 0
}

Chifoumi *Presentation::getModele()
{
    return _leModele;
}

ChifoumiVue *Presentation::getVue()
{
    return _laVue;
}

void Presentation::setModele(Chifoumi *m)
{
    _leModele = m;
}

void Presentation::setVue(ChifoumiVue *v)
{
    _laVue = v;
}

char Presentation::testVictoire()
{
    char gagnant = 'N';     // On initialise le caractère de retour du gagnant a N
    if (_leModele->getScoreJoueur() == _leModele->getScorePourVictoire()){
        gagnant = 'J';
    }
    else if (_leModele->getScoreMachine() == _leModele->getScorePourVictoire()){
        gagnant = 'M';
    }
    return gagnant;
}

void Presentation::unJoueurAGagne(char c)
{
    QMessageBox msgBox;
    switch (c){
        case 'J' :
            msgBox.setText("Bravo ! Vous avez gagné !!!");
            msgBox.exec();
            _leModele->setEtat(Chifoumi::partieFinie);
            break;
        case 'M' :
            msgBox.setText("Dommage ! Vous avez perdu.");
            msgBox.exec();
            _leModele->setEtat(Chifoumi::partieFinie);
            break;
    }
}



void Presentation::nouvellePartie()
{
    //qDebug() << "NouvellePartie" << Qt::endl;
    // Modification du modèle
    _leModele->initScores();        // On repasse les scores à 0
    _leModele->initCoups();         // On repasse les coups à rien
    _leModele->setEtat(Chifoumi::enCours);  // On s'assure que la partie est dans l'état "en cours"
    // Modification de l'affichage
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(), _leModele->getScoreMachine());
}

void Presentation::jouerPapier()
{
    //qDebug() << "jouerPapier" << Qt::endl;
    // Modification du modèle
    _leModele->setCoupJoueur(Chifoumi::papier);     // coupJoueur du modèle prend la valeur papier
    Chifoumi::UnCoup coupMachine = _leModele->genererUnCoup();  // On récupère le coup joué par la machine
    _leModele->setCoupMachine(coupMachine);         // coupMachine du modèle prend la valeur contenue dans coupMachine
    char gagnant = _leModele->determinerGagnant();  // On récupère le caractère indiquant le vainqueur de la manche
    _leModele->majScores(gagnant);                  // On met à jour les scores du modèle
    gagnant = testVictoire();                   // On lance la fonction qui vérifie la victoire
    if (gagnant != 'N'){                        // Si un joueur a gagné
        unJoueurAGagne(gagnant);                // On s'occupe de l'affichage
    }
    // Modification de l'affichage
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(), _leModele->getScoreMachine());
}

void Presentation::jouerCiseau()
{
    //qDebug() << "jouerCiseau" << Qt::endl;
    // Modification du modèle
    _leModele->setCoupJoueur(Chifoumi::ciseau);     // coupJoueur du modèle prend la valeur papier
    Chifoumi::UnCoup coupMachine = _leModele->genererUnCoup();  // On récupère le coup joué par la machine
    _leModele->setCoupMachine(coupMachine);         // coupMachine du modèle prend la valeur contenue dans coupMachine
    char gagnant = _leModele->determinerGagnant();  // On récupère le caractère indiquant le vainqueur de la manche
    _leModele->majScores(gagnant);                  // On met à jour les scores du modèle
    gagnant = testVictoire();                   // On lance la fonction qui vérifie la victoire
    if (gagnant != 'N'){                        // Si un joueur a gagné
        unJoueurAGagne(gagnant);                // On s'occupe de l'affichage
    }
    // Modification de l'affichage
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(), _leModele->getScoreMachine());
}

void Presentation::jouerPierre()
{
    //qDebug() << "jouerPierre" << Qt::endl;
    // Modification du modèle
    _leModele->setCoupJoueur(Chifoumi::pierre);     // coupJoueur du modèle prend la valeur papier
    Chifoumi::UnCoup coupMachine = _leModele->genererUnCoup();  // On récupère le coup joué par la machine
    _leModele->setCoupMachine(coupMachine);         // coupMachine du modèle prend la valeur contenue dans coupMachine
    char gagnant = _leModele->determinerGagnant();  // On récupère le caractère indiquant le vainqueur de la manche
    _leModele->majScores(gagnant);                  // On met à jour les scores du modèle
    gagnant = testVictoire();                   // On lance la fonction qui vérifie la victoire
    if (gagnant != 'N'){                        // Si un joueur a gagné
        unJoueurAGagne(gagnant);                // On s'occupe de l'affichage
    }
    // Modification de l'affichage
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(), _leModele->getScoreMachine());
}


void Presentation::aProposDe()
{
    //qDebug() << "Test procédure aProposDe" << Qt::endl;
    QMessageBox msgBox;
    msgBox.setText("Chifoumi v4 \n09/05/2022 \nJuan David Rodriguez Sinclair \nEsteban Dujardin \nDamien Lanusse \nTDI TP2");
    msgBox.exec();
}
