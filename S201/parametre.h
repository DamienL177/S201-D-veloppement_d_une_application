#ifndef PARAMETRE_H
#define PARAMETRE_H

#include <QDialog>
#include "presentation.h"

namespace Ui {
class Parametre;
}

class Presentation;
class Parametre : public QDialog
{
    Q_OBJECT

public:
    Parametre(Presentation *presentation, QWidget *parent = nullptr);
    ~Parametre();

signals:
    void modification(QString, int, int);

private slots:
    void modifierParametres();
    /* Modification des paramètres du modèle */

private:
    Ui::Parametre *ui;
    Presentation *_laPresentation;
};

#endif // PARAMETRE_H
