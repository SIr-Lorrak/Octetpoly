#include "Case.h"
//---------------------------------Constructeurs------------------------------------------
Case::Case(){
	occupation = 0;
	type = '0';
	investissement = 0;
	prixAchat = 0;
	prixDeVente = 0;
}

Case::~Case(){
	//TODO
}

//-------------------------------------Getters-------------------------------------------
unsigned int Case::getOccupation(){
	return occupation;
}

char Case::getType(){
	return type;
}

int Case::getInvestissement(){
	return investissement;
}

//-------------------------------------Setters-------------------------------------------
void Case::setOccupation(unsigned int occupant){
	occupation = occupant;
}

void Case::setType(char categorie){
	type = categorie;
}

void Case::setInvestissement(int i){
	investissement = i;
}

void Case::setPrixAchat(unsigned int pa){
	prixAchat = pa;
}

void Case::setPrixDeVente(unsigned int pdv){
	prixDeVente = pdv;
}

//-------------------------------------Méthodes------------------------------------------

void Case::initCase(char categorie,unsigned int pa, unsigned int pdv){
	setType(categorie);
	setPrixAchat(pa);
	setPrixDeVente(pdv);
}


