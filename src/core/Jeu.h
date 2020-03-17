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
		Chance Paquet;
		Joueur j[4];
		Ordi o[4];
		unsigned int nbOrdi;
		unsigned int nbTour;
		unsigned int ordre[4];
		bool konami[10]; //pour le konami code
		

	public :
		Jeu();
		void sauver(const string & file) const ;
		void charger(const string & file);
		void actionClavier(const char touche);
		void actionSouris(const float x,const float y);
};

#endif