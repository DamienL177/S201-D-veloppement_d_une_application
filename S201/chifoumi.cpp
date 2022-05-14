/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= mod�le) Chifoumi-v1
 **************************************************************/
#include "chifoumi.h"
#include <cstdlib>
#include <ctime>


    ///* ---- PARTIE MOD�LE ---------------------------

Chifoumi::Chifoumi():
    etatPartie(initial),
    scoreJoueur(0),
    scoreMachine(0),
    coupJoueur(rien),
    coupMachine(rien)
{
    //ctor
    // partie mod�le
}

Chifoumi::~Chifoumi()
{
    //dtor
}

Chifoumi::UnEtat Chifoumi::getEtat()
{
    return etatPartie;
}

        /// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
    return coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match gagne par la machine
    gagnantARetourner = 'M';

    // il sera modifi� dans l'un des cas suivants
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

         ///* M�thodes utilitaires du Mod�le

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
   return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur � retourner
    valeurGeneree = (UnCoup)randMinMax(0,3);
    return valeurGeneree;
}

        /// Setters
void Chifoumi::setEtat(UnEtat p_etat)  {
    (*this).etatPartie = p_etat;
}

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
    (*this).coupJoueur = p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
    (*this).coupMachine = p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
    (*this).scoreJoueur = p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    (*this).scoreMachine = p_score;
}

void Chifoumi::majScores(char p_gagnant) {
    int scoreAModifier;
    switch (p_gagnant) {
        case 'J':
            scoreAModifier = getScoreJoueur();
            scoreAModifier +=1 ;
            setScoreJoueur(scoreAModifier);
            break;
        case 'M':
            scoreAModifier = getScoreMachine();
            scoreAModifier +=1 ;
            setScoreMachine(scoreAModifier);
            break;
    }
}

void Chifoumi::initScores() {
    (*this).scoreJoueur = 0;
    (*this).scoreMachine = 0;
}

void Chifoumi::initCoups() {
    (*this).coupJoueur = rien;
    (*this).coupMachine = rien;
}
