#ifndef OCTET_PION_H
#define OCTET_PION_H

#include <iostream>
#include <string.h>

#include "Case.h"
//#include "Carte.h"

using namespace std;

const int MAXCASEHT = 24; ///Max case achetée
const int MAXCASEP = 32;  ///Max case du plateau
const int INITCOIN = 500; ///Argent initial
const int MAXCARTE = 20;  ///Max cartes du pion


const string noms[20] = {"Tom Pousse","Haaaamid","Pedro","Sabrina","SaBine",
						 "Jessica","Nathan","Aspifion","Mais il est fou lui enfin","M. Pronost le meilleur prof de la terre",
						 "Granolax","M. Pujo","Corrine","Alexandra","Jus d'huitre",
						 "Guy the Boomer","José Pélouze","BITENTRONC","Patoche","Nabil"};


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

		string nom;						///Nom du pion
		int karma;						///Karma du pion
		unsigned int rang;				///Rang du pion
		float bitcoin;					///Argent du pion
		unsigned int nbpropriete;		///Nombre de propriétés que possède le pion
		unsigned int pos;				///Position du pion
		char car;						///Caractère du pion
		Des d;							///Dés du pion
		bool prisonnier;				///Booléen qui indique si le joueur est prisonnier ou non
		Case ** propriete;				///Tableau de pointeur vers case de propriétés du pion
		bool doubles[2];				///Tableau de trois booléens qui indique le nombre de double à la suite du pion
		//Carte ** deck;


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
	@brief Accesseur du booléen prisonnier qui définit si le pion est en prison ou non
	@param none
	**/
	bool getPrisonnier() const;

	/**
	@brief Mutateur du pion
	@param none
	**/
	Pion * getPion();

	Des getDes() const;

	/**
	@brief Mutateur du caractère du pion
	@param c : charactere
	**/
	void setCar(const char c);

	/**
	@brief Mutateur de l'argent (bitcoin) du pion
	@param argent : float
	**/
	void setCoin(const float argent);

	void setNom(const string & n);

	void setRang(const unsigned int r);


	void nomAleatoire();

	/**
	@brief Procédure qui lance les dés du pion
	@param none
	*/
	void lanceDes();

	/**
	@brief Procédure permettant au pion de se déplacer
	@param none
	**/
	void avancer();

	/**
	@brief	Fonction qui retourne l'indice de la case avec le plus gros loyer
	@param none
	*/
	unsigned int rapportePlus() const;

	/**
	@brief Fonction qui retourne l'indice de la case la plus chère
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

	unsigned int patrimoineActif();

	/**
	@brief Procédure qui donne 20 bitcoins au pion lorsqu'il passe par la case départ
	@param none
	*/
	void salaire();

	/**
	@brief Procédure qui permet au pion de vendre une propriété
	@param indP : entier non signé , c : Un pointeur vers la case que le pion veut vendre
	*/
	void vend(unsigned int indP, Case * c);

	/**
	@brief Procédure qui permet au pion d'acheter l'entreprise ou la banque sur laquelle le pion est tombé
	@param c : Un pointeur vers la case entreprise ou banque où se trouve le pion 
	*/
	void achete(Case * c);

	void investit(int i,Case * c);


};

#endif