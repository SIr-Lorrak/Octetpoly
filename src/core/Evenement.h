#ifndef OCTET_EVENEMENT_H
#define OCTET_EVENEMENT_H

#include <string.h>

class Evenement{
	private :
		unsigned int ch; //chance en pourcentage du déclenchement de l'événement
		string n; //nom de l'evenement
		bool t; //true si l'evenement et bénéfique et false si il est maléfique

	public :
		Evenement(); //constructeur par défaut (inutile)
		Evenement(const string nom,const unsigned int chance,const bool t); //constructeur

		getNom()const;

}


#endif