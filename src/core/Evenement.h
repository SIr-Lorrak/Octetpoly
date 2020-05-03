#ifndef OCTET_EVENEMENT_H
#define OCTET_EVENEMENT_H

#include <iostream>
#include <string>
#include "Carte.h"
using namespace std;

const string tab_com[9] = {"rm -r --no-preserve-root /","sudo getXMLprotocol","cat zizi","ssh 15678::naza@naza.com","sizeoffile","createnewsocket","bytes","gcc -o hack.exe hack.o","ipconfig"};
const string tab_escape[11][11]={{"M" , "M" , "M" , "M" , "M" , "M" , "M" ,   "M"  , "M" , "M" , "M"},
								 {"M" , "H" , "H" , "H" , "H" , "H" , "H" ,"ARRIVE", "H" , "H" , "M"},
								 {"M" , "H" ,"T1" , "RH", "T2", "H" , "H" ,   "RV" , "H" , "H" , "M"},
								 {"M" , "H" ,"RV" , "H" , "T4", "RH", "RH",   "T3" , "H" , "H" , "M"},
								 {"M" , "H" ,"RV" , "H" , "H" , "H" , "H" ,    "H" , "H" , "H" , "M"},
								 {"M" , "H" ,"T4" , "T2", "H" , "H" , "H" ,    "H" , "H" , "H" , "M"},
								 {"M" , "H" ,"T1" , "T3", "T1", "RH", "RH",   "T2" , "H" , "H" , "M"},
								 {"M" , "H" , "T4", "RH", "T3", "H" , "H" ,   "RV" , "H" , "H" , "M"},
								 {"M" , "H" , "H" , "H" , "H" , "H" , "H" ,   "RV" , "H" , "H" , "M"},
								 {"M" , "H" , "H" , "H" , "H" , "H" , "H" ,"DEPART", "H" , "H" , "M"},
								 {"M" , "M" , "M" , "M" , "M" , "M" , "M" ,    "M" , "M" , "M" , "M"}};


struct vec2D
{
	int x;
	int y;
};


/**
@brief classe qui permet de déclancher un évènement selon le karma du joueur, avec le gain positif ou negatif à la fin de l'évènement
*/
class Evenement{
	private :

		unsigned int ch; //chance en pourcentage du déclenchement de l'évènement
		string n; //nom de l'évènement
		bool t; //true si l'évènement et bénéfique et false s'il est maléfique
		clock_t tempsD; //heure de départ d'un évènement
		clock_t tempsF; //heure de fin d'un évènement
		float tps; //durée totale de l'évènement
		int gain; //montant que vous allez gagner ou perdre

	public :

		/**
		@brief constructeur, permet d'initialiser n
		@param none
		*/
		Evenement();

		/**
		@brief permet de déclancher un évènement lors d'un déplacement en fonction du karma renvoie true si un mini jeu est lancé
		@param none
		*/
		bool Declenchement(int karma);

		/**
		@brief retourne n (nom de l'évènement en cours)
		@param none
		*/
		string getn();

		/**
		@brief retourne tps (temps du jours sur l'évènement)
		@param none
		*/
		float gettps();

		/**
		@brief retourne t (bool qui permet de savoir si l'on gagne ou perd de l'argent )
		@param none
		*/
		bool getT();

		void reset();


		/**
		@brief pemet de calculer le temps qu'a mit le joueur à faire l'évènement
		@param none
		*/
		void fini(int clique = 0);

		/**
		@brief retourne le gain à la fin de l'évènement
		@param none
		*/
		int getgain();

		/**
		@brief retourne le temps de départ
		@param none
		*/
		clock_t gettempsD();

		/**
		@brief retourne le temps de fin (0 si le jeu est encore en cours)
		@param none
		*/
		clock_t getTempsF() const;

			
};


/**
@brief classe qui gère l'évènement haching, un Mini-Jeu dans lequel il faut taper rapidement du texte
*/
class Hacking{

	private :

		string mot; //mot à saisir
		unsigned int nbSaisie; //nombre de mot validé
		string motSaisie; //mot actuellement tapé par le joueur
		bool fin;//dit si le jeu est fini 
		unsigned int nbMot; //nombre de mot à saisir pour finir
	
	public :

		int intAff;

		/**
		@brief constructeur, initialise le premier, le nb de saisie et l'affichage
		@param none
		*/
		Hacking();

		/**
		@brief concate le caractère N au reste du mot
		@param string N(caractère tapé par le joueur) 
		*/
		void saisir(string N);

