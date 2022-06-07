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
    QString requete;                // La requete exécutée par le QSqlQuery
    bool bdExiste = mydb.isValid(); // La base de données existe-t-elle
    bool tableUtilisateurExiste;    // La table utilisateur existe-t-elle
    bool tablePartieExiste;         // La table partie existe-t-elle
    QStringList list;               // La liste qui va recueillir les tables de la bd et les champs de la table partie
    bool tableModifiee = false;     // La table a-t-elle été modifiée
    bool tableCreee;                // A-t-on créé la table
    QSqlQuery query;                // La requete que l'on execute

    if(!bdExiste){
        qDebug() << "Base de données non existante" << Qt::endl;
    }
    if(bdExiste){
        // Si la BD existe : on vérifie qu'elle contienne la table
        list = mydb.tables();
        tableUtilisateurExiste = list.contains(NOM_TABLE_UTILISATEUR);
        tablePartieExiste = list.contains(NOM_TABLE_PARTIE);
    }

    // Traitements de la table Utilisateur
    // Si la table existe dans la base de données : on met dans qDebug que la table existe déjà
    if(bdExiste && tableUtilisateurExiste){
        //qDebug() << "La table Utilisateur existe déjà : annulez" << Qt::endl;
    }
    // Si la table n'existe pas on la créé
    if(bdExiste && !tableUtilisateurExiste){
        requete = QString("create table Utilisateur (num int primary key, nom varchar(25), mdp varchar(25), unique (nom))");
        tableCreee = query.exec(requete);
        tableModifiee = true;
    }

    if(!bdExiste){
        //qDebug() << "Base de données non existante" << Qt::endl;
    }

    if(bdExiste && !tableCreee && !tableUtilisateurExiste){
        //qDebug() << "Problème lors de la création de la table Utilisateur" << Qt::endl;
    }

    // Traitements de la table Partie
    // Si la table existe dans la base de données : on met dans qDebug que la table existe déjà
    if(bdExiste && tablePartieExiste){
        //qDebug() << "La table Partie existe déjà : annulez" << Qt::endl;
    }
    // Si la table n'existe pas on la créé
    if(bdExiste && !tablePartieExiste){
        QSqlQuery query;
        requete = QString("create table Partie (num int primary key, horodatage datetime, nomJHumain varchar(25), scoreJHumain int,");
        requete.insert(requete.size(), " nomJMachine varchar(25), scoreJMachine int, numUtilisateur int, ");
        requete.insert(requete.size(), "foreign key (numUtilisateur) references Utilisateur(num))");
        tableCreee = query.exec(requete);
        //qDebug() << tableCreee << Qt::endl;
        tableModifiee = true;
    }

    if(bdExiste && !tableCreee && !tableUtilisateurExiste){
        //qDebug() << "Problème lors de la création de la table Partie" << Qt::endl;
    }

    return tableModifiee;
}

bool Database::tentativeConnexion(QString nomUtilisateur, QString mdpUtilisateur, int& numUtilisateur)
{
    //qDebug() << "Tentative connexion base de données" << Qt::endl;
    bool connexionReussie = false;  // La variable renvoyant si la connexion a réussi ou non
    bool commandeExecutee = true;
    QSqlQuery query;                // On initalise la requette sql
    QVariant variant;                 // On initalise le variant contenant le nom de l'utilisateur
    QVariant resultat;              // Le résultat obtenu suite à l'exécution de la commande
    QVariant varNumUser;            // Le variant du numéro utilisateur

    // On récupère le mot de passe correspondant à l'utilisateur
    query.prepare("select num, mdp from Utilisateur where nom = ?");
    variant = QVariant(nomUtilisateur);
    query.addBindValue(variant);

    // On vérifie que la commande s'exécute bien
    if(!query.exec()){
        commandeExecutee = false;
        qDebug() << "Problème dans la commande" << Qt::endl;
    }

    // Si la commande est exécutée on vérifie si le mot de passe correspond
    if(commandeExecutee && query.next()){
        if(query.value(1) == mdpUtilisateur){
            connexionReussie = true;
        }
    }

    // Si la connexion a réussi on récupère le numéro de l'utilisateur
    if(connexionReussie){
        varNumUser = query.value(0);
        numUtilisateur = varNumUser.toInt();
    }

    // On renvoie si le mot de passe correspond
    return connexionReussie;
}

void Database::ajouterPartie(QDateTime *horodatage, QString nomJoueur, int scoreJoueur, QString nomMachine, int scoreMachine, int numUtilisateur)
{
    QVariantList list;      // On récupère une liste contenant toutes les parties
    int nbParties;
    bool nbPartieRecupere;
    QSqlQuery query;
    int numPartie;
    bool insertionReussie = true;

    // On commence par regarder combien de parties nous avons dans la base de données
    nbPartieRecupere = query.exec("select num from Partie");

    // On ne continue que si la requete a fonctionné
    if(nbPartieRecupere){
        for (int i = 0; query.next(); i++){
            list << query.value(0);
        }
        nbParties = list.size();
        //qDebug() << nbParties << Qt::endl;

        // A partir de ce nombre de parties nous calculons le numéro de la nouvelle partie
        // La première partie étant la partie 1, il nous faut ajouter 1 au nombre de parties
        numPartie = nbParties + 1;

        // Nous préparons la requete à exécuter
        query.prepare("insert into Partie values (?, ?, ?, ?, ?, ?, ?)");
        query.addBindValue(QVariant(numPartie));
        query.addBindValue(QVariant(horodatage->toString(QString("yyyy-MM-ddThh:mm:ss"))));
        query.addBindValue(QVariant(nomJoueur));
        query.addBindValue(QVariant(scoreJoueur));
        query.addBindValue(QVariant(nomMachine));
        query.addBindValue(QVariant(scoreMachine));
        query.addBindValue(QVariant(numUtilisateur));
        insertionReussie = query.exec();
    }

    if (!insertionReussie){
        qDebug() << "Problème dans l'insertion de la partie dans la base de données" << Qt::endl;
    }
}

void Database::chargerResultats(QSqlQueryModel *& model)
{
    QString strQuery;       // La requete a exécuter pour récupèrer le modele en QString pour la composer
    QSqlQuery query;        // La requete QSqlQuery pour construire le modèle
    // On compose la requete sql
    strQuery = QString("select nomJHumain, scoreJHumain, nomJMachine, scoreJMachine, scoreJHumain / scoreJMachine as Ratio ");
    strQuery.insert(strQuery.size(), QString("from Partie where scoreJMachine <> 0 order by Ratio desc limit 10"));
    //query.prepare(strQuery);        // On place la requête dans le QSqlQuery
    //query.exec();
    model->setQuery(strQuery); // On récupère le modèle
    model->setHeaderData(0, Qt::Horizontal, QString("Nom Joueur"));
    model->setHeaderData(1, Qt::Horizontal, QString("Score Joueur"));
    model->setHeaderData(2, Qt::Horizontal, QString("Nom Machine"));
    model->setHeaderData(3, Qt::Horizontal, QString("Score Machine"));
    model->setHeaderData(4, Qt::Horizontal, QString("Ratio"));
}
