#ifndef OCTET_CASE_H
#define OCTET_CASE_H

class Case{
private:

	unsigned int occupation;
	char type;
	int investissement;
	unsigned int prix;
	unsigned int prixDeBase;
	unsigned int prixM;
	unsigned int prixB;

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
	//----------------------------------Setters------------------------------------------
	/**
	@brief affecte une valeur au champs occupation
	@param occupant : int
	*/ 
	void setOccupation(unsigned int occupant);
	/**
	@brief affecte une valeur au champs type
	@param categorie : char
	*/ 
	void setType(char categorie);

	//---------------------------------Methodes------------------------------------------
	/**
	@brief Permet l'initialisation d'une case au lancement d'une partie 
	(prix de base et type)
	@param categorie : char, pa : unsigned : int, pdv : unsigned int
	*/ 
	void initCase(char categorie,unsigned int p);

	/**
	@brief Initialise le prix de base d'une entreprise ou d'une banque
	@param none
	*/ 
	void initPrixDeBase();

	/**
	@brief Change l'investissment, le prix,le prixB, le prixM
	@param i : int
	*/ 
	void investir(int i);

};

#endif