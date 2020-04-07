#ifndef OCTET_CARTE_H
#define OCTET_CARTE_H

#include <iostream>
#include <string>

using namespace std;


/**
@brief classe qui définie les cartes chances
*/
class Carte {

	private:

		int gain; // somme gagner ou perdu indiqué sur la carte
		int id_case; // id de la case où le jouer doit se rendre indiqué sur la carte
		int id_carte; // id de la carte pioché
		bool casePlus3; // indique si le joueur doit reculer de 3 cases
		const string tab_carte[2][3] = {{"Avancez jusqu’à la case départ.","Vous êtes vieux ?","Reculez de trois cases."},{"<--------------","Payer vos cotisation de retraite s’élevant à 500$.","--------------->"}};

	public:

		/**
		@brief retourne le gain0
		@param none
		*/
		int getgain() const;

		/**
		@brief retourne l'id de la case
		@param none
		*/
		int getid_case() const;

		/**
		@brief retourne l'id de la carte
		@param none
		*/
		int getid_carte() const;

		/**
		@brief retourne le titre de la case
		@param none
		*/
		string getTitre() const;

		/**
		@brief retourne le Texte de la case
		@param none
		*/
		string getTexte() const;

		/** 
		@brief retourne un bool
		@param none
		*/
		bool getcasePlus3() const;

		/**
		@brief pioche une carte au hasard
		@param none
		*/
		void randomCarte();


};



#endif

