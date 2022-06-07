#ifndef CHIFOUMI_H
#define CHIFOUMI_H

#include <QObject>

class Chifoumi : public QObject
{
    Q_OBJECT
    ///* ---- PARTIE MOD�LE ---------------------------

    ///* Une d�finition de type �num�r�
    public:
        enum UnCoup {pierre = 0, papier = 1, ciseau = 2, rien = 3};
        enum UnEtat {initial, enCours, partieFinie, enPause};

    ///* M�thodes du Mod�le
    public:
        Chifoumi();
        virtual ~Chifoumi();

        // Getters
        UnEtat getEtat();
            /* retourne l'état de la partie */
        UnCoup getCoupJoueur();
            /* retourne le dernier coup jou� par le joueur */
        UnCoup getCoupMachine();
            /* retourne le dernier coup jou� par le joueur */
        unsigned int getScoreJoueur();
            /* retourne le score du joueur */
        unsigned int getScoreMachine();
            /* retourne le score de la machine */
        unsigned int getScorePourVictoire();
            /* retourne le score nécessaire pour gagner */
        unsigned int getTpsRestant();
            /* retourne le temps restant dans la partie */
        unsigned int getTpsPourFin();
            /* retourne le temps avant l'arrêt forcé */
        QString getNomJoueur();
            /* retourne le nom du joueur */
        char determinerGagnant();
            /* d�termine le gagnant 'J' pour joueur, 'M' pour machine, 'N' pour match nul
               en fonction du dernier coup jou� par chacun d'eux */

    ///* M�thodes utilitaires du Mod�le
    public :
        UnCoup genererUnCoup();
    /* retourne une valeur al�atoire = pierre, papier ou ciseau.
       Utilis�e pour faire jouer la machine */

    // Setters
    public:
        void setEtat(UnEtat p_etat);
            /* initialise l'attribut etatPartie avec la valeur
                du paramètre p_etat */
        void setCoupJoueur(UnCoup p_coup);
            /* initialise l'attribut coupJoueur avec la valeur
               du param�tre p_coup */
        void setCoupMachine(UnCoup p_coup);
             /* initialise l'attribut coupmachine avec la valeur
               du param�tre p_coup */
        void setScoreJoueur(unsigned int p_score);
            /* initialise l'attribut scoreJoueur avec la valeur
               du param�tre p_score */
        void setScoreMachine(unsigned int p_score);
             /* initialise l'attribut coupMachine avec la valeur
               du param�tre p_score */
        void setScorePourVictoire(unsigned int p_int);
             /* initialise l'attribut scorePourGagner avec la valeur
               du paramètre p_int */
        void setTpsRestant(unsigned int p_int);
             /* initialise l'attribut tpsRestant avec la valeur
               du paramètre p_int */
        void setTpsAvantFin(unsigned int p_int);
            /* Initialise le temps de jeu d'une partie */
        void setNomJoueur(QString p_qstring);
            /* Initialise le nom du joueur */

        // Autres modificateurs
         void majScores(char p_gagnant);
            /* Mise � jour des scores en fonction des r�gles de gestion actuelles :
                - 1 point pour le gagnant lorsqu'il y a un gagnant
                - 0 point en cas de match nul
            */
        void initScores();
            /* initialise � 0 les attributs scoreJoueur et scoreMachine
               NON indispensable */
        void initCoups();
            /* initialise � rien les attributs coupJoueur et coupMachine
               NON indispensable */


    ///* Attributs du Mod�le
     private:
        UnEtat etatPartie;          // L'état actuel de la partie
        unsigned int scoreJoueur;   // score actuel du joueur
        unsigned int scoreMachine;  // score actuel de la Machine
        UnCoup coupJoueur;          // dernier coup jou� par le joueur
        UnCoup coupMachine;         // dernier coup jou� par la machine
        unsigned int scorePourVictoire;      // Le score nécessaire pour gagné
        unsigned int tpsRestant;             // Le temps restant dans la partie
        unsigned int tpsAvantFin;           // Le temps avant la fin de la partie
        QString nomJoueur;          // Le nom que le joueur saisi pour jouer
};

#endif // CHIFOUMI_H
