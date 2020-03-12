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

	/**
	@brief Action possible sur l'entreprise 
	@param none
	**/
	void entreprise();

	/**
	@brief Action possible sur la banque 
	@param none
	**/
	void banque();

	/**
	@brief Action possible en prison 
	@param none
	**/
	void prison();

	/**
	@brief Tire une carte chance 
	@param none	
	**/
	void carteChance();

	/**
	@brief Permet d'augmenter le loyer d'une entreprise
	@param none
	**/
	void campagneDePub();

	/**
	@brief Permet de se déplacer sur une entreprises/banques (pas encore acheté) ou sur une des ses entreprises/banques
	@param none
	**/
	void porteOuverte();

};

#endif