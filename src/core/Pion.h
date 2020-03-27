#ifndef OCTET_PION_H
#define OCTET_PION_H

#include <iostream>
#include <string.h>

#include "Case.h"

using namespace std;

const int MAXCASEHT = 24; //Max case achetée
const int MAXCASEP = 32; //Max case du plateau
const int INITCOIN = 500; //A changer
const int MAXCARTE = 20; //Max cartes du pion


const string noms[20] = {"Tom Pousse","Haaaamid","Pedro","Sabrina","SaBine","Jessica","Nathan","Aspifion","Mais il est fou lui enfin","M. Pronost le meilleur prof de la terre",
						 "Bamboula","M. Pujo","Corrine","Alexandra","Jus d'huitre","Guy the Boomer","José Pélouze","BITENTRONC","Patoche","Nabil"};


 								
struct Des{								///Les 2 Des du pion
	unsigned int D1;
	unsigned int D2;
};
				
class Pion{
	private :
		string nom;
		int karma;
		unsigned int rang;
		int bitcoin;					///Argent du pion
		unsigned int nbpropriete;
		unsigned int pos;				///Position du pion
		char car;	
		Des d;					///Caractère du pion
		bool prisonnier;
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

	///---------------------------------Méthode-------------------------------------------

		void nomAleatoire();

		Pion * getPion();

		/**
		@brief
		@param
		*/
		unsigned int getRang() const;

		/**
		@brief
		@param
		*/
		string getNom() const;

		void setNom(const string & n);

		/**
		@brief
		@param
		*/
		unsigned int getNbPropriete() const;

		/**
		@brief Accesseur de la position du pion
		@param none
		**/
		unsigned int getPos() const;

		/**
		@brief Accesseur du karma du pion
		@param none
		**/
		int getKarma() const;

		/**
		@brief Accesseur de l'argent du pion
		@param none
		**/
		float getCoin() const;

		/**
		@brief Accesseur du caractère du pion
		@param none
		**/
		char getCar() const;


		Des getDes() const;

		/**
		@brief Accesseur du booléen prisonnier qui définit si le pion est prisonnié ou non
		@param none
		**/
		bool getPrisonnier() const;

		/**
		@brief Mutateur du caractère du pion
		@param none
		**/
		void setCar(const char c);

		bool estFaillite() const;

		/**
		@brief Fonctdesdesion Avancer qui permet au Pion de lancer les dés afin de se déplacer
		@param none
		**/
		void avancer();

		/**
		@brief
		@param
		*/
		unsigned int rapportePlus() const;

		/**
		@brief
		@param
		*/
		unsigned int plusCher() const;

		/**
		@brief
		@param
		*/
		void ajouterLettre(const string lettre);

		/**
		@brief
		@param
		*/
		void effacerLettre();

		/**
		@brief
		@param
		*/
		void lanceDes();

};

#endif