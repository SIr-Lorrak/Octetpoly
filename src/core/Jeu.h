#ifndef OCTET_JEU_H
#define OCTET_JEU_H

#include "Plateau.h"
#include "Joueur.h"
#include "Ordi.h"

class Jeu{
private:


public:
//-------------------------------------Constructeurs-------------------------------------


//-------------------------------------Méthodes------------------------------------------
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

	/**
	@brief Détermine l'action possible sur la case
	@param none
	**/
	void ActionCase();


};


#endif