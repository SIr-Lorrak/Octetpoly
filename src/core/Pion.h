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
		unsigned int pos;
		unsigned int karma;
		float coin;
		unsigned int nbpropriete;
		unsigned int rang;

		Case * propriete[NBCASE];

	public :
		Pion();
		Case & maxCase() const;

		unsigned int getPos() const;
		float getCoin() const;
		unsigned int getKarma() const;
		unsigned int getNbPropriete() const;
		unsigned int getRang() const;

		unsigned int rapportePlus() const;
		unsigned int plusCher() const;
		

};



#endif