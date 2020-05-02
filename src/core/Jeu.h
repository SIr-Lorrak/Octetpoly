#ifndef OCTET_JEU_H
#define OCTET_JEU_H

#include <iostream>
#include <string>

#include "Plateau.h"
#include "Carte.h"
#include "Ordi.h"
#include "Joueur.h"
#include "Evenement.h"

using namespace std;

bool fichierExiste(const string & file);
bool estPasDans(const unsigned int n, const unsigned int tab[],const unsigned int taille = 4);

/**
brief permet le fonctionnement du jeu peut importe le type d'affichage
*/
class Jeu{
	private :
		
		
		//Chance Paquet;//après implémantation des cartes chance.
		//Evenement e; //après implémantation des minis jeux.
		Joueur * tabJ[4];
		Ordi * tabO;

		unsigned int nbJoueur;//donne le nombre de joueur réel
		unsigned int joueurCourant;//donne le rang du joueur en train de jouer 
		unsigned int nbTour;//si a 0 la partie n'a pas encore débuté alors on est encore dans le menu avant le jeu.
		unsigned int ordre[4];//donne l'ordre des joueur (ex 4>2>3>1>4>2 etc)
		unsigned int prixAPayer;//le prix a payer 
		unsigned int Vainqueur;

		unsigned int nbVente;//donne le nombre de propriété vendu par le jouer en mode vente
		string choix;//Permet de stocker une saisie du joueur
		string vente[24];//Permet de stocker tout les entreprise ou banque que le joueur veut vendre

		Carte * chance;

		bool konami[10]; //vérifie si une suite de 10 touches précise est entrer (a chaque bonne appuie on ajoute un true et a chaque maivais appuie on met tout a false)

		bool attendreNom;//dans le menu démarrer, permet d'attendre que l'utilisateur est rentrer le nom du joueur
		bool confirmation;//pour demander une confirmation lors des actions "importante"
		bool desLance;//dit si le joueur courant a lancé ces dés (a réinitialiser à la fin de chaque tour)
		bool avance;//dit si le joueur a avancer
		bool attendreAmplete;
		bool actionObligatoire;
		bool vend;//Permet de savoir si on entre en mode vente (modification d'affichage)
		bool ad;//Permet de savoir si on entre en mode campagne de pub (modification d'affichage)
		bool porteO;//Permet de savoir si on entre en mode porte ouvert (modification d'affichage)
		bool quitte;
		bool pause;
		bool nouvellePartie;
		bool desLancePrison; 
		bool apresPorteOuverte;//Permet d'empêcher de jouer juste après une porte ouverte


		bool tourOrdi;//dit si le joueur courrant est un ordi ou un joueur réel

		Evenement e;
		Hacking h;
		Clicker c;
		Escape es;
		Lucky lu;
		
//-------------------------------------Méthodes------------------------------------------

		/**
		@brief vérifie si la suite de touche KONAMICODE est entrée ou non (aura un effet aleatoire sur le joueur)
		@param un string : la touche entrer par le joueur 
		*/
		void konamiCode(const string touche);

		/**
		@brief démarre la partir après que les choix est été fait dans le menu de départ
		@param aucun
		*/
		void commencerPartie();

		/**
		@brief dans le menu de départ, ajoute un Joueur et donc retire un Ordi
		@param none
		*/
		void ajouterJoueur();

		/**
		@brief dans le menu de départ, enleve un joueur
		@param none
		*/
		void enleverJoueur(unsigned int n=0);

		/**
		@brief ajoute dans vend[] le nom de l'entreprise choisi d'on l'indice est dans choix.
		@param none
		*/
		void ajouterVente();

		/**
		@brief enleve le dernier choix de vend[]
		@param none
		*/
		void enleverVente();

		/**
		@brief dans le menu de départ ajoute une lettre au nom d'un Joueur
		@param un entier : l'indice du joueur
		@param un string : la/les lettre a rajouter (normalement c'est une lettre seul)
		*/
		void ajouterLettre(const unsigned int j, const string lettre);


		/**
		@brief Permet ajouter un nombre à la séléction lors du mode vente ou pour choisir sa destination
		dans porte ouverte ou pour savoir sur quelle quartier la campagne de pub aura lieu,etc
		@param un string : le/les nombre a rajouter 
		*/
		void ajouterNombre(const string nombre);

		/**
		@brief Permet effacer un nombre à la selection lors du mode vente ou pour choisir sa destination
		dans porte ouverte ou pour savoir sur quelle quartier la campagne de pub aura lieu,etc
		@param none 
		*/
		void effacerNombre();

		/**
		@brief Permet ajouter ou effacer un nombre, permet au joueur de choisir sa destination
		dans porte ouverte ou pour savoir sur quelle quartier la campagne de pub aura lieu,etc
		ou bien quelle quartier veut-il vendre
		@param touche : string
		*/
		void ecrire(const string touche);

