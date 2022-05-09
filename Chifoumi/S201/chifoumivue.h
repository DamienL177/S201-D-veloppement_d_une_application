#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

///* Une d�finition de type �num�r�
public:
    enum UnCoup {pierre = 0, papier = 1, ciseau = 2, rien = 3};

public:
    ChifoumiVue(QWidget *parent = nullptr);
    ~ChifoumiVue();

private slots:
    void nouvellePartie();
    // Le joueur demande à commencer une nouvelle partie

    void jouerPapier();
    // Le joueur demande à joueur papier

    void jouerCiseau();
    // Le joueur demande à jouer ciseau

    void jouerPierre();
    // Le joueur demande à jouer pierre

private:
    // VARIABLES
    Ui::ChifoumiVue *ui;
    int scoreJoueur;        // Variable contenant le score du joueur
    int scoreMachine;       // Variable contenant le score de la machine
    UnCoup figureJoueur;    // Variable contenant la figure du joueur
    UnCoup figureMachine;   // Variable contenant la figure de la machine
    QPixmap rienPixmap;     // Variable contenant la pixmap pour affichage lorsqu'il n'y a pas eu de choix de figure
    QPixmap ciseauPixmap;   // Variable contenant la pixmap lorsque la figure est ciseau
    QPixmap papierPixmap;   // Variable contenant la pixmap lorsque la figure est papier
    QPixmap pierrePixmap;   // Variable contenant la pixmap lorsque la figure est pierre

    // SOUS-PROGRAMMES---------------------------------------
    // Getters -------------------
    UnCoup getCoupJoueur();
    // Renvoie le dernier coup joué par le joueur

    UnCoup getCoupMachine();
    // Renvoie le dernier coup joué par la machine

    int getScoreJoueur();
    // Renvoie le score actuel du joueur

    int getScoreMachine();
    // Renvoie le coup actuel de la machine

    // Setters ------------------
    void setCoupJoueur(UnCoup);
    // Renvoie le dernier coup joué par le joueur

    void setCoupMachine(UnCoup);
    // Renvoie le dernier coup joué par la machine

    void setScoreJoueur(int);
    // Renvoie le score actuel du joueur

    void setScoreMachine(int);
    // Renvoie le coup actuel de la machine

    // Autre ---------------------
    void definirFigureMachine();
    // Calculer la figure de la machine

    char determinerGagnant();
    // Trouver le vainqueur de la manche entre le joueur et la machine

    void majScore(char);
    // Modifier les scores tant enregistrés par le système qu'affichés
};
#endif // CHIFOUMIVUE_H
