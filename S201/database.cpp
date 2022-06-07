#include "database.h"
#include <QDebug>
#include <QSqlQuery>

Database::Database()
{

}

bool Database::openDatabase()
{
    mydb = QSqlDatabase::addDatabase("QODBC");
    mydb.setHostName("lakartxela");
    mydb.setDatabaseName("S2.01");
    mydb.setUserName("dlanusse_bd");
    mydb.setPassword("dlanusse_bd");
    bool aRenvoyer = mydb.open();
    return aRenvoyer;
}

void Database::closeDatabase()
{
    mydb.close();
}


bool Database::restoreDatabase()
{
    QString requete;
    bool bdExiste = mydb.isValid();
    bool tableExiste;
    QStringList list;
    bool tableModifiee = false;
    bool tableCreee;

    if(!bdExiste){
        qDebug() << "Base de données non existante" << Qt::endl;
    }
    if(bdExiste){
        // Si la BD existe : on vérifie qu'elle contienne la table
        list = mydb.tables();
        tableExiste = list.contains(QString("Utilisateur"));
    }

    // Traitements de la table Utilisateur
    // Si la table existe dans la base de données : on met dans qDebug que la table existe déjà
    if(bdExiste && tableExiste){
        //qDebug() << "La table existe déjà : annulez" << Qt::endl;
    }
    // Si la table n'existe pas on la créé
    if(bdExiste && !tableExiste){
        QSqlQuery query;
        requete = QString("create table Utilisateur (num int primary key, nom varchar(25), mdp varchar(25), unique (nom))");
        tableCreee = query.exec(requete);
        tableModifiee = true;
    }

    if(bdExiste && !tableCreee && !tableExiste){
        qDebug() << "Problème lors de la création de la table" << Qt::endl;
    }

    return tableModifiee;
}

bool Database::tentativeConnexion(QString nomUtilisateur, QString mdpUtilisateur)
{
    //qDebug() << "Tentative connexion base de données" << Qt::endl;
    bool connexionReussie = false;  // La variable renvoyant si la connexion a réussi ou non
    bool commandeExecutee = true;
    QSqlQuery query;                // On initalise la requette sql
    QVariant variant;                 // On initalise le variant contenant le nom de l'utilisateur
    QVariant resultat;              // Le résultat obtenu suite à l'exécution de la commande

    // On récupère le mot de passe correspondant à l'utilisateur
    query.prepare("select mdp from Utilisateur where nom = ?");
    variant = QVariant(nomUtilisateur);
    query.addBindValue(variant);

    // On vérifie que la commande s'exécute bien
    if(!query.exec()){
        commandeExecutee = false;
        qDebug() << "Problème dans la commande" << Qt::endl;
    }

    // Si la commande est exécutée on vérifie si le mot de passe correspond
    if(commandeExecutee && query.next()){
        if(query.value(0) == mdpUtilisateur){
            connexionReussie = true;
        }
    }

    // On renvoie si le mot de passe correspond
    return connexionReussie;
}