		/**
		@brief dans Touche.cpp permet de gerer les touche lors de la vente
		@param un string, touche, correspond à la touche enfoncée pas l'utilisateur.
		*/
		void modeVente(const string touche);

		/**
		@brief Permet au joueur de récupèré l'argent de ses ventes et de reset toutes les cases
		qui ont été vendu
		@param none
		@return none
		*/
		void remiseZeroEtVente();

		/**
		@brief détecte si il y a une victoire monopole et met le vainqueur dans vainqueur.
		@param none
		@return none
		*/
		void victoireMonopole();

		/**
		@brief sauvegarde le jeu dans un fichier pour reprendre plus tard
		@param un string : le nom/path du fichier
		*/
		void sauver(const string & file) const;

		/**
		@brief charge le jeu depuis un fichier
		@param un string : le nom/path du fichier
		*/
		bool charger(const string & file);

		/**
		@brief fait les actions durant la partie
		@param un string : touche, la touche entrer par le joueur
		*/
		void actionPartie(const string & touche);

		/**
		@brief permet d'effectuer une action selon la touche appuyer
		@param none
		*/
		void actionMiniJeu(const string touche);

		/**
		@brief permet de gerer les evenement de clavier dans le menu de départ
		@param none
		*/
		void actionMenu(const string & touche);

		/**
		@brief permet de gérer les touches rentré par l'utilisateur dans le menu de pause
		@param un string, touche, représente la touche enfoncé.
		*/
		void actionPause(const string & touche);

		/**
		@brief permet de gerer l'action alors que la partie est terminée
		@param none mait pourrais prendre une touche pour changer d'action (pour voir les stats de la partie par exemple dans un futur plus ou moins proche)
		*/
		void actionVictoire();

		/**
		@brief Procédure qui gère les actions sur une case banque ou entreprise 
		@param none
		*/
		void actionBE(const string touche);

		/**
		@brief Procédure qui gère les investissements
		@param none
		*/
		void investirEJoueur(const string touche);
			
		/**
		@brief Echange d'argent entre joueur
		@param payeur : unsigned int ; creancier : unsigned int, montant : unsigned int
		*/
		void paye(unsigned int payeur, unsigned int creancier, float montant);

		/**
		@brief Procédure qui gére le loyer à payer par un joueur
		@param none
		*/
		void payeLoyerJoueur(const string touche);

		/**
		@brief Fonction qui prends en paramètre la case sur laque le joueurCourant veux
		mettre une pub
		@param quelleCase : unsigned int
		*/
		void pub(unsigned int quelleCase);

		/**
		@brief permet de gérer les touches de l'utilisateur pendant qu'il doit payer les impôts
		@param un string touche, la touche entrée par l'utilisateur
		*/
		void impot(const string touche);

		/**
		@brief permet de gérer les touches rentrée par l'utilisateur alors qu'il est en prison
		@param toujours la même la touche rentrée sous forme de string.	
		*/
		void actionPrison(const string touche);

		/**
		@brief Détermine l'action possible sur la case
		@param none
		*/
		void actionCase(const string & touche = "");

		/**
		@brief permet à la fin de chaque tour de reset tous les booléens pour le déroulement du tour suivant
		@param none
		*/
		void resetBool();
		

	public :
		Plateau board;//seul donnée membre en public.

		/**
		@brief constructeur par défaut de Jeu
		@param aucun
		*/
		Jeu();

		/**
		@brief accesseur de l'ordre de passage des Pion
		@param un tableau d'entier en résultat (son contenue avant l'appelle sera remplacer par l'ordre des Pion)
		*/
		void getOrdre(unsigned int tab[4]) const;

		unsigned int getVainqueur()const;

		void prixKarma();

		/**
		@brief renvoie le booléen demander
		@param un string : type, il donne le nom du booléen demander 
		*/
		bool getBool(const string & type) const;

		/**
		@brief renvoie le nombre d'entreprises/banques qui ont été choisi pour être vendu
		@param none
		*/
		unsigned int getNbVente();

		/**
		@brief renvoie ne nombre de joueur (non-ordi)
		@param none
		*/
		unsigned int getNbJoueur()const;

		/**
		@brief renvoie le nombre de tour de la partie (0 si la partie n'a pas commence)
		@param none
		*/
		unsigned int getNbTour()const;

		/**
		@brief renvoie un pointeur du joueur de rang i
		@param un entier : i, le rang du joueur demander
		*/
		Joueur * getJoueur(const unsigned int i) const;

		/**
		@brief renvoie un pointeur vers un Ordi de rang i
		@param le rang i, un entier non-signé
		*/
		Ordi * getOrdi(const unsigned int i) const;

