#ifndef IDENTIFICATION_H
#define IDENTIFICATION_H

#include <QWidget>
#include "presentation.h"

namespace Ui {
class Identification;
}

class Presentation;
class Identification : public QWidget
{
    Q_OBJECT

public:
    explicit Identification(Presentation *presentation, QWidget *parent = nullptr);
    ~Identification();
    void fermerFenetre();

signals:
    void tentativeConnexion(QString, QString);

private slots:
    void userTentativeConnexion();
    /* L'utilisateur tente de se connecter */

private:
    Ui::Identification *ui;
    Presentation *_laPresentation;
};

#endif // IDENTIFICATION_H
