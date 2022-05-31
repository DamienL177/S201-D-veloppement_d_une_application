#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include "chifoumi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

    public:
        ChifoumiVue(QMainWindow *parent = nullptr);
        ~ChifoumiVue();

    public:
        // pour créer une connexion avec la présentation
        void nvlleConnexion(QObject *c);
        void supprConnexion(QObject *c);
        void pauseConnextion(QObject *c);
        void repriseConnexion(QObject *c);
        // ordres reçus par la présentation
        void majInterface(Chifoumi *c);     // La mise à jour traditionnelle
        void majInterface(int tpsRestant);  // La mise à jour lorsque seul le temps restant change

    private:
        Ui::ChifoumiVue *ui;
};
#endif // CHIFOUMIVUE_H
