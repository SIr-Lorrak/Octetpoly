#ifndef OCTET_PION_H
#define OCTET_PION_H

#include "Case.h"
//#include "Carte.h"

const int MAXCASEHT = 24; //Max case achetée
const int MAXCASEP = 32; //Max case du plateau
const int INITCOIN = 0; //A changer
const int MAXCARTE = 20; //Max cartes du pion

/**
@brief Classe Pion
**/

class Pion{
	private :	
				int pos;								///Position du pion
				int karma;								///Karma positif ou négatif du pion
				float bitcoin;							///Argent du pion
				Case * proprietes[MAXCASEHT];			///Tableau de pointeur sur case
				char c; 								///Caractère du pion
				struct Des 								///Les 2 Des du pion
				{
					int D1;
					int D2;
				};
				bool prisonnier;
				//Carte * cartes[MAXCARTE];

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
	@brief Accesseur de la position du pion
	@param none
	**/
	int getpos();

	/**
	@brief Accesseur du karma du pion
	@param none
	**/
	int getkarma();

	/**
	@brief Accesseur de l'argent du pion
	@param none
	**/
	float getbitcoin();

	/**
	@brief Accesseur du tableau qui comporte les indices des cases achetées par le pion
	@param none
	**/
	//int getIndCaseAchetee(); // void a la place de int

	/**
	@brief Accesseur du caractère du pion
	@param none
	**/
	char getc();

	/**
	@brief Accesseur du booléen prisonnier qui définit si le pion est prisonnié ou non
	@param none
	**/
	bool getprisonnier();

	/**
	@brief Mutateur du caractère du pion
	@param c : charactere
	**/
	void setc(char c);

	/**
	@brief Procédure Avancer qui permet au Pion de lancer les dés afin de se déplacer
	@param pos : entier; des : structure Des;
	**/
	void Avancer(int pos, Des des);

	/**
	@brief Procédure Prisonnier qui permet de déplacer le Pion sur la Case Prison s'il a tiré une carte prison.
	@param none
	**/
	void Prisonnier();
};

#endif