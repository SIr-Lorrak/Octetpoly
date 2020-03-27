#ifndef OCTET_PION_H
#define OCTET_PION_H

#include <iostream>
#include <string.h>

#include "Case.h"
//#include "Carte.h"

using namespace std;

const int MAXCASEHT = 24; //Max case achetée
const int MAXCASEP = 32;  //Max case du plateau
const int INITCOIN = 500; //Argent initial
const int MAXCARTE = 20;  //Max cartes du pion

/**
@brief Classe Pion
**/
struct Des 								///Les 2 Des du pion
	{	
		unsigned int D1;
		unsigned int D2;
	};

class Pion{
	
	private :

		string nom;
		int karma;
		unsigned int rang;
		float bitcoin;					///Argent du pion
		unsigned int nbpropriete;
		unsigned int pos;				///Position du pion
		char car;						///Caractère du pion
		Des d;							
		bool prisonnier;
		Case ** propriete;				///Tableau de pointeur vers case de proprietes du pion
		bool doubles[2];				///Tableau de trois booléens qui indique le nombre de double à la suite du pion


	public :

///-----------------------Constructeur/Destructeur--------------------------------------
	/**
	@brief Crée le Joueur (constructeur par défaut)
	@param none
	**/
	Pion();

	/**
	@brief Destructeur de la classe
	@param none
	**/
	~Pion();

///---------------------------------Méthode-------------------------------------------
	
	/**
	@brief Accesseur du nom du pion
	@param none
	**/
	string getNom() const;

	/**
	@brief Accesseur du karma du pion
	@param none
	**/
	int getKarma() const;

	/**
	@brief Accesseur du rang du pion
	@param none
	*/
	unsigned int getRang() const;

	/**
	@brief Accesseur de l'argent du pion
	@param none
	**/
	float getCoin() const;

	/**
	@brief Accesseur du nombre de propriétés détenues par le joueur
	@param none
	*/
	unsigned int getNbPropriete() const;

	/**
	@brief Accesseur de la position du pion
	@param none
	**/
	unsigned int getPos() const;

	/**
	@brief Accesseur du caractère du pion
	@param none
	**/
	char getCar() const;

	/**
	@brief Accesseur du booléen prisonnier qui définit si le pion est prisonnié ou non
	@param none
	**/
	bool getPrisonnier() const;

	/**
	@brief Mutateur du caractère du pion
	@param c : charactere
	**/
	void setCar(const char c);

	/**
	@brief Mutateur du caractère du pion
	@param argent : float
	**/
	void setCoin(const float argent);

	/**
	@brief Mutateur du pion
	@param argent : float
	**/
	Pion * getPion();

	/**
	@brief Procédure qui lance les dés du pion
	@param none
	*/
	void lanceDes();

	/**
	@brief Procédure permettant de se déplacer
	@param none
	**/
	void avance();

	/**
	@brief
	@param none
	*/
	unsigned int rapportePlus() const;

	/**
	@brief
	@param none
	*/
	unsigned int plusCher() const;

	/**
	@brief Procédure qui ajoute une lettre au nom du pion
	@param lettre : string
	*/
	void ajouterLettre(const string lettre);

	/**
	@brief Procédure qui efface une lettre au nom du pion
	@param none
	*/
	void effacerLettre();

	/**
	@brief Fonction qui fait la somme de la revente de tous les biens (entreprises et banques) du pion
	@param none
	*/
	float ReventeToFaillite();

	/**
	@brief 
	@param none
	*/
	void salaire();

	/**
	@brief 
	@param none
	*/
	void vendrePropriete();

	/**
	@brief 
	@param c : Un pointeur vers la case qui est achetée
	*/
	void achete(Case * c);


};

#endif