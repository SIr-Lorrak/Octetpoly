#ifndef OCTET_CASE_H
#define OCTET_CASE_H

class Case{
private:

	unsigned int occupation;
	char type;
	int investissement;
	unsigned int prix;
	unsigned int prixDeBase;

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
	@brief Récupére le champs occupation
	@param none
	@return occupation : unsigned int
	*/ 
	unsigned int getOccupation();

	/**
	@brief Récupére le champs type
	@param none
	@return type : char
	*/ 
	char getType();

	/**
	@brief Récupére le champs type
	@param none
	@return investissement : int
	*/ 
	int getInvestissement();

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
	@brief Change l'investissment, le prixDeVente
	@param i : int
	*/ 
	void investir(int i);
};

#endif