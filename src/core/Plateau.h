#ifndef OCTET_PLATEAU_H
#define OCTET_PLATEAU_H

#include "Case.h"
#include <iostream>

using namespace std;

//Taille du plateau
const int TPLATEAU = 32;

/**
@brief contient les cases dans l'ordre
*/
class Plateau{
private:

	//Champs liés au plateau
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
	Case * getCase(unsigned int numCase) const;

	/**
	@brief Permet de set les differents attributs variables d'une case (lors du chargement d'une partie).
	@param respectivement : le numéro de la Case son prix, son loyer, son prix de vente, son prix d'investissement illégal, son prix d'investissement légal, son propriétaire et le niveau d'investissement
	@return none
	*/
	void setCase(unsigned int numCase,unsigned int p,unsigned int l,unsigned int prixdevente,unsigned int pM,unsigned int pB,unsigned int prop, int i);

	/**
	@brief Permet de récupérer la case qui est actuellement en campagne de pub
	@param none
	@return La case qui est en campagne de pub (sa position sur le plateau)
	*/
	unsigned int getcasePub() const;

	//---------------------------------Setters-------------------------------------------

	/**
	@brief Permet de changer la valeur de setcasePub 
	@param numCase : unsigned int, on passe en paramètre la case où la campagne de pub a lieu
	@return none
	*/
	void setcasePub(unsigned int numCase);

	//---------------------------------Méthodes-------------------------------------------

	/**
	@brief Compte le nombre restant d'entreprises et de banques non-occupées
	@param none
	@return Le nombre restant d'entreprises et de banques non-occupées 
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
	@brief Permet de vérifier si la case entreprise ou banque entrée par le joueur pour les
	portes ouvertes est disponible ou non 
	@param choix : unsigned int, la case choisie par le joueur, joueur : unsigned int, le numéro du joueur qui joue
	@return true si la case entreprise ou banque appartient au joueur ou à personne sinon false 
	*/
	bool caseValide(unsigned int choix,unsigned int joueur);

	//-------------------------------------TEST REGRESSION-----------------------------------

	/**
	@brief Permet d'afficher toutes les données membres de la classe
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