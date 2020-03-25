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
		unsigned int nbJoueur;
		unsigned int joueurCourant;
		unsigned int nbTour;//si a 0 la partie n'a pas encore débuté alors on est encore dans le menu avant le jeu.
		unsigned int ordre[4];
		bool konami[10]; //pour le konami code ^^vv<><>ba "entrée"
		bool attendreNom;
		bool attendreChoix;
		bool confirmation;
		bool desLance;
		bool avance;
		bool tourOrdi;

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
		@param aucun
		*/
		void ajouterJoueur();

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
		@brief
		@param
		*/
		void actionPartie(const string & touche);
		

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
		@brief 
		@param
		*/
		void actionClavier(const string & touche);

		/**
		@brief
		@param
		*/
		void actionSouris(const float x,const float y);

		/**
		@brief Détermine qui joue au tour suivant
		@param none
		*/
		void tourSuivant();

		~Jeu();
		/**
		@brief Action possible sur l'entreprise 
		@param none
		*/
		void entreprise();

		/**
		@brief Action possible sur la banque 
		@param none
		*/
		void banque();

		/**
		@brief Action possible en prison 
		@param none
		*/
		void prison();

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
		@brief Détermine l'action possible sur la case
		@param none
		*/
		void actionCase(unsigned int num);




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
		brief permet d'effectuer une action selon la touche appuyer
		param none
		*/
		void actionMiniJeu(const string touche);


};

#endif