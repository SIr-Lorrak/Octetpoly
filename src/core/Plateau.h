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
	Case * tabC; //Un tableau de case (représente le plateau)
	unsigned int casePub; //La case (position) où à lieu la campagne de pub

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
	@param numCase : unsigned int, on passe en paramètre la case voulue
	@return L'adresse d'une case
	*/
	Case * getCase(unsigned int numCase);

	/**
	@brief Permet de récupérer la case qui est actuellement en campagne de pub
	@param none
	@return La case qui est en camapagne de pub (sa position sur le plateau)
	*/
	unsigned int getcasePub();

	//---------------------------------Setters-------------------------------------------

	/**
	@brief Permet de changer la valeur de setcasePub 
	@param numCase : unsigned int, on passe en paramètre la case où la campagne de pub a lieu
	@return none
	*/
	void setcasePub(unsigned int numCase);

	//---------------------------------Méthodes-------------------------------------------

	/**
	@brief Compte le nombre restant d'entreprise et de banque non-occupé
	@param none
	@return Le nombre restant d'entreprise et de banque non-occupé 
	*/
	unsigned int nbCaseFree();

	/**
	@brief Permet de recupérer l'indice d'une case entreprise ou banque par l'intermédiaire
	de son nom
	@param nom : const & string, on passe en paramètre le nom de la case
	@return L'indice de la case, c'est-à-dire sa position sur le plateau 
	*/
	unsigned int getIndice(const string & nom) const;

	/**
	@brief Permet de vérifier si la case entreprise ou banque entrez par le joueur pour les
	portes ouvertes est disponible ou non 
	@param choix : unsigned int, la case choisie par le joueur, joueur : unsigned int, le numéro du joueur qui joue
	@return true si la case entreprise ou banque appartient au joueur ou à personne sinon false 
	*/
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