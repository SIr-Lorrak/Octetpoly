#ifndef OCTET_PION_H
#define OCTET_PION_H

#include <iostream>
#include <string>

#include "Case.h"
//#include "Carte.h"

using namespace std;

const int MAXCASEHT = 24; ///Max case achetée
const int MAXCASEP = 32;  ///Max case du plateau
const int INITCOIN = 150000; ///Argent initial
const int MAXCARTE = 20;  ///Max cartes du pion


const string noms[20] = {"Tom Pousse",//0
						 "Haaamid",
						 "Pedro",
						 "Sabrina",
						 "SaBine",
						 "Jessica",//5
						 "Nathan",
						 "Aspifion",
						 "MIEFLE",
						 "M. Pronost",
						 "Granolax",//10
						 "M. Pujo",
						 "Corrine",
						 "Alexandra",
						 "Jus d'huitre",
						 "GuyZeBoomer",//15
						 "M. Pélouze",
						 "BITENTRONC",
						 "Patoche",
						 "Nabil"};


/**
@brief les doubles dés lancé par les pions
**/
struct Des 								///Les 2 Des du pion
	{	
		unsigned int D1;
		unsigned int D2;
	};

/**
@brief représente les pions qui se déplacent sur le terrain
*/
class Pion{
	
	private :

		string nom;						///Nom du pion
		int karma;						///Karma du pion
		unsigned int rang;				///Rang du pion
		int bitcoin;					///Argent du pion
		unsigned int nbpropriete;		///Nombre de propriétés que possède le pion
		unsigned int pos;				///Position du pion
		char car;						///Caractère du pion
		Des d;							///Dés du pion
		bool prisonnier;				///Booléen qui indique si le pion est prisonnier ou non
		Case ** propriete;				///Tableau de pointeur vers case de propriétés du pion
		bool doubles[2];				///Tableau de trois booléens qui indique le nombre de double à la suite du pion
		//Carte ** deck;
		bool ticket;					//Ticket du joueur (utiliser pour les portes ouvertes)
		bool tourUn;

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
	int getCoin() const;

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

	/**
	@brief renvoie les Dés du Pion
	@param
	*/
	Des getDes() const;

	/**
	@brief Permet de savoir si le joueur a un ticket
	@param none
	@return True si le joueur a acheté un ticket sinon false
	**/
	bool getTicket() const;

	/**
	@brief renvoie si le Pion est déjà repassé par la Case départ (ce qui veut dire qu'il a effectué un tour et qu'il n'est plus limité)
	@param none
	*/
	bool getTourUn() const;

	/**
	@brief donne un ticket gratuitement au Pion (/!\ sers uniquement lors du chargement d'une partie)
	@param none
	*/
	void donTicket();


	/**
	@brief met le pion en prison si il est libre et inversement (utiliser a l'exterieur que au chargement d'un fichier de sauvegarde)
	@param none
	*/
	void setPrisonnier();

	/**
	@brief pour changer le karma (uniquement lors du chargement d'une nouvelle partie)
	@param un entier k, valeur du karma
	*/
	void setKarma(const unsigned int k);

	/**
	@brief Permet de récupérer une propriété du joueur
	@param indice : unsigned int, l'indice de la case qu'on veut récupérer
	@return L'adresse de la case
	**/
	Case * getPropriete(unsigned int indice)const;

	/**
	@brief Mutateur du caractère du pion
	@param c : charactere
	**/
	void setCar(const char c);

	/**
	@brief Mutateur de l'argent (bitcoin) du pion
	@param argent : float
	**/
	void setCoin(const int argent);

	/**
	@brief set le nom du Pion (uniquement lors du chargement)
	@param le nom n du Pion
	*/
	void setNom(const string & n);

	/**
	@brief set le rang du Pion
	@param le rang r
	*/
	void setRang(const unsigned int r);

	/**
	@brief set la position du Pion sur le Plateau
	@param la position p
	*/
	void setPos(const unsigned int p);

	/**
	@brief set le pion comme ayant déjà fait le premier tour (unsiquement lors du chargement)
	@param un entier non-signé tour
	*/
	void setTourUn(const unsigned int tour);

	/**
	@brief choisi un nom aleatoire pour le Pion (sers pour les Ordis seulement)
	@param none
	*/
	void nomAleatoire();

	/**
	@brief Permet de modifier la valeur du ticket 
	@param achat : bool, true si le joueur a acheter un ticket, false si il l'a consommé
	@return none
	**/
	void setTicket(bool achat);

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

	/**
	@brief renvoie la somme des prix de vente de toutes les propriété de Pion
	@param none
	*/
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
	void vend(string nom);

	/**
	@brief Le Pion est exproprié de l'entreprise/la banque nom
	@param le nom de la Case, nom
	*/
	void estRacheter(string nom);

	/**
	@brief Procédure qui permet au pion d'acheter l'entreprise ou la banque sur laquelle le pion est tombé
	@param c : Un pointeur vers la case entreprise ou banque où se trouve le pion 
	*/
	void achete(Case * c);

	/**
	@brief on donne une case au Pion (/!\ uniquement lors du chargement d'une sauvegarde)
	@param le pointeur vers la case donnée
	*/
	void don(Case *c);

	/**
	@brief Procédure qui permet au pion d'investir dans son entreprise s'il se trouve sur sa case
	@param i : l'entier qui nous dit si le joueur investit dans l'illégal ou non,	c : Un pointeur vers la case entreprise ou banque où se trouve le pion 
	*/
	void investit(int i,Case * c);

	/**
	@brief Procédure qui reset
	@param none
	*/
	void EstEnFaillite();


};

#endif