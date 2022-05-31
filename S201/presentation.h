#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include <QTimer>
#include "chifoumi.h"

class ChifoumiVue;
class Presentation : public QObject
{
    Q_OBJECT
public:
    explicit Presentation(Chifoumi *c, QObject *parent = nullptr);

public:
    Chifoumi* getModele();
    ChifoumiVue* getVue();
    void setModele(Chifoumi *m);
    void setVue(ChifoumiVue *v);

private:
    void unJoueurAGagne(char c);
    // Affiche le message box de victoire et arrête le jeu

    void leTempsEstFini(char c);
    // Affiche le message box de fin de temps

    char testVictoire();
    // Teste si l'un des joueurs gagne

    char testVictoireTpsFini();
    // Renvoie le joueur qui a gagné lorsque le temps est fini

public slots:
    void nouvellePartie();
    // Le joueur demande à commencer une nouvelle partie

    void jouerPapier();
    // Le joueur demande à joueur papier

    void jouerCiseau();
    // Le joueur demande à jouer ciseau

    void jouerPierre();
    // Le joueur demande à jouer pierre

    // pour afficher l'à propos de
    void aProposDe();

    void demandePause();
    // Le joueur demande à mettre la partie en pause

    void demandeReprise();
    // Le joueur demande à reprendre la partie

    void tempsRestantDiminue();
    // Le temps restant de la partie diminue

private:
    Chifoumi * _leModele;
    ChifoumiVue * _laVue;
    QTimer *_leTimer;
};

#endif // PRESENTATION_H
