#ifndef OCTET_CASE_H
#define OCTET_CASE_H

class Case{
private:

	int occupation;
	char type;
	int investissement;

public:
	//---------------------------------Constructeur--------------------------------------
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
	int getoccupation();
	/**
	@brief Récupére le champs type
	@param none
	**/ 
	char gettype();
	/**
	@brief Récupére le champs investissement
	@param none
	**/ 
	int getinvestissement();

	//----------------------------------Setters------------------------------------------
	/**
	@brief affecte une valeur au champs occupation
	@param occupant : int
	**/ 
	void setoccupation(int occupant);
	/**
	@brief affecte une valeur au champs type
	@param categorie : char
	**/ 
	void settype(char categorie);
	/**
	@brief affecte une valeur au champs investissement
	@param i : int
	**/ 
	void setinvestissement(int i);

};

#endif