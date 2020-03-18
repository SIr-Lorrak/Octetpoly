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
		Plateau p;
		//Chance Paquet;//après implémantation des cartes chance.
		//Evenement e; //après implémantation des minis jeux.
		Joueur * j[4];
		Ordi * o;
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


		void konamiCode(const string touche);
		void commencerPartie();
		void ajouterJoueur();
		void ajouterLettre(const unsigned int j, const char lettre);
		void sauver(const string & file) const ;
		void charger(const string & file);
		

	public :
		Jeu();
		void getOrdre(unsigned int tab[4]) const;
		void actionClavier(const string touche);
		void actionSouris(const float x,const float y);

	/**
	@brief Détermine qui joue au tour suivant
	@param none
	*/
	void tourSuivant();

	~Jeu();
//-------------------------------------Méthodes------------------------------------------
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

};

#endif