#include "chifoumivue.h"
#include "chifoumi.h"
#include "presentation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Création du modèle
    Chifoumi *c = new Chifoumi();
    //Création de la présentation
    Presentation *p = new Presentation(c);
    //Création de la vue
    ChifoumiVue w;
    // associer la vue à la présentation
    p->setVue(&w);
    // initialiser la vue en conformité avec l'état initial du modèle
    p->getVue()->majInterface(c->getEtat(),c->getCoupJoueur(),c->getCoupMachine(),c->getScoreJoueur(), c->getScoreMachine());
    // connexion des signaux de la vue avec les slots de la présentation
    w.nvlleConnexion(p);

    w.show();
    return a.exec();
}
