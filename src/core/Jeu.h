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
};

#endif