#include "presentation.h"
#include "chifoumivue.h"
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
    // Modification de l'affichage
    _laVue->majInterface(_leModele->getEtat(),_leModele->getCoupJoueur(),_leModele->getCoupMachine(),_leModele->getScoreJoueur(), _leModele->getScoreMachine());
}

