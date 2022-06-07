#include "presentation.h"
#include "chifoumivue.h"
#include <QMessageBox>
#include <QDebug>

Presentation::Presentation(Chifoumi *c, QObject *parent)
    : QObject{parent}, _leModele(c)
{
    _leModele->initCoups();     // On initialise les coups à rien
    _leModele->initScores();    // On initialise les scores à 0
    _leTimer = new QTimer(this);        // On initialise le timer
    // On connecte le timer
    _leTimer->connect(_leTimer, SIGNAL(timeout()), this, SLOT(tempsRestantDiminue()));
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

char Presentation::testVictoireTpsFini()
{
    char gagnant = 'N';     // On initialise le caractère de retour du gagnant a N
    if (_leModele->getScoreJoueur() > _leModele->getScoreMachine()){
        gagnant = 'J';
    }
    else if (_leModele->getScoreMachine() > _leModele->getScoreJoueur()){
        gagnant = 'M';
    }
    return gagnant;
}

void Presentation::unJoueurAGagne(char c)
{
    QMessageBox msgBox; // On prépare le QMessageBox pour afficher le vainqueur
    /* Lorsque quelqu'un gagne :
        On construit le texte à placer dans le QMessageBox
     */
    QString s = QString("Bravo ");
    QString num;
    switch (c){
        case 'J' :      // Le cas où le joueur gagne
            s.insert(s.size(), _leModele->getNomJoueur());
            s.insert(s.size(), " ! Vous avez gagné avec ");
            s.insert(s.size(), num.setNum(_leModele->getScorePourVictoire()));
            s.insert(s.size(), " points en ");
            s.insert(s.size(), num.setNum(_leModele->getTpsPourFin() - _leModele->getTpsRestant()));
            s.insert(s.size(), " secondes.");
            break;
        case 'M' :      // Le cas où la machine gagne
            s.insert(s.size(), "La Machine ! Vous avez gagné avec ");
            s.insert(s.size(), num.setNum(_leModele->getScorePourVictoire()));
            s.insert(s.size(), " points en ");
            s.insert(s.size(), num.setNum(_leModele->getTpsPourFin() - _leModele->getTpsRestant()));
            s.insert(s.size(), " secondes.");
            break;
    }
    // On arrête le timer
    _leTimer->stop();
    // On définit le texte du QMessageBox et on l'affiche
    msgBox.setText(s);
    msgBox.exec();
    // On modifie l'état du modèle
    _leModele->setEtat(Chifoumi::partieFinie);
}

void Presentation::leTempsEstFini(char c)
{
    QMessageBox msgBox; // On prépare le QMessageBox pour afficher le vainqueur
    /* Lorsque quelqu'un gagne :
        On construit le texte à placer dans le QMessageBox
     */
    QString s = QString("Helas chers joueurs! Temps de jeu fini ! ");
    QString num;
    switch (c){
        case 'J' :      // Le cas où le joueur gagne
            s.insert(s.size(), _leModele->getNomJoueur());
            s.insert(s.size(), " termine toutefois mieux, avec ");
            s.insert(s.size(), num.setNum(_leModele->getScorePourVictoire()));
            s.insert(s.size(), " points !");
            break;
        case 'M' :      // Le cas où la machine gagne
            s.insert(s.size(), "La Machine termine toutefois mieux, avec ");
            s.insert(s.size(), num.setNum(_leModele->getScorePourVictoire()));
            s.insert(s.size(), " points !");
            break;
        case 'N' :      // Le cas où le match est nul
            s.insert(s.size(), "Il y a match nul.");
            break;
    }
    // On définit le texte du QMessageBox et on l'affiche
    msgBox.setText(s);
    msgBox.exec();
    // On modifie l'état du modèle
    _leModele->setEtat(Chifoumi::partieFinie);
}



void Presentation::nouvellePartie()
{
    //qDebug() << "NouvellePartie" << Qt::endl;
    // Lancement du timer
    _leTimer->start(1000);
    // Modification du modèle
    _leModele->initScores();        // On repasse les scores à 0
    _leModele->initCoups();         // On repasse les coups à rien
    _leModele->setEtat(Chifoumi::enCours);  // On s'assure que la partie est dans l'état "en cours"
    _leModele->setTpsRestant(_leModele->getTpsPourFin());  // On remet le temps restant au maximum
    // Modification de l'affichage
    _laVue->fermerConnexionParam(this);
    _laVue->majInterface(_leModele);
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
    _laVue->majInterface(_leModele);
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
    _laVue->majInterface(_leModele);
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
    _laVue->majInterface(_leModele);
}


void Presentation::aProposDe()
{
    //qDebug() << "Test procédure aProposDe" << Qt::endl;
    QMessageBox msgBox;
    msgBox.setText("Chifoumi v6 \n24/05/2022 \nJuan David Rodriguez Sinclair \nEsteban Dujardin \nDamien Lanusse \nTDI TP2");
    msgBox.exec();
}

void Presentation::demandePause()
{
    //qDebug() << "Test mise en Pause" << Qt::endl;
    _leModele->setEtat(Chifoumi::enPause);
    _laVue->repriseConnexion(this);
    _laVue->majInterface(_leModele);
    _leTimer->stop();
}

void Presentation::demandeReprise()
{
    //qDebug() << "Test Reprise" << Qt::endl;
    _leModele->setEtat(Chifoumi::enCours);
    _laVue->pauseConnexion(this);
    _laVue->majInterface(_leModele);
    _leTimer->start(1000);
}

void Presentation::tempsRestantDiminue()
{
    //qDebug() << "Test" << Qt::endl;
    // On modifie le modèle
    unsigned int tpsRestant = _leModele->getTpsRestant();
    // On vérifie s'il reste du temps
    if(tpsRestant > 0){
        tpsRestant -= 1;
        _leModele->setTpsRestant(tpsRestant);
        // On fait la mise à jour de l'affichage
        _laVue->majInterface(tpsRestant);
        // On relance le timer
        _leTimer->start(1000);
     }
    else{
        // On identifie le caractère du gagnant comme étant le temps
        char gagnant = testVictoireTpsFini();
        leTempsEstFini(gagnant);
    }
}

void Presentation::modificationParametre()
{
    //qDebug()<< "Test" << Qt::endl;
    // On créé la boite de dialogue
    Parametre _lesParametres(this, _laVue);
    _lesParametres.setFixedSize(296,157);
    _lesParametres.exec();
}

void Presentation::modifierParametres(QString nomJoueur, int score, int tps)
{
    // On modifie les paramètres dans le modèle
    _leModele->setNomJoueur(nomJoueur);
    _leModele->setScorePourVictoire(score);
    _leModele->setTpsAvantFin(tps);
    _laVue->majInterface(_leModele);
}
