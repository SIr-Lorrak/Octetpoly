#ifndef OCTET_EVENEMENT_H
#define OCTET_EVENEMENT_H

#include <iostream>
#include <string>
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
		int gain; //montant que vous aller gagner ou perdre

	public :

		/**
		@brief constructeur, permet d'initialiser n
		@param none
		*/
		Evenement();

		/**
		@brief permet de déclancher un événément lors d'un déplacement en fonction du karma renvoie true si une un mini jeu est lancé
		@param none
		*/
		bool Declenchement(int karma);

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

		void reset();


		/**
		@brief pemet de calculer le temps qu'a mit le joueur a faire l'évenement
		@param none
		*/
		void fini(int clique = 0);

		/**
		@brief retourne le gain à la fin de l'évenement
		@param none
		*/
		int getgain();

		/**
		@brief retourne le temps de départ
		@param none
		*/
		clock_t gettempsD();

		/**
		@brief retourne le temps de fin (0 si le jeu est encore en cour)
		@param none
		*/
		clock_t getTempsF() const;

			
};


/**
@brief classe qui gère l'évenement haching
*/
class Hacking{

	private :

		string mot; //mot à saisir
		unsigned int nbSaisie; //nombre de mot valider
		string motSaisie; //mot actuellement taper par le joueur
		bool fin;//dit si le jeu est fini 
		unsigned int nbMot; //nombre de mot a saisir pour finir
	
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
		@brief enlève le dernier caractère de motSaisie
		@param none
		*/
		void effacerLettre();

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

		unsigned int getnbMot();

		/**
		@brief retourne un entier qui permet de choisir le bon affichage
		@param none
		*/
		int getIntAff();

		/**
		@brief retourne le booléen qui dit si le hacking 
		@param none
		*/
		bool getFin() const;

		/**
		brief permet de reset les données membres à la fin de l'évenement hacking
		param none
		*/
		void resetHack();
		 	
};

/**
brief classe qui gère l'évenement clicker
*/
class Clicker {

	private :

	bool Fin;
	unsigned int nbclique; // nombre d'appue sur la barre espace
	float tps_actuel; //temps actuel pour le timer

	public :
	
	/**
	brief constructeur met le nombre de clique et le temps à 0
	param none
	*/
	Clicker();

	/**
	@brief permet le gestion du temps et la fin du mini jeu
	@param clock_t tempsD(temps de départ)
	*/
	void gestionTps(clock_t tempsD);

	/**
	brief permet d'ajouter un clique au compteur
	@param none
	*/
	void ajoutClique();

	/**
	@brief retourne le bool fin
	@param none
	*/
	bool getFin() const;

	/**
	brief retourne le temps actuel pour le timer
	param none
	*/
	float gettps_actuel();

	/**
	brief retourne le nombre d'appuie 
	param none
	*/
	unsigned int getnbclique();

	/**
	brief permet de reset les données membres à la fin de l'évenement clicker
	param none
	*/
	void resetClicker();



};


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
	Escape();
	void deplacePolice(clock_t tempsD);
	void avancerJoueur(string direction);
	void victoireDefaite();
	vec2D getJoueur();
	vec2D getPolice();
	bool getFin();
	bool getFin() const;
	bool getEchec();
	void resetEscape();

};


class Lucky {
	
	private : 


	public :
};




#endif