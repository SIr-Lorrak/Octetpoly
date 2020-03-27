#ifndef OCTET_PLATEAU_H
#define OCTET_PLATEAU_H

#include "Case.h"
#include "Ordi.h"
#include "Joueur.h"

//Taille du plateau
const int TPLATEAU = 32;

class Plateau{
private:

	//Champs liée au plateau
	Case * tabC;

public:
	//---------------------------------Constructeur--------------------------------------
	/**
	@brief Crée le plateau (constructeur par défaut)
	@param none
	*/
	Plateau();

	/**
	@brief Destructeur de la classe
	@param none
	*/
	~Plateau();

	//---------------------------------Méthodes-------------------------------------------

	/**
	@brief Permet de récupèrer l'adresse d'une case
	@param numCase : unsigned int
	@return L'adresse d'une case
	*/
	Case * getCase(unsigned int numCase);

};


#endif