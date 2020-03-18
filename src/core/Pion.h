#ifndef OCTET_PION_H
#define OCTET_PION_H

#include <iostream>
#include <string.h>

#include "Case.h"

using namespace std;

const int NBCASE = 32;
const int MAXCASEHT = 24; //Max case achetée
const int MAXCASEP = 32; //Max case du plateau
const int INITCOIN = 0; //A changer
const int MAXCARTE = 20; //Max cartes du pion
class Pion{
	private :
		string nom;
		int karma;
				float bitcoin;							///Argent du pion
		unsigned int nbpropriete;
		unsigned int rang;
				int pos;								///Position du pion
				char c; 								///Caractère du pion
				struct Des 								///Les 2 Des du pion
				{
					int D1;
					int D2;
				};
				bool prisonnier;

		Case * propriete;

	public :
		Pion();
		Case & maxCase() const;

		float getCoin() const;
		unsigned int getKarma() const;
		unsigned int getNbPropriete() const;
		unsigned int getRang() const;

		Case & rapportePlus() const;
		Case & plusCher() const;
		string getNom() const;
		void ajouterLettre(const char lettre);

};

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
	@param none
	**/
	void setc(char);

	/**
	@brief Fonctdesdesion Avancer qui permet au Pion de lancer les dés afin de se déplacer
	@param pos : Position du Pion; 
	**/
	void Avancer(int pos, Des des);

};

#endif