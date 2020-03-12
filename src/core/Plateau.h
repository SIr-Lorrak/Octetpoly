#ifndef OCTET_PLATEAU_H
#define OCTET_PLATEAU_H

#include <string.h>
#include "Case.h"
#include "Joueur.h"
#include "Ordi.h"

//Taille du plateau
const int TPLATEAU = 32;

class Plateau{
private:

	//Champs liée au plateau
	unsigned int nbcase;
	Case * tabC;

public:
	//---------------------------------Constructeur--------------------------------------
	/**
	@brief Crée le plateau (constructeur par défaut)
	@param none
	**/
	Plateau();
	/**
 	
	@brief Destructeur de la classe
	@param none
	**/
	~Plateau();

	//---------------------------------Méthodes-------------------------------------------

	Case & getCase();

	void reset();

};

#endif