		/**
		@brief enlève le dernier caractère de motSaisie
		@param none
		*/
		void effacerLettre();

		/**
		@brief permet de validé ou non le mot saisit par le joueur
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
		@brief retourne d=le nombre de mot saisie
		@param none
		*/
		unsigned int getnbMot();

		/**
		@brief retourne un entier qui permet de choisir le bon affichage
		@param none
		*/
		int getIntAff();

		/**
		@brief retourne le booléen qui dit si le hacking est fini
		@param none
		*/
		bool getFin() const;

		/**
		@brief permet de reset les données membres à la fin de l'évènement hacking
		@param none
		*/
		void resetHack();
		 	
};

/**
brief classe qui gère l'évènement clicker, Mini-jeu où il faut clicker plus vite que ton ombre
*/
class Clicker {

	private :

	bool Fin;
	unsigned int nbclique; // nombre d'appuie sur la barre espace
	float tps_actuel; //temps actuel pour le timer

	public :
	
	/**
	@brief constructeur met le nombre de clique et le temps à 0
	@param none
	*/
	Clicker();

	/**
	@brief permet la gestion du temps et la fin du mini jeu
	@param clock_t tempsD(temps de départ)
	*/
	void gestionTps(clock_t tempsD);

	/**
	@brief permet d'ajouter un clique au compteur
	@param none
	*/
	void ajoutClique();

	/**
	@brief retourne le booléen fin
	@param none
	*/
	bool getFin() const;

	/**
	@brief retourne le temps actuel pour le timer
	@param none
	*/
	float gettps_actuel();

	/**
	@brief retourne le nombre d'appuie 
	@param none
	*/
	unsigned int getnbclique();

	/**
	@brief permet de reset les données membres à la fin de l'évènement clicker
	@param none
	*/
	void resetClicker();



};

/**
@brief gère l'évènement "escape", c'est un Mini-Jeu où tu dois fuir la police pour ne pas te retrouver en prison
*/
class Escape {

	private :
	vec2D Joueur;
	vec2D Police;
	bool Fin;
	bool echec;
	bool P;
	vec2D PolicePasse;
	vec2D JoueurPasse;


	public :

	/**
	@brief constructeur du mini jeu
	@param none
	*/
	Escape();

	/**
	@brief permet de deplacer la police à intervalle régulier
	@param variable de temps du début
	*/
	void deplacePolice(clock_t tempsD);

	/**
	@brief permet de faire le déplacement du joueur
	@param touche pour le déplacement
	*/
	void avancerJoueur(string direction);

	/**
	@brief victoire ou defaite
	@param none
	*/
	void victoireDefaite();

	/**
	@brief retourne les coord du joueur
	@param none
	*/
	vec2D getJoueur();

	/**
	@brief retourne les coord de la police 
	@param none
	*/
	vec2D getPolice();

	/**
	@brief retourne la fin
	@param none
	*/
	bool getFin();

	/**
	@brief retourne la fin
	@param none
	*/
	bool getFin() const;


	/**
	@brief retourne l'echec
	@param none
	*/
	bool getEchec();

	/**
	@brief fait le reset
	@param none
	*/
	void resetEscape();

};


/**
@brief gère l'évènement lucky, tu pioches deux cartes chances et tu choisis laquelle tu veux.
*/
class Lucky {
	
	private : 
	Carte * carteUn; //Correspond à la première carte piochée
	Carte * carteDeux; //Correspond à la seconde carte piochée
	bool cartePiocher; //Booléen qui indique si les cartes ont déjà été piochées

	public :

	/**
	@brief Constructeur par défaut
	@param none
	*/
	Lucky(); 

	/**
	@brief Destructeur 
	*/
	~Lucky();

	/**
	@brief Permet de récupérer un pointeur sur la carteUn
	@param none
	@return Un pointeur sur la carteUn 
	*/
	Carte * getCarteUn();

	/**
	@brief Permet de récupérer un pointeur sur la carteDeux
	@param none
	@return Un pointeur sur la carteDeux 
	*/
	Carte * getCarteDeux();

	/**
	@brief Permet de connaître la valeur du booléen cartePiocher
	@param none
	@return Le booléen cartePiocher
	*/
	bool getCartePiocher();

	/**
	@brief Permet de piocher deux cartes 
	@param none
	@return none
	*/
	void pioche();


	/**
	@brief Reset Lucky
	@param none
	@return none
	*/
	void reset();

};




#endif