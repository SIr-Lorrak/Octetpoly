#ifndef OCTET_PION_H
#define OCTET_PION_H

#include <iostream>
#include <string.h>

#include "Case.h"

using namespace std;

const int NBCASE = 32;

class Pion{
	private :
		string nom;
		int karma;
		float coin;
		unsigned int nbpropriete;
		unsigned int rang;

		Case * propriete;

	public :
		Pion();
		Case & maxCase() const;

		float getCoin() const;
		unsigned int getKarma() const;
		unsigned int getNbPropriete() const;
		unsigned int getRang() const;

		Case & rapportePlus() const;
		Case & plusCher() const;
		string getNom() const;
		void ajouterLettre(const char lettre);

};



#endif