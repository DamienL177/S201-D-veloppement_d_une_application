#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
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
public slots:
    void nouvellePartie();
    // Le joueur demande à commencer une nouvelle partie

    void jouerPapier();
    // Le joueur demande à joueur papier

    void jouerCiseau();
    // Le joueur demande à jouer ciseau

    void jouerPierre();
    // Le joueur demande à jouer pierre

private:
    Chifoumi * _leModele;
    ChifoumiVue * _laVue;
};

#endif // PRESENTATION_H
