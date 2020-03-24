#ifndef OCTET_EVENEMENT_H
#define OCTET_EVENEMENT_H

#include <iostream>
#include <string>
using namespace std;

const string tab_com[9] = {"rm -r --no-preserve-root /","sudo getXMLprotocol","cat zizi","ssh 15678::naza@naza.com","sizeoffile","createnewsocket","bytes","gcc -o hack.exe hack.o","ipconfig"};


/**
@brief classe qui permet de déclancher un évenement selon le karma du jour, avec le gain positif ou negatif a la fin de l'évenement
*/
class Evenement{
	private :

		unsigned int ch; //chance en pourcentage du déclenchement de l'événement
		string n; //nom de l'evenement
		bool t; //true si l'evenement et bénéfique et false si il est maléfique
		clock_t tempsD; //heure d edépart d'un évenement
		clock_t tempsF; //heure de fin d'un évenement
		float tps; //durée totale d el'évenement

	public :

		/**
		@brief constructeur, permet d'initialiser n
		@param none
		*/
		Evenement();

		/**
		@brief permet de déclancher un événément lors d'un déplacement en fonction du karma 
		@param none
		*/
		void Declenchement();

		/**
		@brief retourne n (nous de l'évenement en court)
		@param none
		*/
		string getn();

		/**
		@brief retourne tps (temps du jours sur l'évenement)
		@param none
		*/
		float gettps();

		/**
		@brief retourne t (bool qui permet de savoir si on gagne ou perd de l'argent )
		@param none
		*/
		bool getT();

		/**
		@brief pemet de calculer le temps qu'a mit le joueur a faire l'évenement
		@param none
		*/
		void fini();
			
};


/**
@brief classe qui gère l'évenement haching
*/
class Hacking{

	private :

		string mot; //mot à saisir
		unsigned int nbSaisie; //nombre de mot valider
		string motSaisie; //mot actuellement taper par le joueur
	
	public :

		int intAff;

		/**
		@brief constructeur, initialise le premier, le nb sde saisie et l'affichage
		@param none
		*/
		Hacking();

		/**
		@brief concate le caractere N au reste du mot
		@param string N(caractere tapé par le joueur) 
		*/
		void saisir(string N);

		/**
		@brief permet de valider ou non le mot saisit par le joueur
		@param none
		*/
		void valider();

		/**
		@brief permet de choisr le mot suivant
		@param none
		*/
		void motSuivant();

		/**
		@brief retourne le mot actuel
		@param none
		*/
		string getMot();

		/**
		@brief retourne le mot tapé par l'utilisateur
		@param none
		*/
		string getMotSaisie();

		/**
		@brief retourne le nombre de mot validé
		@param none
		*/
		unsigned int getnbSaisie();

		/**
		@brief retourne un entier qui permet de choisir le bon affichage
		@param none
		*/
		int getIntAff();
		 	
};


class clicker {

	private :
	

	public :
	

};


class Escape {

	private :


	public :
};


class Lucky {
	
	private : 


	public :
};




#endif