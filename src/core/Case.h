#ifndef OCTET_CASE_H
#define OCTET_CASE_H

#include <string>

class Case{
private:

	bool ad; //Indique si la case est en publicité
	std::string nom;
	unsigned int occupation;//Qui occupe la case
	char type; //Type une entreprise, une banque, un case chance,...
	int investissement; //Permet de savoir l'entreprise a investi dans le légal ou illégal

	unsigned int loyer; //Prix à donner au joueur à qui appartient l'entreprise
	unsigned int prix; //Prix d'achat
	unsigned int prixInitial;
	unsigned int prixM; //Prix pour un investissement illégale
	unsigned int prixB; //Prix pour un investissement légal
	unsigned int prixDeVente; //Prix de revente
	
public:
	//---------------------------------Constructeurs--------------------------------------
	/**
	@brief Crée une case (constructeur par défaut)
	@param none
	*/
	Case();

	/**
	@brief Destructeur de la classe
	@param none
	*/
	~Case();

	//----------------------------------Getters------------------------------------------
	/**
	@brief Indique à qui appartient l'entreprise ou la banque
	@param none
	@return occupation : unsigned int | 0 : Innocupé ; 1 : Joueur1 ; 2 : Joueur2 ; etc...
	*/ 
	unsigned int getOccupation() const;

	/**
	@brief
	@param
	*/
	unsigned int getPrixDeBase() const;

	/**
	@brief
	@param
	*/
	unsigned int getLoyer() const;

	/**
	@brief Indique le prix de l'entreprise ou de la banque
	@param none
	@return prix : unsigned int
	*/ 
	unsigned int getPrix() const;

	/**
	@brief Indique le prix d'un investissement illégal (mauvais)
	@param none
	@return prixM : unsigned int
	*/ 
	unsigned int getPrixM() const;

	/**
	@brief Indique le prix d'un investissement légal (bon)
	@param none
	@return prixB : unsigned int
	*/ 
	unsigned int getPrixB() const;

	/**
	@brief 
	@param
	*/
	unsigned int getLoyer() const;

	/**
	@brief Informe sur le prix initial de l'entreprise ou banque
	@param none
	@return prixInitial : unsigned int 
	*/
	unsigned int getPrixInitial() const;

	/**
	@brief Informe sur le prix de vente de l'entreprise ou de la banque
	@param none
	@return prixDeVente : unsigned int 
	*/
	unsigned int getPrixDeVente() const;

	/** 
	@brief Indique l'investissement de l'entreprise
	@param none
	@return investissement : int | <0 si investissement illégal,
	>0 si investissement dans le légal, =0 si aucun investissement
	*/ 
	int getInvestissement() const;

	/**
	@brief Récupére le type de la case
	@param none
	@return type : char | 'D' : Départ ; 'E' : Entreprise ; 'B' : Banque ; 'P' : Prison ;
	'C' : Chance ; 'I' : Impôt ; 'O' : Porte Ouverte ; 'A' : Publicité (Advertising)
	*/ 
	char getType() const;

	bool getAd() const;
	//----------------------------------Setters------------------------------------------
	//---------------------------------Methodes------------------------------------------
	/**
	@brief Permet l'initialisation d'une case au lancement d'une partie 
	(prix de base et type)
	@param categorie : char ; prix : unsigned int
	*/ 
	void initCase(char categorie,unsigned int p,string nom);

	/**
	@brief Initialise le prix de base d'une entreprise ou d'une banque
	@param none
	*/ 
	void initPrixInitial();

	/**
	@brief Change l'investissment, le prix,le prixB, le prixM
	@param i : int
	*/ 
	void investir(int i);

	/**
	@brief Affecte un propriètaire et change les prix
	@param i : unsigned int
	*/ 
	void estAcheter(unsigned int i);

	/**
	@brief Indique que l'entreprise fait de la pub (Change les prix)
	@param i : unsigned int
	*/ 
	void advertising(unsigned int i);


	/**
	@brief Indique que l'entreprise ne fait plus de pub (Change les prix)
	@param i : unsigned int
	*/ 
	void endAdvertising(unsigned int i);

	/**
	@brief Renitialisation de la carte
	@param none
	*/ 
	void reset();
};

#endif