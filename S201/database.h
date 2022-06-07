#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDateTime>

#define DATABASE_NAME "S2.01"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database();
    bool openDatabase();
    void closeDatabase();
    bool restoreDatabase();
    bool tentativeConnexion(QString nomUtilisateur, QString mdpUtilisateur, int& numUtilisateur);
    // On vérifie si l'utilisateur existe avec son mot de passe dans la base de données
    void ajouterPartie(QDateTime *horodatage, QString nomJoueur, int scoreJoueur, QString nomMachine, int scoreMachine, int numUtilisateur);
    // On rajoute une partie finie à la base de données

private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H
