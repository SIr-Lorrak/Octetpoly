#ifndef OCTET_JEU_H
#define OCTET_JEU_H

#include <iostream>
#include <fstream>
#include <string.h>

#include "Plateau.h"
#include "Ordi.h"
#include "Joueur.h"

using namespace std;

class Jeu{
private :
//-------------------------------------Données membres-------------------------
		Plateau board;
		//Chance Paquet;//après implémantation des cartes chance.
		//Evenement e; //après implémantation des minis jeux.
		Joueur * tabJ[4];
		Ordi * tabO;
		unsigned int nbJoueur;
		unsigned int joueurCourant;
		unsigned int nbTour;//si a 0 la partie n'a pas encore débuté alors on est encore dans le menu avant le jeu.
		unsigned int ordre[4];
		unsigned int casePub; //Quelle case à de la publicité
		unsigned int coeffAd;
		float coinCourant;
		bool konami[10]; //pour le konami code ^^vv<><>ba "entrée"
		bool attendreNom;
		bool attendreChoix;
		bool confirmation;
		bool desLance;
		bool avance;
		bool tourOrdi;//bool qui permet de savoir à quelle tableau on doit accéder		
		//tourOrdi = false un joueur joue ; tourOrdi = true un ordi joue
		
//-------------------------------------Méthodes------------------------------------------

		/**
		@brief
		@param
		*/
		void konamiCode(const string touche);

		/**
		@brief
		@param
		*/
		void commencerPartie();

		/**
		@brief
		@param
		*/
		void ajouterJoueur();

		/**
		@brief
		@param
		*/
		void ajouterLettre(const unsigned int j, const string lettre);

		/**
		@brief
		@param
		*/
		void sauver(const string & file) const ;

		/**
		@brief
		@param
		*/
		void charger(const string & file);
		

public :
		/**
		@brief
		@param
		*/
		Jeu();

		/**
		@brief
		@param
		*/
		void getOrdre(unsigned int tab[4]) const;

		/**
		@brief
		@param
		*/
		void actionClavier(const string touche);

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
	@brief Appeler lors d'un paimement impossible causé par un manque de fond
	@param none
	*/
	void faillite();

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
	void actionCase(const string touche);

	/**
	@brief Echange d'argent entre joueur
	@param payeur : unsigned int ; creancier : unsigned int, montant : unsigned int
	*/
	void paye(unsigned int payeur, unsigned int creancier, float montant);

	/**
	@brief Un ordi doit payer un loyer
	@param c : pointeur sur Case ; float argent du joueur qui doit payer le loyer
	*/
	void payeLoyer();

	void investirEOrdi();

	void actionBEOrdi();
};

#endif

