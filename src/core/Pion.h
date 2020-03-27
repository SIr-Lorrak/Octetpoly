#ifndef OCTET_PION_H
#define OCTET_PION_H

#include <iostream>

#include "Case.h"

using namespace std;

const int MAXCASEHT = 24; //Max case achetée
const int MAXCASEP = 32; //Max case du plateau
const int INITCOIN = 500; //A changer
const int MAXCARTE = 20; //Max cartes du pion

/**
@brief Classe Pion
**/
struct Des 								///Les 2 Des du pion
	{	
		int D1;
		int D2;
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
		unsigned prisonnier;
		Case ** propriete;

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


///---------------------------------Getters-------------------------------------------	
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


///-------------------------------------Setters-------------------------------------------
	void setCar(const char c);

	/**
	@brief Mutateur du caractère du pion
	@param argent : float
	**/
	void setCoin(const float argent);


///------------------------------------Méthodes------------------------------------------

	/**
	@brief Procédure qui lance les dés du pion
	@param none
	*/
	void lanceDes();

	/**
	@brief Procédure permettant de se déplacer
	@param none
	**/
	void avancer();

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
	@brief Procdédure qui permet au joueur d'acheter une banque ou une entreprise
	@param c : pointeur sur case
	*/
	void acheter(Case * c);

	void salaire();

	/**
	@brief Procdédure qui fait vendre des propriété au joueur
	@param c : pointeur sur case
	*/
	void vendre();

	Pion * getPion();

	/**
	@brief Procdédure qui nous informe de notre patrimoineActif
	@param none
	@return la somme des prix de vente (banque + entreprise)
	*/
	float patrimoineActif();
};

#endif