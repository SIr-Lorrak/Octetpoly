#ifndef OCTET_JEU_H
#define OCTET_JEU_H

#include <iostream>
#include <fstream>
#include <string.h>

#include "Plateau.h"
#include "Ordi.h"
#include "Joueur.h"
#include "Evenement.h"

using namespace std;

/**
brief permet le fonctionnement du jeu peut importe le type d'affichage
*/
class Jeu{
	private :
		Plateau board;
		//Chance Paquet;//après implémantation des cartes chance.
		//Evenement e; //après implémantation des minis jeux.
		Joueur * tabJ[4];
		Ordi * tabO;

		unsigned int nbJoueur;//donne le nombre de joueur réel
		unsigned int joueurCourant;//donne le rang du joueur en train de jouer 
		unsigned int nbTour;//si a 0 la partie n'a pas encore débuté alors on est encore dans le menu avant le jeu.
		unsigned int ordre[4];//donne l'ordre des joueur (ex 4>2>3>1>4>2 etc)
		unsigned int casePub;
		float coeffAd;

		bool konami[10]; //vérifie si une suite de 10 touches précise est entrer (a chaque bonne appuie on ajoute un true et a chaque maivais appuie on met tout a false)

		bool attendreNom;//dans le menu démarrer, permet d'attendre que l'utilisateur est rentrer le nom du joueur
		bool confirmation;//pour demander une confirmation lors des actions "importante"
		bool desLance;//dit si le joueur courant a lancé ces dés (a réinitialiser à la fin de chaque tour)
		bool avance;//dit si le joueur a avancer 
		bool tourFini;
		bool attendreAmplete;
		bool actionObligatoire;

		bool tourOrdi;//dit si le joueur courrant est un ordi ou un joueur réel

		Evenement e;
		Hacking h;
		
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
		void enleverJoueur();

		/**
		@brief dans le menu de départ ajoute une lettre au nom d'un Joueur
		@param un entier : l'indice du joueur
		@param un string : la/les lettre a rajouter (normalement c'est une lettre seul)
		*/
		void ajouterLettre(const unsigned int j, const string lettre);

		/**
		@brief sauvegarde le jeu dans un fichier pour reprendre plus tard
		@param un string : le nom/path du fichier
		*/
		void sauver(const string & file) const ;

		/**
		@brief charge le jeu depuis un fichier
		@param un string : le nom/path du fichier
		*/
		void charger(const string & file);

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
		@brief Procédure qui gère les action sur une case banque ou entreprise d'un ordi
		@param none
		*/
		void actionBE(const string touche);

		/**
		@brief Procédure qui gère les investissement d'un joueur
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
		void payeLoyerJoueur();

		/**
		@brief Permet d'augmenter le loyer d'une entreprise
		@param none
		*/
		void campagneDePub(const string touche);

		/**
		@brief Fonction qui prends en paramètre la case sur laque le joueurCourant veux
		mettre un pub
		@param quelleCase : unsigned int
		*/
		void pub(unsigned int quelleCase);

		/**
		@brief Détermine l'action possible sur la case
		@param none
		*/
		void actionCase(const string & touche = "");


		void resetBool();
		

	public :
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


		/**
		@brief renvoie le booléen demander
		@param un string : type, il donne le nom du booléen demander 
		*/
		bool getBool(const string & type) const;

		Case & getJCase(const unsigned int i) ;

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

		Ordi * getOrdi(const unsigned int i) const;

		Pion * getPion(const unsigned int i) const;

		unsigned int getJoueurCourant()const;


		/**
		@brief choisi l'action correspondante à la touche entrer par l'utilisateur
		@param un string : touche, c'est la touche entrer par le joueur
		*/
		void actionClavier(const string & touche);

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
		void carteChance();

		/**
		@brief Permet d'augmenter le loyer d'une entreprise
		@param none
		*/
		void campagneDePub();

		/**
		@brief Permet de se déplacer sur une entreprises/banques 
		(pas encore acheté) ou sur une des ses entreprises/banques
		@param none
		*/
		void porteOuverte();

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
		brief permet de retourner hacking h
		param none
		*/
		Hacking geth();

		/**
		@brief destructeur de Jeu
		@param none
		*/
		~Jeu();
		

};

#endif


