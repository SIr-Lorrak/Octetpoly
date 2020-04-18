#ifndef OCTET_PLATEAU_H
#define OCTET_PLATEAU_H

#include "Case.h"
#include <iostream>

using namespace std;

//Taille du plateau
const int TPLATEAU = 32;

class Plateau{
private:

	//Champs liée au plateau
	Case * tabC;
	unsigned int casePub;

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

	//---------------------------------Getters-------------------------------------------

	/**
	@brief Permet de récupèrer l'adresse d'une case
	@param numCase : unsigned int
	@return L'adresse d'une case
	*/
	Case * getCase(unsigned int numCase);

	unsigned int getcasePub();

	//---------------------------------Setters-------------------------------------------

	void setcasePub(unsigned int numCase);

	//---------------------------------Méthodes-------------------------------------------

	unsigned int nbCaseFree();

	unsigned int getIndice(const string & nom) const;

	bool caseValide(unsigned int choix,unsigned int joueur);

	//-------------------------------------TEST REGRESSION-----------------------------------

	/**
	@brief Permet d'afficher toutes les données membre de la classe
	@param none
	*/
	void affichageRegression();

	/**
	@brief Teste toutes les fonctions de la classe
	@param none
	*/
	void testRegressionPlateau();

};


#endif