		/**
		@brief renvoie le pointeur vers Pion de rang i (le rang commence a 1 contrairement a l'indice)
		@param le rang i, un entier non-signé
		*/
		Pion * getPion(const unsigned int i) const;

		/**
		@brief renvoie le rang du joueur dont c'est le tour
		@param none
		*/
		unsigned int getJoueurCourant()const;

		/**
		@brief renvoie un pointeur vers la Carte actuellement piocher
		@param none
		*/
		Carte * getCarte()const;

		/**
		@brief renvoie le nom de la i-ème entreprise vendu
		@param l'indice indice, un entier non-signé
		*/
		string getVente(unsigned int indice);

		/**
		@brief revoie le choix du joueur quand le joueur vend un quartier ou
		choisie son quartier pour la campagne de pub ou lors de son déplacement
		pour les portes ouvertes
		@param none
		@return le choix du joueur : string
		*/
		string getChoix() const;

		/**
		@brief renvoie le prix que le joueur doit payer lors des impôts, de la prison, ou pendant la vente
		@param none
		*/
		unsigned int getPrixAPayer();
		
		/**
		@brief choisi l'action correspondante à la touche entrer par l'utilisateur
		@param un string : touche, c'est la touche entrer par le joueur
		*/
		void actionClavier(const string & touche);

		/**
		@brief permet de définir les actions qu'ont les boutons
		@param l'action du bouton enfoncé ou relaché selon le choix (actuellement c'est au relachement)
		*/
		void action(const string & action);

		/**
		@brief permet de définir les actions que fera une IA durant son tour
		@param none
		*/
		void actionOrdi();

		/**
		@brief choisi l'action correspondante au coordonné du clique de l'utilisateur
		@param deux float : x et y, les coordonnées de la souris
		*/
		void actionSouris(const float x,const float y);

		/**
		@brief Détermine qui joue au tour suivant
		@param none
		*/
		void tourSuivant();

		/**
		@brief Tire une carte chance 
		@param none	
		*/
		void actionChance(const string & touche);

		/**
		@brief fait les différente action qu'on une carte chance Carte
		@param none
		*/
		void carteChance();

		/**
		@brief Permet d'augmenter le loyer d'une entreprise
		@param none
		*/
		void campagneDePub(const string touche);

		/**
		@brief Permet de se déplacer sur une entreprises/banques 
		(pas encore acheté) ou sur une des ses entreprises/banques
		@param none
		*/
		void porteOuverte(const string & touche);

		/**
		@brief indique combien la vente rapportera
		@return le gain de la vente : unsigned int
		*/
		unsigned int totalVente();

		/**
		@brief Permet de vérifier si le joueur n'essaye pas de vendre deux fois de suite la
		même case
		@param indice : unsigned int, l'indice de la propriété que le joueur veut vendre
		@return true si le joueur l'a déja vendu sinon false
		*/
		bool dejaEnVente(unsigned int indice);

		/**
		brief seteur permetant de mettre à jour l'évenement e
		param unsigned int n(valeurs qui differents selon ce que l'on veut mettre à jour) 
		*/
		void sete(unsigned int n);

		/**
		brief seteur permetant de mettre à jour hacking h
		param unsigned int n(valeurs qui differents selon ce que l'on veut mettre à jour) 
		*/
		void seth(unsigned int n);

		/**
		brief permet de retourner l'évenement e
		param none
		*/
		Evenement gete();

		/**
		@brief permet de retourner le mini jeu hacking h
		@param none
		*/
		Hacking geth();


		/**
		@brief permet de retourner le mini jeu Clicker c
		@param none
		*/
		Clicker getc();

		/**
		@brief renvoie le mini jeu Escape es
		@param none
		*/
		Escape getes();

		/**
		@brief renvoie le mini jeu Lucky lu
		@param none
		*/
		Lucky getlu();

		/**
		@brief permet de reset le clicker
		@param none
		*/
		void setc();

		/**
		@brief reset entièrement le Jeu à la fin d'une partie ou quand le joueur souhaite retourner au menu de départ en cour de partie
		@param none
		*/
		void reset();

		/**
		@brief test de régression de Jeu
		@param none
		*/
		void testRegression();

		/**
		@brief destructeur de Jeu
		@param none
		*/
		~Jeu();

		/**
		@brief permet de définir les condition pour lesquels on ne veut pas que le joueur utilise le clavier (pour l'instant on l'autorise tout le temps)
		@param none
		*/
		bool accepteClavier() const;

		/**
		@brief permet d'update les minis Jeux automatiquement lorsque le joueur ne fait rien (pour le timer et la police qui avance)
		@param none
		*/
		void updateMiniJeu();
		

};

#endif


