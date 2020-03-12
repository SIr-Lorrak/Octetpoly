#ifndef OCTET_CASE_H
#define OCTET_CASE_H

class Case{
private:

	unsigned int occupation;
	char type;
	int investissement;
	unsigned int prixAchat;
	unsigned int prixDeVente;

public:
	//---------------------------------Constructeurs--------------------------------------
	/**
	@brief Crée une case (constructeur par défaut)
	@param none
	**/
	Case();

	/**
	@brief Destructeur de la classe
	@param none
	**/
	~Case();


	//----------------------------------Getters------------------------------------------
	/**
	@brief Récupére le champs occupation
	@param none
	**/ 
	unsigned int getOccupation();
	/**
	@brief Récupére le champs type
	@param none
	**/ 
	char getType();
	/**
	@brief Récupére le champs investissement
	@param none
	**/ 
	int getInvestissement();

	//----------------------------------Setters------------------------------------------
	/**
	@brief affecte une valeur au champs occupation
	@param occupant : int
	**/ 
	void setOccupation(unsigned int occupant);
	/**
	@brief affecte une valeur au champs type
	@param categorie : char
	**/ 
	void setType(char categorie);
	
	void setPrixAchat(unsigned int pa);

	void setPrixDeVente(unsigned int pdv);

	//---------------------------------Methodes------------------------------------------
	/**
	@brief Permet l'initialisation d'une case au lancement d'une partie
	@param categorie : char, pa : unsigned : int, pdv : unsigned int
	**/ 
	void initCase(char categorie,unsigned int pa, unsigned int pdv);

	/**
	@brief Change l'investissment, le prixDeVente
	@param i : int
	**/ 
	void investir(int i);


};

#endif